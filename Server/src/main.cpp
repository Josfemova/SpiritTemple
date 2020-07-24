#include "include/Server.hpp"
#include <memory>

int main()
{
    std::unique_ptr<Server> gameServer(new Server(3000));
    ce::log("game ended");
    return 0;
}
