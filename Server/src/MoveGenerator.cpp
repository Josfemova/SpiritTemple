#include "include/MoveGenerator.hpp"
#include "include/Game.hpp"
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
    auto randomDelta = []() { return Game::randomInt(-1, 1); };
    for (int i = 0; i < size; i++)
    {
        int deltaX;
        int deltaY;
        posCheck = false;
        while (!posCheck)
        {
            deltaX = randomDelta();
            deltaY = randomDelta();
            if (deltaX != 0 || deltaY != 0)
                posCheck = (level[y + deltaY][x + deltaX] == 0) ? false : true;
        }
        route.push_back(getDirectionValue(deltaX, deltaY));
        x += deltaX;
        y += deltaY;
    }
    return route;
}
Pair MoveGenerator::getDeltaValues(std::string direction)
{
    Direction dir = stringToDirection(direction);
    Pair result;
    switch (dir)
    {
    case Direction::NORTH:
        result = std::make_pair(1, 0);
        break;
    case Direction::SOUTH:
        result = std::make_pair(-1, 0);
        break;
    case Direction::EAST:
        result = std::make_pair(0, 1);
        break;
    case Direction::WEST:
        result = std::make_pair(0, -1);
        break;
    case Direction::NORTHEAST:
        result = std::make_pair(1, 1);
        break;
    case Direction::NORTHWEST:
        result = std::make_pair(1, -1);
        break;
    case Direction::SOUTHEAST:
        result = std::make_pair(-1, 1);
        break;
    case Direction::SOUTHWEST:
        result = std::make_pair(-1, -1);
        break;
    default:
        result = std::make_pair(0, 0);
        break;
    }
    return result;
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
        break;
    case Direction::SOUTH:
        return Direction::NORTH;
        break;
    case Direction::EAST:
        return Direction::WEST;
        break;
    case Direction::WEST:
        return Direction::EAST;
        break;
    case Direction::NORTHEAST:
        return Direction::SOUTHWEST;
        break;
    case Direction::NORTHWEST:
        return Direction::SOUTHEAST;
        break;
    case Direction::SOUTHEAST:
        return Direction::NORTHWEST;
        break;
    case Direction::SOUTHWEST:
        return Direction::NORTHEAST;
        break;
    default:
        return Direction::STALL;
        break;
    }
}
std::string MoveGenerator::directionToString(Direction direction)
{
    switch (direction)
    {
    case Direction::NORTH:
        return "NORTH";
        break;
    case Direction::SOUTH:
        return "SOUTH";
        break;
    case Direction::EAST:
        return "EAST";
        break;
    case Direction::WEST:
        return "WEST";
        break;
    case Direction::NORTHEAST:
        return "NORTHEAST";
        break;
    case Direction::NORTHWEST:
        return "NORTHWEST";
        break;
    case Direction::SOUTHEAST:
        return "SOUTHEAST";
        break;
    case Direction::SOUTHWEST:
        return "SOUTHWEST";
        break;
    default:
        return "";
    }
}
Direction MoveGenerator::stringToDirection(std::string direction)
{
    Direction dir = Direction::STALL;
    if (direction == "NORTH")
        dir = Direction::NORTH;
    else if (direction == "SOUTH")
        dir = Direction::SOUTH;
    else if (direction == "EAST")
        dir = Direction::EAST;
    else if (direction == "WEST")
        dir = Direction::WEST;
    else if (direction == "NORTHEAST")
        dir = Direction::NORTHEAST;
    else if (direction == "NORTHWEST")
        dir = Direction::NORTHWEST;
    else if (direction == "SOUTHEAST")
        dir = Direction::SOUTHEAST;
    else if (direction == "SOUTHWEST")
        dir = Direction::SOUTHWEST;
    return dir;
}
std::string MoveGenerator::inverseDirectionToString(Direction direction)
{
    switch (direction)
    {
    case Direction::NORTH:
        return "SOUTH";
        break;
    case Direction::SOUTH:
        return "NORTH";
        break;
    case Direction::EAST:
        return "WEST";
        break;
    case Direction::WEST:
        return "EAST";
        break;
    case Direction::NORTHEAST:
        return "SOUTHWEST";
        break;
    case Direction::NORTHWEST:
        return "SOUTHEAST";
        break;
    case Direction::SOUTHEAST:
        return "NORTHWEST";
        break;
    case Direction::SOUTHWEST:
        return "NORTHEAST";
        break;
    default:
        return "";
        break;
    }
}
