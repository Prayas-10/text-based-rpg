#include "game.h"
#include "tutorial.h"
#include "constants.h"
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    setupConsole();
    Game game;
    game.run();
    return 0;
}

