#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "map.h"
#include "ui.h"
#include "story.h"
#include "saveSystem.h"
#include "constants.h"
class Game
{
private:
    Player* player;
    Map map;
    Story story;
    bool isRunning;
    int currentState;
    void showTitleScreen();
    void showMainMenu();
    void startNewGame();
    void continueGame();
    void loadGame();
    bool saveExists();
    void autoSave();
    void showWorldScreen();
public:
    Game();
    ~Game();
    void run();
};
#endif

