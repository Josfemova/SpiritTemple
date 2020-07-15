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
ce::list<ce::list<int>> Level::getSimpleMatrix(){
    ce::list<ce::list<int>> simpleMatrix;
    //initialize list
    for (int i = 0; i < lengthy; i++){
        ce::list<int> x(1, lengthx);
        simpleMatrix.push_back(x);
    }
    int x;
    int y;
    for(auto x: obstacles){
        int i = x["gridx"];
        int j = x["gridy"];
        simpleMatrix[i][j] = 0;
    }
    /*
    for(auto x: enemies){

    }
    ce::list<Enemy> tempEnemies = enemies;
    while (!tempEnemies.empty())
    {
        Enemy x = tempEnemies.pop_back();
        const int i = x.getX();
        const int j = x.getX();
        A[i][j] = 0;
    }*/
    return simpleMatrix;
    
}
void Level::triggerGroupCall(int id){
    {
        //for(){
            enemies[0].groupCall();
        //}
    }
}

