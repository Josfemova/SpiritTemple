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
    json obstacles;
    json instructions;
    ce::list<Item> items;
    ce::list<Enemy> enemies;
public:
    const int lengthx;
    const int lengthy;
    Level(json playerInfo, json obstacles, json items, json enemies, int lengthx, int lengthy);
    void finish();
    void start(std::shared_ptr<Level> level);
    ce::list<ce::list<int>> getSimpleMatrix();
    void manageEvent(json event);
    void triggerGroupCall(int id);
    json getInstructions();
    Pair playerPos() const;
};


#endif //GAMESERVER_LEVEL_HPP
