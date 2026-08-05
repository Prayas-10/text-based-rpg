#include "story.h"
#include "battlesystem.h"
#include "enemy.h"
#include "ui.h"
#include "player.h"
#include "map.h"
#include "soundManager.h"
#include "item.h"
#include "saveSystem.h"

#include <string>
#include <vector>

using namespace std;

extern int currentSlot;

void Story::speak(
    const string& text
) const
{
    // don't clearScreen() here - the dialogue lives in the story
    // viewport and gets typed out there instead. the location text
    // just shows whatever currentLocation was last set to (each
    // chapter sets it at the start, fight() keeps it synced too)
    drawGameLayout(
        "STORY",
        currentLocation
    );

    typewriterStoryPanel(
        "DHARMADEVA'S BLADE",
        text
    );

    waitForEnter();
}

int Story::choose(
    const vector<string>& options
) const
{
    return navigateMenu(options);
}

bool Story::fight(
    Player& player,
    Map& map,
    int enemyId,
    const string& chapterMusic
) const
{
    const vector<Enemy> enemies =
        loadEnemies(
            "data/enemy.json"
        );

    for (const Enemy& source : enemies)
    {
        if (source.getId() != enemyId)
            continue;

        // Chapter music is stopped before battle music starts.
        // Battle music uses the music channel, while enemy cries
        // use the separate effect channel.

        SoundManager::stopMusic();

        SoundManager::playLoop(
            "data/sounds/battle_background.mp3"
        );

        Enemy enemy = source;

        BattleSystem battle(
            player,
            enemy,
            map
        );

        const bool won =
            battle.run();

        // Battle is now completely over.
        // Stop battle music before restoring chapter music.

        SoundManager::stopMusic();

        if (won)
        {
            SoundManager::playLoop(
                chapterMusic
            );
        }

        return won;
    }

    return false;
}

void Story::playPrologue(
    Player& p
)
{
    prologue.play(p);
}

// -- SHOPS (Chapter 1) --
void Story::buy(
    Player& player,
    const string& label,
    int itemId,
    const string& itemName,
    const string& category,
    const string& effectType,
    int power,
    int price
) const
{
    if (player.gold < price)
    {
        speak(
            "You don't have enough gold for that. (" +
            to_string(price) +
            " gold needed)"
        );

        return;
    }

    player.gold -= price;

    player.inventory.addItem(
        Item(
            itemId,
            itemName,
            category,
            effectType,
            power
        ),
        1
    );

    speak(
        "You bought " +
        label +
        " for " +
        to_string(price) +
        " gold."
    );
}

void Story::sellItem(
    Player& player
) const
{
    if (player.inventory.empty())
    {
        speak("You have nothing to sell.");
        return;
    }

    vector<string> names;

    for (const auto& entry : player.inventory.getItems())
    {
        names.push_back(
            entry.item.getName() +
            " x" +
            to_string(entry.quantity)
        );
    }

    names.push_back("Cancel");

    const int choice = choose(names);

    if (
        choice < 0 ||
        choice == static_cast<int>(names.size()) - 1
    )
    {
        return;
    }

    const auto& entries = player.inventory.getItems();
    const int itemId = entries[choice].item.getId();
    const string itemName = entries[choice].item.getName();

    player.inventory.removeItem(itemId, 1);
    player.gold += 5;

    speak(
        "You sold " +
        itemName +
        " for 5 gold."
    );
}

void Story::blacksmith(
    Player& player
) const
{
    speak(
        "You've entered the blacksmith's forge. "
        "The blacksmith greets you warmly and offers his services."
    );

    while (true)
    {
        const int choice = choose(
            {
                "Sharpen Sword (10 gold)",
                "Repair Armor (10 gold)",
                "Buy Shield (25 gold)",
                "Upgrade Armor (30 gold)",
                "Leave"
            }
        );

        if (choice < 0 || choice == 4)
            break;

        if (choice == 0)
        {
            buy(player, "a sharpened sword", 19, "Sharpened Sword", "Material", "none", 0, 10);
            player.setFlag("sword_sharpened");
        }
        else if (choice == 1)
        {
            buy(player, "repaired armor", 20, "Repaired Armor", "Material", "none", 0, 10);
            player.setFlag("armor_repaired");
        }
        else if (choice == 2)
        {
            buy(player, "a shield", 18, "Shield", "Armor", "none", 5, 25);
        }
        else if (choice == 3)
        {
            buy(player, "an armor upgrade", 21, "Armor Upgrade", "Armor", "none", 8, 30);
            player.setFlag("armor_upgraded");
        }
    }
}

