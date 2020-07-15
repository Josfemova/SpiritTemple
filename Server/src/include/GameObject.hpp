#ifndef GAMESERVER_GAMEOBJECT_HPP
#define GAMESERVER_GAMEOBJECT_HPP

#include <string>
#include "GOType.hpp"

class GameObject {
private:
    GOType type;
    int gridx;
    int gridy;
    int id;
public:
    GOType getType();
    GameObject(){};
    explicit GameObject(GOType type,int id, int px, int py): type{type}, id{id}, gridx{px}, gridy{py} {}
    int getX() const { return gridx;}
    void setX(int value) { gridx = value; }
    int getY() const { return gridy;}
    void setY(int value) { gridy = value; }
    int getID() const { return id;}
    void setID(int value) { id = value; }
};


#endif //GAMESERVER_GAMEOBJECT_HPP
