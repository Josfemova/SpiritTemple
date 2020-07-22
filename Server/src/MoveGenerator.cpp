#include "include/MoveGenerator.hpp"

#include <utility>

Pair MoveGenerator::teleport(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos)
{
    MoveGenerator::pathfinding = new Pathfinding(std::move(matrix));
    return pathfinding->teleportEnemy(enemyPos, playerPos);
}

listDirections MoveGenerator::getRoute(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos, RouteType type)
{
    MoveGenerator::pathfinding = new Pathfinding(std::move(matrix));
    switch (type)
    {
    case RouteType::Astar:
        return MoveGenerator::Astar(enemyPos, playerPos);
    case RouteType::BreadCrumbing:
        return MoveGenerator::BreadCrumbing(enemyPos, playerPos);
    case RouteType::Backtracking:
        return MoveGenerator::Backtracking(enemyPos, playerPos);
    case RouteType::LineSight:
        return MoveGenerator::LineSight(enemyPos, playerPos);
    default:
        return listDirections();
    }
}

listDirections MoveGenerator::randomPath(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos, int size)
{
    MoveGenerator::pathfinding = new Pathfinding(std::move(matrix));
    return MoveGenerator::pathfinding->RandomPath(enemyPos, playerPos, size);
}

listDirections MoveGenerator::Astar(Pair enemyPos, Pair playerPos)
{
    return MoveGenerator::pathfinding->AStarSearch(enemyPos, playerPos);
}

listDirections MoveGenerator::LineSight(Pair enemyPos, Pair playerPos)
{
    return MoveGenerator::pathfinding->LineSight(enemyPos, playerPos);
}

listDirections MoveGenerator::BreadCrumbing(Pair enemyPos, Pair playerPos)
{
    return listDirections();
}

listDirections MoveGenerator::Backtracking(Pair enemyPos, Pair playerPos)
{
    return listDirections();
}
Pathfinding *MoveGenerator::pathfinding;

listDirections MoveGenerator::randomPathGenerator(int size, int x, int y, gmatrix level)
{
    listDirections route;
    bool posCheck;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> randomDelta(-1, 1);
    for (int i = 0; i < size; i++)
    {
        int deltaX;
        int deltaY;
        posCheck = false;
        while (!posCheck)
        {
            deltaX = randomDelta(rng);
            deltaY = randomDelta(rng);
            if (deltaX != 0 || deltaY != 0)
                posCheck = (level[y + deltaY][x + deltaX] == 0) ? false : true;
        }
        Direction step = getDirectionValue(deltaX, deltaY);
        route.push_back(step);
        x += deltaX;
        y += deltaY;
    }
    return route;
}
Direction MoveGenerator::getDirectionValue(int deltaX, int deltaY)
{
    if (deltaX == 0)
    {
        return (deltaY == 1) ? Direction::NORTH : Direction::SOUTH;
    }
    else if (deltaY == 0)
    {
        return (deltaX == 1) ? Direction::EAST : Direction::WEST;
    }
    else if (deltaX == 1)
    {
        return (deltaY == 1) ? Direction::NORTHEAST : Direction::SOUTHEAST;
    }
    else
    { // deltax == -1
        return (deltaY == 1) ? Direction::NORTHWEST : Direction::SOUTHWEST;
    }
}
