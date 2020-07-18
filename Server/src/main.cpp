#include <iostream>
#include "include/MoveGenerator.hpp"
#include "include/Level.hpp"
#include "include/Enemy.hpp"
#include <unistd.h>
#include "include/Server.hpp"
#include <memory>

int serverStart()
{
    std::unique_ptr<Server> gameServer(new Server(3000));
    return 0;
}

//ENEMY HAS THIS METHODS SO NO PROBLEM
std::string getNextMovement(Direction direction);
std::string getPreviousMovement(Direction direction);
void printBreadcrumbs(listDirections &directions);

int main()
{
    //serverStart();
    /*Game a;
    std::ifstream t("/home/jose/Desktop/githubU/SpiritTemple/Extra/initialData.json");
    std::stringstream buffer;
    buffer << t.rdbuf();
    //
    std::string response(a.startLevel(buffer.str()));
    ce::debuglog(response);*/


    // Simple level matrix
    ce::list<int> a{1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
    ce::list<int> b{1, 1, 1, 0, 1, 1, 1, 0, 1, 1};
    ce::list<int> c{1, 1, 1, 0, 1, 1, 0, 1, 0, 1};
    ce::list<int> d{0, 0, 1, 0, 1, 0, 0, 0, 0, 1};
    ce::list<int> e{1, 1, 1, 0, 1, 1, 1, 0, 1, 0};
    ce::list<int> f{1, 0, 1, 1, 1, 1, 0, 1, 0, 0};
    ce::list<int> g{1, 0, 0, 0, 0, 1, 0, 0, 0, 1};
    ce::list<int> h{1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
    ce::list<int> i{1, 1, 1, 0, 0, 0, 1, 0, 0, 1};
    gmatrix matrix{a,b,c,d,e,f,g,h,i};

    ce::list<ce::list<int>> inverted;
    for(auto fila: matrix){
        inverted.push_front(fila);
    }

    for(auto fila : inverted){
        ce::debuglog(fila.toString());
    }

    Pathfinding pathfinding(matrix);

    Pair src = std::make_pair(0,0); // Enemy position
    Pair dest = std::make_pair(0, 4); // Player position
    //std::cout<<"("<<std::to_string(src.first)<<","<<std::to_string(src.second)<<")"<<std::endl;

    return 0;
}

std::string getNextMovement(Direction direction)
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

std::string getPreviousMovement(Direction direction)
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

void printBreadcrumbs(listDirections &breadcrumbs)
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
