#ifndef GAMESERVER_GAMEOBJECT_HPP
#define GAMESERVER_GAMEOBJECT_HPP

#include <string>
#include "GOType.hpp"


/**
 * @brief general class to represent game objects
 * 
 */
class GameObject {
private:
    GOType type;
    int gridy;
    int gridx;
    int id;
public:
    GameObject()= default;
    GOType getType();
    explicit GameObject(GOType type,int id, int py, int px);
    int getY() const;
    void setY(int value);
    int getX() const;
    void setX(int value);
    int getID() const;
    void setID(int value);
};


#endif //GAMESERVER_GAMEOBJECT_HPP
