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
    /**
     * @brief Construct a new Game Object object
     * 
     */
    GameObject()= default;
    /**
     * @brief Get the GameObject type
     * 
     * @return GOType 
     */
    GOType getType();
    /**
     * @brief Initialize a new GameObject with the given parameters
     * 
     * @param type Game object type
     * @param id if in the game engine
     * @param py y coordinates of enemy
     * @param px x coordinates of enemy
     */
    explicit GameObject(GOType type,int id, int py, int px);
    int getY() const;
    /**
     * @brief get the Y coordinate position
     * 
     * @param value 
     */
    void setY(int value);
    /**
     * @brief set the Y coordinate position
     * 
     * @return int 
     */
    int getX() const;
    /**
     * @brief get the X coordinate position
     * 
     * @param value 
     */
    void setX(int value);
    /**
     * @brief get the ID of the object 
     * 
     * @return int 
     */
    int getID() const;
};


#endif //GAMESERVER_GAMEOBJECT_HPP
