#include "include/Enemy.hpp"
#include "include/Direction.hpp"
#include "include/utilities.hpp"
#include "include/nlohmannJson.hpp"

Enemy::Enemy(int id, int py, int px, std::string& type) :
 GameObject{GOType::enemy, id, py, px}
{
    setEnemyType(type);    
}
void Enemy::activate(std::shared_ptr<Level> parent){
    this->parent = parent;
    if(enemyType != EnemyType::SpEye  || enemyType != EnemyType::Chuchu)
        this->normalPath = MoveGenerator::randomPathGenerator(5, getX(), getY(), parent->getSimpleMatrix());
}
void Enemy::setEnemyType(std::string& type)
{
    if (type == "SpGray")
        enemyType = EnemyType::SpGray;
    else if (type == "SpRed")
        enemyType = EnemyType::SpRed;
    else if (type == "SpBlue")
        enemyType = EnemyType::SpBlue;
    else if (type == "SpEye")
        enemyType = EnemyType::SpEye;
    else if (type == "Mouse")
        enemyType = EnemyType::Mouse;
    else if (type == "Chuchu")
        enemyType = EnemyType::Chuchu;
}
void Enemy::updateData(int py, int px, int damage, bool range)
{
    setY(py);
    setX(px);
    damageDone = damage;
    inRange = range;
}

void Enemy::setRouteVelocity(double routeVel)
{
    route_velocity = routeVel;
}

void Enemy::setChaseVelocity(double chaseVel)
{
    chase_velocity = chaseVel;
}

void Enemy::setVisibilityRadius(double radius)
{
    visibility_radius = radius;
}

void Enemy::setDamage(int damage)
{
    damageDone = damage;
}

void Enemy::setInRange(bool range)
{
    inRange = range;
}

void Enemy::setChasing(bool chase)
{
    isChasing = chase;
}

Pair Enemy::enemyPos() const
{
    return std::make_pair(getX(), getY());
}

double Enemy::getRouteVelocity() const
{
    return route_velocity;
}

double Enemy::getChaseVelocity() const
{
    return chase_velocity;
}

double Enemy::getVisibilityRadius() const
{
    return visibility_radius;
}

int Enemy::getDamage() const
{
    return damageDone;
}

bool Enemy::isInRange() const
{
    return inRange;
}

bool Enemy::playerIsSafe() const
{
    // Check if the player is inside the safe zone
    return true;
}

EnemyType Enemy::getEnemyType()
{
    return enemyType;
}

std::string Enemy::getTypeS()
{
    switch (enemyType)
    {
        case EnemyType::SpGray:
            return "SpGray";
        case EnemyType::SpRed:
            return "SpRed";
        case EnemyType::SpBlue:
            return "SpBlue";
        case EnemyType::SpEye:
            return "SpEye";
        case EnemyType::Mouse:
            return "Mouse";
        case EnemyType::Chuchu:
            return "Chuchu";
        default:
            return "";
    }
}

void Enemy::refreshState()
{
    Pathfinding pathfinding(parent->getSimpleMatrix());

    // Check vision range and player position...

    // Chuchu always chase the player even is inside the safe zone, this enemy is harmless
    if(enemyType == EnemyType::Chuchu){
        isChasing = true;
        chasePath = pathfinding.LineSight(enemyPos(), parent->playerPos());
    }

    // SpEye doesn't move but calls the other specters
    if(isInRange() && enemyType == EnemyType::SpEye){
        parent->triggerGroupCall(getID());
    }

    if(isInRange() && enemyType != EnemyType::SpEye && enemyType != EnemyType::Mouse && enemyType != EnemyType::Chuchu){
        isChasing = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
        parent->triggerGroupCall(getID());
    }

    if(playerIsSafe() && !breadcrumbs.empty()){
        isChasing = false;
        isBacktracking = true;
        chasePath.clear();
    }

    if(!isInRange() && !playerIsSafe() && breadcrumbs.empty()){
        isChasing = false;
        isBacktracking = false;
    }
}

void Enemy::groupCall(){
    Pathfinding pathfinding(parent->getSimpleMatrix());

    // Teleport SpBlue
    if(enemyType == EnemyType::SpBlue && !isTeleported){
        teleportation = pathfinding.teleportEnemy(enemyPos(), parent->playerPos());
        isTeleported = true;
    }

    // Replace chasePath
    if(enemyType == EnemyType::SpGray || enemyType == EnemyType::SpRed){
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }

    if(enemyType == EnemyType::SpBlue && isTeleported){
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }
}

std::string Enemy::update()
{
    if(isChasing){
        breadcrumbs.push_back(chasePath.front());
        return MoveGenerator::directionToString(chasePath.pop_front());
    }
    else if(isBacktracking){
        return MoveGenerator::inverseDirectionToString(breadcrumbs.pop_back());
    }
    else{
       if(isBackTrackDefault){

       }else{

       }
    }
}