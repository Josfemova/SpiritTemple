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
    Pathfinding pathfinding(matrix);
    Pair enemyPos = std::make_pair(0, 0);
    Pair playePos = std::make_pair(7, 0);
    listDirections path = pathfinding.RandomPath(enemyPos, playePos, 3);

    std::cout << "Size: " << path.size() << std::endl;

    for (int i = 0; i < path.size(); i++)
    {
        Direction direction = path[i];
        switch (direction)
        {
        case Direction::NORTH:
            std::cout << "NORTH -> ";
            break;
        case Direction::SOUTH:
            std::cout << "SOUTH -> ";
            break;
        case Direction::EAST:
            std::cout << "EAST -> ";
            break;
        case Direction::WEST:
            std::cout << "WEST -> ";
            break;
        case Direction::NORTHEAST:
            std::cout << "NORTHEAST -> ";
            break;
        case Direction::NORTHWEST:
            std::cout << "NORTHWEST -> ";
            break;
        case Direction::SOUTHEAST:
            std::cout << "SOUTHEAST -> ";
            break;
        case Direction::SOUTHWEST:
            std::cout << "SOUTHWEST -> ";
            break;
        default:
            break;
        }
    }
    return 0;
}
