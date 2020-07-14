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
    Game a;
    std::ifstream t("/home/jose/Desktop/githubU/SpiritTemple/Extra/initialData.json");
    std::stringstream buffer;
    buffer << t.rdbuf();
    //
    std::string response(a.startLevel(buffer.str()));
    ce::debuglog(response);

    // Simple level matrix
    int matrix[9][10] =
        {
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
            {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}};
    /*
    // ADAPTING ENEMY CLASS FOR TESTING (THE PLAYER'S METHODS
    // DON'T BELONG TO HIM) BUT IT'S JUST FOR TESTING NOW
    Enemy enemy1(1, 8, 0, "SpGray");
    Enemy enemy2(2, 7, 5, "SpBlue");
    Enemy enemy3(3, 1, 0, "Chuchu");
    enemy1.setMatrix(matrix);
    enemy1.setInRange(true);
    enemy1.setPlayer(1,2);

    enemy2.setMatrix(matrix);
    enemy2.setInRange(true);
    enemy2.setPlayer(1,2);

    enemy3.setMatrix(matrix);
    enemy3.setInRange(true);
    enemy3.setPlayer(1,2);

    // Testing A* and BreadCrumbing for SpGray or SpRed
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

    // Testing LineSight for Chuchu
    enemy3.setPlayer(4,5);
    while (enemy3.enemyPos() != enemy3.playerPos()){
        enemy3.update();
        sleep(1);
    }
    */
    return 0;
}
