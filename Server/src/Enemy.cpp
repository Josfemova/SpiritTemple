#include "include/Enemy.hpp"
#include "include/Direction.hpp"
#include "include/utilities.hpp"
#include "include/nlohmannJson.hpp"

Enemy::Enemy(int id, int px, int py, std::string type) : GameObject{GOType::enemy}
{
    enemyID = id;
    setX(px);
    setY(py);
    setEnemyType(type);
}

void Enemy::setEnemyType(std::string type)
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

void Enemy::updateData(int px, int py, int damage, bool range)
{
    setX(px);
    setY(py);
    damageDone = damage;
    inRange = range;
}

void Enemy::setEnemy(int px, int py)
{
    setX(px);
    setY(py);
}

void Enemy::setEnemyX(int px)
{
    setX(px);
}

void Enemy::setEnemyY(int py)
{
    setY(py);
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

std::string Enemy::toString()
{
    return "";
}

int Enemy::getEnemyX() const
{
    return getX();
}

int Enemy::getEnemyY() const
{
    return getY();
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
void Enemy::refreshState(){
    bool playerIsSafe = false;
    //check rango vision
    bool inRange = false;

    if(playerIsSafe){
        chasePath.clear();

    }
    else if(inRange){
        parent->triggerGroupCall(enemyID);
        //consigue su lista de migas
    }
    //movedSafeSpace


    //calcula los nuevos paths
}
void Enemy::groupCall(){
    //reemplaza lista actual por lista de Astar
}
std::string Enemy::update()
{
    if(isChasing){
        return getNextMovement(chasePath.pop_front());
    }else if(isBacktracking){
        return getNextMovement(breadcrumbs.pop_back());
    }else{
        //OBVIAMENTE SE CAMBIA
        //movimiento normal 
        return getNextMovement(normalPath[0]);
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