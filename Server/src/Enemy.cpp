#include "include/Enemy.hpp"

Enemy::Enemy(int id, int px, int py, std::string type) {
    enemyID = id;
    enemyX = px;
    enemyY = py;
    setEnemyType(type);
}

void Enemy::setEnemyType(std::string type) {
    if(type == "SpGray"){
        enemyType = EnemyType::SpGray;
        return;
    }
    if(type == "SpRed"){
        enemyType = EnemyType::SpRed;
        return;
    }
    if(type == "SpBlue"){
        enemyType = EnemyType::SpBlue;
        return;
    }
    if(type == "SpEye"){
        enemyType = EnemyType::SpEye;
        return;
    }
    if(type == "Mouse"){
        enemyType = EnemyType::Mouse;
        return;
    }
    if(type == "Chuchu"){
        enemyType = EnemyType::Chuchu;
        return;
    }
}

void Enemy::updateData(int px, int py, int damage, bool range) {
    enemyX = px;
    enemyY = py;
    damageDone = damage;
    inRange = range;
}

void Enemy::setEnemy(int px, int py) {
    enemyX = px;
    enemyY = py;
}

void Enemy::setEnemyX(int px) {
    enemyX = px;
}

void Enemy::setEnemyY(int py) {
    enemyY = py;
}

void Enemy::setRouteVelocity(float routeVel) {
    route_velocity = routeVel;
}

void Enemy::setChaseVelocity(float chaseVel) {
    chase_velocity = chaseVel;
}

void Enemy::setVisibilityRadius(float radius) {
    visibility_radius = radius;
}

void Enemy::setDamage(int damage) {
    damageDone = damage;
}

void Enemy::setInRange(bool range) {
    inRange = range;
}

void Enemy::toString() {
    std::cout<<"Position: ("<<enemyX<<","<<enemyY<<")\n";
}

int Enemy::getEnemyX() const {
    return enemyX;
}

int Enemy::getEnemyY() const {
    return enemyY;
}

Pair Enemy::enemyPos() const {
    return std::make_pair(enemyX, enemyY);
}

float Enemy::getRouteVelocity() const {
    return route_velocity;
}

float Enemy::getChaseVelocity() const {
    return chase_velocity;
}

float Enemy::getVisibilityRadius() const {
    return visibility_radius;
}

int Enemy::getDamage() const {
    return damageDone;
}

bool Enemy::isInRange() const {
    return inRange;
}

EnemyType Enemy::getType() {
    return enemyType;
}

std::string Enemy::getTypeS() {
    switch (enemyType){
        case EnemyType::SpGray:
            return "SpGray";
        case EnemyType::SpRed:
            return "SpRed";
        case EnemyType::SpBlue:
            return "SpBlue";
        case EnemyType::SpEye:
            return "SpEye";
        case EnemyType::Mouse:
            return "Mouse";
        case EnemyType::Chuchu:
            return "Chuchu";
        default:
            return "";
    }
}

std::string Enemy::update() {
    if(inRange && (enemyType == EnemyType::SpGray || enemyType == EnemyType::SpRed)){
        listDirections path = MoveGenerator::getRoute(matrix, enemyPos(), playerPos(), RouteType::Astar);
        if(!path.empty()){
            // To print it on the server console
            std::string movement = "MOVE TO " + Pathfinding::getNextMovement(path[0]);
            std::cout<<movement<<std::endl;
            Pathfinding::setNewEnemyPos(path[0], enemyX, enemyY);
            breadcrumbs.push_back(path[0]);
            toString();
            Pathfinding::printBreadcrumbs(breadcrumbs);

            // To list instructions
            return Pathfinding::getNextMovement(path[0]);
        }
    }

    if(inRange && enemyType == EnemyType::SpBlue){
        // Teleportation
        // To print it on the server console
        std::string result = "ENEMY" + std::to_string(enemyID) + " TELEPORTED FROM (";
        result += std::to_string(enemyX) + "," + std::to_string(enemyY) + ") TO (";
        try{
            //Pathfinding::teleportEnemy(matrix, enemyX, enemyY, playerX, playerY);
            Pathfinding pathfinding(matrix);
            pathfinding.teleportEnemy(enemyX, enemyY, playerX, playerY);
        }
        catch (error_t){}
        result += std::to_string(enemyX) + "," + std::to_string(enemyY) + ")";
        std::cout<<result<<std::endl;

        // To list instructions
        return std::to_string(enemyX) + "," + std::to_string(enemyY);
    }

    if(inRange && enemyType == EnemyType::Chuchu){
        listDirections path = MoveGenerator::getRoute(matrix, enemyPos(), playerPos(), RouteType::LineSight);
        if(!path.empty()){
            // To print it on the server console
            std::cout<<"\nEnemy / ID:"<<std::to_string(enemyID) <<" / Type: "<<getTypeS()<<std::endl;
            Pathfinding::printLineSight(path);
            std::cout<<"Instruction: Move to "<<Pathfinding::getNextMovement(path[0])<<std::endl;
            Pathfinding::setNewEnemyPos(path[0], enemyX, enemyY);
            toString();

            // To list instructions
            return Pathfinding::getNextMovement(path[0]);
        }
    }

    if(!inRange && !breadcrumbs.empty()){
        int n = breadcrumbs.size()-1;
        if(n >= 0){
            // To print it on the server console
            std::string movement = "MOVE TO " + Pathfinding::getPreviousMovement(breadcrumbs[n]);
            std::string result = Pathfinding::getPreviousMovement(breadcrumbs[n]);
            std::cout<<movement<<std::endl;
            Pathfinding::setPreviousEnemyPos(breadcrumbs[n], enemyX, enemyY);
            breadcrumbs.pop_back();
            toString();
            std::cout<<"\n";

            // To list instructions
            return result;
        }

    }
    return "Hi";
}

//************TEMPORAL METHODS*************//

void Enemy::setMatrix(int (*newMatrix)[10]){
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            matrix[i][j] = newMatrix[i][j];
        }
    }
}

void Enemy::setPlayer(int px, int py) {
    playerX = px;
    playerY = py;
}

void Enemy::setPlayerX(int px) {
    playerX = px;
}

void Enemy::setPlayerY(int py) {
    playerY = py;
}

Pair Enemy::playerPos() const {
    return std::make_pair(playerX, playerY);
}

int Enemy::getPlayerX() const {
    return playerX;
}

int Enemy::getPlayerY() const {
    return playerY;
}

listDirections Enemy::getBreadCrumbs() const {
    return breadcrumbs;
}














