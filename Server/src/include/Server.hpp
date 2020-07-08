#ifndef GAMESERVER_SERVER_HPP
#define GAMESERVER_SERVER_HPP
#include "Game.hpp"
#include <string>

class Server
{
private:
    Game *game = nullptr;
    int port = 3000; //default port
    int serverSocket;
    bool on = false;
    std::string readMsg();
    void startAndWait(int port = 3000);
    void listenClient();
    void loadLevel();
public:
    Server();
    Server(int port);
    void sleep();
    void wake();
};

#endif //GAMESERVER_SERVER_HPP
