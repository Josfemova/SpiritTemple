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
private:
    std::shared_ptr<Level> currentLevel = nullptr;
    int playerLives=3;

public:
    static int randomInt(int lowerLimit, int upperLimit);
    std::string startLevel(std::string&);
    std::string getResponse(std::string&);
};

#endif //GAMESERVER_GAME_HPP
