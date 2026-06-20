#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

struct Skill
{
    std::string name;
    int damage;
};

class Enemy
{
private:
    std::string name;
    int hp;
    int maxHp;
    std::vector<Skill> skills;

public:
    Enemy();

    Enemy(
        std::string name,
        int hp,
        std::vector<Skill> skills
    );

    std::string getName() const;
    int getHp() const;

    void takeDamage(int dmg);

    Skill getRandomSkill() const;

    void display() const;
};

std::vector<Enemy> loadEnemies(
    const std::string& filename
);

#endif