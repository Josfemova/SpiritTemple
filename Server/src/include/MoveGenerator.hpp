#ifndef GAMESERVER_MOVEGENERATOR_HPP
#define GAMESERVER_MOVEGENERATOR_HPP

#include "Pathfinding.hpp"

class MoveGenerator{
public:
    static const int COLS = 10;
    static listDirections getRoute(int (*newMatrix)[COLS], Pair enemyPos, Pair playerPos, RouteType type);
private:
    static Pathfinding *pathfinding;
    static listDirections Astar(Pair enemyPos, Pair playerPos);
    static listDirections BreadCrumbing(Pair enemyPos, Pair playerPos);
    static listDirections Backtracking(Pair enemyPos, Pair playerPos);
    static listDirections LineSight(Pair enemyPos, Pair playerPos);
};

#endif //GAMESERVER_MOVEGENERATOR_HPP
