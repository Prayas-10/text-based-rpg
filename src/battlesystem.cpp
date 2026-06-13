#include "battlesystem.h"
#include "game.h"

BattleSystem::BattleSystem(Player& p, Enemy& e, Map& m)
    : player(p), enemy(e), map(m) {}
bool BattleSystem::run() { return true; }
