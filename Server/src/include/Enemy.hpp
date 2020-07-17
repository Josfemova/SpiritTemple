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
    bool inRange;
    bool isChasing=false;
    bool isBacktracking = false;
    int notChasingIndex;
    listDirections normalPath;
    listDirections breadcrumbs;
    listDirections chasePath;
    void setEnemyType(std::string& type);

public:
    Enemy(int id, int px, int py, std::string& type);
    void updateData(int px, int py, int damage, bool range);
    void setRouteVelocity(float routeVel);
    void setChaseVelocity(float chaseVel);
    void setVisibilityRadius(float radius);
    void setDamage(int damage);
    void setInRange(bool range);
    std::string toString();
    Pair enemyPos() const;
    float getRouteVelocity() const;
    float getChaseVelocity() const;
    float getVisibilityRadius() const;
    int getDamage() const;
    bool isInRange() const;

    EnemyType getEnemyType();
    std::string getTypeS();

    std::string update();
    void refreshState(); //el mae calcula los paths
    void groupCall();
    // Initial methods
    void generatRandomPath(){
        //guardar index

    } // se llama al princio

    //utilities
    std::string getNextMovement(Direction direction);
    std::string getPreviousMovement(Direction direction);


};

#endif //GAMESERVER_ENEMY_HPP
