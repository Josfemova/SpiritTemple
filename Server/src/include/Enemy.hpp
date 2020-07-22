#ifndef GAMESERVER_ENEMY_HPP
#define GAMESERVER_ENEMY_HPP

#include "MoveGenerator.hpp"
#include "EnemyType.hpp"
#include "Direction.hpp"
#include "Level.hpp"
#include <memory>
using json = nlohmann::json;
class Level;
class Enemy : public GameObject{
private:
    friend class Level;
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




    void updateData(int py, int px, int damage, bool range);

    void setRouteVelocity(int routeVel);
    void setChaseVelocity(int chaseVel);
    void setVisibilityRadius(int radius);

    void setDamage(int damage);
    void setInRange(bool range);
    void setChasing(bool chase);

    Pair enemyPos() const;
    int getRouteVelocity() const;
    int getChaseVelocity() const;
    int getVisibilityRadius() const;

    int getDamage() const;
    bool isInRange() const;
    bool playerIsSafe() const;

    EnemyType getEnemyType();
    std::string getTypeS();

    void refreshState();
    void groupCall();
    void update();

    //Movement functions are owned by Movement Generator
};

#endif //GAMESERVER_ENEMY_HPP
