#include <iostream>
#include "include/MoveGenerator.hpp"
#include "include/Level.hpp"
#include "include/Enemy.hpp"
#include <unistd.h>

int main()
{

    // Simple level matrix
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

    // ADAPTING ENEMY CLASS FOR TESTING (THE PLAYER'S METHODS
    // DON'T BELONG TO HIM) BUT IT'S JUST FOR TESTING NOW
    Enemy enemy1(1, 8, 0, "SpGray");
    Enemy enemy2(2, 7, 5, "SpBlue");
    enemy1.setMatrix(matrix);
    enemy1.setPlayer(1,2);
    enemy1.setInRange(true);

    enemy2.setMatrix(matrix);
    enemy2.setInRange(true);
    enemy2.setPlayer(1,2);

    // Testing A* and BreadCrumbing in for SpGray or SpRed
    while (enemy1.enemyPos() != enemy1.playerPos()){
        enemy1.update();
        sleep(1);
    }

    enemy1.setInRange(false);
    // Testing Backtracking for SpGray or SpRed
    while (!enemy1.getBreadCrumbs().empty()){
        enemy1.update();
        sleep(1);
    }

    // Testing Teleportation for SpBlue
    enemy2.update();

    return 0;
}
