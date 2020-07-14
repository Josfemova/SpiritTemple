#include "include/Pathfinding.hpp"

void Node::update(double FNew, double GNew, double HNew, int i, int j)
{
    F = FNew;
    G = GNew;
    H = HNew;
    parent_i = i;
    parent_j = j;
}

void Node::setPxy(int i, int j)
{
    parent_i = i;
    parent_j = j;
}

int Node::getPx() const
{
    return parent_i;
}

int Node::getPy() const
{
    return parent_j;
}

double Node::getF() const
{
    return F;
}

double Node::getG() const
{
    return G;
}

Pathfinding::Pathfinding(int (*newMatrix)[10])
{
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            matrix[i][j] = newMatrix[i][j];
        }
    }
}

bool Pathfinding::isValid(int row, int col)
{
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

bool Pathfinding::isUnBlocked(int row, int col) const
{
    return matrix[row][col] == 1;
}

bool Pathfinding::isDestination(int row, int col, Pair dest)
{
    return (row == dest.first && col == dest.second);
}

bool Pathfinding::nodeValidations(int row, int col, Pair dest) const
{
    return isValid(row, col) && isUnBlocked(row, col) && !isDestination(row, col, dest);
}

double Pathfinding::getHeuristicCost(int row, int col, Pair dest)
{
    return (sqrt((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

Direction Pathfinding::setMovement(int srcX, int srcY, int destX, int destY)
{
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

std::string Pathfinding::getNextMovement(Direction direction)
{
    switch (direction)
    {
        case Direction::NORTH:
            return "NORTH";
        case Direction::SOUTH:
            return "SOUTH";
        case Direction::EAST:
            return "EAST";
        case Direction::WEST:
            return "WEST";
        case Direction::NORTHEAST:
            return "NORTHEAST";
        case Direction::NORTHWEST:
            return "NORTHWEST";
        case Direction::SOUTHEAST:
            return "SOUTHEAST";
        case Direction::SOUTHWEST:
            return "SOUTHWEST";
        default:
            return "";
    }
}

std::string Pathfinding::getPreviousMovement(Direction direction)
{
    switch (direction)
    {
        case Direction::NORTH:
            return "SOUTH";
        case Direction::SOUTH:
            return "NORTH";
        case Direction::EAST:
            return "WEST";
        case Direction::WEST:
            return "EAST";
        case Direction::NORTHEAST:
            return "SOUTHWEST";
        case Direction::NORTHWEST:
            return "SOUTHEAST";
        case Direction::SOUTHEAST:
            return "NORTHWEST";
        case Direction::SOUTHWEST:
            return "NORTHEAST";
        default:
            return "";
    }
}

void Pathfinding::setNewEnemyPos(Direction direction, int &px, int &py)
{
    switch (direction)
    {
        case Direction::NORTH:
            px--;
            break;
        case Direction::SOUTH:
            px++;
            break;
        case Direction::EAST:
            py++;
            break;
        case Direction::WEST:
            py--;
        case Direction::NORTHEAST:
            px--; py++;
            break;
        case Direction::NORTHWEST:
            px--; py--;
            break;
        case Direction::SOUTHEAST:
            px++; py++;
            break;
        case Direction::SOUTHWEST:
            px++; py--;
            break;
        default:
            break;
    }
}

void Pathfinding::setPreviousEnemyPos(Direction direction, int &px, int &py) {
    switch (direction)
    {
        case Direction::NORTH:
            px++;
            break;
        case Direction::SOUTH:
            px--;
            break;
        case Direction::EAST:
            py--;
            break;
        case Direction::WEST:
            py++;
            break;
        case Direction::NORTHEAST:
            px++; py--;
            break;
        case Direction::NORTHWEST:
            px++; py++;
            break;
        case Direction::SOUTHEAST:
            px--; py--;
            break;
        case Direction::SOUTHWEST:
            px--; py++;
            break;
        default:
            break;
    }
}

void Pathfinding::teleportEnemy(int &enemyX, int &enemyY, int &playerX, int &playerY) const
{
    int tempPlayerX = playerX;
    int tempPlayerY = playerY;
    Pair dest = std::make_pair(playerX, playerY);

    // Calculate all valid adjacent nodes near the player
    adjacentNodes nearNodes;
    checkAdjacentNodes(nearNodes, tempPlayerX, tempPlayerY, dest);

    adjacentNodes closestNodes;
    for(int i=0; i<nearNodes.size(); i++)
    {
        Pair currentNode = nearNodes[i];
        tempPlayerX = currentNode.first;
        tempPlayerY = currentNode.second;
        checkAdjacentNodes(closestNodes, tempPlayerX, tempPlayerY, dest);
    }

    // Initialize random generator
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, closestNodes.size()-1);

    // Teleport enemy
    Pair teleport = closestNodes[dist(rng)];
    enemyX = teleport.first;
    enemyY = teleport.second;
}

void Pathfinding::checkAdjacentNodes(adjacentNodes &cells, int px, int py, Pair dest) const
{
    // NORTH NODE
    if(nodeValidations(px-1, py, dest)){
        Pair pair = std::make_pair(px-1, py);
        addNode(cells, pair, dest);
    }

    // SOUTH NODE
    if(nodeValidations(px+1, py, dest)){
        Pair pair = std::make_pair(px+1, py);
        addNode(cells, pair, dest);
    }

    // EAST NODE
    if(nodeValidations(px, py+1, dest)){
        Pair pair = std::make_pair(px, py+1);
        addNode(cells, pair, dest);
    }

    // WEST NODE
    if(nodeValidations(px, py-1, dest)){
        Pair pair = std::make_pair(px, py-1);
        addNode(cells, pair, dest);
    }

    // NORTHEAST NODE
    if(nodeValidations(px-1, py+1, dest)){
        Pair pair = std::make_pair(px-1, py+1);
        addNode(cells, pair, dest);
    }

    // NORTHWEST NODE
    if(nodeValidations(px-1, py-1, dest)){
        Pair pair = std::make_pair(px-1, py-1);
        addNode(cells, pair, dest);
    }

    // SOUTHEAST NODE
    if(nodeValidations(px+1, py+1, dest)){
        Pair pair = std::make_pair(px+1, py+1);
        addNode(cells, pair, dest);
    }

    // SOUTHWEST NODE
    if(nodeValidations(px+1, py-1, dest)){
        Pair pair = std::make_pair(px+1, py-1);
        addNode(cells, pair, dest);
    }
}

void Pathfinding::addNode(adjacentNodes &cells, Pair &pair, Pair &dest)
{
    if(!cells.contains(pair) && pair!=dest){
        cells.push_back(pair);
    }
}

void Pathfinding::printAstar(Node (*nodeDetails)[10], Pair &dest, listDirections &shortestPath)
{
    ce::log("The destination cell is found");
    ce::log("The path is");

    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;

    while(!(nodeDetails[row][col].getPx() == row && nodeDetails[row][col].getPy() == col))
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

    std::string result = "Route to the player (A*): ";
    for(int i=0; i<shortestPath.size(); i++)
    {
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
    ce::log(stringForm);
}

void Pathfinding::printBreadcrumbs(listDirections &breadcrumbs)
{
    std::string result = "Breadcrumbs: ";
    if(!breadcrumbs.empty()){
        for(int i=0; i<breadcrumbs.size(); i++)
        {
            if(breadcrumbs[i] == Direction::NORTH){
                result += "NORTH <- ";
            }
            else if(breadcrumbs[i] == Direction::SOUTH){
                result += "SOUTH <- ";
            }
            else if(breadcrumbs[i] == Direction::EAST){
                result += "EAST <- ";
            }
            else if(breadcrumbs[i] == Direction::WEST){
                result += "WEST <- ";
            }
            else if(breadcrumbs[i] == Direction::NORTHEAST){
                result += "NORTHEAST <- ";
            }
            else if(breadcrumbs[i] == Direction::NORTHWEST){
                result += "NORTHWEST <- ";
            }
            else if(breadcrumbs[i] == Direction::SOUTHEAST){
                result += "SOUTHEAST <- ";
            }
            else if(breadcrumbs[i] == Direction::SOUTHWEST){
                result += "SOUTHWEST <- ";
            }
        }
        std::string stringForm = result.substr(0,result.size()-3);
        ce::log(stringForm);
        ce::log("\n");
    }
    else{
        result += "[]";
        ce::log(result);
    }
}

void Pathfinding::printLineSight(listDirections &line)
{
    std::string result = "Line Sight: ";
    if(!line.empty()){
        for(int i=0; i<line.size(); i++)
        {
            if(line[i] == Direction::NORTH){
                result += "NORTH -> ";
            }
            else if(line[i] == Direction::SOUTH){
                result += "SOUTH -> ";
            }
            else if(line[i] == Direction::EAST){
                result += "EAST -> ";
            }
            else if(line[i] == Direction::WEST){
                result += "WEST -> ";
            }
            else if(line[i] == Direction::NORTHEAST){
                result += "NORTHEAST -> ";
            }
            else if(line[i] == Direction::NORTHWEST){
                result += "NORTHWEST -> ";
            }
            else if(line[i] == Direction::SOUTHEAST){
                result += "SOUTHEAST -> ";
            }
            else if(line[i] == Direction::SOUTHWEST){
                result += "SOUTHWEST -> ";
            }
        }
        std::string stringForm = result.substr(0,result.size()-3);
        ce::log(stringForm);
    }
    else{
        result += "[]";
        ce::log(result);
    }
}

void Pathfinding::setLineSight(adjacentNodes &nodes, listDirections &line)
{
    line.clear();
    for(int i=0; i<nodes.size(); i++)
    {
        if(i+1 != nodes.size()){
            Pair src = nodes[i];
            Pair dest = nodes[i+1];
            line.push_back(setMovement(src.first, src.second, dest.first, dest.second));
        }
    }
}

listDirections Pathfinding::AstarSearch(Pair src, Pair dest) const
{
    // List of directions to follow between the enemy's position and the
    // player's position
    listDirections shortestPath;

    // If the source is out of range
    if(!isValid(src.first, src.second)){
        ce::log("\nSource is invalid");
        return shortestPath;
    }

    //If the destination is out of range
    if(!isValid(dest.first, dest.second)){
        ce::log("\nDestination is invalid");
        return shortestPath;
    }

    // Either the source or the destination is blocked
    if(!isUnBlocked(src.first, src.second) || !isUnBlocked(dest.first, dest.second)){
        ce::log("\nSource or the destination is blocked");
        return shortestPath;
    }

    // If the destination node is the same as source node
    if(isDestination(src.first, src.second, dest)){
        ce::log("\nWe already at the destination");
        return shortestPath;
    }

    // Closed list and initialized false cause the node has not been included yet
    // The closed list is implemented as a boolean 2D array
    bool closedList[ROWS][COLS];
    memset(closedList, false, sizeof(closedList));

    // 2D array to hold the details of nodes
    Node nodeDetails[ROWS][COLS];

    int i, j;

    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
                printAstar(nodeDetails, dest, shortestPath);
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
        ce::log("Failed to find the destination node");
    }

    return shortestPath;
}

listDirections Pathfinding::LineSight(Pair src, Pair dest)
{
    // If the source is out of range
    if(!isValid(src.first, src.second)){
        ce::log("\nSource is invalid");
        return line;
    }

    //If the destination is out of range
    if(!isValid(dest.first, dest.second)){
        ce::log("\nDestination is invalid");
        return line;
    }

    // Either the source or the destination is blocked
    if(!isUnBlocked(src.first, src.second) || !isUnBlocked(dest.first, dest.second)){
        ce::log("\nSource or the destination is blocked");
        return line;
    }

    // If the destination node is the same as source node
    if(isDestination(src.first, src.second, dest)){
        ce::log("\nWe already at the destination");
        return line;
    }

    int dx = abs(dest.first - src.first);
    int dy = abs(dest.second - src.second);

    int sx = src.first < dest.first ? 1 : -1;
    int sy = src.second < dest.second ? 1 : -1;

    int err = dx - dy;
    int e2;
    int currentX = src.first;
    int currentY = src.second;
    int previousX = currentX;
    int previousY = currentY;

    while(true)
    {
        if(!isUnBlocked(currentX, currentY)){
            Pair newSrc = bestAdjacentNode(previousX, previousY, dest);
            currentX = newSrc.first;
            currentY = newSrc.second;
            LineSight(newSrc, dest);
            break;
        }

        if(currentX == dest.first && currentY == dest.second){
            nodes.push_back(std::make_pair(currentX, currentY));
            setLineSight(nodes, line);
            return line;
        }

        nodes.push_back(std::make_pair(currentX, currentY));

        previousX = currentX;
        previousY = currentY;

        e2 = 2 * err;
        if(e2 > -1 * dy){
            err = err - dy;
            currentX = currentX + sx;
        }

        if(e2 < dx){
            err = err + dx;
            currentY = currentY + sy;
        }
    }

    return line;
}

Pair Pathfinding::bestAdjacentNode(int &px, int &py, Pair &dest) const
{
    std::set<pPair> adjNodes;

    // NORTH NODE
    if(isValid(px-1, py) && isUnBlocked(px-1, py)){
        int H = ManhattanDistance(px-1, py, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px - 1, py)));
    }

    // SOUTH NODE
    if(isValid(px+1, py) && isUnBlocked(px+1, py)){
        int H = ManhattanDistance(px+1, py, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px + 1, py)));
    }

    // EAST NODE
    if(isValid(px, py+1) && isUnBlocked(px, py+1)){
        int H = ManhattanDistance(px, py+1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px, py + 1)));
    }

    // WEST NODE
    if(isValid(px, py-1) && isUnBlocked(px, py-1)){
        int H = ManhattanDistance(px, py-1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px, py - 1)));
    }

    // NORTHEAST NODE
    if(isValid(px-1, py+1) && isUnBlocked(px-1, py+1)){
        int H = ManhattanDistance(px-1, py+1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px - 1, py + 1)));
    }

    // NORTHWEST NODE
    if(isValid(px-1, py-1) && isUnBlocked(px-1, py-1)){
        int H = ManhattanDistance(px-1, py-1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px - 1, py - 1)));
    }

    // SOUTHEAST NODE
    if(isValid(px+1, py+1) && isUnBlocked(px+1, py+1)){
        int H = ManhattanDistance(px+1, py+1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px + 1, py + 1)));
    }

    // SOUTHWEST NODE
    if(isValid(px+1, py-1) && isUnBlocked(px+1, py-1)){
        int H = ManhattanDistance(px+1, py-1, dest);
        adjNodes.insert(std::make_pair(H, std::make_pair(px + 1, py - 1)));
    }

    pPair temp = std::make_pair(INT_MAX, std::make_pair(0,0));
    for(int i=0; i < adjNodes.size(); i++){
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

int Pathfinding::ManhattanDistance(int px, int py, Pair dest)
{
    return abs(px - dest.first) + abs(py - dest.second);
}




