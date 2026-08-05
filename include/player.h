#ifndef PLAYER_H
#define PLAYER_H
#include "inventory.h"
#include "constants.h"
class Player
{
public:
    // -- BASIC INFORMATION --
    string name;
    string title;
    // -- STATS --
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    int xp;
    int level;
    int xpToNextLevel;
    int gold;
    // -- LOCATION --
    int currentLocationId;
    // -- INVENTORY --
    Inventory inventory;
    // -- STORY / GAME FLAGS --
    map<string, bool> flags;
    // -- CONSTRUCTOR --
    Player(string n = "Kaji");
    // -- HEALTH --
    bool isAlive() const;
    void takeDamage(int damage);
    void heal(int amount);
    void restoreMP(int amount);
    // -- EXPERIENCE / LEVEL --
    void addXP(int amount);
    void levelUp();
    // -- STORY FLAGS --
    bool getFlag(
        const string& flag
    ) const;
    void setFlag(
        const string& flag,
        bool value = true
    );
    // -- SAVE / LOAD --
    void saveToFile(
        ostream& out
    ) const;
    void loadFromFile(
        istream& in
    );
};
#endif

