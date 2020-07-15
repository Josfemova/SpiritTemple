#ifndef GAMESERVER_SERVER_HPP
#define GAMESERVER_SERVER_HPP
#include "Game.hpp"
#include <string>

class Server
{
private:
    Game *game = nullptr;
    int serverSocket;
    bool on = false;
    void sendMsg(std::string);
    std::string readMsg(bool isLarge = false);
    void startAndWait(int port = 3000);
    void listenClient();
    void loadLevel();
public:
    Server();
    explicit Server(int port);
    void sleep();
    void wake();
};

#endif //GAMESERVER_SERVER_HPP