void Story::herbalist(
    Player& player
) const
{
    speak(
        "You've entered the herbalist's shop. "
        "The herbalist greets you and offers his remedies."
    );

    while (true)
    {
        const int choice = choose(
            {
                "Healing Herb - jadibuti (8 gold)",
                "Antidote for Poison (12 gold)",
                "Bandages (5 gold)",
                "Stamina Herb (10 gold)",
                "Leave"
            }
        );

        if (choice < 0 || choice == 4)
            break;

        if (choice == 0)
            buy(player, "a healing herb", 4, "Healing Herb", "Consumable", "heal_hp", 25, 8);
        else if (choice == 1)
            buy(player, "an antidote", 6, "Antidote", "Consumable", "cure_poison", 0, 12);
        else if (choice == 2)
            buy(player, "bandages", 5, "Bandage", "Consumable", "heal_hp", 15, 5);
        else if (choice == 3)
            buy(player, "a stamina herb", 7, "Stamina Herb", "Consumable", "restore_mp", 15, 10);
    }
}

void Story::market(
    Player& player
) const
{
    speak(
        "You've entered the bustling marketplace. "
        "Vendors shout their wares and the aroma of street food fills the air."
    );

    while (true)
    {
        const int choice = choose(
            {
                "Buy Provisions (6 gold)",
                "Buy Travel Clothes (8 gold)",
                "Buy a Torch (5 gold)",
                "Sell an Item",
                "Leave"
            }
        );

        if (choice < 0 || choice == 4)
            break;

        if (choice == 0)
            buy(player, "provisions", 22, "Provisions", "Consumable", "heal_hp", 10, 6);
        else if (choice == 1)
            buy(player, "travel clothes", 23, "Travel Clothes", "Material", "none", 0, 8);
        else if (choice == 2)
            buy(player, "a torch", 24, "Torch", "Material", "none", 0, 5);
        else if (choice == 3)
            sellItem(player);
    }
}

// -- CHAPTER 1 - THE KINGDOM OF GORKHA --
void Story::playChapter1(
    Player& p,
    Map& m
)
{
    const string music =
        "data/sounds/chapter1_gorkha.mp3";

    SoundManager::stopMusic();
    SoundManager::playLoop(music);

    m.setLocation(
        "Kingdom of Gorkha"
    );

    currentLocation = "Kingdom of Gorkha";

    speak("CHAPTER 1 - THE KINGDOM OF GORKHA");

    speak(
        "The first rays of dawn spread across the hills of Gorkha as the "
        "palace slowly came to life. Soldiers stood watch along the stone "
        "walls while merchants and craftsmen began preparing for another "
        "day within the kingdom."
    );

    speak(
        "The Kaji tightened the straps of his pack and stepped beyond the "
        "palace gates. Every familiar sight - the bustling streets, the "
        "fluttering banners of Gorkha, and the towering fortress above - "
        "served as a reminder of what he was fighting to protect."
    );

    speak(
        "Before leaving the kingdom behind, he decided to make a final "
        "round through the city. There were still a few matters to "
        "settle before the long journey began."
    );

    bool blacksmithVisited = false;
    bool herbalistVisited = false;
    bool marketVisited = false;

    while (true)
    {
        vector<string> options =
        {
            "Visit the Blacksmith",
            "Visit the Herbalist",
            "Visit the Market"
        };

        const bool readyToLeave =
            blacksmithVisited &&
            herbalistVisited &&
            marketVisited;

        if (readyToLeave)
            options.push_back("Leave Town");

        const int choice = choose(options);

        if (choice == 0)
        {
            blacksmithVisited = true;
            blacksmith(p);
        }
        else if (choice == 1)
        {
            herbalistVisited = true;
            herbalist(p);
        }
        else if (choice == 2)
        {
            marketVisited = true;
            market(p);
        }
        else if (readyToLeave && choice == 3)
        {
            break;
        }
    }

    speak(
        "As the Kaji made his way toward the eastern gate, "
        "a frantic shout echoed through the busy streets."
    );

    speak("\"Stop! Thief!\"");

    speak(
        "A thief raced through the crowd with a merchant's stolen pouch. "
        "Without hesitation, the Kaji gave chase through the bustling "
        "marketplace. After a brief pursuit, the thief stopped, drew a "
        "rusty dagger, and turned to face him."
    );

    speak(
        "Thief: \"You'll have to get through me first!\""
    );

    if (!fight(
        p,
        m,
        10,
        music
    ))
    {
        return;
    }

    p.gold += 50;

    p.inventory.addItem(
        Item(
            4,
            "Healing Herb",
            "Consumable",
            "heal_hp",
            25
        ),
        2
    );

    speak(
        "The Kaji returned the stolen pouch to the grateful merchant."
    );

    speak(
        "Merchant: \"Thank you, Kaji. Your courage has saved my "
        "livelihood. Please accept this small reward.\""
    );

    speak(
        "Rewards obtained: 50 Coins, 2 Healing Herbs."
    );

    speak(
        "With the marketplace safe once more, the Kaji continued toward "
        "the eastern gate. Taking one final look at the Kingdom of "
        "Gorkha, he stepped beyond its walls and began his journey into "
        "the countryside."
    );

    p.setFlag("chapter1_complete");
}

