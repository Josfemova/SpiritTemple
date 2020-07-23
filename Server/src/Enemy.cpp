#include "include/Enemy.hpp"
#include "include/Direction.hpp"
#include "include/utilities.hpp"
#include "include/nlohmannJson.hpp"
#include <cstdlib>
Enemy::Enemy(int id, int py, int px, std::string &type) : GameObject{GOType::enemy, id, py, px}, frameCount{1}
{
    setEnemyType(type);
}
void Enemy::activate(std::shared_ptr<Level> parent)
{
    this->parent = parent;
    if (enemyType != EnemyType::SpEye || enemyType != EnemyType::Chuchu)
        this->normalPath = MoveGenerator::randomPathGenerator(5, getX(), getY(), parent->getSimpleMatrix());
}
void Enemy::setEnemyType(std::string &type)
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

void Enemy::setDamage(int damage)
{
    damageDone = damage;
}

void Enemy::setChasing(bool chase)
{
    isChasing = chase;
}

Pair Enemy::enemyPos() const
{
    return std::make_pair(getX(), getY());
}

int Enemy::getDamage() const
{
    return damageDone;
}

bool Enemy::playerIsSafe() const
{
    gmatrix state = parent->getSimpleMatrix();
    Pair pos = parent->playerPos();
    if(state[pos.second][pos.first]==0){
        return true;
    }else{
        return false;
    }

}
bool Enemy::playerInRange() const{
    Pair player = parent->playerPos();
    int deltay = abs(player.first - getY());
    int deltax = abs(player.second - getX());
    if(deltax<visibility_radius && deltay < visibility_radius){
        return true;
    }else{
        return false;
    }

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
    if (enemyType == EnemyType::Chuchu)
    {
        isChasing = true;
        chasePath = pathfinding.LineSight(enemyPos(), parent->playerPos());
    }

    // SpEye doesn't move but calls the other specters
    if (playerInRange() && enemyType == EnemyType::SpEye)
    {
        parent->triggerGroupCall(getID());
    }

    if (playerInRange() && enemyType != EnemyType::SpEye && enemyType != EnemyType::Mouse && enemyType != EnemyType::Chuchu)
    {
        isChasing = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
        parent->triggerGroupCall(getID());
    }

    if (playerIsSafe() && !breadcrumbs.empty())
    {
        isChasing = false;
        isBacktracking = true;
        chasePath.clear();
    }

    if (!playerInRange() && !playerIsSafe() && breadcrumbs.empty())
    {
        isChasing = false;
        isBacktracking = false;
    }
}

void Enemy::groupCall()
{
    Pathfinding pathfinding(parent->getSimpleMatrix());

    // Teleport SpBlue
    if (enemyType == EnemyType::SpBlue && !isTeleported)
    {
        teleportation = pathfinding.teleportEnemy(enemyPos(), parent->playerPos());
        isTeleported = true;
    }

    // Replace chasePath
    if (enemyType == EnemyType::SpGray || enemyType == EnemyType::SpRed)
    {
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }

    if (enemyType == EnemyType::SpBlue && isTeleported)
    {
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }
}

void Enemy::update()
{
    frameCount = frameCount+1;
    std::string dir;
    bool canChase = (frameCount % chase_velocity == 0);
    bool canMove  = (frameCount % route_velocity == 0);
    if (enemyType == EnemyType::SpEye || enemyType == EnemyType::Chuchu
    || (!canChase && !canMove))
    {
        return;
    }
    else if (isChasing && canChase)
    {
        //chasing player
        frameCount = 1;
        breadcrumbs.push_back(chasePath.front());
        dir = MoveGenerator::directionToString(chasePath.pop_front());
    }
    else if (isBacktracking && canMove)
    {
        //backtracking
        frameCount = 1;
        dir = MoveGenerator::inverseDirectionToString(breadcrumbs.pop_back());
    }
    else if (canMove)
    {
        //normal path
        frameCount = 1;

        if (isBackTrackDefault)
        {
            if (lastDefaultPos == -1)
            {
                isBackTrackDefault = false;
                dir = MoveGenerator::directionToString(normalPath[++lastDefaultPos]);
            }
            else
            {
                dir = MoveGenerator::inverseDirectionToString(normalPath[lastDefaultPos]);
                --lastDefaultPos;
            }
        }
        else
        {
            if (lastDefaultPos == (normalPath.size() - 1))
            {
                isBackTrackDefault = true;
                dir = MoveGenerator::inverseDirectionToString(normalPath[lastDefaultPos]);
                --lastDefaultPos;
            }
            else
            {
                dir = MoveGenerator::directionToString(normalPath[++lastDefaultPos]);
            }
        }
    }
    Pair delta = MoveGenerator::getDeltaValues(dir);
    setX(getX() + delta.second);
    setY(getY() + delta.first);
    ce::debuglog(delta.first, delta.second);
    json instruction = {
        {"cmd", "move-enemy"},
        {"target", getID()},
        {"args", dir},
        {"valx",delta.second},
        {"valy",delta.first}};
    parent->addInstruction(instruction);
}