#ifndef CHEESEITEM_H
#define CHEESEITEM_H

#include "item.h"

class CheeseItem: public Item
{
public:
    CheeseItem(int r, int c);
    void setCollected(bool b);
    bool isCollected();
    void setId(int i);
    int getId();
private:
    bool collected;
    int id;
};

#endif // CHEESEITEM_H
