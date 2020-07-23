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
class Enemy : public GameObject{
private:
    friend class Level;
    friend class GeneticLab;
    std::shared_ptr<Level> parent;
    EnemyType enemyType;
    int route_velocity = 5;
    int chase_velocity = 5;
    int frameCount;
    int visibility_radius=2;
    int lastDefaultPos = -1; //starts before first movement in list 
    bool isBackTrackDefault = false;
    int damageDone=0;
    bool inRange = false;
    bool isChasing = false;
    bool isBacktracking = false;
    bool isTeleported = false;
    Pair teleportation; //position from which enemy teleported
    listDirections normalPath;
    listDirections breadcrumbs;
    listDirections chasePath;
    void setEnemyType(std::string& type);
public:
    Enemy(int id, int py, int px, std::string& type);
    void activate(std::shared_ptr<Level> parent);
    void setDamage(int damage);
    void setChasing(bool chase);
    Pair enemyPos() const;
    int getDamage() const;
    bool playerInRange() const;
    bool playerIsSafe() const;
    EnemyType getEnemyType();
    std::string getTypeS();
    void refreshState();
    void groupCall();
    void update();

    //Movement functions are owned by Movement Generator
};

#endif //GAMESERVER_ENEMY_HPP
