#ifndef GAMESERVER_LEVEL_HPP
#define GAMESERVER_LEVEL_HPP

#include "list.hpp"
#include "nlohmannJson.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

typedef ce::list<std::string> lvlInstructions;
typedef std::pair<int, int> Pair;
using json = nlohmann::json;

class Enemy;
class Item;
class Level {
private:
    int id;
    int playerx;
    int playery;
    int lengthx;
    int lengthy;
    json playerInfo;
    json obstacles;
    json instructions;
    ce::list<Item> items;
    ce::list<Enemy> enemies;
public:
    Level(json playerInfo, json obstacles, json items, json enemies, int lengthx, int lengthy);
    void finish();
    void start();

    // Returns a level matrix with "0" representing obstacles and safe areas
    // (where the enemy can't walk) and "1" which is where the enemy can walk
    ce::list<ce::list<int>> getSimpleMatrix();

    // Manage the events, for each event add an instruction
    void manageEvent(json event){
        //muevo jugador
        if(event["reqType"] == "movePlayer"){
            //muevo al jugador   
        }

        //le digo a cada enemigo que haga refresh
                //for violento


        //enemigo.update()
    }

    void triggerGroupCall(int id);

    // Return all instructions added by manageEvent
    json getInstructions();

    Pair playerPos() const;
};


#endif //GAMESERVER_LEVEL_HPP
