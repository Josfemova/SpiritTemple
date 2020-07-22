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
        route.push_back(getDirectionValue(deltaX, deltaY));
        x += deltaX;
        y += deltaY;
    }
    return route;
}



Direction MoveGenerator::getDirectionValue(int deltaX, int deltaY)
{
    if (deltaX == 0)
        return (deltaY == 1) ? Direction::NORTH : Direction::SOUTH;
    else if (deltaY == 0)
        return (deltaX == 1) ? Direction::EAST : Direction::WEST;
    else if (deltaX == 1)
        return (deltaY == 1) ? Direction::NORTHEAST : Direction::SOUTHEAST;
    else // deltax == -1
        return (deltaY == 1) ? Direction::NORTHWEST : Direction::SOUTHWEST;
}
Direction MoveGenerator::getInverseDirection(Direction direction)
{
    switch (direction)
    {
    case Direction::NORTH:
        return Direction::SOUTH;
    case Direction::SOUTH:
        return Direction::NORTH;
    case Direction::EAST:
        return Direction::WEST;
    case Direction::WEST:
        return Direction::EAST;
    case Direction::NORTHEAST:
        return Direction::SOUTHWEST;
    case Direction::NORTHWEST:
        return Direction::SOUTHEAST;
    case Direction::SOUTHEAST:
        return Direction::NORTHWEST;
    case Direction::SOUTHWEST:
        return Direction::NORTHEAST;
    default:
        return Direction::STALL;
    }
}
std::string MoveGenerator::directionToString(Direction direction)
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
std::string MoveGenerator::inverseDirectionToString(Direction direction)
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