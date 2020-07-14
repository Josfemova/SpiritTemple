#ifndef GAMESERVER_GAMEOBJECT_HPP
#define GAMESERVER_GAMEOBJECT_HPP

#include <string>
#include "GOType.hpp"

class GameObject {
private:
    GOType type;
    int gridx;
    int gridy;
public:
    GOType getType();
    GameObject(){};
    explicit GameObject(GOType type): type{type} {}
    int getX() const { return gridx;}
    void setX(int value) { gridx = value; }
    int getY() const { return gridy;}
    void setY(int value) { gridy = value; }
};


#endif //GAMESERVER_GAMEOBJECT_HPP