// -- CHAPTER 2 - THE COUNTRYSIDE: ROAD TO SLESHMANTAK --
void Story::playChapter2(
    Player& p,
    Map& m
)
{
    const string music =
        "data/sounds/chapter2_countryside.mp3";

    SoundManager::stopMusic();
    SoundManager::playLoop(music);

    m.setLocation(
        "Countryside Village"
    );

    currentLocation = "Countryside Village";

    speak("CHAPTER 2 - THE COUNTRYSIDE: ROAD TO SLESHMANTAK");

    speak(
        "The morning sun rises over the hills as the Kaji leaves Gorkha "
        "behind. The road stretches through peaceful villages, fields "
        "and flowing rivers."
    );

    speak(
        "Though the countryside is calm, the Kaji cannot forget the "
        "king's command. Somewhere beyond these lands lies the "
        "Sleshmantak Jungle... and the Hidden Cave of Dharmadeva."
    );

    speak(
        "After a long day of travel, the Kaji arrives at a crossroad. "
        "The path to the left leads to a Mountain Pass, while the path "
        "to the right leads to a riverside path."
    );

    const int route = choose(
        {
            "Take the Mountain Pass",
            "Take the Riverside Path"
        }
    );

    if (route == 0)
    {
        speak(
            "The Kaji takes the path to the Mountain Pass, where the air "
            "is crisp and the views are breathtaking."
        );

        speak(
            "As he navigates the narrow trail, a hungry wolf suddenly "
            "emerges from the rocks, blocking his path."
        );

        if (!fight(p, m, 11, music))
            return;

        speak("You have defeated the Wolf!");
    }
    else
    {
        speak(
            "The Kaji follows the riverside path, where the cool breeze "
            "carries the scent of fresh water and the river flows "
            "swiftly beside the trail."
        );

        speak(
            "As he walks along the riverbank, a loud rustling erupts "
            "from the bushes. A wild boar charges out, blocking his way."
        );

        if (!fight(p, m, 1, music))
            return;

        speak("You have defeated the Boar!");
    }

    speak(
        "After overcoming the dangers of the road... both paths merge "
        "once more. Ahead, the Kaji notices smoke rising from a small "
        "village in the distance."
    );

    speak(
        "As the sun begins to descend, the Kaji arrives at a small "
        "village in the countryside. Unlike Gorkha, there are no great "
        "walls or busy markets. The villagers live simple lives, "
        "tending their fields and caring for their families."
    );

    speak(
        "For a moment, the Kaji is reminded why he accepted the king's "
        "mission... to protect the peace that these people cherish."
    );

    speak(
        "As he continues his journey through the village... "
        "a worried farmer approaches."
    );

    speak(
        "Farmer: \"Traveler! Wild Boars have been destroying our crops. "
        "Please... help us!\""
    );

    const int helpChoice = choose(
        {
            "Help the farmer",
            "Decline and move on"
        }
    );

    if (helpChoice == 0)
    {
        speak("The Kaji agrees to help out.");

        if (!fight(p, m, 1, music))
            return;

        speak("You have defeated the Boar!");

        speak(
            "After defeating the beast, the grateful villagers gather "
            "around him."
        );

        speak(
            "Farmer: \"You have saved this season's harvest. "
            "We are forever in your debt.\""
        );

        speak(
            "The village elder steps forward. Village Elder: \"Night "
            "has fallen, brave young man. You've earned a warm meal and "
            "a place to rest. Our village welcomes you.\""
        );

        speak(
            "The Kaji accepts their hospitality and spends the night "
            "safely in the village."
        );

        speak(
            "Night falls. After a warm meal, the Kaji sits beside the "
            "village elder as both look towards the distant forest."
        );

        speak(
            "Village Elder: \"Beyond those hills... lies the "
            "Sleshmantak. Our ancestors feared that forest.\""
        );

        speak("Kaji: \"Is it truly that dangerous?\"");

        speak(
            "Village Elder: \"It is not the beasts you should fear. The "
            "jungle has a will of its own. Many entered seeking glory... "
            "few ever returned.\""
        );

        speak("A heavy silence falls between them.");

        speak(
            "Village Elder: \"Walk with courage... but never with "
            "pride.\""
        );

        speak("Kaji: \"Thank you. I shall remember these words.\"");

        speak(
            "The elder smiles faintly. \"Get some rest, young man. "
            "Tomorrow... your journey shall truly begin.\""
        );
    }
    else
    {
        speak(
            "The Kaji bows politely to the farmer. Kaji: \"I am truly "
            "sorry. My duty leaves me no time to stay.\""
        );

        speak(
            "The farmer nods, though disappointment is clear on his "
            "face. Farmer: \"I understand. May the gods watch over your "
            "journey.\""
        );

        speak(
            "The Kaji resumes his journey, leaving the village behind "
            "as the last rays of sunlight fade beyond the hills."
        );

        speak(
            "As dusk settles over the countryside, a sudden rustling "
            "breaks the silence. A wild boar bursts from the bushes and "
            "charges towards him."
        );

        if (!fight(p, m, 1, music))
            return;

        speak("You have defeated the Boar!");

        speak(
            "Night falls. With no village in sight, the Kaji builds a "
            "small camp beside the road. He gathers dry branches, "
            "lights a fire and roasts the boar meat over the flames."
        );

        speak(
            "The crackling fire is the only sound breaking the night's "
            "silence. As the Kaji finishes his meal... a twig snaps "
            "somewhere beyond the firelight."
        );

        speak(
            "He instantly reaches for his sword. Kaji: \"Who's there?\""
        );

        speak(
            "Silence. Then the sound of another step. An old man "
            "carrying a lantern slowly steps into the light. Without a "
            "word, he sits beside the fire."
        );

        speak(
            "The Kaji never lowers his guard. Old Man: \"Mind if an "
            "old traveler warms himself?\""
        );

        speak(
            "The Kaji studies him for a moment before nodding. The old "
            "man quietly accepts a piece of the roasted meat."
        );

        speak("After a long silence... Kaji: \"Who are you?\"");

        speak(
            "The old man smiles. Old Man: \"Just someone who once "
            "walked where you're going.\""
        );

        speak(
            "The Kaji's expression hardens. Kaji: \"Sleshmantak!? "
            "How did you know?\""
        );

        speak(
            "The old man nods. Old Man: \"Remember this... The beasts "
            "of the Sleshmantak are not what should worry you. The "
            "forest remembers every soul that enters it.\""
        );

        speak("He stands. \"Sleep while you still can.\"");

        speak(
            "Without another word, the old man walks into the darkness. "
            "The Kaji could do nothing but watch until the lantern "
            "disappeared among the trees."
        );

        speak(
            "With dawn still hours away, the Kaji settles down to rest."
        );
    }

    // Mid-chapter checkpoint - matches the old draft's rest() save
    // point. Progress stays at 2 (still Chapter 2), but the full
    // player state (HP/MP, gold, inventory) is saved here too.

    {
        saveSystem save;

        save.saveGame(
            2,
            currentSlot,
            p,
            m.getLocation()
        );
    }

    speak(
        "At night... a voice echoes through the darkness. "
        "\"Only the worthy shall claim the blade.\""
    );

    speak(
        "The Kaji jolts awake before dawn. Though the voice is gone, "
        "its words still linger in his mind."
    );

    speak(
        "The first rays of sunlight pierce the morning mist. The Kaji "
        "silently packs his belongings and sets out once more."
    );

    speak(
        "As the morning mist settles across the countryside, the Kaji "
        "resumes his journey towards Sleshmantak. The morning passes "
        "peacefully. The village fades into the distance, and the "
        "roads become increasingly deserted."
    );

    speak(
        "As the road narrows between rocky cliffs, several figures step "
        "onto the path ahead. Others emerge from the trees behind him. "
        "The Kaji has been ambushed by a group of bandits!"
    );

    speak(
        "Bandit Leader: \"That's far enough, traveler. Hand over your "
        "valuables, and perhaps we'll spare you.\""
    );

    speak(
        "Bandit Leader: \"That armor... you're one of the Gorkhali "
        "Kajis. Royal soldiers are said to travel with heavy purses. "
        "Hand them over.\""
    );

    speak("Kaji: \"Stand aside.\"");

    speak("Bandit Leader: \"You'll regret refusing us.\"");

    if (!fight(p, m, 2, music))
        return;

    speak(
        "You have defeated the bandits! They flee into the countryside, "
        "leaving the roads clear once more."
    );

    speak(
        "By evening... the countryside had disappeared. The trees "
        "became taller. The birdsong grew quieter. Mist crept across "
        "the road. The Kaji stopped."
    );

    speak(
        "Before him... stood an ancient forest unlike any he had seen "
        "before."
    );

    speak(
        "THE SLESHMANTAK JUNGLE. The villagers spoke of this place "
        "only in whispers. Some claimed spirits wandered beneath its "
        "towering trees. Others believed no traveler who entered alone "
        "ever returned."
    );

    speak(
        "The Kaji rested his hands upon the hilt of his sword. Without "
        "another glance behind him... he stepped into the shadows of "
        "the Sleshmantak Jungle."
    );

    speak("Whatever awaited there... he would face it alone.");

    p.setFlag("chapter2_complete");
}

