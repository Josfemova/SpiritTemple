#include "include/Pathfinding.hpp"
#include <climits>
#include <cfloat>
#include <random>
#include <stack>
void Node::update(double FNew, double GNew, double HNew, int i, int j)
{
    F = FNew;
    G = GNew;
    H = HNew;
    parent_i = i;
    parent_j = j;
}

void Node::setPyx(int i, int j)
{
    parent_i = i;
    parent_j = j;
}

int Node::getPx() const
{
    return parent_j;
}

int Node::getPy() const
{
    return parent_i;
}

double Node::getF() const
{
    return F;
}

double Node::getG() const
{
    return G;
}

Pathfinding::Pathfinding(gmatrix matrix)
{
    this->matrix = matrix;
}

bool Pathfinding::isValid(int row, int col)
{
    int ROWS = matrix.size();
    int COLS = matrix[0].size();
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

bool Pathfinding::isUnBlocked(int row, int col)
{
    return matrix[row][col] == 1;
}

bool Pathfinding::isDestination(int row, int col, Pair dest)
{
    return (row == dest.first && col == dest.second);
}

bool Pathfinding::nodeValidations(int row, int col, Pair dest)
{
    return isValid(row, col) && isUnBlocked(row, col) && !isDestination(row, col, dest);
}

bool Pathfinding::initialValidations(Pair src, Pair dest)
{
    // If the source is out of range
    if(!isValid(src.first, src.second)){
        ce::log("\nSource is invalid");
        return false;
    }

    //If the destination is out of range
    if(!isValid(dest.first, dest.second)){
        ce::log("\nDestination is invalid");
        return false;
    }

    // Either the source or the destination is blocked
    if(!isUnBlocked(dest.first, dest.second)){ //!isUnBlocked(src.first, src.second) || 
        ce::log("\nSource or the destination is blocked");
        return false;
    }
    return true;
}

double Pathfinding::getHeuristicCost(int row, int col, Pair dest)
{
    return (sqrt((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

Direction Pathfinding::setMovement(int srcY, int srcX, int destY, int destX)
{
    if(srcX == destX && srcY+1 == destY){
        return Direction::NORTH;
    }
    else if(srcX == destX && srcY-1 == destY){
        return Direction::SOUTH;
    }
    else if(srcX+1 == destX && srcY == destY){
        return Direction::EAST;
    }
    else if(srcX-1 == destX && srcY == destY){
        return Direction::WEST;
    }
    else if(srcX+1 == destX && srcY+1 == destY){
        return Direction::NORTHEAST;
    }
    else if(srcX-1 == destX && srcY+1 == destY){
        return Direction::NORTHWEST;
    }
    else if(srcX+1 == destX && srcY-1 == destY){
        return Direction::SOUTHEAST;
    }
    else if(srcX-1 == destX && srcY-1 == destY){
        return Direction::SOUTHWEST;
    }
    else{
        return Direction();
    }
}

Pair Pathfinding::teleportEnemy(Pair src, Pair dest)
{
    int tempPlayerY = dest.first;
    int tempPlayerX = dest.second;
    Pair tempSrc = std::make_pair(tempPlayerY, tempPlayerX);

    adjacentNodes nodes;
    adjNodes(nodes, src, tempSrc, dest);

    adjacentNodes closestNodes;
    for(auto currentNode : nodes){
        tempPlayerY = currentNode.first;
        tempPlayerX = currentNode.second;
        tempSrc = std::make_pair(tempPlayerY, tempPlayerX);
        adjNodes(closestNodes, src, tempSrc, dest);
    }

    // Initialize random generator
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, closestNodes.size()-1);

    // Teleport enemy
    while(true){
        Pair teleport = closestNodes[dist(rng)];
        if(nodeValidations(teleport.first, teleport.second, dest)){
            return teleport;
        }
    }
}


void Pathfinding::adjNodes(adjacentNodes &nodes, Pair &src, Pair &tempSrc, Pair &dest)
{
    // NORTH NODE
    if(nodeValidations(tempSrc.first+1, tempSrc.second, dest)){
        Pair pair = std::make_pair(tempSrc.first+1, tempSrc.second);
        addNode(nodes, src, pair, dest);
    }
    // SOUTH NODE
    if(nodeValidations(tempSrc.first-1, tempSrc.second, dest)){
        Pair pair = std::make_pair(tempSrc.first-1, tempSrc.second);
        addNode(nodes, src, pair, dest);
    }
    // EAST NODE
    if(nodeValidations(tempSrc.first, tempSrc.second+1, dest)){
        Pair pair = std::make_pair(tempSrc.first, tempSrc.second+1);
        addNode(nodes, src, pair, dest);
    }
    // WEST NODE
    if(nodeValidations(tempSrc.first, tempSrc.second-1, dest)){
        Pair pair = std::make_pair(src.first, src.second-1);
        addNode(nodes, src, pair, dest);
    }
    // NORTHEAST NODE
    if(nodeValidations(tempSrc.first+1, tempSrc.second+1, dest)){
        Pair pair = std::make_pair(tempSrc.first+1, tempSrc.second+1);
        addNode(nodes, src, pair, dest);
    }

    // NORTHWEST NODE
    if(nodeValidations(tempSrc.first+1, tempSrc.second-1, dest)){
        Pair pair = std::make_pair(tempSrc.first+1, tempSrc.second-1);
        addNode(nodes, src, pair, dest);
    }
    // SOUTHEAST NODE
    if(nodeValidations(tempSrc.first-1, tempSrc.second+1, dest)){
        Pair pair = std::make_pair(tempSrc.first-1, tempSrc.second+1);
        addNode(nodes, src, pair, dest);
    }
    // SOUTHWEST NODE
    if(nodeValidations(tempSrc.first-1, tempSrc.second-1, dest)){
        Pair pair = std::make_pair(tempSrc.first-1, tempSrc.second-1);
        addNode(nodes, src, pair, dest);
    }
}

void Pathfinding::addNode(adjacentNodes &adjNodes, Pair &src, Pair &pair, Pair &dest)
{
    if(!adjNodes.contains(pair) && pair!=src && pair!=dest){
        adjNodes.push_back(pair);
    }
}

//Nice
Pair Pathfinding::randomNode(adjacentNodes &adjNodes)
{
    if(adjNodes.size() > 1){
        // Initialize random generator
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, adjNodes.size()-1);
        Pair node = adjNodes[dist(rng)];
        return node;
    }
    else if(adjNodes.size() == 1){
        Pair node = adjNodes.pop_front();
        return node;
    }
    else{
        return std::make_pair(-1, -1);
    }
}

listDirections Pathfinding::AStarSearch(Pair src, Pair dest)
{
    // List of directions to follow between the enemy's position and the
    // player's position
    listDirections shortestPath;

    // Initial validations
    if(!initialValidations(src, dest)){
        return shortestPath;
    }

    // If the destination node is the same as source node
    if(isDestination(src.first, src.second, dest)){
        ce::log("We already at the destination");
        return shortestPath;
    }

    int ROWS = matrix.size();
    int COLS = matrix[0].size();

    // Closed list and initialized false cause the node has not been included yet
    // The closed list is implemented as a boolean matrix
    ce::list<ce::list<bool>> closedList;

    // Matrix to hold the details of nodes
    // Node nodeDetails[ROWS][COLS];
    ce::list<ce::list<Node>> nodesDetails;

    int i, j;

    // Initialize both matrix
    for(i=0; i<ROWS; i++){
        ce::list<bool> r(false, COLS);
        ce::list<Node> y(Node(), COLS);
        closedList.push_back(r);
        nodesDetails.push_back(y);
    }

    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            nodesDetails[i][j].update(FLT_MAX, FLT_MAX, FLT_MAX, -1, -1);
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    nodesDetails[i][j].update(0.0, 0.0, 0.0, i, j);

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


        //----------- 1st Successor (North) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i+1, j, i, j, 1.0)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 2nd Successor (South) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i-1, j, i, j, 1.0)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 3rd Successor (East) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i, j+1, i, j, 1.0)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 4th Successor (West) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i, j-1, i, j, 1.0)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 5th Successor (North-East) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i+1, j+1, i, j, 1.414)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 6th Successor (North-West) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i+1, j-1, i, j, 1.414)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 7th Successor (South-East) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i-1, j+1, i, j, 1.414)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }

        //----------- 8th Successor (South-West) ------------//
        if(AStarMovement(nodesDetails,closedList, openList, dest, i-1, j-1, i, j, 1.414)){
            foundDest = true;
            setAStarPath(nodesDetails, dest, shortestPath);
            break;
        }
    }

    // If the destination node is not found and the open
    if (!foundDest){
        ce::log("Failed to find the destination node");
    }

    return shortestPath;
}

bool Pathfinding::AStarMovement(ce::list<ce::list<Node>> &nodesDetails, ce::list<ce::list<bool>> &closedList,
        std::set<pPair> &openList, Pair &dest, int row, int col, int pi, int pj, float g)
{
    // To store the 'G', 'H' and F'
    double GNew, HNew, FNew;

    // Only process this node if this is a valid one
    if (isValid(row, col)){
        // If the destination node is the same as the current successor
        if (isDestination(row, col, dest)){
            // Set the Parent of the destination node
            nodesDetails[row][col].setPyx(pi, pj);
            return true;
        }
        // If the successor is already on the closed list or if it is blocked
        // then ignore it. Else do the following
        else if (!closedList[row][col] && isUnBlocked(row, col)){
            GNew = nodesDetails[pi][pj].getG() + g;
            HNew = getHeuristicCost(row, col, dest);
            FNew = GNew + HNew;

            // If it isn’t on the open list, add it to the open list. Make the current square
            // the parent of this square. Record the f, g, and h costs of the square cell
            //                            OR
            // If it is on the open list already, check to see if this path to that square is
            // better, using 'f' cost as the measure.
            if (nodesDetails[row][col].getF() == FLT_MAX || nodesDetails[row][col].getF() > FNew){
                openList.insert(std::make_pair(FNew,std::make_pair(row, col)));
                // Update the details of this node
                nodesDetails[row][col].update(FNew, GNew, HNew, pi, pj);
            }
        }
    }
    return false;
}

void Pathfinding::setAStarPath(ce::list<ce::list<Node>> &nodesDetails, Pair &dest, listDirections &path)
{
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> stackPath;

    while(!(nodesDetails[row][col].getPy() == row && nodesDetails[row][col].getPx() == col))
    {
        stackPath.push(std::make_pair(row, col));
        int temp_row = nodesDetails[row][col].getPy();
        int temp_col = nodesDetails[row][col].getPx();
        path.push_front(setMovement(temp_row, temp_col, row, col));
        row = temp_row;
        col = temp_col;
    }
    path.pop_back();
}

/*listDirections Pathfinding::LineSight(Pair src, Pair dest)
{
    // Initial validations
    if(!initialValidations(src, dest)){
        return BresenhamLine;
    }
    ce::debuglog("fallando");
    // If the destination node is the same as source node
    if(isDestination(src.first, src.second, dest)){
        ce::log("We already at the destination");
        return BresenhamLine;
    }

    int dy = abs(dest.first - src.first);
    int dx = abs(dest.second - src.second);

    int sy = src.first < dest.first ? 1 : -1;
    int sx = src.second < dest.second ? 1 : -1;

    int err = dy - dx;
    int e2;
    int currentY = src.first;
    int currentX = src.second;
    int previousY = currentY;
    int previousX = currentX;

    while(true)
    {
        if(!isUnBlocked(currentY, currentX)){
            Pair newSrc = bestAdjacentNode(previousY, previousX, dest);
            if(newSrc != src){
                currentY = newSrc.first;
                currentX = newSrc.second;
                LineSight(newSrc, dest);
                break;
            }
            else{
                BresenhamLine = AStarSearch(BresenhamNodes[0], dest);
                return BresenhamLine;
            }
        }

        if(currentY == dest.first && currentX == dest.second){
            BresenhamNodes.push_back(std::make_pair(currentY, currentX));
            setLineSight(BresenhamNodes, BresenhamLine);
            return BresenhamLine;
        }

        BresenhamNodes.push_back(std::make_pair(currentY, currentX));

        previousY = currentY;
        previousX = currentX;

        e2 = 2 * err;
        if(e2 > -1 * dx){
            err = err - dx;
            currentY = currentY + sy;
        }

        if(e2 < dy){
            err = err + dy;
            currentX = currentX + sx;
        }
    }
    
    return BresenhamLine;
}
*/
Pair Pathfinding::bestAdjacentNode(int &py, int &px, Pair &dest)
{
    std::set<pPair> adjNodes;

    // NORTH NODE
    if(isValid(py+1, px) && isUnBlocked(py+1, px)){
        int H = ManhattanDistance(py+1, px, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py+1, px)));
    }

    // SOUTH NODE
    if(isValid(py-1, px) && isUnBlocked(py-1, px)){
        int H = ManhattanDistance(py-1, px, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py-1, px)));
    }

    // EAST NODE
    if(isValid(py, px+1) && isUnBlocked(py, px+1)){
        int H = ManhattanDistance(py, px+1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py, px+1)));
    }

    // WEST NODE
    if(isValid(py, px-1) && isUnBlocked(py, px-1)){
        int H = ManhattanDistance(py, px-1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py, px-1)));
    }

    // NORTHEAST NODE
    if(isValid(py+1, px+1) && isUnBlocked(py+1, px+1)){
        int H = ManhattanDistance(py+1, px+1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py+1, px+1)));
    }

    // NORTHWEST NODE
    if(isValid(py+1, px-1) && isUnBlocked(py+1, px-1)){
        int H = ManhattanDistance(py+1, px-1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py+1, px-1)));
    }

    // SOUTHEAST NODE
    if(isValid(py-1, px+1) && isUnBlocked(py-1, px+1)){
        int H = ManhattanDistance(py-1, px+1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py-1, px+1)));
    }

    // SOUTHWEST NODE
    if(isValid(py-1, px-1) && isUnBlocked(py-1, px-1)){
        int H = ManhattanDistance(py-1, px-1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(py-1, px-1)));
    }

    pPair temp = std::make_pair(INT_MAX, std::make_pair(0,0));
    for(int i=0; i<adjNodes.size(); i++){
        pPair p = *adjNodes.begin();

        if(p.first < temp.first){
            temp = p;
        }
        // Remove this vertex from the open list
        adjNodes.erase(adjNodes.begin());
    }
    Pair src = temp.second;
    return src;
}

int Pathfinding::ManhattanDistance(int py, int px, Pair dest)
{
    return abs(py - dest.first) + abs(px - dest.second);
}

void Pathfinding::setLineSight(adjacentNodes &BresenhamNodes, listDirections &BresenhamLine)
{
    BresenhamLine.clear();
    for(int i=0; i<BresenhamNodes.size(); i++)
    {
        if(i+1 != BresenhamNodes.size()){
            Pair src = BresenhamNodes[i];
            Pair dest = BresenhamNodes[i+1];
            BresenhamLine.push_back(setMovement(src.first, src.second, dest.first, dest.second));
        }
    }
}