#include <iostream>
#include "include/MoveGenerator.hpp"
#include "include/Level.hpp"
#include "include/Enemy.hpp"
#include <unistd.h>
#include "include/Server.hpp"
#include <memory>

int main()
{
    std::unique_ptr<Server> gameServer(new Server(3000));
    ce::log("game ended");
    return 0;
}
