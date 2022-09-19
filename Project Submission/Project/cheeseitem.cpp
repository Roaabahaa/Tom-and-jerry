#include "cheeseitem.h"

CheeseItem::CheeseItem(int r, int c): Item("cheese.png", r, c)
{
    collected = false;
}

void CheeseItem::setCollected(bool b)
{
    collected = b;
}

bool CheeseItem::isCollected()
{
    return collected;
}

void CheeseItem::setId(int i)
{
    id = i;
}

int CheeseItem::getId()
{
    return id;
}