// -- CHAPTER 3 - THE FOREST OF GORKHA --
void Story::playChapter3(
    Player& p,
    Map& m
)
{
    const string music =
        "data/sounds/chapter3_forest.mp3";

    SoundManager::stopMusic();
    SoundManager::playLoop(music);

    m.setLocation(
        "Forest of Gorkha"
    );

    currentLocation = "Forest of Gorkha";

    speak("CHAPTER 3 - THE FOREST OF GORKHA");

    speak(
        "Leaving the Kingdom of Gorkha behind, the Kaji ventured into "
        "the dense forest that stretched across the foothills. Towering "
        "trees blocked much of the sunlight, while the sounds of birds "
        "and distant wildlife echoed through the wilderness."
    );

    speak(
        "As the Kaji pressed deeper into the forest, a wild boar "
        "suddenly burst from the undergrowth, charging straight toward "
        "him."
    );

    if (!fight(p, m, 1, music))
        return;

    speak(
        "After a brief struggle, the Kaji defeated the wild boar and "
        "continued along the forest path."
    );

    speak(
        "Soon, he arrived at a fast-flowing river. Finding a safe place "
        "to cross, he carefully stepped into the water. Halfway across, "
        "the surface suddenly rippled as a gharial emerged, blocking "
        "his path."
    );

    if (!fight(p, m, 3, music))
        return;

    speak(
        "After a fierce battle, the Kaji defeated the gharial and "
        "safely crossed the river."
    );

    speak(
        "As he approached the edge of the forest, a powerful roar "
        "echoed through the trees. From the shadows emerged a "
        "magnificent tiger, its piercing eyes fixed upon the Kaji. The "
        "villagers called it the Guardian Tiger, the ancient protector "
        "of the forest and the final obstacle before anyone could "
        "leave its domain."
    );

    if (!fight(p, m, 6, music))
        return;

    speak(
        "After an intense battle, the Kaji emerged victorious. The "
        "Guardian Tiger let out one final roar before retreating into "
        "the depths of the forest, acknowledging the Kaji's strength "
        "and determination."
    );

    speak(
        "With the forest now behind him, the Kaji stepped onto the "
        "open path beyond, ready to continue his journey toward the "
        "next region."
    );

    p.setFlag("chapter3_complete");
}

