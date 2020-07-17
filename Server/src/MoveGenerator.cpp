#include "include/MoveGenerator.hpp"

#include <utility>

Pair MoveGenerator::teleport(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos) {
    MoveGenerator::pathfinding = new Pathfinding(std::move(matrix));
    return pathfinding->teleportEnemy(enemyPos, playerPos);
}

listDirections MoveGenerator::getRoute(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos, RouteType type) {
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

listDirections MoveGenerator::randomPath(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos, int size) {
    MoveGenerator::pathfinding = new Pathfinding(std::move(matrix));
    return MoveGenerator::pathfinding->RandomPath(enemyPos, playerPos, size);
}

listDirections MoveGenerator::Astar(Pair enemyPos, Pair playerPos) {
    return MoveGenerator::pathfinding->AStarSearch(enemyPos, playerPos);
}

listDirections MoveGenerator::LineSight(Pair enemyPos, Pair playerPos) {
    return MoveGenerator::pathfinding->LineSight(enemyPos, playerPos);
}

listDirections MoveGenerator::BreadCrumbing(Pair enemyPos, Pair playerPos) {
    return listDirections();
}

listDirections MoveGenerator::Backtracking(Pair enemyPos, Pair playerPos) {
    return listDirections();
}

Pathfinding* MoveGenerator::pathfinding;


