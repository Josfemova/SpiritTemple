#ifndef SPIRITTEMPLE_PATHFINDING_HPP
#define SPIRITTEMPLE_PATHFINDING_HPP

#include <bits/stdc++.h>
#include "Direction.hpp"
#include "RouteType.hpp"
#include "utilities.hpp"
#include "list.hpp"
#include <random>

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;
typedef ce::list<Direction> listDirections;
typedef ce::list<Pair> adjacentNodes;

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
    void setPxy(int i, int j);

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
    static const int ROWS = 10;
    static const int COLS = 10;
    int matrix[ROWS][COLS] = {0};
    listDirections line;
    adjacentNodes nodes;

public:
    /**
     * @brief update the matrix
     * @param newMatrix
     */
    explicit Pathfinding(int (*newMatrix)[COLS]);

    /**
     * @brief check whether given node (row, col) is a valid node or not
     * @param row
     * @param col
     * @return true
     * @return false
     */
    static bool isValid(int row, int col);

    /**
     * @brief returns true if the node isn't blocked, else false
     * @param row
     * @param col
     * @return true
     * @return false
     */
    bool isUnBlocked(int row, int col) const;

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
    bool nodeValidations(int row, int col, Pair dest) const;

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
     *
     * @param direction
     * @return next node movement
     */
    static std::string getNextMovement(Direction direction);

    /**
     *
     * @param direction
     * @return previous node movement
     */
    static std::string getPreviousMovement(Direction direction);

    /**
     * @brief update enemy position
     * @param direction
     * @param px
     * @param py
     */
    static void setNewEnemyPos(Direction direction, int &px, int &py);

    /**
     * @brief update enemy position
     * @param direction
     * @param px
     * @param py
     */
    static void setPreviousEnemyPos(Direction direction, int &px, int &py);

    /**
     * @brief move the enemy to a position close to the player
     * @param newMatrix
     * @param enemyX
     * @param enemyY
     * @param playerX
     * @param playerY
     */
    void teleportEnemy(int &enemyX, int &enemyY, int &playerX, int &playerY) const;

    /**
     * @brief get all the adjacent nodes to a particular node
     * @param pathfinding
     * @param nodes
     * @param px
     * @param py
     * @param dest
     */
    void checkAdjacentNodes(adjacentNodes &cells, int px, int py, Pair dest) const;

    /**
     * @brief add a node to the list of nodes near the player
     * @param cells
     * @param pair
     * @param dest
     */
    static void addNode(adjacentNodes &cells, Pair &pair, Pair &dest);

    /**
     * @brief print the astar from the source to destination
     * @param nodeDetails
     * @param dest
     */
    static void printAstar(Node nodeDetails[][COLS], Pair &dest, listDirections &shortestPath);

    /**
     * @brief print breadcrumbs left by the enemy when chasing the player
     * @param breadcrumbs
     */
    static void printBreadcrumbs(listDirections &breadcrumbs);

    /**
     * @brief print bresenham line
     * @param line
     */
    static void printLineSight(listDirections &line);

    /**
     * @brief add a node to the list of node for bresenham line
     * @param nodes
     * @param line
     */
    static void setLineSight(adjacentNodes &nodes, listDirections &line);

    /**
     * @brief find the shortest path between a given source node to a destination
     * node according to A* Search Algorithm
     * @param src
     * @param dest
     */
     listDirections AstarSearch(Pair src, Pair dest) const;

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
     Pair bestAdjacentNode(int &px, int &py, Pair &dest) const;

     /**
      *
      * @param px
      * @param py
      * @param dest
      * @return the manhattan heuristic cost
      */
     static int ManhattanDistance(int px, int py, Pair dest);
};

#endif //SPIRITTEMPLE_PATHFINDING_HPP
