#include "include/Level.hpp"
#include "include/ItemType.hpp"
#include "include/GameObject.hpp"

Level::Level(json playerInfo, json obstacles, json items, json enemies)
{
    this->playerInfo = playerInfo;
    this->obstacles = obstacles;
    for(auto x:items){
        Item y{Item::getItemType(x["type"])};
        this->items.push_back(y);
    }
    for(auto x:enemies){
        Enemy y{x["ID"],x["gridx"],x["gridy"],x["type"]};
        this->enemies.push_back(y);
    }

}

/* TODO */
void Level::getMatrix(){
    /*Needs refining
    ce::list<ce::list<int>> A;
    for(int i=0; i<lengthx; i++){
        for(int j=0; j<lengthy; j++){
            A[i][j] =  1;
        }
    }
    for(auto x: obstacles){
        int i = x["gridx"];
        int j = x["gridy"];
        A[i][j] = 0;
    }
    ce::list<Item> tempItems = items;
    while (!tempItems.empty())
    {
        Item x = tempItems.pop_back();
        const int i = x.getX();
        const int j = x.getX();
        A[i][j] = 0;
    }
    ce::list<Enemy> tempEnemies = enemies;
    while (!tempEnemies.empty())
    {
        Enemy x = tempEnemies.pop_back();
        const int i = x.getX();
        const int j = x.getX();
        A[i][j] = 0;
    }*/
    
}


