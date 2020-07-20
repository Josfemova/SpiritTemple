#include "include/Level.hpp"
#include "include/ItemType.hpp"
#include "include/GameObject.hpp"

Level::Level(json playerInfo, json obstacles, json items, json enemies, int lengthx, int lengthy) : lengthx{lengthx}, lengthy{lengthy}
{
    this->playerInfo = playerInfo;
    this->obstacles = obstacles;
    id = playerInfo["ID"];
    playerx = playerInfo["gridx"];
    playery = playerInfo["gridy"];

    std::string type;
    for (auto x : items)
    {
        type = x["type"];
        Item y{Item::getItemType(type), x["ID"], x["gridx"], x["gridy"]};
        this->items.push_back(y);
    }
    for (auto x : enemies)
    {
        type = x["type"];
        Enemy y{x["ID"], x["gridx"], x["gridy"], type};
        this->enemies.push_back(y);
    }
}

void Level::start()
{
    //Do something
}

void Level::finish()
{
    //Do something
}

/* TODO */
ce::list<ce::list<int>> Level::getSimpleMatrix()
{
    ce::list<ce::list<int>> simpleMatrix;
    for (int i = 0; i < lengthy; i++)
    {
        ce::list<int> y(1, lengthx);
        simpleMatrix.push_back(y);
    }
    int x;
    int y;
    ce::debuglog("obs");
    for (auto obs : obstacles)
    {
        x = obs["gridx"];
        y = obs["gridy"];
        simpleMatrix[y][x] = 0;
    }
    if (!items.empty())
    {
        for (auto item : items)
        {
            x = item.getX();
            y = item.getY();
            simpleMatrix[y][x] = 0;
        }
    }
    if (!enemies.empty())
    {
        for (auto enemy : enemies)
        {
            x = enemy.getX();
            y = enemy.getY();
            simpleMatrix[y][x] = 0;
        }
    }
    //
    //
    //
    //
    simpleMatrix[playery][playerx] = 2;
    //
    //
    //
    ce::list<ce::list<int>> inverted;
    for (auto fila : simpleMatrix)
    {
        inverted.push_front(fila);
    }
    for (auto fila : inverted)
    {
        ce::debuglog(fila.toString());
    }
    return simpleMatrix;
}
void Level::manageEvent(json event)
{
    std::string cmd(event["cmd"]);

    if (cmd == "move-player")
    {
        playerx += event["valA"];
        playery += event["vaklB"];
        
    }
    else if (cmd == "attack-enemy")
    {
        int enemyID = event[1];

    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "movePlayer")
    {
    }
    /*for(auto x : enemies){
        x.update();
    }*/
}
void Level::triggerGroupCall(int id)
{
    {
        for (auto enemy : enemies)
        {
            if (enemy.getID() != id)
            {
                enemy.setChasing(true);
                enemy.groupCall();
            }
        }
    }
}
json Level::getInstructions()
{
    return json();
}
Pair Level::playerPos() const
{
    return std::make_pair(playery, playerx);
}
