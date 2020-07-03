#include "include/MoveGenerator.hpp"

MoveGenerator::MoveGenerator(int (*newMatrix)[10]) {
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            matrix[i][j] = newMatrix[i][j];
        }
    }
    pathfinding = new Pathfinding(matrix);
}

ce::list<Direction> MoveGenerator::getRoute(Pair enemyPos, Pair playerPos, RouteType type) {
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

ce::list<Direction> MoveGenerator::Astar(Pair enemyPos, Pair playerPos) {
    return pathfinding->AstarSearch(enemyPos, playerPos);
}

ce::list<Direction> MoveGenerator::BreadCrumbing(Pair enemyPos, Pair playerPos) {
    ce::list<Direction> a;
    return a;
    //Do something
}

ce::list<Direction> MoveGenerator::Backtracking(Pair enemyPos, Pair playerPos) {
    ce::list<Direction> a;
    return a;
    //Do something
}

ce::list<Direction> MoveGenerator::LineSight(Pair enemyPos, Pair playerPos) {
    ce::list<Direction> a;
    return a;
    //Do something
}
