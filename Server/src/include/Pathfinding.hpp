#ifndef SPIRITTEMPLE_PATHFINDING_HPP
#define SPIRITTEMPLE_PATHFINDING_HPP

#define ROW 9
#define COL 10

#include <bits/stdc++.h>
#include "Direction.hpp"
#include "RouteType.hpp"
#include "list.hpp"

typedef std::pair<int, int> Pair ;
typedef std::pair<double, std::pair<int, int>> pPair;

/**
 * @brief Hold the parameter of each node
 */
class Node {
private:
    int parent_i{}, parent_j{};
    double F{}, G{}, H{};
public:
    Node(){}
    /**
     * @brief Update all data of the node
     * @param FNew
     * @param GNew
     * @param HNew
     * @param i
     * @param j
     */
    void update(double FNew, double GNew, double HNew, int i, int j){
        F = FNew;
        G = GNew;
        H = HNew;
        parent_i = i;
        parent_j = j;
    }

    /**
     * @brief Set the parent coordinate of the node
     * @param i
     * @param j
     */
    void setPxy(int i, int j) { parent_i = i; parent_j = j;}

    /**
     * @brief Set the parent x coordinate of the node
     * @param i
     */
    void setPx(int i) { parent_j = i; }

    /**
     * @brief Set the parent y coordinate of the node
     * @param j
     */
    void setPy(int j) { parent_j = j; }

    /**
     * @brief Set the F parameter of the node
     * @param FNew
     */
    void setF(double FNew){ F = FNew; }

    /**
     * @brief Set the G parameter of the node
     * @param GNew
     */
    void setG(double GNew){ G = GNew; }

    /**
     * @brief Set the H parameter of the node
     * @param HNew
     */
    void setH(double HNew){ H = HNew; }

    /**
     *
     * @return parent_i
     */
    int getPx() const{ return parent_i; }

    /**
     *
     * @return parent_j
     */
    int getPy() const{ return parent_j; }

    /**
     *
     * @return F
     */
    double getF() const{ return F; }

    /**
     *
     * @return G
     */
    double getG() const{ return G; }

    /**
     *
     * @return H
     */
    double getH() const{ return H; }
};

/**
 * @brief Manage everything related with path finding, A*, bread crumbing, backtracking
 * and line sight
 */
class Pathfinding {
private:
    int matrix[ROW][COL] = {0};

public:
    /**
     * @brief Update the matrix
     * @param newMatrix
     */
    explicit Pathfinding(int (*newMatrix)[COL]){
        for(int i=0; i<ROW; i++){
            for(int j=0; j<COL; j++){
                matrix[i][j] = newMatrix[i][j];
            }
        }
    }

    /**
     * @brief Check whether given node (row, col) is a valid node or not
     * @param row
     * @param col
     * @return true
     * @return false
     */
    static bool isValid(int row, int col){
        return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
    }

    /**
     * @brief Returns true if the node isn't blocked, else false
     * @param row
     * @param col
     * @return true
     * @return false
     */
    bool isUnBlocked(int row, int col){
        return matrix[row][col] == 1;
    }

    /**
     * @brief Check whether destination node has been reached or not
     * @param row
     * @param col
     * @param dest
     * @return true
     * @return false
     */
    static bool isDestination(int row, int col, Pair dest){
        return (row == dest.first && col == dest.second);
    }

