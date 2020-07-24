#ifndef GAMESERVER_ENEMY_HPP
#define GAMESERVER_ENEMY_HPP

#include "MoveGenerator.hpp"
#include "EnemyType.hpp"
#include "GeneticLab.hpp"
#include "Direction.hpp"
#include "Level.hpp"
#include <memory>
using json = nlohmann::json;
class Level;
/**
 * @brief Representation of enemy game objects
 * 
 */
class Enemy : public GameObject{
private:
    friend class Level;
    friend class GeneticLab;
    std::shared_ptr<Level> parent;
    EnemyType enemyType;
    int route_velocity = 5;
    int chase_velocity = 5;
    int frameCount;
    int visibility_radius=2; //how much can the enemy look ahead
    int lastDefaultPos = -1; //starts before first movement in list 
    bool isBackTrackDefault = false;
    int damageDone=0;
    bool inRange = false;
    bool isChasing = false;
    bool isBacktracking = false;
    bool isTeleported = false;
    Pair teleportDest;
    Pair teleportSrc; //position from which enemy teleported
    listDirections normalPath;
    listDirections breadcrumbs;
    listDirections chasePath;
    void setEnemyType(std::string& type);
public:
    /**
     * @brief Construct a new Enemy object based on the YX coordinates 
     * 
     * @param id id of the game object in the game engine
     * @param py y coordinate of enemy
     * @param px x coordinate of enemy
     * @param type string containing an EnemyType value
     */
    Enemy(int id, int py, int px, std::string& type);
    /**
     * @brief Generates initial normal path pathfinding in most enemies, 
     * sets initial state for all enemies
     * 
     * @param parent 
     */
    void activate(std::shared_ptr<Level> parent);

    
    void setDamage(int damage);
    /**
     * @brief Flags enemy in chasing state, increased speed 
     * 
     * @param chase 
     */
    void setChasing(bool chase);
    /**
     * @brief returns enemyPosition as a X,Y <int,int> pair
     * 
     * @return Pair 
     */
    Pair enemyPos() const;
    /**
     * @brief Get the Damage objectgets how many times an spectrum was able to hit the player
     * 
     * @return int 
     */
    int getDamage() const;

    /**
     * @brief checks if the player is in the visibility range of the enemy
     * 
     * @return true 
     * @return false 
     */
    bool playerInRange() const;
    /**
     * @brief check if player is in a bolcked location
     * 
     * @return true 
     * @return false 
     */
    bool playerIsSafe() const;
    /**
     * @brief Get the Enemy Type
     * 
     * @return EnemyType 
     */
    EnemyType getEnemyType();
    std::string getTypeS();
    /**
     * @brief enemy will check again if the current conditions remain the same, or they need to be adjusted
     * 
     */
    void refreshState();
    /**
     * @brief Defines what an enemy does in case one enemy triggers an alert
     * 
     */
    void groupCall();
    /**
     * @brief pops the next movement from the movement queue
     * 
     */
    void update();

    //Movement functions are owned by Movement Generator
};

#endif //GAMESERVER_ENEMY_HPP
