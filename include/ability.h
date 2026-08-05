#ifndef ABILITY_H
#define ABILITY_H
#include "constants.h"
#include <string>
#include <vector>
enum class AbilityType
{
    ATTACK,
    SPELL
};

class Ability
{
private:
    int id;
    string name;
    string description;
    AbilityType type;
    int power;
    int mpCost;
public:
    Ability();
    Ability(
        int id,
        string name,
        string description,
        AbilityType type,
        int power,
        int mpCost
    );
    int getId() const;
    string getName() const;
    string getDescription() const;
    AbilityType getType() const;
    int getPower() const;
    int getMPCost() const;
};

// Load attacks and spells
vector<Ability> loadAbilities(
    const string& filename
);
#endif