    /**
     * @brief Calculate the "H" Heuristic
     * @param row
     * @param col
     * @param dest
     * @return the diagonal cost of the movement
     */
    static double getHeuristicCost(int row, int col, Pair dest){
        return ((double) sqrt((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
    }

    static Direction setMovement(int srcX, int srcY, int destX, int destY){
        if(srcX-1 == destX && srcY == destY){
            return Direction::NORTH;
        }
        else if(srcX+1 == destX && srcY == destY){
            return Direction::SOUTH;
        }
        else if(srcX == destX && srcY+1 == destY){
            return Direction::EAST;
        }
        else if(srcX == destX && srcY-1 == destY){
            return Direction::WEST;
        }
        else if(srcX-1 == destX && srcY+1 == destY){
            return Direction::NORTHEAST;
        }
        else if(srcX-1 == destX && srcY-1 == destY){
            return Direction::NORTHWEST;
        }
        else if(srcX+1 == destX && srcY+1 == destY){
            return Direction::SOUTHEAST;
        }
        else{
            return Direction::SOUTHWEST;
        }
    }

    /**
     * @brief Print the path from the source to destination
     * @param nodeDetails
     * @param dest
     */
    static void printPath(Node nodeDetails[][COL], Pair dest, ce::list<Direction> &shortestPath){
        std::cout<<"\nThe path is ";
        int row = dest.first;
        int col = dest.second;

        std::stack<Pair> Path;

        while(!(nodeDetails[row][col].getPx() == row
                && nodeDetails[row][col].getPy() == col))
        {
            Path.push(std::make_pair(row, col));
            int temp_row = nodeDetails[row][col].getPx();
            int temp_col = nodeDetails[row][col].getPy();
            shortestPath.push_front(setMovement(temp_row, temp_col, row, col));
            row = temp_row;
            col = temp_col;
        }

        Path.push(std::make_pair(row, col));
        while (!Path.empty())
        {
            std::pair<int, int> p = Path.top();
            Path.pop();
            printf("-> (%d,%d) ", p.first, p.second);
        }

        std::cout<<"\n";
        std::string result = "Tha path is: ";
        for(int i=0; i<shortestPath.size(); i++){
            if(shortestPath[i] == Direction::NORTH){
                result += "NORTH -> ";
            }
            else if(shortestPath[i] == Direction::SOUTH){
                result += "SOUTH -> ";
            }
            else if(shortestPath[i] == Direction::EAST){
                result += "EAST -> ";
            }
            else if(shortestPath[i] == Direction::WEST){
                result += "WEST -> ";
            }
            else if(shortestPath[i] == Direction::NORTHEAST){
                result += "NORTHEAST -> ";
            }
            else if(shortestPath[i] == Direction::NORTHWEST){
                result += "NORTHWEST -> ";
            }
            else if(shortestPath[i] == Direction::SOUTHEAST){
                result += "SOUTHEAST -> ";
            }
            else if(shortestPath[i] == Direction::SOUTHWEST){
                result += "SOUTHWEST -> ";
            }
        }
        std::string stringForm = result.substr(0,result.size()-3);
        std::cout<<stringForm<<std::endl;
    }

    /**
     * @brief Find the shortest path between a given source node to a destination
     * node according to A* Search Algorithm
     * @param src
     * @param dest
     */
    ce::list<Direction> AstarSearch(Pair src, Pair dest){
        // List of directions to follow between the enemy's position and the
        // player's position
        ce::list<Direction> shortestPath;

        // If the source is out of range
        if(!isValid(src.first, src.second)){
            std::cout<<"Source is invalid\n";
            return shortestPath;
        }

        //Id the destination is out of range
        if(!isValid(dest.first, dest.second)){
            std::cout<<"Destination is invalid\n";
            return shortestPath;
        }

        // Either the source or the destination is blocked
        if(!isUnBlocked(src.first, src.second) || !isUnBlocked(dest.first, dest.second)){
            std::cout<<"Source or the destination is blocked\n";
            return shortestPath;
        }

        // If the destination node is the same as source node
        if(isDestination(src.first, src.second, dest)){
            std::cout<<"We are already at the destination\n";
            return shortestPath;
        }

        // Closed list and initialized false cause the node has not been included yet
        // The closed list is implemented as a boolean 2D array
        bool closedList[ROW][COL];
        memset(closedList, false, sizeof(closedList));

        // 2D array to hold the details of that node
        Node nodeDetails[ROW][COL];

        int i, j;

        for(i=0; i<ROW; i++){
            for(j=0; j<COL; j++){
                nodeDetails[i][j].update(FLT_MAX, FLT_MAX, FLT_MAX, -1, -1);
            }
        }

        // Initialising the parameters of the starting node
        i = src.first, j = src.second;
        nodeDetails[i][j].update(0.0, 0.0, 0.0, i, j);

        /*
         * Open list that contain information as <F, <i,j>> where F = G + H and
         * i, j are the row and column index of that node.
         */
        std::set<pPair> openList;

        // Add the starting node to the open list and set its 'F' as 0
        openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

        // Boolean variable that indicates the destination is not reached yet
        bool foundDest = false;

        while(!openList.empty())
        {
            pPair p = *openList.begin();

            // Remove this vertex from the open list
            openList.erase(openList.begin());

            // Add this vertex to the closed list
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            // To store the 'G', 'H' and F' ot the 8 successors
            double GNew, HNew, FNew;

            //----------- 1st Successor (North) ------------//

            // Only process this node if this is a valid one
            if (isValid(i-1, j)){
                // If the destination node is the same as the current successor
                if (isDestination(i-1, j, dest)){
                    // Set the Parent of the destination node
                    nodeDetails[i-1][j].setPxy(i, j);
                    //shortestPath.push_back(Direction::NORTH);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }
                    // If the successor is already on the closed list or if it is blocked
                    // then ignore it. Else do the following
                else if (!closedList[i-1][j] && isUnBlocked(i-1, j)){
                    GNew = nodeDetails[i][j].getG() + 1.0;
                    HNew = getHeuristicCost(i-1, j, dest);
                    FNew = GNew + HNew;

                    // If it isn’t on the open list, add it to the open list. Make the current square
                    // the parent of this square. Record the f, g, and h costs of the square cell
                    //                            OR
                    // If it is on the open list already, check to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (nodeDetails[i-1][j].getF() == FLT_MAX || nodeDetails[i-1][j].getF() > FNew){
                        openList.insert(std::make_pair(FNew,std::make_pair(i-1, j)));
                        // Update the details of this node
                        nodeDetails[i-1][j].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 2nd Successor (South) ------------//

            if (isValid(i+1, j)){
                if (isDestination(i+1, j, dest)){
                    nodeDetails[i+1][j].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }
                else if (!closedList[i + 1][j] && isUnBlocked(i+1, j)){
                    GNew = nodeDetails[i][j].getG() + 1.0;
                    HNew = getHeuristicCost(i+1, j, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i+1][j].getF() == FLT_MAX || nodeDetails[i+1][j].getF() > FNew){
                        openList.insert( std::make_pair (FNew, std::make_pair (i+1, j)));
                        // Update the details of this node
                        nodeDetails[i+1][j].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 3rd Successor (East) ------------//

            if (isValid(i, j + 1)){
                if (isDestination(i, j+1, dest)){
                    nodeDetails[i][j+1].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }
                else if (!closedList[i][j+1] && isUnBlocked(i, j+1)){
                    GNew = nodeDetails[i][j].getG() + 1.0;
                    HNew = getHeuristicCost(i, j+1, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i][j+1].getF() == FLT_MAX || nodeDetails[i][j+1].getF() > FNew){
                        openList.insert( std::make_pair(FNew,std::make_pair (i, j+1)));
                        // Update the details of this node
                        nodeDetails[i][j+1].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 4th Successor (West) ------------//

            if (isValid(i, j - 1)){
                if (isDestination(i, j-1, dest)){
                    nodeDetails[i][j-1].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }

                else if (!closedList[i][j-1] && isUnBlocked(i, j-1)){
                    GNew = nodeDetails[i][j].getG() + 1.0;
                    HNew = getHeuristicCost(i, j-1, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i][j-1].getF() == FLT_MAX || nodeDetails[i][j-1].getF() > FNew){
                        openList.insert( std::make_pair (FNew,std::make_pair (i, j-1)));
                        // Update the details of this node
                        nodeDetails[i][j-1].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 5th Successor (North-East) ------------//

            if (isValid(i - 1, j + 1)){
                if (isDestination(i-1, j+1, dest)){
                    nodeDetails[i-1][j+1].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }
                else if (!closedList[i - 1][j + 1] && isUnBlocked(i-1, j+1)){
                    GNew = nodeDetails[i][j].getG() + 1.414;
                    HNew = getHeuristicCost(i-1, j+1, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i-1][j+1].getF() == FLT_MAX || nodeDetails[i-1][j+1].getF() > FNew){
                        openList.insert( std::make_pair (FNew, std::make_pair(i-1, j+1)));
                        // Update the details of this node
                        nodeDetails[i-1][j+1].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 6th Successor (North-West) ------------//
            if (isValid (i-1, j-1)){
                if (isDestination (i-1, j-1, dest)){
                    nodeDetails[i-1][j-1].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }
                else if (!closedList[i-1][j-1] && isUnBlocked(i-1,j-1)){
                    GNew = nodeDetails[i][j].getG() + 1.414;
                    HNew = getHeuristicCost(i-1, j-1, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i-1][j-1].getF() == FLT_MAX || nodeDetails[i-1][j-1].getF() > FNew){
                        openList.insert( std::make_pair (FNew, std::make_pair (i-1, j-1)));
                        // Update the details of this node
                        nodeDetails[i-1][j-1].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 7th Successor (South-East) ------------//

            if (isValid(i+1, j+1)){
                if (isDestination(i+1, j+1, dest)){
                    nodeDetails[i+1][j+1].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }

                else if (!closedList[i + 1][j + 1] && isUnBlocked(i+1, j+1)){
                    GNew = nodeDetails[i][j].getG() + 1.414;
                    HNew = getHeuristicCost(i+1, j+1, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i+1][j+1].getF() == FLT_MAX || nodeDetails[i+1][j+1].getF() > FNew){
                        openList.insert(std::make_pair(FNew,std::make_pair (i+1, j+1)));
                        // Update the details of this node
                        nodeDetails[i+1][j+1].update(FNew, GNew, HNew, i, j);
                    }
                }
            }

            //----------- 8th Successor (South-West) ------------//

            if (isValid (i+1, j-1)){
                if (isDestination(i+1, j-1, dest)){
                    nodeDetails[i+1][j-1].setPxy(i, j);
                    std::cout<<"The destination cell is found\n";
                    printPath(nodeDetails, dest, shortestPath);
                    foundDest = true;
                    break;
                }

                else if (!closedList[i+1][j-1] && isUnBlocked(i+1, j-1)){
                    GNew = nodeDetails[i][j].getG() + 1.414;
                    HNew = getHeuristicCost(i+1, j-1, dest);
                    FNew = GNew + HNew;

                    if (nodeDetails[i+1][j-1].getF() == FLT_MAX || nodeDetails[i+1][j-1].getF() > FNew){
                        openList.insert(std::make_pair(FNew, std::make_pair(i+1, j-1)));
                        // Update the details of this node
                        nodeDetails[i+1][j-1].update(FNew, GNew, HNew, i, j);
                    }
                }
            }
        }
        // If the destination node is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination node. This may happen when the
        // there is no way to destination node (due to blockages)
        if (!foundDest){
            std::cout<<"Failed to find the Destination Node\n";
        }

        return shortestPath;
    }
};

#endif //SPIRITTEMPLE_PATHFINDING_HPP
