#ifndef GAMESERVER_GAME_HPP
#define GAMESERVER_GAME_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "./nlohmannJson.hpp"

class Game
{
public:
    void generateMatrix();
    std::string getResponse(std::string);
};

#endif //GAMESERVER_GAME_HPP
