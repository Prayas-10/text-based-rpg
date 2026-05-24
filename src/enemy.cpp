
#include "enemy.h"

Enemy::Enemy(string n, string d, int h, int a,
             int def, int xp, string l) {}
bool   Enemy::isAlive() const            { return true; }
int    Enemy::normalAttack(Player& p)    { return 0; }
void   Enemy::printStatus() const        {}