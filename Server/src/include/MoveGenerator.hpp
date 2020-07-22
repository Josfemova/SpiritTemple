#ifndef GAMESERVER_MOVEGENERATOR_HPP
#define GAMESERVER_MOVEGENERATOR_HPP

#include "Pathfinding.hpp"
#include "list.hpp"
#include "Direction.hpp"
class MoveGenerator{
public:
    static Pair teleport(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos);
    static listDirections getRoute(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos, RouteType type);
    static listDirections randomPath(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos, int size);
    static listDirections randomPathGenerator(int size, int x, int y, gmatrix level);
private:
    static Pathfinding* pathfinding;
    static listDirections Astar(Pair enemyPos, Pair playerPos);
    static listDirections LineSight(Pair enemyPos, Pair playerPos);
    static listDirections BreadCrumbing(Pair enemyPos, Pair playerPos);
    static listDirections Backtracking(Pair enemyPos, Pair playerPos);
    static Direction getDirectionValue(int deltaX, int deltaY);
};

#endif //GAMESERVER_MOVEGENERATOR_HPP
