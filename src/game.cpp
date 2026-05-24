#include "game.h"

Game::Game()  { player = nullptr; isRunning = false; currentState = STATE_MENU; }
Game::~Game() { if (player != nullptr) delete player; }
void Game::run() {}