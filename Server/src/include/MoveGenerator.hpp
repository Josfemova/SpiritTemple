#ifndef GAMESERVER_MOVEGENERATOR_HPP
#define GAMESERVER_MOVEGENERATOR_HPP

#include "Pathfinding.hpp"

class MoveGenerator{
public:
    static listDirections getRoute(gmatrix matrix, Pair enemyPos, Pair playerPos, RouteType type);
    static listDirections randomPath(gmatrix matrix, Pair enemyPos, Pair playerPos, int size);
private:
    static Pathfinding* pathfinding;
    static listDirections Astar(Pair enemyPos, Pair playerPos);
    static listDirections BreadCrumbing(Pair enemyPos, Pair playerPos);
    static listDirections Backtracking(Pair enemyPos, Pair playerPos);
    static listDirections LineSight(Pair enemyPos, Pair playerPos);
};

#endif //GAMESERVER_MOVEGENERATOR_HPP
