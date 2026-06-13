#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"
#include "ui.h"
#include "constants.h"

class Game
{
private:
    Player *player;
    Map map;
    bool isRunning;
    int currentState;
    void showTitleScreen();
    void showMainMenu();
    void startNewGame();
    void continueGame();
    void autoSave();
    void loadGame();
    bool saveExists();
    void playIntro();
    void playScene1();
    void playScene2();
    void playScene3();
    void playScene4();
    void playScene5();

public:
    Game();
    ~Game();
    void run();
};

#endif