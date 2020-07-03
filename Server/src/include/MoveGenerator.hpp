#ifndef GAMESERVER_MOVEGENERATOR_HPP
#define GAMESERVER_MOVEGENERATOR_HPP
#define ROW 9
#define COL 10

#include "Pathfinding.hpp"

class MoveGenerator{
public:
    MoveGenerator(int (*newMatrix)[COL]);
    ce::list<Direction> getRoute(Pair enemyPos, Pair playerPos, RouteType type);
private:
    int matrix[ROW][COL] = {0};
    Pathfinding *pathfinding;
    ce::list<Direction> Astar(Pair enemyPos, Pair playerPos);
    ce::list<Direction> BreadCrumbing(Pair enemyPos, Pair playerPos);
    ce::list<Direction> Backtracking(Pair enemyPos, Pair playerPos);
    ce::list<Direction> LineSight(Pair enemyPos, Pair playerPos);

};

#endif //GAMESERVER_MOVEGENERATOR_HPP
