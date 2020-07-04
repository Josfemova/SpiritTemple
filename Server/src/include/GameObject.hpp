#ifndef GAMESERVER_GAMEOBJECT_HPP
#define GAMESERVER_GAMEOBJECT_HPP

#include <string>
#include "GOType.hpp"

class GameObject {
private:
    GOType type;
public:
    GOType getType() const;
    std::string update() const;
};


#endif //GAMESERVER_GAMEOBJECT_HPP
