#ifndef GAMESERVER_GAMEOBJECT_HPP
#define GAMESERVER_GAMEOBJECT_HPP

#include <string>
#include "GOType.hpp"

class GameObject {
private:
    GOType type;
public:
    GOType getType();
    std::string update();
};


#endif //GAMESERVER_GAMEOBJECT_HPP
