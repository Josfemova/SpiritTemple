#ifndef GAMESERVER_SERVER_HPP
#define GAMESERVER_SERVER_HPP
#include "Game.hpp"

class Server
{
private:
    Game *game = nullptr;
    int port = 3000; //default port;
    int serverSocket;

public:
    Server();
    Server(int port);
    void startAndWait();
    void listenClient();
    void loadLevel();
};

#endif //GAMESERVER_SERVER_HPP
