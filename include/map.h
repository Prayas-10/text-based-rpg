#ifndef MAP_H
#define MAP_H


#include "enemy.h"
#include "constants.h"

struct NPC {
    string name;
    string dialogue;
    bool hasSpoken;
    NPC(string n, string d);
};

struct Area {
    int id;
    string name;
    string description;
    string atmosphereLine;
    Enemy* enemy;
    NPC* npc;
    int nextAreaId;
    bool isLocked;
    bool enemyDefeated;
    Area();
};

class Map {
private:
    Area areas[12];
public:
    Map();
    Area& getArea(int id);
};

#endif