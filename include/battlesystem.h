#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "player.h"
#include "enemy.h"
#include "map.h"
#include "ability.h"
#include "constants.h"

class BattleSystem
{
private:
    Player& player;
    Enemy& enemy;
    Map& map;

    vector<Ability> attacks;
    vector<Ability> spells;
    vector<string> battleLog;

    int enemyHitsTaken = 0;
    bool defending = false;
    bool fled = false;

    void loadAbilities();
    void playerTurn();
    bool useItem();
    void enemyTurn();

    void performAttack(
        const Ability& ability
    );

    void performSpell(
        const Ability& spell
    );

    void addLog(
        const string& message
    );

public:
    BattleSystem(
        Player& p,
        Enemy& e,
        Map& m
    );

    bool run();
};

#endif
