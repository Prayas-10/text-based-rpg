#ifndef UI_H
#define UI_H


#include "constants.h"
#include <limits>

void setupConsole();
void setColor(int code);
void resetColor();
int  navigateMenu(vector<string> options);

void waitForEnter();
void printSlow(string text, int delayMs = 35);

class Player;
class Enemy;
struct Area;

#endif