#ifndef GAMESERVER_MOVEGENERATOR_HPP
#define GAMESERVER_MOVEGENERATOR_HPP
#define ROW 9
#define COL 10

#include "Pathfinding.hpp"

class MoveGenerator{
public:
    static listDirections getRoute(int (*newMatrix)[COL], Pair enemyPos, Pair playerPos, RouteType type);
private:
    static Pathfinding *pathfinding;
    static listDirections Astar(Pair enemyPos, Pair playerPos);
    static listDirections BreadCrumbing(Pair enemyPos, Pair playerPos);
    static listDirections Backtracking(Pair enemyPos, Pair playerPos);
    static listDirections LineSight(Pair enemyPos, Pair playerPos);
};

#endif //GAMESERVER_MOVEGENERATOR_HPP
