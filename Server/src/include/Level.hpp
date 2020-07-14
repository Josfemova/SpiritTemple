#ifndef GAMESERVER_LEVEL_HPP
#define GAMESERVER_LEVEL_HPP
#define ROW 9
#define COL 10

#include "Item.hpp"
#include "Enemy.hpp"
#include "list.hpp"
#include "nlohmannJson.hpp"

typedef ce::list<std::string> lvlInstructions;
typedef std::pair<int, int> Pair;
typedef int(&matrix)[ROW][COL];

using json = nlohmann::json;


//remove after corrections
class Enemy;
class Item;
class Level {
private:
    int lengthx;
    int lengthy;
    json playerInfo;
    json obstacles;
    json instructions;
    ce::list<Item> items;
    ce::list<Enemy> enemies;
    
    
public:
    Level(json playerInfo, json obstacles, json items, json enemies);
    void finish();
    void start();

    // Returns a level matrix with "0" representing obstacles and safe areas
    // (where the enemy can't walk) and "1" which is where the enemy can walk
    matrix getSimpleMatrix();
    //temporal. replicates upper functionality but based on json info
    void getMatrix();
    // Manage the events, for each event add an instruction
    void manageEvents(json events);

    // Return all instructions added by manageEvent
    json getInstructions();
};


#endif //GAMESERVER_LEVEL_HPP
