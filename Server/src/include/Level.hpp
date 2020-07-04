#ifndef GAMESERVER_LEVEL_HPP
#define GAMESERVER_LEVEL_HPP
#define ROW 9
#define COL 10

#include "list.hpp"
#include "GameObject.hpp"
#include "nlohmannJson.hpp"

typedef ce::list<ce::list<GameObject>> lvlMatrix;
typedef ce::list<std::string> lvlInstructions;
typedef std::pair<int, int> Pair;
typedef int(&array)[ROW][COL];

using json = nlohmann::json;

class Level {
private:
    int playerLives;
    int playerID;
    int playerX;
    int playerY;
    bool started;
    int simpleMatrix[ROW][COL];
    lvlMatrix matrix;
    lvlInstructions instructions;

public:
    //Level(lvlMatrix);
    Level();
    Level(int (*newMatrix)[COL]);
    Level(int (*newMatrix)[COL], int id, int lives, int px, int py);
    void start();
    void finish();
    void updatePlayerPos(int px, int py);
    void setPlayerX(int px);
    void setPlayerY(int py);

    array getSimpleMatrix();
    Pair playerPos() const;
    int getPlayerX() const;
    int getPlayerY() const;
    bool isStarted() const;

    //void manageEvents(json);
    //lvlInstructions getInstructions();
};


#endif //GAMESERVER_LEVEL_HPP
