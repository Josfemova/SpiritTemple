#ifndef GAMESERVER_LEVEL_HPP
#define GAMESERVER_LEVEL_HPP
#define ROW 9
#define COL 10

#include "include/list.hpp"
#include "include/Item.hpp"
#include "include/Enemy.hpp"
#include "include/nlohmannJson.hpp"

typedef ce::list<std::string> lvlInstructions;
typedef std::pair<int, int> Pair;
typedef int(&matrix)[ROW][COL];

using json = nlohmann::json;

class Level {
private:
    int lives;
    int playerID;
    int playerX;
    int playerY;

    json obstacles;
    ce::list<Item> items;
    ce::list<Enemy> enemies;
    
    json instructions;

public:
    Level();
    void finish();
    void start();

    // Returns a level matrix with "0" representing obstacles and safe areas
    // (where the enemy can't walk) and "1" which is where the enemy can walk
    matrix getSimpleMatrix();

    // Manage the events, for each event add an instruction
    void manageEvents(json events);

    // Return all instructions added by manageEvent
    json getInstructions();
};


#endif //GAMESERVER_LEVEL_HPP
