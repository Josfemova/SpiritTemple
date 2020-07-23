#ifndef SPIRITTEMPLE_PATHFINDING_HPP
#define SPIRITTEMPLE_PATHFINDING_HPP

#include <utility>
#include <set>
#include "Direction.hpp"
#include "RouteType.hpp"
#include "utilities.hpp"
#include "list.hpp"
#include <random>

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;
typedef ce::list<Direction> listDirections;
typedef ce::list<Pair> adjacentNodes;
typedef ce::list<ce::list<int>> gmatrix;

/**
 * @brief hold the parameters of each node
 */
class Node {
private:
    int parent_i{};
    int parent_j{};
    double F{};
    double G{};
    double H{};
public:
    Node()= default;
    /**
     * @brief update all data of the node
     * @param FNew
     * @param GNew
     * @param HNew
     * @param i
     * @param j
     */
    void update(double FNew, double GNew, double HNew, int i, int j);

    /**
     * @brief set the parent coordinate of the node
     * @param i
     * @param j
     */
    void setPyx(int i, int j);

    /**
     *
     * @return parent_i
     */
    int getPx() const;

    /**
     *
     * @return parent_j
     */
    int getPy() const;

    /**
     *
     * @return F
     */
    double getF() const;

    /**
     *
     * @return G
     */
    double getG() const;
};

/**
 * @brief Manage everything related with path finding, A*, bread crumbing, backtracking
 * and line sight
 */
class Pathfinding {
private:
    gmatrix matrix;
    listDirections BresenhamLine;
    adjacentNodes BresenhamNodes;

public:
    /**
     * @brief update the matrix
     * @param newMatrix
     */
    explicit Pathfinding(gmatrix matrix);

    /**
     * @brief check whether given node (row, col) is a valid node or not
     * @param row
     * @param col
     * @return true
     * @return false
     */
    bool isValid(int row, int col);

    /**
     * @brief returns true if the node isn't blocked, else false
     * @param row
     * @param col
     * @return true
     * @return false
     */
    bool isUnBlocked(int row, int col);

    /**
     * @brief check whether destination node has been reached or not
     * @param row
     * @param col
     * @param dest
     * @return true
     * @return false
     */
    static bool isDestination(int row, int col, Pair dest);

    /**
     * @brief checks everything related to a node in the matrix
     * @param row
     * @param col
     * @param dest
     * @return true
     * @return false
     */
    bool nodeValidations(int row, int col, Pair dest);

    bool initialValidations(Pair src, Pair dest);

    /**
     * @brief calculate the "H" Heuristic
     * @param row
     * @param col
     * @param dest
     * @return the diagonal cost of the movement
     */
    static double getHeuristicCost(int row, int col, Pair dest);

    /**
     * @brief it set and return the specific movement from a node and its adjacent nodes
     * @param srcX
     * @param srcY
     * @param destX
     * @param destY
     * @return Direction
     */
    static Direction setMovement(int srcX, int srcY, int destX, int destY);

    /**
     * @brief move the enemy to a position close to the player
     * @param newMatrix
     * @param enemyX
     * @param enemyY
     * @param playerX
     * @param playerY
     */
    Pair teleportEnemy(Pair src, Pair dest);

    listDirections RandomPath(Pair src, Pair dest, int size);
    void adjNodes(adjacentNodes &nodes, Pair &src, Pair &tempSrc, Pair &dest);
    static void addNode(adjacentNodes &adjNodes, Pair &src, Pair &pair, Pair &dest);
    static Pair randomNode(adjacentNodes &adjNodes);

    /**
     * @brief find the shortest path between a given source node to a destination
     * node according to A* Search Algorithm
     * @param src
     * @param dest
     */
    listDirections AStarSearch(Pair src, Pair dest);
    bool AStarMovement(ce::list<ce::list<Node>> &nodesDetails, ce::list<ce::list<bool>> &closedList,
            std::set<pPair> &openList, Pair &dest, int row, int col, int pi, int pj, float g);
    void setAStarPath(ce::list<ce::list<Node>> &nodesDetails, Pair &dest, listDirections &path);


    /**
      * @brief find the line between a given source node to a destination
      * @param src
      * @param dest
      * @return
      */
    listDirections LineSight(Pair src, Pair dest);

    /**
      * @brief find the best adjacent node
      * @param px
      * @param py
      * @param dest
      * @return the best adjacent node
      */
    Pair bestAdjacentNode(int &py, int &px, Pair &dest);

    /**
      *
      * @param px
      * @param py
      * @param dest
      * @return the manhattan heuristic cost
      */
    static int ManhattanDistance(int py, int px, Pair dest);

    /**
    * @brief add a node to the list of node for bresenham line
    * @param nodes
    * @param line
    */
    static void setLineSight(adjacentNodes &BresenhamNodes, listDirections &BresenhamLine);
};

#endif //SPIRITTEMPLE_PATHFINDING_HPP
