#ifndef GAMESERVER_GAME_HPP
#define GAMESERVER_GAME_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "nlohmannJson.hpp"
#include "Level.hpp"
#include <memory>

class Game
{
    std::shared_ptr<Level> currentLevel=nullptr;
    int playerLives;
public:
    void startLevel();
    std::string getResponse(std::string);
};

#endif //GAMESERVER_GAME_HPP
