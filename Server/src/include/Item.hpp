#ifndef GAMESERVER_ITEM_HPP
#define GAMESERVER_ITEM_HPP

#include "GameObject.hpp"
#include "ItemType.hpp"
#include "GOType.hpp"

class Item : public GameObject
{
private:
    ItemType itemType;

public:
    static ItemType getItemType(std::string value);
    explicit Item(ItemType type, int id, int px, int py) : GameObject{GOType::item, id, px, py}, itemType{type}{}
};

#endif