// -- CHAPTER 4 - THE CAVE OF SHADOWS --
void Story::playChapter4(
    Player& p,
    Map& m
)
{
    const string music =
        "data/sounds/chapter4_cave.mp3";

    SoundManager::stopMusic();
    SoundManager::playLoop(music);

    m.setLocation(
        "Cave of Shadows"
    );

    currentLocation = "Cave of Shadows";

    speak("CHAPTER 4 - THE CAVE OF SHADOWS");

    speak(
        "Beyond the forest, the Kaji arrived at the foot of a towering "
        "mountain. Hidden among its rocky cliffs lay the entrance to a "
        "dark and ancient cave. A cold wind swept through the opening, "
        "carrying with it an eerie silence."
    );

    speak(
        "As the Kaji approached, a pair of glowing eyes appeared from "
        "the shadows. A fierce Shadow Wolf stepped into his path, "
        "growling as it prepared to attack."
    );

    if (!fight(p, m, 4, music))
        return;

    speak(
        "After a hard-fought battle, the Kaji defeated the Shadow Wolf "
        "and cautiously entered the cave."
    );

    speak("The cave soon split into two narrow passages.");

    const int path = choose(
        {
            "Go Left",
            "Go Right"
        }
    );

    if (path == 0)
    {
        p.setFlag("cave_left");

        speak(
            "The left passage is narrow and cold. Tucked into a "
            "crevice, the Kaji finds a half-burnt torch left behind by "
            "an earlier traveler."
        );

        p.inventory.addItem(
            Item(24, "Torch", "Material", "none", 0),
            1
        );
    }
    else
    {
        p.setFlag("cave_right");

        speak(
            "The right passage opens into a wider cavern. Among "
            "scattered bones, the Kaji finds a pouch of coins dropped "
            "by some unlucky soul."
        );

        p.gold += 20;
    }

    speak("Both paths eventually lead to the heart of the cave.");

    speak(
        "As the Kaji ventured deeper into the darkness, a deafening "
        "hiss echoed through the cavern. From the shadows emerged a "
        "massive Cave Serpent, its scales glistening in the faint "
        "light. The beast coiled around towering pillars of stone, its "
        "piercing eyes fixed upon the lone warrior."
    );

    if (!fight(p, m, 5, music))
        return;

    speak(
        "The battle pushed the Kaji to his limits, but with one final "
        "strike, he defeated the Cave Serpent."
    );

    speak(
        "Kaji: \"The darkness has been conquered. Now, the real "
        "journey begins.\""
    );

    speak(
        "Before leaving, a faint blue glow caught the Kaji's attention. "
        "Curious, he followed the light to a hidden chamber concealed "
        "behind the serpent's lair. At the center of the chamber stood "
        "an ancient stone altar. Resting upon it was a magnificent "
        "sword, its blade engraved with mysterious runes that "
        "shimmered with an otherworldly light."
    );

    speak(
        "As the Kaji grasped the hilt, a surge of energy flowed "
        "through his body, and an ancient voice echoed throughout the "
        "chamber."
    );

    speak(
        "Ancient Voice: \"You have proven your courage. Wield this "
        "blade wisely, for it is a weapon capable of changing the tide "
        "of even the greatest battles.\""
    );

    speak(
        "The Kaji slowly drew the sword from the altar. A brilliant "
        "flash of light filled the chamber as the weapon awakened "
        "after centuries of silence."
    );

    p.inventory.addItem(
        Item(25, "Dharmadeva's Blade", "Weapon", "none", 20),
        1
    );

    speak("System: You have obtained the Dharmadeva's Blade.");

    speak(
        "Item Description: A legendary sword said to possess the power "
        "to change the tide of any battle. Though its true strength "
        "remains dormant, it will awaken as its wielder grows stronger."
    );

    speak(
        "The Kaji secured the Dharmadeva's Blade to his side and "
        "smiled."
    );

    speak(
        "Kaji: \"This blade... it feels like it remembers every "
        "warrior who ever held it. I will carry their will forward and "
        "protect Gorkha, even if it costs me everything.\""
    );

    speak(
        "He tightened his grip on the sword as he stepped out of the "
        "cave, the harsh sunlight washing over him after the darkness "
        "within. Clutching his newly acquired weapon, the Kaji left "
        "the Cave of Shadows behind."
    );

    p.setFlag("chapter4_complete");
}
