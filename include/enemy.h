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
    int id;
    std::string name;
    std::string difficulty;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int gold;
    std::vector<Skill> skills;
public:
    Enemy();
    Enemy(
        int id,
        std::string name,
        std::string difficulty,
        int hp,
        int attack,
        int defense,
        int gold,
        std::vector<Skill> skills
    );
    // Basic information
    int getId() const;
    std::string getName() const;
    std::string getDifficulty() const;
    // Combat statistics
    int getHp() const;
    int getMaxHp() const;
    int getAttack() const;
    int getDefense() const;
    int getGold() const;
    // Skills
    const std::vector<Skill>& getSkills() const;
    Skill getRandomSkill() const;
    // Combat
    void takeDamage(int dmg);
    bool isAlive() const;
    // UI/debug display
    void display() const;
};
// Loads all enemies from enemy.json
std::vector<Enemy> loadEnemies(
    const std::string& filename
);
#endif

