#ifndef GAMESERVER_ITEM_HPP
#define GAMESERVER_ITEM_HPP
#include "include/GameObject.hpp"
#include "include/GOType.hpp"

class Item : GameObject
{
private:
    int itemID;

public:
    Item() : GameObject{GOType::item}{}
};

#endif