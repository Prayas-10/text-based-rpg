#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"
#include "player.h"
#include "constants.h"

class Enemy {
public:
    string name;
    string description;
    int hp;
    int maxHP;
    int attack;
    int defense;
    int xpReward;
    string lootName;

    Enemy(string n, string d, int h, int a,
          int def, int xp, string l);

    bool isAlive() const;
    int normalAttack(Player& p);
    void printStatus() const;
    virtual string specialMove(Player& p) = 0;
    virtual ~Enemy() {}
};

#endif