#include <iostream>
#include <json.hpp>
#include <enemy.h>
#include <player.h>
#include <inventory.h>
#include <item.h>
#include <ui.h>
#include <constant.h>

using json = nlohmann::json;

void battle(Player &player, Enemy &enemy)
{
    std::cout << "\n=== A wild " << enemy.getName() << " appears! ===\n";

    while (player.getHp() > 0 && enemy.getHp() > 0)
    {
        displayBattleStatus(player, enemy);

        std::cout << "\nChoose an action:\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Use Item (Potion)\n";
        std::cout << "3. Run\n";
        std::cout << ">>> ";
        int choice;
        std::cin >> choice;

        bool turnPassed = false; // Ensures enemy doesn't attack if player makes an invalid choice

        switch (choice)
        {
        case 1:
        {
            Skill skill = player.getRandomSkill();
            std::cout << "\nYou use " << skill.name << "!\n";

            // Formula: Damage = Skill Damage - Enemy Defense
            int damageDealt = skill.damage - enemy.getDef();
            if (damageDealt < 1)
            {
                damageDealt = 1; // Minimum 1 damage cap
            }
            
            enemy.takeDamage(damageDealt);
            std::cout << "You dealt " << damageDealt << " damage to " << enemy.getName() << "!\n";

            turnPassed = true;
            break;
        }
        case 2:
        {
            if (player.getInventory().empty())
            {
                std::cout << "\nYour inventory is empty!\n";
                continue; // Loops back up, doesn't cost a turn
            }

            displayInventory(player);
            std::cout << "Select an item number: ";
            int itemChoice;
            std::cin >> itemChoice;

            if (itemChoice < 1 || itemChoice > player.getInventory().size())
            {
                std::cout << "Invalid item choice!\n";
                continue; // Loops back up
            }

            Item item = player.getInventory()[itemChoice - 1];
            std::cout << "\nYou use " << item.getName() << "!\n";

            // Item effect internally handles capping health at max HP
            item.applyEffect(player);
            player.removeItem(item);

            turnPassed = true;
            break;
        }
        case 3:
        {
            std::cout << "\nYou managed to run away safely!\n";
            return;
        }
        default:
            std::cout << "\nInvalid action! Focus on the fight.\n";
            continue; // Loops back up without letting enemy attack
        }

        // --- ENEMY'S TURN ---
        // Only executes if the player took a valid action and the enemy didn't perish
        if (turnPassed && enemy.getHp() > 0)
        {
            std::cout << "\n" << enemy.getName() << "'s turn!\n";

            // Safely calls your randomized skill logic from the Enemy class
            Skill enemySkill = enemy.getRandomSkill();
            std::cout << enemy.getName() << " uses \"" << enemySkill.name << "\"!\n";

            // Formula: Damage = Enemy Skill Damage - Player Defense (Without std::max)
            int damageTaken = enemySkill.damage - player.getDef();
            if (damageTaken < 1)
            {
                damageTaken = 1; // Minimum 1 damage cap
            }

            player.takeDamage(damageTaken);
            std::cout << "You took " << damageTaken << " damage!\n";
        }
    }

    // --- BATTLE RESOLUTION ---
    std::cout << "\n===========================================\n";
    if (player.getHp() <= 0)
    {
        std::cout << "You have been defeated by the " << enemy.getName() << "...\n";
    }
    else
    {
        std::cout << "Victory! You defeated the " << enemy.getName() << ".\n";
        // TODO: Add rewards calculation here (e.g., player.addGold(enemy.getGold()))
    }
}