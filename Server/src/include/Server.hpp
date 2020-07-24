#ifndef GAMESERVER_SERVER_HPP
#define GAMESERVER_SERVER_HPP
#include "Game.hpp"
#include <string>

/**
 * @brief in charge of giving the game engine the needed information to operate
 * 
 */
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
    /**
     * @brief Construct a new Server
     * 
     */
    Server();
    /**
     * @brief Construct a new Server with a given port
     * 
     * @param port 
     */
    explicit Server(int port);
    /**
     * @brief stop request handling
     * 
     */
    void sleep();
    /**
     * @brief restart request handling
     * 
     */
    void wake();
};

#endif //GAMESERVER_SERVER_HPP
