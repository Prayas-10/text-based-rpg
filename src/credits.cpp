#include "credits.h"
#include "ui.h"
#include "soundManager.h"
void showCredits()
{
    SoundManager::event("game_end");
    clearScreen();
    drawCenteredText(0, 5, 120, "P R A T I V I N D H Y A", COL_GOLD);
    drawCenteredText(0, 8, 120, "CREDITS", COL_YELLOW);
    drawCenteredText(0, 11, 120, "A Prayas Production", COL_WHITE);
    drawCenteredText(0, 13, 120, "Story and Game Design", COL_CYAN);
    drawCenteredText(0, 14, 120, "Prayas Team", COL_WHITE);
    drawCenteredText(0, 16, 120, "Programming", COL_CYAN);
    drawCenteredText(0, 17, 120, "Prayas Team", COL_WHITE);
    drawCenteredText(0, 19, 120, "Thank you for playing.", COL_GOLD);
    drawCenteredText(0, 23, 120, "Press ENTER to return to the main menu.", COL_GRAY);
    waitForEnter();
}
