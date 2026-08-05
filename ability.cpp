#include "ability.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

// -- DEFAULT --
Ability::Ability()
{
    id = 0;
    name = "";
    description = "";
    type = AbilityType::ATTACK;
    power = 0;
    mpCost = 0;
}

// -- CONSTRUCTOR --
Ability::Ability(
    int id,
    string name,
    string description,
    AbilityType type,
    int power,
    int mpCost
)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->type = type;
    this->power = power;
    this->mpCost = mpCost;
}

// -- GETTERS --
int Ability::getId() const
{
    return id;
}

string Ability::getName() const
{
    return name;
}

string Ability::getDescription() const
{
    return description;
}

AbilityType Ability::getType() const
{
    return type;
}

int Ability::getPower() const
{
    return power;
}

int Ability::getMPCost() const
{
    return mpCost;
}

// -- LOAD ABILITIES --
vector<Ability> loadAbilities(
    const string& filename
)
{
    vector<Ability> abilities;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open ability file: "
            << filename << endl;
        return abilities;
    }
    try
    {
        json data;
        file >> data;

        // -- ATTACKS --
        if (data.contains("attacks"))
        {
            for (const auto& attack : data["attacks"])
            {
                Ability ability(
                    attack.value("id", 0),
                    attack.value(
                        "name",
                        "Unknown Attack"
                    ),
                    attack.value(
                        "description",
                        ""
                    ),
                    AbilityType::ATTACK,
                    attack.value(
                        "power",
                        0
                    ),
                    attack.value(
                        "mpCost",
                        0
                    )
                );
                abilities.push_back(ability);
            }
        }

        // -- SPELLS --
        if (data.contains("spells"))
        {
            for (const auto& spell : data["spells"])
            {
                Ability ability(
                    spell.value("id", 0),
                    spell.value(
                        "name",
                        "Unknown Spell"
                    ),
                    spell.value(
                        "description",
                        ""
                    ),
                    AbilityType::SPELL,
                    spell.value(
                        "power",
                        0
                    ),
                    spell.value(
                        "mpCost",
                        0
                    )
                );
                abilities.push_back(ability);
            }
        }
    }
    catch (const json::exception& e)
    {
        cerr << "Error reading "
            << filename
            << ": "
            << e.what()
            << endl;
    }
    return abilities;
}

