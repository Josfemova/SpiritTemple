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
    return std::make_pair(getY(), getX());
}

int Enemy::getDamage() const
{
    return damageDone;
}

bool Enemy::playerIsSafe() const
{
    gmatrix state = parent->getSimpleMatrix();
    Pair pos = parent->playerPos();
    if (state[pos.first][pos.second] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Enemy::playerInRange() const
{
    Pair player = parent->playerPos();
    int deltay = abs(player.first - getY());
    int deltax = abs(player.second - getX());
    if (deltax < visibility_radius && deltay < visibility_radius)
    {
        ce::debuglog("Player in range");
        return true;
    }
    else
    {
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

    if (enemyType == EnemyType::Chuchu)
    {
        isChasing = true;
        gmatrix &test = parent->getSimpleMatrix();
        chasePath = MoveGenerator::getRoute(test, getY(), getX(), parent->playerPos(), RouteType::LineSight);
    }

    // SpEye doesn't move but calls the other specters
    if (playerInRange() && !playerIsSafe() && enemyType == EnemyType::SpEye)
    {
        ce::debuglog("SpEye");
        //ce::debuglog("Haré un triggerGroupCall");
        parent->triggerGroupCall(getID());
    }
    
    if (playerInRange() && !playerIsSafe() && enemyType != EnemyType::SpEye && enemyType != EnemyType::Mouse && enemyType != EnemyType::Chuchu)
    {
        ce::debuglog("Astar");
        isChasing = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
        //parent->triggerGroupCall(getID());
    }

    if (playerIsSafe())
    {
        if (isTeleported)
        {
            setX(teleportSrc.second);
            setY(teleportSrc.first);
            json instruction = {
                {"cmd", "teleport-enemy"},
                {"target", getID()},
                {"valx", teleportSrc.second},
                {"valy", teleportSrc.first}};
            parent->addInstruction(instruction);
            isTeleported = false;
            breadcrumbs.clear();
            isChasing = false;
            isBacktracking = false;
            lastDefaultPos = -1;
            normalPath = MoveGenerator::randomPathGenerator(5, getX(), getY(), parent->getSimpleMatrix());
        }
        else if (!breadcrumbs.empty() && enemyType != EnemyType::Chuchu)
        {
            ce::debuglog("breadcrumbs for ", getTypeS());
            isChasing = false;
            isBacktracking = true;
            chasePath.clear();
        }
    }
    
    if (breadcrumbs.empty() && enemyType != EnemyType::Chuchu)
    {
        isBacktracking = false;
    }
}

void Enemy::groupCall()
{
    Pathfinding pathfinding(parent->getSimpleMatrix());

    // Teleport SpBlue
    if (enemyType == EnemyType::SpBlue && !isTeleported)
    {
        isChasing = true;
        teleportSrc = std::make_pair(getY(), getX());
        teleportDest = pathfinding.teleportEnemy(enemyPos(), parent->playerPos());
        //setX(teleportDest.second);
        //setY(teleportDest.first);
        json instruction = {
            {"cmd", "teleport-enemy"},
            {"target", getID()},
            {"valx", teleportDest.second},
            {"valy", teleportDest.first}};
        parent->addInstruction(instruction);
        isTeleported = true;
    }

    // Replace chasePath
    if (enemyType == EnemyType::SpGray || enemyType == EnemyType::SpRed)
    {
        isChasing = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }

    if (enemyType == EnemyType::SpBlue && isTeleported)
    {
        isChasing = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }
}

void Enemy::update()
{
    refreshState();
    ce::debuglog(isChasing);
    
    frameCount = frameCount + 1;
    std::string dir;
    bool canChase = (frameCount % chase_velocity == 0);
    bool canMove = (frameCount % route_velocity == 0);
    if (enemyType == EnemyType::SpEye || (!canChase && !canMove))
    {
        return;
    }
    else if (isChasing && canChase)
    {
        ce::debuglog("Si entró", chasePath.empty());
        //chasing player
        frameCount = 1;
        if (!chasePath.empty())
        {
            breadcrumbs.push_back(chasePath.front());
            dir = MoveGenerator::directionToString(chasePath.pop_front());
        }
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
    json instruction = {
        {"cmd", "move-enemy"},
        {"target", getID()},
        {"valx", delta.second},
        {"valy", delta.first}};
    parent->addInstruction(instruction);
}