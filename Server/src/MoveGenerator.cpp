#include "include/MoveGenerator.hpp"
#include "include/Game.hpp"
#include <utility>

Pair MoveGenerator::teleport(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos)
{
    MoveGenerator::pathfinding = new Pathfinding(std::move(matrix));
    return pathfinding->teleportEnemy(enemyPos, playerPos);
}

listDirections MoveGenerator::getRoute(gmatrix &matrix, int enemyY, int enemyX, Pair playerPos, RouteType type)
{

    std::make_pair(enemyY, enemyX);
    switch (type)
    {
    case RouteType::Astar:
        return MoveGenerator::Astar(std::make_pair(enemyY, enemyX), playerPos);
    case RouteType::BreadCrumbing:
        return MoveGenerator::BreadCrumbing(std::make_pair(enemyY, enemyX), playerPos);
    case RouteType::Backtracking:
        return MoveGenerator::Backtracking(std::make_pair(enemyY, enemyX), playerPos);
    case RouteType::LineSight:
        return MoveGenerator::LineSight(enemyY, enemyX, playerPos.first, playerPos.second, matrix);
    default:
        return listDirections();
    }
}
listDirections MoveGenerator::Astar(Pair enemyPos, Pair playerPos)
{
    return MoveGenerator::pathfinding->AStarSearch(enemyPos, playerPos);
}

listDirections MoveGenerator::LineSight(int enemyY, int enemyX, int playerY, int playerX, gmatrix &state)
{

    ce::debuglog("calc bresenham");
    ce::list<Pair> toValidate = bresenhamLine(enemyY, enemyX, playerY, playerX);

    int size = toValidate.size();
    int validSize = 0;
    bool valid = true;

    //cleaning invalid nodes
    while (valid && validSize != (size))
    {
        Pair p = toValidate[validSize];
        if (state[p.first][p.second] == 0)
        {
            valid = false;
        }else{
            validSize += 1;
            ce::debuglog("valid size is =", validSize);
        }
    }

    ce::debuglog("post validation");
    listDirections result;

    if (toValidate.empty() || validSize == 0)
        return listDirections{Direction::STALL};
    //return listDirections{Direction::STALL};
    while (toValidate.size() != validSize)
    {
        toValidate.pop_back();
    }
    //cleaning finished

    ce::debuglog("before the pushback");
    int currentPosY = enemyY;
    int currentPosX = enemyX;

    for (auto &coord : toValidate)
    {
        result.push_back(getDirectionValue(coord.second - currentPosX, coord.first - currentPosY));
        currentPosX = coord.second;
        currentPosY = coord.first;
    }
    return result;
    //return MoveGenerator::pathfinding->LineSight(enemyPos, playerPos);
}
ce::list<Pair> MoveGenerator::bresenhamLine(int originY, int originX, int destY, int destX)
{
    ce::list<std::pair<int, int>> coords;
    bool inverted = false;
    int dx = destX - originX; //delta X
    int dy = destY - originY; //delta Y

    if (dx == 0 && dy == 0)
    {
        ce::debuglog("calc bresenham: pair 0,0");
        coords.push_back(std::make_pair(0, 0));
    }

    else if (dx == 0)
    {
        ce::debuglog("calc bresenham: inc dec");
        //simple lambda to reduce amount of if statements
        auto inc_dec = (dy < 0) ? [](int y) { return y - 1; } : [](int y) { return y + 1; };
        while (originY != destY)
        {
            coords.push_back(std::make_pair(originY, originX));
            originY = inc_dec(originY);
        }
    }
    else if (dy == 0)
    {
        //simple lambda to reduce amount of if statements
        auto inc_dec = (dx < 0) ? [](int x) { return x - 1; } : [](int x) { return x + 1; };
        while (originX != destX)
        {
            coords.push_back(std::make_pair(originY, originX));
            originX = inc_dec(originX);
        }
    }
    else
    {
        double m = ((double)dy / dx);

        int adjust = (m >= 0) ? 1 : -1;
        int offset = 0;
        int delta;
        //case dx>dy
        if (m <= 1 && m >= -1)
        {
            delta = abs(dy) * 2;
            int threshold = abs(dx);
            int thresholdInc = abs(dx) * 2;
            int y = originY;
            if (destX < originX)
            {
                std::swap(originX, destX);
                y = destY;
                inverted = true;
            }
            for (int x = originX; x < destX; x++)
            {
                coords.push_back(std::make_pair(y, x));
                offset += delta;
                if (offset >= threshold)
                {
                    y += adjust;
                    threshold += thresholdInc;
                }
            }
        }
        //dx>dy
        else
        {
            delta = abs(dx) * 2;
            int threshold = abs(dy);
            int thresholdInc = abs(dy) * 2;
            int x = originX;
            if (destY < originY)
            {
                std::swap(originY, destY);
                x = destX;
                inverted = true;
            }
            for (int y = originY; y < destY; y++)
            {
                coords.push_back(std::make_pair(y, x));
                offset += delta;
                if (offset >= threshold)
                {
                    x += adjust;
                    threshold += thresholdInc;
                }
            }
        }
    }
    ce::debuglog("calc bresenham: empty check");
    if (coords.size() <= 1)
    {
        return ce::list<Pair>{std::make_pair(0, 0)};
    }
    if (inverted)
    {
        coords.pop_front();
        ce::debuglog("coords getting inverted");
        coords = ce::list<Pair>::getInverse(coords);
    }
    else
    {
        coords.pop_front();
    }
    ce::debuglog(coords[0].first);
    return coords;
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
//delta values are XY Pairs
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
        return (deltaY > 0) ? Direction::NORTH : Direction::SOUTH;
    else if (deltaY == 0)
        return (deltaX > 0) ? Direction::EAST : Direction::WEST;
    else if (deltaX == 1)
        return (deltaY > 0) ? Direction::NORTHEAST : Direction::SOUTHEAST;
    else // deltax == -1
        return (deltaY > 0) ? Direction::NORTHWEST : Direction::SOUTHWEST;
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
