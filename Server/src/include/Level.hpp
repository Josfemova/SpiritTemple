#ifndef GAMESERVER_LEVEL_HPP
#define GAMESERVER_LEVEL_HPP
#include "list.hpp"
#include "GameObject.hpp"


typedef ce::list<ce::list<GameObject>> lvlMatrix;

class Level {
private:
    lvlMatrix matrix;
};


#endif //GAMESERVER_LEVEL_HPP
