#include "include/Enemy.hpp"
#include "include/Direction.hpp"
#include "include/utilities.hpp"
#include "include/nlohmannJson.hpp"

Enemy::Enemy(int id, int py, int px, std::string& type) :
 GameObject{GOType::enemy, id, py, px}
{
    setEnemyType(type);    
}
void Enemy::setParent(std::shared_ptr<Level> parent){
    this->parent = parent;
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

void Enemy::generateRandomPath(int size)
{
    Pathfinding pathfinding(parent->getSimpleMatrix());
    ce::debuglog("after matrix");
    if(enemyType != EnemyType::SpEye  || enemyType != EnemyType::Chuchu){
        normalPath = pathfinding.RandomPath(enemyPos(), parent->playerPos(), size);
    }
}

void Enemy::setRouteVelocity(float routeVel)
{
    route_velocity = routeVel;
}

void Enemy::setChaseVelocity(float chaseVel)
{
    chase_velocity = chaseVel;
}

void Enemy::setVisibilityRadius(float radius)
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

float Enemy::getRouteVelocity() const
{
    return route_velocity;
}

float Enemy::getChaseVelocity() const
{
    return chase_velocity;
}

float Enemy::getVisibilityRadius() const
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
        return getNextMovement(chasePath.pop_front());
    }
    else if(isBacktracking){
        return getPreviousMovement(breadcrumbs.pop_back());
    }
    else{
        if(n > normalPath.size()-1){
            n = 0;
        }
        return getNextMovement(normalPath[++n]);
    }
}

std::string Enemy::getNextMovement(Direction direction)
{
    switch (direction)
    {
        case Direction::NORTH:
            return "NORTH";
        case Direction::SOUTH:
            return "SOUTH";
        case Direction::EAST:
            return "EAST";
        case Direction::WEST:
            return "WEST";
        case Direction::NORTHEAST:
            return "NORTHEAST";
        case Direction::NORTHWEST:
            return "NORTHWEST";
        case Direction::SOUTHEAST:
            return "SOUTHEAST";
        case Direction::SOUTHWEST:
            return "SOUTHWEST";
        default:
            return "";
    }
}

std::string Enemy::getPreviousMovement(Direction direction)
{
    switch (direction)
    {
        case Direction::NORTH:
            return "SOUTH";
        case Direction::SOUTH:
            return "NORTH";
        case Direction::EAST:
            return "WEST";
        case Direction::WEST:
            return "EAST";
        case Direction::NORTHEAST:
            return "SOUTHWEST";
        case Direction::NORTHWEST:
            return "SOUTHEAST";
        case Direction::SOUTHEAST:
            return "NORTHWEST";
        case Direction::SOUTHWEST:
            return "NORTHEAST";
        default:
            return "";
    }
}


