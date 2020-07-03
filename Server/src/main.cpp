#include <iostream>
#include "include/MoveGenerator.hpp"

int main()
{
    std::cout<<"Hello world"<<std::endl;

    //Level matrix
    int matrix[9][10] =
            {
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                    { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
            };

    MoveGenerator moveGenerator(matrix);
    Pair src = std::make_pair(8, 0); // Enemy position
    Pair dest = std::make_pair(0, 0); // Player position

    ce::list<Direction> path; // Shortest path from enemy position to player position
    path = moveGenerator.getRoute(src, dest, RouteType::Astar);

    return 0;
}
