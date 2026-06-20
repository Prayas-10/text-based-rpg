#include "Enemy.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "json.hpp"

using json = nlohmann::json;

Enemy::Enemy()
{
}

Enemy::Enemy(
    std::string name,
    int hp,
    std::vector<Skill> skills
)
{
    this->name = name;
    this->hp = hp;
    this->maxHp = hp;
    this->skills = skills;
}

std::string Enemy::getName() const
{
    return name;
}

int Enemy::getHp() const
{
    return hp;
}

void Enemy::takeDamage(int dmg)
{
    hp -= dmg;

    if(hp < 0)
        hp = 0;
}

Skill Enemy::getRandomSkill() const
{
    int index = rand() % skills.size();
    return skills[index];
}

void Enemy::display() const
{
    std::cout << name
              << " HP: "
              << hp
              << "/"
              << maxHp
              << std::endl;
}

std::vector<Enemy> loadEnemies(
    const std::string& filename
)
{
    std::ifstream file(filename);

    json data;
    file >> data;

    std::vector<Enemy> enemies;

    for(auto enemyData : data["enemies"])
    {
        std::string name =
            enemyData["name"];

        int hp =
            enemyData["hp"];

        std::vector<Skill> skills;

        for(auto skillData :
            enemyData["skills"])
        {
            Skill skill;

            skill.name =
                skillData["name"];

            skill.damage =
                skillData["damage"];

            skills.push_back(skill);
        }

        enemies.push_back(
            Enemy(
                name,
                hp,
                skills
            )
        );
    }

    return enemies;
}