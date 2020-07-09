#ifndef GAMESERVER_GAME_HPP
#define GAMESERVER_GAME_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "./nlohmannJson.hpp"

using json = nlohmann::json;

using namespace std;

class Game
{
public:
    void generateMatrix();
    void getResponse();
    
};

#endif //GAMESERVER_GAME_HPP
