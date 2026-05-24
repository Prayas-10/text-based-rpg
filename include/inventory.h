#ifndef INVENTORY_H
#define INVENTORY_H

#include "game.h"
#include "item.h"
#include "constants.h"

class Inventory {
private:
    vector<Item> items;

public:
    vector<Item>& getItems();
};

#endif