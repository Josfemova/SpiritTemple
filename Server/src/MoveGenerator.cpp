#include "include/MoveGenerator.hpp"

listDirections MoveGenerator::getRoute(int (*newMatrix)[10], Pair enemyPos, Pair playerPos, RouteType type) {
    MoveGenerator::pathfinding = new Pathfinding(newMatrix);
    switch (type) {
        case RouteType::Astar:
            return MoveGenerator::Astar(enemyPos, playerPos);
        case RouteType::BreadCrumbing:
            return MoveGenerator::BreadCrumbing(enemyPos, playerPos);
        case RouteType::Backtracking:
            return MoveGenerator::Backtracking(enemyPos, playerPos);
        case RouteType::LineSight:
            return MoveGenerator::LineSight(enemyPos, playerPos);
        default:
            ce::list<Direction> dir;
            return dir;
    }
}

listDirections MoveGenerator::Astar(Pair enemyPos, Pair playerPos) {
    return MoveGenerator::pathfinding->AstarSearch(enemyPos, playerPos);
}

listDirections MoveGenerator::BreadCrumbing(Pair enemyPos, Pair playerPos) {
    ce::list<Direction> a;
    return a;
    //Do something
}

listDirections MoveGenerator::Backtracking(Pair enemyPos, Pair playerPos) {
    ce::list<Direction> a;
    return a;
    //Do something
}

listDirections MoveGenerator::LineSight(Pair enemyPos, Pair playerPos) {
    ce::list<Direction> a;
    return a;
    //Do something
}

Pathfinding* MoveGenerator::pathfinding;
