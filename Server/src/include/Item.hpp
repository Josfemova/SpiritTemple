#ifndef GAMESERVER_ITEM_HPP
#define GAMESERVER_ITEM_HPP

#include "GameObject.hpp"
#include "ItemType.hpp"
#include "GOType.hpp"

class Item : public GameObject
{
private:
    int itemID;
    ItemType type;

public:
    static ItemType getItemType(std::string value);
    Item(ItemType type) : GameObject{GOType::item}{}
};

#endif