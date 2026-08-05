#include "battlesystem.h"
#include "ui.h"
#include "soundManager.h"
#include "saveSystem.h"

#include <windows.h>
#include <algorithm>
#include <string>

using namespace std;

extern int currentSlot;

BattleSystem::BattleSystem(
    Player& p,
    Enemy& e,
    Map& m
)
    : player(p),
      enemy(e),
      map(m)
{
    loadAbilities();
}

void BattleSystem::loadAbilities()
{
    const vector<Ability> abilities =
        ::loadAbilities("data/abilities.json");

    attacks.clear();
    spells.clear();

    for (const Ability& ability : abilities)
    {
        if (ability.getType() == AbilityType::ATTACK)
            attacks.push_back(ability);
        else if (ability.getType() == AbilityType::SPELL)
            spells.push_back(ability);
    }

    if (attacks.size() > 4)
        attacks.resize(4);

    if (spells.size() > 4)
        spells.resize(4);
}

void BattleSystem::addLog(const string& message)
{
    battleLog.push_back(message);

    if (battleLog.size() > 20)
        battleLog.erase(battleLog.begin());
}

void BattleSystem::performAttack(
    const Ability& ability
)
{
    const int damage = max(0, ability.getPower());

    enemy.takeDamage(damage);

    SoundManager::event("attack");

    addLog(
        player.name +
        " used " +
        ability.getName() +
        "!"
    );

    addLog(
        enemy.getName() +
        " took " +
        to_string(damage) +
        " damage."
    );
}

void BattleSystem::performSpell(
    const Ability& spell
)
{
    const int cost = max(0, spell.getMPCost());
    const int damage = max(0, spell.getPower());

    if (spell.getName().empty())
        return;

    if (damage <= 0)
    {
        addLog("That spell has no effect.");
        return;
    }

    if (player.mp < cost)
    {
        addLog("Not enough MP.");
        return;
    }

    player.mp -= cost;
    enemy.takeDamage(damage);

    addLog(
        player.name +
        " cast " +
        spell.getName() +
        "!"
    );

    addLog(
        enemy.getName() +
        " took " +
        to_string(damage) +
        " damage."
    );
}

bool BattleSystem::useItem()
{
    const auto& entries = player.inventory.getItems();

    vector<string> names;

    for (const auto& entry : entries)
    {
        if (
            entry.quantity > 0 &&
            entry.item.isUsable()
        )
        {
            names.push_back(entry.item.getName());
        }
    }

    if (names.empty())
    {
        addLog("You have no usable items.");
        return false;
    }

    const int selected = navigateMenu(names);

    if (
        selected < 0 ||
        selected >= static_cast<int>(names.size())
    )
    {
        return false;
    }

    const string& name = names[selected];

    const Item* item =
        player.inventory.findItem(name);

    if (item == nullptr)
        return false;

    if (item->getEffectType() == "heal_hp")
    {
        if (player.hp >= player.maxHp)
        {
            addLog("HP is already full.");
            return false;
        }

        player.heal(item->getPower());

        addLog(
            player.name +
            " used " +
            item->getName() +
            "."
        );

        addLog(
            "HP restored by " +
            to_string(item->getPower()) +
            "."
        );
    }
    else if (
        item->getEffectType() ==
        "restore_mp"
    )
    {
        if (player.mp >= player.maxMp)
        {
            addLog("MP is already full.");
            return false;
        }

        player.restoreMP(item->getPower());

        addLog(
            player.name +
            " used " +
            item->getName() +
            "."
        );

        addLog(
            "MP restored by " +
            to_string(item->getPower()) +
            "."
        );
    }
    else
    {
        addLog(
            "That item cannot be used in battle."
        );

        return false;
    }

    player.inventory.removeItem(
        item->getId(),
        1
    );

    SoundManager::event("button_enter");

    return true;
}

void BattleSystem::playerTurn()
{
    const vector<string> mainActions =
    {
        "Attack",
        "Spell",
        "Item",
        "Defend",
        "Run"
    };

    const vector<string> sideActions =
    {
        "Save"
    };

    int panel = 0;
    int index = 0;

    const bool chose =
        navigateDualMenu(
            mainActions,
            sideActions,
            panel,
            index
        );

    if (!chose)
    {
        fled = true;
        return;
    }

    if (panel == 1)
    {
        // Save doesn't cost a turn - persist the full player
        // state right now (mid-battle) and let the player pick
        // an actual action afterwards.

        saveSystem save;
        const int progress = save.load(currentSlot);

        save.saveGame(
            progress > 0 ? progress : 1,
            currentSlot,
            player,
            map.getLocation()
        );

        addLog("Game saved.");
        playerTurn();
        return;
    }

    const int selected = index;

    if (selected == 0)
    {
        if (attacks.empty())
        {
            addLog("No attacks are available.");
            return;
        }

        vector<string> names;

        for (const Ability& attack : attacks)
            names.push_back(attack.getName());

        const int choice =
            navigateMenu(names);

        if (
            choice >= 0 &&
            choice < static_cast<int>(
                attacks.size()
            )
        )
        {
            performAttack(
                attacks[choice]
            );
        }

        return;
    }

    if (selected == 1)
    {
        if (spells.empty())
        {
            addLog("No spells are available.");
            return;
        }

        vector<string> names;

        for (const Ability& spell : spells)
        {
            names.push_back(
                spell.getName() +
                " [" +
                to_string(
                    spell.getMPCost()
                ) +
                " MP]"
            );
        }

        const int choice =
            navigateMenu(names);

        if (
            choice >= 0 &&
            choice < static_cast<int>(
                spells.size()
            )
        )
        {
            performSpell(
                spells[choice]
            );
        }

        return;
    }

    if (selected == 2)
    {
        useItem();
        return;
    }

    if (selected == 3)
    {
        defending = true;

        addLog(
            player.name +
            " takes a defensive stance."
        );

        return;
    }

    if (selected == 4)
    {
        fled = true;

        addLog(
            player.name +
            " attempts to escape."
        );

        return;
    }
}

