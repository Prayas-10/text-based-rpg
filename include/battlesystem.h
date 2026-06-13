#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H


#include "player.h"
#include "enemy.h"
#include "map.h"
#include "constants.h"

class BattleSystem {
private:
    Player& player;
    Enemy& enemy;
    Map& map;
public:
    BattleSystem(Player& p, Enemy& e, Map& m);
    bool run();
};

#endif