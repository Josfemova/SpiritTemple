#include "include/Enemy.hpp"
#include "include/Direction.hpp"
#include "include/utilities.hpp"
#include "include/nlohmannJson.hpp"
#include <cstdlib>

int Enemy::lastDeathOrder = 0;
Enemy::Enemy(int id, int py, int px, std::string &type) : GameObject{GOType::enemy, id, py, px}, frameCount{1}
{
    setEnemyType(type);
}
void Enemy::activate(std::shared_ptr<Level> parent)
{
    this->parent = parent;
    if (enemyType != EnemyType::SpEye || enemyType != EnemyType::Chuchu)
        if (enemyType == EnemyType::Mouse)
            this->normalPath = MoveGenerator::randomPathGenerator(22, getX(), getY(), parent->getSimpleMatrix());
        else
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
    bool isSpBlue = (enemyType == EnemyType::SpBlue);
    bool isChuchu = (enemyType == EnemyType::Chuchu);
    bool isSpEye = (enemyType == EnemyType::SpEye);
    bool isMouse = (enemyType == EnemyType::Mouse);
    bool isSpectre = (!isChuchu && !isMouse && !isSpEye);
    Pathfinding pathfinding(parent->getSimpleMatrix());
    if (isChuchu)
    {
        isChasing = true;
        gmatrix &test = parent->getSimpleMatrix();
        chasePath = MoveGenerator::getRoute(test, getY(), getX(), parent->playerPos(), RouteType::LineSight);
    }
    if(isChasing && chasePath.empty()){
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }

    if (playerInRange() && !playerIsSafe())
    {
        if (isSpEye)
        {
            parent->triggerGroupCall(getID());
            return;
        }
        else if (isSpectre)
        {
            parent->triggerGroupCall(getID());
            //ce::debuglog("Astar");
            isChasing = true;
            chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
            chase_count += 1;
        }
        
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
            //breadcrumbs.clear();
            isChasing = false;
            isBacktracking = false;
            lastDefaultPos = -1;
            normalPath = MoveGenerator::randomPathGenerator(5, getX(), getY(), parent->getSimpleMatrix());
        }
        else if (!breadcrumbs.empty() && !isChuchu)
        {
            //ce::debuglog("breadcrumbs for ", getTypeS());
            isChasing = false;
            isBacktracking = true;
            chasePath.clear();
        }
    }

    if (breadcrumbs.empty() && isSpectre)
    {
        isBacktracking = false;
    }
}

void Enemy::groupCall()
{
    if (isDead)
    {
        return;
    }
    Pathfinding pathfinding(parent->getSimpleMatrix());

    // Teleport SpBlue
    if (enemyType == EnemyType::SpBlue && !isTeleported)
    {
        isChasing = true;
        teleportSrc = std::make_pair(getY(), getX());
        teleportDest = pathfinding.teleportEnemy(enemyPos(), parent->playerPos());
        setX(teleportDest.second);
        setY(teleportDest.first);
        json instruction = {
            {"cmd", "teleport-enemy"},
            {"target", getID()},
            {"valx", teleportDest.second},
            {"valy", teleportDest.first}};
        parent->addInstruction(instruction);
        isTeleported = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }
    // Replace chasePath
    if (enemyType == EnemyType::SpGray || enemyType == EnemyType::SpRed)
    {
        isChasing = true;
        chasePath = pathfinding.AStarSearch(enemyPos(), parent->playerPos());
    }
}

void Enemy::update()
{
    Pathfinding pathfinding(parent->getSimpleMatrix());
    bool isSpBlue = (enemyType == EnemyType::SpBlue);
    bool isChuchu = (enemyType == EnemyType::Chuchu);
    bool isSpEye = (enemyType == EnemyType::SpEye);
    bool isMouse = (enemyType == EnemyType::Mouse);
    bool isSpectre = (!isChuchu && !isMouse && !isSpEye);

    if (isDead)
    {
        return;
    }
    if (!isMouse && mouseInRange())
    {
        return;
    }
    refreshState();
    frameCount = frameCount + 1;
    std::string dir = "";
    bool canChase = (frameCount % chase_velocity == 0);
    bool canMove = (frameCount % route_velocity == 0);
    if (isSpEye || (!canChase && !canMove))
    {
        return;
    }
    if (playerIsInAttackRange())
    {
        ce::log("oh no!!! the player got to close to the enemy!!!");
        parent->resolveEnemyAttack();
        return;
    }
    else if (isChasing && canChase)
    {
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
    if (dir == "" && canMove)
    {
        if (isSpBlue)
        {
            ce::debuglog("//////////////////////");
            ce::debuglog(chasePath.empty(), breadcrumbs.empty(), isTeleported);
            ce::debuglog(isChasing, normalPath.empty());
            ce::debuglog("//////////////////////");
        }
        return;
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

std::string Enemy::toString()
{
    auto str = [](int x) { return std::to_string(x); };
    return ("(" + str(route_velocity) + "," + str(chase_velocity) + "," + str(visibility_radius) + ")");
}

void Enemy::die()
{
    deathOrder = ++lastDeathOrder;
    isDead = true;
    json instruction = {
        {"cmd", "kill-enemy"},
        {"target", getID()}};
    parent->addInstruction(instruction);
}

bool Enemy::mouseInRange()
{
    ce::list<Enemy> &enemies = parent->getEnemies();
    bool result = false;
    if (enemies.empty())
        return result;
    for (auto enemy : enemies)
    {
        if (enemy.enemyType == EnemyType::Mouse)
        {
            int deltay = abs(enemy.getY() - getY());
            int deltax = abs(enemy.getX() - getX());
            result = (deltax < visibility_radius && deltay < visibility_radius) ? true : false;
        }
    }
    return result;
}
bool Enemy::playerIsInAttackRange()
{
    Pair player = parent->playerPos();
    if (abs(getX() - player.second) == 1 && abs(getY() - player.first) == 1)
        return true;
    else
        return false;
}