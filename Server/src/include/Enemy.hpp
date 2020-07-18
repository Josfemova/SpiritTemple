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
    std::shared_ptr<Level> parent;
    EnemyType enemyType;
    float route_velocity;
    float chase_velocity;
    float visibility_radius;
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
    void updateData(int py, int px, int damage, bool range);
    void generateRandomPath(int size); //To normalPath, save the index...

    void setRouteVelocity(float routeVel);
    void setChaseVelocity(float chaseVel);
    void setVisibilityRadius(float radius);

    void setDamage(int damage);
    void setInRange(bool range);
    void setChasing(bool chase);

    Pair enemyPos() const;
    float getRouteVelocity() const;
    float getChaseVelocity() const;
    float getVisibilityRadius() const;

    int getDamage() const;
    bool isInRange() const;
    bool playerIsSafe() const;

    EnemyType getEnemyType();
    std::string getTypeS();

    void refreshState();
    void groupCall();
    std::string update();

    std::string getNextMovement(Direction direction);
    std::string getPreviousMovement(Direction direction);
};

#endif //GAMESERVER_ENEMY_HPP
