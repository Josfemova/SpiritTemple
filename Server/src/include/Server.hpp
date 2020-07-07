#ifndef GAMESERVER_SERVER_HPP
#define GAMESERVER_SERVER_HPP
#include "Game.hpp"

class Server
{
private:
    Game *game = nullptr;
    int connection;

public:
    void startAndWait();
    void listen();
    void loadLevel();
};

#endif //GAMESERVER_SERVER_HPP
