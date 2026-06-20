#ifndef PLAYER_H
#define PLAYER_H


#include "inventory.h"
#include "constants.h"

class Player {
public:
    string name;
    string title;
    int hp;
    int mp;
    int xp;
    int level;
    int xpToNextLevel;
    int currentLocationId;
    Inventory inventory;
    map<string, bool> flags;

    Player(string n);
    bool isAlive() const;
};

#endif