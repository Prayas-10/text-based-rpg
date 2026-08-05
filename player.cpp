#include "player.h"
#include <iostream>
using namespace std;

// -- CONSTRUCTOR --
Player::Player(string n)
{
    name = n;
    title = "Kaji";
    // --------------------------------------------------------
    // Starting stats
    // --------------------------------------------------------
    maxHp = 100;
    hp = maxHp;
    maxMp = 50;
    mp = maxMp;
    xp = 0;
    level = 0;
    xpToNextLevel = 100;
    gold = 108;
    // --------------------------------------------------------
    // Starting location
    // --------------------------------------------------------
    currentLocationId = 0;
}

// -- IS ALIVE --
bool Player::isAlive() const
{
    return hp > 0;
}

// -- TAKE DAMAGE --
void Player::takeDamage(int damage)
{
    if (damage < 0)
        damage = 0;
    hp -= damage;
    if (hp < 0)
        hp = 0;
}

// -- HEAL --
void Player::heal(int amount)
{
    if (amount <= 0)
        return;
    hp += amount;
    if (hp > maxHp)
        hp = maxHp;
}

// -- RESTORE MP --
void Player::restoreMP(int amount)
{
    if (amount <= 0)
        return;
    mp += amount;
    if (mp > maxMp)
        mp = maxMp;
}

// -- ADD XP --
void Player::addXP(int amount)
{
    if (amount <= 0)
        return;
    xp += amount;
    while (xp >= xpToNextLevel)
    {
        xp -= xpToNextLevel;
        levelUp();
    }
}

// -- LEVEL UP --
void Player::levelUp()
{
    level++;
    // Increase maximum stats.
    maxHp += 20;
    maxMp += 10;
    // Fully restore after leveling.
    hp = maxHp;
    mp = maxMp;
    // Increase XP requirement.
    xpToNextLevel += 50;
}

// -- GET STORY FLAG --
bool Player::getFlag(
    const string& flag
) const
{
    auto it = flags.find(flag);
    if (it == flags.end())
        return false;
    return it->second;
}

// -- SET STORY FLAG --
void Player::setFlag(
    const string& flag,
    bool value
)
{
    flags[flag] = value;
}

// -- SAVE --
void Player::saveToFile(
    ostream& out
) const
{
    // plain text save format, one field per line. not fancy but it
    // works and it's easy to eyeball a save file when debugging
    out << name << '\n';
    out << title << '\n';
    out << hp << '\n';
    out << maxHp << '\n';
    out << mp << '\n';
    out << maxMp << '\n';
    out << xp << '\n';
    out << level << '\n';
    out << xpToNextLevel << '\n';
    out << gold << '\n';
    out << currentLocationId << '\n';
    out << flags.size() << '\n';
    for (const auto& flag : flags)
    {
        out << flag.first << '\n';
        out << flag.second << '\n';
    }

    inventory.saveToFile(out);
}

// -- LOAD --
void Player::loadFromFile(
    istream& in
)
{
    // reads back everything saveToFile wrote, in the same order
    getline(in, name);
    getline(in, title);
    in >> hp;
    in >> maxHp;
    in >> mp;
    in >> maxMp;
    in >> xp;
    in >> level;
    in >> xpToNextLevel;
    in >> gold;
    in >> currentLocationId;
    size_t flagCount;
    in >> flagCount;
    flags.clear();
    for (size_t i = 0; i < flagCount; i++)
    {
        string flagName;
        bool flagValue;
        in >> flagName;
        in >> flagValue;
        flags[flagName] = flagValue;
    }
    // Clear the newline left by >>.
    in.ignore(
        (numeric_limits<streamsize>::max)(),
        '\n'
    );

    inventory.loadFromFile(in);
}

