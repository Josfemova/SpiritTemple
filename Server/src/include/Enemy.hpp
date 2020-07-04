#ifndef GAMESERVER_ENEMY_HPP
#define GAMESERVER_ENEMY_HPP

// Temp define
#define ROW 9
#define COL 10

#include "MoveGenerator.hpp"
#include "EnemyType.hpp"
#include "Direction.hpp"
#include "Level.hpp"
#include "list.hpp"

class Enemy {
private:
    int ID;
    int enemyX;
    int enemyY;
    EnemyType enemyType;
    float route_velocity;
    float chase_velocity;
    float visibility_radius;
    int damageDone;
    bool inRange;
    listDirections breadcrumbs;
    void setEnemyType(std::string type);

    // TEMPORAL ATTRIBUTES TO TEST PATH FINDING ALGORITHMS
    int matrix[ROW][COL];
    int playerX;
    int playerY;

public:
    Enemy(int id, int px, int py, std::string type);
    void updataData(int px, int py, int damage, bool range);
    void setEnemy(int px, int py);
    void setEnemyX(int px);
    void setEnemyY(int py);
    void setRouteVelocity(float routeVel);
    void setChaseVelocity(float chaseVel);
    void setVisibilityRadius(float radius);
    void setDamage(int damage);
    void setInRange(bool range);
    void toString();

    int getEnemyX() const;
    int getEnemyY() const;
    Pair enemyPos() const;
    float getRouteVelocity() const;
    float getChaseVelocity() const;
    float getVisibilityRadius() const;
    int getDamage() const;
    bool isInRange() const;

    EnemyType getType();
    std::string update();

    // TEMPORAL METHODS TO TEST BREAD CRUMBING AND BACKTRACKING ALGORITHM
    void setMatrix(int (*newMatrix)[COL]);
    void setPlayer(int px, int py);
    void setPlayerX(int px);
    void setPlayerY(int py);

    Pair playerPos() const;
    int getPlayerX() const;
    int getPlayerY() const;
    listDirections getBreadCrumbs() const;
};

#endif //GAMESERVER_ENEMY_HPP
