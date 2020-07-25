#include "include/Item.hpp"

ItemType Item::getItemType(std::string value){
    if(value == "chest")
        return ItemType::CHEST;
    else if(value == "jar")
        return ItemType::JAR;
    else
        return ItemType::OTHER;
}
