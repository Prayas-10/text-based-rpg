#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <map>
#include <limits>

using namespace std;

// Game States
const int STATE_MENU      = 0;
const int STATE_CUTSCENE  = 1;
const int STATE_EXPLORING = 2;
const int STATE_BATTLE    = 3;
const int STATE_INVENTORY = 4;
const int STATE_GAMEOVER  = 5;

// Colors
const int COL_WHITE  = 15;
const int COL_YELLOW = 14;
const int COL_RED    = 12;
const int COL_CYAN   = 11;
const int COL_GREEN  = 10;
const int COL_GRAY   = 7;
const int COL_DARK   = 8;
const int COL_GOLD   = 6;

// Console
const int CONSOLE_WIDTH = 62;
const int BAR_WIDTH     = 22;

// Forward declarations
class Player;
class Enemy;
class Map;
class Game;


const string SAVE_FILE     = "save.dat";
const string AUTOSAVE_FILE = "autosave.dat";
const int    AUTOSAVE_INTERVAL = 300; // seconds

const string KAJI_NAME = "The Kaji";


#endif