#include "enemy.h"
#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// -- DEFAULT CONSTRUCTOR --
Enemy::Enemy()
{
    id = 0;
    name = "";
    difficulty = "";
    hp = 0;
    maxHp = 0;
    attack = 0;
    defense = 0;
    gold = 0;
    skills.clear();
}

// -- FULL CONSTRUCTOR --
Enemy::Enemy(
    int id,
    string name,
    string difficulty,
    int hp,
    int attack,
    int defense,
    int gold,
    vector<Skill> skills
)
{
    this->id = id;
    this->name = name;
    this->difficulty = difficulty;
    this->hp = hp;
    this->maxHp = hp;
    this->attack = attack;
    this->defense = defense;
    this->gold = gold;
    this->skills = skills;
}

// -- GETTERS --
int Enemy::getId() const
{
    return id;
}

string Enemy::getName() const
{
    return name;
}

string Enemy::getDifficulty() const
{
    return difficulty;
}

int Enemy::getHp() const
{
    return hp;
}

int Enemy::getMaxHp() const
{
    return maxHp;
}

int Enemy::getAttack() const
{
    return attack;
}

int Enemy::getDefense() const
{
    return defense;
}

int Enemy::getGold() const
{
    return gold;
}

const vector<Skill>& Enemy::getSkills() const
{
    return skills;
}

// -- RANDOM SKILL --
Skill Enemy::getRandomSkill() const
{
    if (skills.empty())
    {
        return { "Basic Attack", attack };
    }
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(
        0,
        static_cast<int>(skills.size()) - 1
    );
    return skills[dist(gen)];
}

// -- TAKE DAMAGE --
void Enemy::takeDamage(int dmg)
{
    if (dmg < 0)
        dmg = 0;
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}

// -- ALIVE CHECK --
bool Enemy::isAlive() const
{
    return hp > 0;
}

// -- DISPLAY --
void Enemy::display() const
{
    cout << "ID         : " << id << '\n';
    cout << "Name       : " << name << '\n';
    cout << "Difficulty : " << difficulty << '\n';
    cout << "HP         : " << hp << "/" << maxHp << '\n';
    cout << "Attack     : " << attack << '\n';
    cout << "Defense    : " << defense << '\n';
    cout << "Gold       : " << gold << '\n';
    cout << "Skills:\n";
    for (const Skill& skill : skills)
    {
        cout << "  - "
            << skill.name
            << " (" << skill.damage << " damage)\n";
    }
}

// -- LOAD ENEMIES FROM JSON --
vector<Enemy> loadEnemies(const string& filename)
{
    vector<Enemy> enemies;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open enemy file: "
            << filename << '\n';
        return enemies;
    }
    try
    {
        json data;
        file >> data;
        if (!data.contains("enemies"))
        {
            cerr << "Error: enemy.json does not contain "
                "\"enemies\".\n";
            return enemies;
        }
        for (const auto& enemyData : data["enemies"])
        {
            vector<Skill> skills;
            if (enemyData.contains("skills"))
            {
                for (const auto& skillData : enemyData["skills"])
                {
                    Skill skill;
                    skill.name =
                        skillData.value(
                            "name",
                            "Unknown Skill"
                        );
                    skill.damage =
                        skillData.value(
                            "damage",
                            0
                        );
                    skills.push_back(skill);
                }
            }
            Enemy enemy(
                enemyData.value("id", 0),
                enemyData.value(
                    "name",
                    "Unknown Enemy"
                ),
                enemyData.value(
                    "difficulty",
                    "Unknown"
                ),
                enemyData.value(
                    "hp",
                    1
                ),
                enemyData.value(
                    "attack",
                    0
                ),
                enemyData.value(
                    "defense",
                    0
                ),
                enemyData.value(
                    "gold",
                    0
                ),
                skills
            );
            enemies.push_back(enemy);
        }
    }
    catch (const json::exception& e)
    {
        cerr << "Error reading enemy.json: "
            << e.what() << '\n';
    }
    return enemies;
}

