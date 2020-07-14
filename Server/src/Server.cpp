#include "include/Server.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <iostream>
#include "include/utilities.hpp"

std::string Server::readMsg(bool isLarge)
{
    int size = 128;
    if (isLarge)
    {
        size = 100000;
    }
    char buffer[size] = {0};
    read(serverSocket, buffer, size);
    std::string msg(buffer);
    return msg;
}
void Server::sendMsg(std::string m)
{
    const char *msg = m.c_str();
    send(serverSocket, msg, strlen(msg), 0);
}
void Server::startAndWait(int port)
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0 || server_fd == -1)
        ce::errorlog("socket failed");

    int sockAttachResult = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (sockAttachResult < 0)
        ce::errorlog("setsockopt");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int attachResult = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (attachResult < 0)
        ce::errorlog("bind failed");

    if (listen(server_fd, 3) < 0)
        ce::errorlog("listen");
    //wait for connection to arrive
    ce::log("waiting for client connection");
    serverSocket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (serverSocket < 0)
        ce::errorlog("accept");
    game = new Game();
}
void Server::listenClient()
{
    ce::log("connection started");
    while (on)
    {
        std::string message(readMsg());
        if (message == "loadLevel")
        {
            std::string levelJson(readMsg(true));
            //
            std::ifstream t("/home/jose/Desktop/githubU/SpiritTemple/Extra/initialData.json");
            std::stringstream buffer;
            buffer << t.rdbuf();
            //
            std::string response(game->startLevel(buffer.str()));
            sendMsg("loading level");
        }
        else if (message == "event")
        {
            std::string event(readMsg());
            std::string response(game->getResponse(message));
            sendMsg(response);
        }
    }
}
void Server::loadLevel()
{
}

//
// Public methods
//

Server::Server()
{
    startAndWait();
    on = true;
    listenClient();
}
Server::Server(int port)
{
    startAndWait(port);
    on = true;
    listenClient();
}
void Server::sleep()
{
    on = false;
}

void Server::wake()
{
    on = true;
    listenClient();
}
