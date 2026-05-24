#ifndef GAME_H
#define GAME_H

#include "game.h"
#include "player.h"
#include "map.h"
#include "ui.h"
#include "constants.h"

class Game {
private:
    Player* player;
    Map map;
    bool isRunning;
    int currentState;
public:
    Game();
    ~Game();
    void run();
};

#endif