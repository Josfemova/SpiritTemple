#include "include/Level.hpp"
#include "include/ItemType.hpp"
#include "include/GameObject.hpp"

Level::Level(json playerInfo, json obstacles, json items, json enemies, int lengthx, int lengthy):
lengthx{lengthx}, lengthy{lengthy}
{
    this->playerInfo = playerInfo;
    this->obstacles = obstacles;
    int player[3] = {playerInfo["player"]["ID"], playerInfo["player"]["gridx"], playerInfo["player"]["gridy"]};
    id = player[0];
    playerx = player[1];
    playery = player[2];
    std::string type;
    for(auto x:items){
        type = x["type"];
        Item y{Item::getItemType(type),x["ID"],x["gridx"],x["gridy"]};
        this->items.push_back(y);
    }
    for(auto x:enemies){
        type = x["type"];
        Enemy y{x["ID"],x["gridx"],x["gridy"],type};
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
ce::list<ce::list<int>> Level::getSimpleMatrix(){
    ce::list<ce::list<int>> simpleMatrix;
    //initialize list
    for (int i = 0; i < lengthy; i++){
        ce::list<int> y(1, lengthx);
        simpleMatrix.push_back(y);
    }
    int x;
    int y;
    for(auto obs: obstacles){
        x = obs["gridx"];
        y = obs["gridy"];
        simpleMatrix[y][x] = 0;
    }
    for(auto item: items){
        x = item.getX();
        y = item.getY();
        simpleMatrix[y][x] = 0;
    }
    for(auto enemy: enemies){
        x = enemy.getX();
        y = enemy.getY();
        simpleMatrix[y][x] = 0;
    }

    ce::list<ce::list<int>> inverted;
    for(auto fila: simpleMatrix){
        inverted.push_front(fila);
    }
    for(auto fila : inverted){
        ce::debuglog(fila.toString());
    }
    return simpleMatrix;
    
}
void Level::triggerGroupCall(int id){
    {
        for (auto enemy : enemies){
            if(enemy.getID()!=id){
                enemy.setChasing(true);
                enemy.groupCall();
            }
        }
    }
}

json Level::getInstructions() {
    return json();
}

Pair Level::playerPos() const
{
    return std::make_pair(playery, playerx);
}