void BattleSystem::enemyTurn()
{
    if (
        !enemy.isAlive() ||
        !player.isAlive()
    )
    {
        return;
    }

    // The enemy cry is an effect, not the battle music.
    // so it plays over the battle background.

    switch (enemy.getId())
    {
    case 1:
        SoundManager::event("wild_boar_cry");
        break;

    case 2:
        // The current asset set contains bandit_cry.mp3.
        // Both the thief encounter and the Bandit use this
        // until a separate thief_cry.mp3 is supplied.
        SoundManager::event("bandit_cry");
        break;

    case 3:
        SoundManager::event("river_gharial_cry");
        break;

    case 4:
        SoundManager::event("shadow_wolf_cry");
        break;

    case 5:
        SoundManager::event("cave_serpent_cry");
        break;

    case 6:
        SoundManager::event("guardian_tiger_cry");
        break;

    case 9:
        SoundManager::event("ancient_guardian_cry");
        break;

    default:
        break;
    }

    const Skill skill =
        enemy.getRandomSkill();

    int damage =
        max(0, skill.damage);

    if (defending)
    {
        damage =
            (damage + 1) / 2;

        defending = false;

        addLog(
            player.name +
            " blocks part of the attack."
        );
    }

    player.takeDamage(damage);

    ++enemyHitsTaken;

    addLog(
        enemy.getName() +
        " used " +
        skill.name +
        "!"
    );

    addLog(
        player.name +
        " took " +
        to_string(damage) +
        " damage."
    );
}

bool BattleSystem::run()
{
    battleLog.clear();
    enemyHitsTaken = 0;
    defending = false;
    fled = false;

    addLog("Battle started!");
    addLog(
        enemy.getName() +
        " appeared!"
    );

    while (
        player.isAlive() &&
        enemy.isAlive()
    )
    {
        // Redraw the full battle layout before every turn.
        // This means HP, MP and enemy HP are visible
        // instead of being overwritten by the action box.

        drawGameLayout(
            "BATTLE",
            "Combat"
        );

        drawBattlePanel(player, enemy, battleLog);

        playerTurn();

        // Show the result of the player's action - damage dealt,
        // the ability name, the attack sound already fired inside
        // performAttack()/performSpell() - before the enemy
        // reacts. Turns resolve one at a time, like a classic
        // turn-based RPG exchange, instead of both turns landing
        // before the screen ever updates.

        drawGameLayout(
            "BATTLE",
            "Combat"
        );

        drawBattlePanel(player, enemy, battleLog);

        if (
            fled ||
            !enemy.isAlive() ||
            !player.isAlive()
        )
        {
            break;
        }

        Sleep(1100);

        enemyTurn();

        // Same beat on the enemy's side: their attack name, the
        // HP it took, and their cry play out and stay on screen
        // before control returns to the player.

        drawGameLayout(
            "BATTLE",
            "Combat"
        );

        drawBattlePanel(player, enemy, battleLog);

        if (!player.isAlive())
            break;

        Sleep(1100);
    }

    if (
        fled &&
        player.isAlive() &&
        enemy.isAlive()
    )
    {
        SoundManager::event("run");

        drawGameLayout(
            "BATTLE",
            "Combat"
        );

        drawBattlePanel(player, enemy, battleLog);

        waitForEnter();

        return false;
    }

    if (
        player.isAlive() &&
        !enemy.isAlive()
    )
    {
        addLog("Victory!");

        SoundManager::event("victory");

        player.gold += enemy.getGold();

        addLog(
            "Earned " +
            to_string(
                enemy.getGold()
            ) +
            " gold."
        );

        const int xpReward =
            max(
                0,
                enemy.getId() * 100
            );

        player.addXP(xpReward);

        addLog(
            "Earned " +
            to_string(xpReward) +
            " XP."
        );

        // heal up only after the enemy is actually dead - had a bug
        // earlier where I restored HP/MP too early and it let free wins
        player.hp = player.maxHp;
        player.mp = player.maxMp;

        addLog(
            "HP and MP fully restored after battle."
        );

        if (
            enemy.getId() == 9 &&
            enemyHitsTaken < 3
        )
        {
            player.setFlag(
                "achievement_viva_espana"
            );

            SoundManager::event(
                "hidden_achievement"
            );

            addLog(
                "Hidden achievement unlocked: Viva Espana!"
            );
        }

        drawGameLayout(
            "BATTLE - VICTORY",
            "Combat"
        );

        drawBattlePanel(player, enemy, battleLog);

        waitForEnter();

        return true;
    }

    addLog("You were defeated.");

    SoundManager::event("defeat");

    drawGameLayout(
        "BATTLE - DEFEAT",
        "Combat"
    );

    drawBattlePanel(player, enemy, battleLog);

    waitForEnter();

    return false;
}
