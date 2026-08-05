#ifndef UI_H
#define UI_H
#include "constants.h"
#include <string>
#include <vector>
// Forward declarations
class Player;
class Enemy;
class Inventory;
class Item;
// -- CONSOLE SETUP --
void setupConsole();
void setColor(int code);
void resetColor();
void gotoxy(int x, int y);
void hideCursor();
void showCursor();
void clearScreen();
// -- INPUT --
// Returns:
// 0 = up
// 1 = down
// 2 = left
// 3 = right
// 4 = select / enter
// 5 = escape
// 6 = none
// 7 = tab
int readInput();
int navigateMenu(std::vector<std::string> options);
// Lets the player hit TAB to jump focus between the main
// story/action panel (bottom-left, wherever drawStoryPanel or
// drawCombatPanel is drawing) and the side panel on the bottom
// right (Inventory / Save / Return to Main Menu and friends).
// Returns false if they backed out with ESC instead of picking.
bool navigateDualMenu(
    const std::vector<std::string>& mainOptions,
    const std::vector<std::string>& sideOptions,
    int& outPanel,
    int& outIndex
);
// -- SCREEN MODES --
void setScreenMode(int mode);
// -- BASIC TEXT --
void printSlow(std::string text, int delayMs = 20);
void typewriter(
    const string& text,
    int delayMs = 35
);
void waitForEnter();
// -- old pacing helpers, kept around so nothing else breaks --
void pause_aftermath();
void pause_weight();
void pause_revelation();
// -- BOX DRAWING --
void drawBox(
    int x,
    int y,
    int width,
    int height
);
void clearBox(
    int x,
    int y,
    int width,
    int height
);
// -- TEXT HELPERS --
void drawText(
    int x,
    int y,
    const std::string& text,
    int color = COL_WHITE
);
void drawCenteredText(
    int x,
    int y,
    int width,
    const std::string& text,
    int color = COL_WHITE
);
// -- RPG LAYOUT --
void drawGameLayout(
    const std::string& title,
    const std::string& location
);
void drawCharacterPanel(
    const Player& player
);
void drawEnemyPanel(
    const Enemy& enemy
);
void drawQuestPanel(
    const std::string& objective
);
void drawInventoryPanel(
    const Inventory& inventory
);
void drawMessageLog(
    const std::vector<std::string>& messages
);
// -- STORY --
void drawStoryPanel(
    const std::string& speaker,
    const std::string& dialogue
);
// Same box as drawStoryPanel, but animates the dialogue in
// character-by-character with punctuation-aware pacing:
// commas pause briefly, a sentence-ending "." pauses a bit
// longer, and a run of dots ("..." or "....") only pauses once
// - after the LAST dot of the run, and longer than a single
// "." or "...". This is what the prologue and every in-game
// story line renders through, so dialogue always animates
// inside the story panel rather than on a bare screen.
void typewriterStoryPanel(
    const std::string& speaker,
    const std::string& dialogue,
    int delayMs = 28
);
// Battle state (player + enemy HP/MP bars and the fight log)
// renders inside the same STORY viewport - not the sidebar -
// so it has real room during combat.
void drawBattlePanel(
    const Player& player,
    const Enemy& enemy,
    const std::vector<std::string>& battleLog
);
// -- SYSTEM PANEL (bottom-right box) --
void drawSystemPanel(
    const std::vector<std::string>& options,
    int selected,
    bool focused
);
// -- COMBAT --
void drawCombatPanel(
    const std::vector<std::string>& actions,
    int selected
);
// -- STATUS BARS --
void drawHPBar(
    int x,
    int y,
    int current,
    int maximum,
    int width = 20
);
void drawMPBar(
    int x,
    int y,
    int current,
    int maximum,
    int width = 20
);
#endif

