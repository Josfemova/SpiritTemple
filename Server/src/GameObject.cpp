#include "include/GameObject.hpp"

GameObject::GameObject(GOType type, int id, int py, int px) : type{type}, id{id}, gridy{py}, gridx{px} {}

GOType GameObject::getType()
{
    return type;
}

int GameObject::getY() const
{
    return gridy;
}

void GameObject::setY(int value)
{
    gridy = value;
}

int GameObject::getX() const
{
    return gridx;
}

void GameObject::setX(int value)
{
    gridx = value;
}

int GameObject::getID() const
{
    return id;
}