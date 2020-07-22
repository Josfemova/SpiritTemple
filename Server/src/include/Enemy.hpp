#ifndef GAMESERVER_ENEMY_HPP
#define GAMESERVER_ENEMY_HPP

#include "MoveGenerator.hpp"
#include "EnemyType.hpp"
#include "Direction.hpp"
#include "Level.hpp"
#include <memory>

class Level;
class Enemy : public GameObject{
private:
    friend class Level;
    std::shared_ptr<Level> parent;
    EnemyType enemyType;
    double route_velocity;
    double chase_velocity;
    double visibility_radius;
    int lastDefaultPos = -1; //starts before first movement in list 
    bool isBackTrackDefault = false;
    int damageDone;
    bool inRange = false;
    bool isChasing = false;
    bool isBacktracking = false;
    bool isTeleported = false;
    Pair teleportation;
    listDirections normalPath;
    listDirections breadcrumbs;
    listDirections chasePath;
    void setEnemyType(std::string& type);

public:
    Enemy(int id, int py, int px, std::string& type);
    void activate(std::shared_ptr<Level> parent);
    void updateData(int py, int px, int damage, bool range);

    void setRouteVelocity(double routeVel);
    void setChaseVelocity(double chaseVel);
    void setVisibilityRadius(double radius);

    void setDamage(int damage);
    void setInRange(bool range);
    void setChasing(bool chase);

    Pair enemyPos() const;
    double getRouteVelocity() const;
    double getChaseVelocity() const;
    double getVisibilityRadius() const;

    int getDamage() const;
    bool isInRange() const;
    bool playerIsSafe() const;

    EnemyType getEnemyType();
    std::string getTypeS();

    void refreshState();
    void groupCall();
    std::string update();

    //Movement functions are owned by Movement Generator
};

#endif //GAMESERVER_ENEMY_HPP
