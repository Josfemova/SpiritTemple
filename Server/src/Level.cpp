#include "include/Level.hpp"

Level::Level() {
    started = true;
}

Level::Level(int (*newMatrix)[10]) {
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            simpleMatrix[i][j] = newMatrix[i][j];
        }
    }
    started = true;
}

Level::Level(int (*newMatrix)[10], int id, int lives, int px, int py) {
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            simpleMatrix[i][j] = newMatrix[i][j];
        }
    }
    playerID = id;
    playerLives = lives;
    playerX = px;
    playerY = py;
    started = true;
}


void Level::start() {
    // Do something
}

void Level::finish() {
    // Do something
}

void Level::updatePlayerPos(int px, int py) {
    playerX = px;
    playerY = py;
}

void Level::setPlayerX(int px) { playerX = px; }

void Level::setPlayerY(int py) { playerY = py; }

Pair Level::playerPos() const {
    Pair playerPos = std::make_pair(playerX, playerY);
    return playerPos;
}

int Level::getPlayerX() const { return playerX; }

int Level::getPlayerY() const { return playerY; }

array Level::getSimpleMatrix() {
    return simpleMatrix;
}

bool Level::isStarted() const { return started; }





