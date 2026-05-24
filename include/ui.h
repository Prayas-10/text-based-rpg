#ifndef UI_H
#define UI_H

#include "game.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "constants.h"

void setupConsole();
void setColor(int code);
void resetColor();
int  navigateMenu(vector<string> options);

#endif