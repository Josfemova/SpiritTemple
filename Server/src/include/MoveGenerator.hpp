#ifndef GAMESERVER_MOVEGENERATOR_HPP
#define GAMESERVER_MOVEGENERATOR_HPP

#include "Pathfinding.hpp"
#include "list.hpp"
#include "Direction.hpp"
struct yxPair
{
    int y;
    int x;
    std::string tostring();
};
class MoveGenerator{
public:
    static Pair teleport(ce::list<ce::list<int>> matrix, Pair enemyPos, Pair playerPos);
    static listDirections getRoute(gmatrix& matrix,int enemyY, int enemyX, Pair playerPos, RouteType type);
    static listDirections randomPathGenerator(int size, int x, int y, gmatrix level);
    
    static Direction getDirectionValue(int deltaX, int deltaY);
    static Pair getDeltaValues(std::string direction);
    static Direction getInverseDirection(Direction dir);
    static std::string directionToString(Direction direction);
    static Direction stringToDirection(std::string direction);
    static std::string inverseDirectionToString(Direction direction);
private:
    static Pathfinding* pathfinding;
    static int randomInt(int lowerLimit, int upperLimit);
    static listDirections Astar(Pair enemyPos, Pair playerPos);
    /**
     * @brief calculates a bresenham line, returns coordinates of its points as YX coordinates
     * 
     * @param originY x coordinate of starting point
     * @param originX y coordinate of starting point
     * @param destX x coordinate of objective
     * @param destY Y coordinate of objective
     * @return ce::list<Pair> YX coordinate pair list
     */
    static ce::list<yxPair> bresenhamLine(int originY, int originX,int destY ,int destX);
    /**
     * @brief Calculates bresenham line, returns portion of the path that is valid
     * 
     * @param enemyY 
     * @param enemyX 
     * @param playerY 
     * @param playerX 
     * @param state 
     * @return listDirections 
     */
    static listDirections LineSight(int enemyY,int enemyX, int playerY, int playerX, gmatrix& state);
    static listDirections BreadCrumbing(Pair enemyPos, Pair playerPos);
    static listDirections Backtracking(Pair enemyPos, Pair playerPos);
    
};

#endif //GAMESERVER_MOVEGENERATOR_HPP
