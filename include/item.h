#ifndef ITEM_H
#define ITEM_H


#include "constants.h"

class Item {
public:
    string name;
    string effectType;
    int power;
    int quantity;

    Item(string n, string e, int p, int q);
};

#endif