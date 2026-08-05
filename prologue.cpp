#include "prologue.h"
#include "ui.h"
#include "saveSystem.h"
#include "soundManager.h"
#include "player.h"

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Current save slot is managed by the save/game system.
extern int currentSlot;

namespace
{
    // Every prologue line renders through the exact same
    // drawGameLayout + story panel that the rest of the game
    // uses, instead of clearScreen() + raw typewriter(). This
    // keeps the prologue strictly inside the RPG layout.

    void speak(
        const string& title,
        const string& location,
        const string& text
    )
    {
        drawGameLayout(title, location);
        typewriterStoryPanel("PROLOGUE", text);
        waitForEnter();
    }
}

// -- PLAY PROLOGUE --
void Prologue::play(Player& player)
{
    SoundManager::stopMusic();
    SoundManager::playLoop("data/sounds/prologue_palace.mp3");

    opening(player);
    scene1(player);
    scene2(player);

    // Prologue music belongs only to the prologue.
    SoundManager::stopMusic();
}

// -- PROLOGUE OPENING --
void Prologue::opening(Player& player)
{
    const string title = "PROLOGUE: THE DIVIDED LANDS";
    const string location = "The Divided Lands";

    speak(title, location, "It was the time of early 1800s (BS).");

    speak(
        title, location,
        "The mighty Himalayas stood silent, witness to a land torn apart."
    );

    speak(
        title, location,
        "Countless small kingdoms - Gorkha, Kantipur, Laltipur, "
        "Bhaktapur, Patan, and many others - each ruled by its own king, "
        "each unaware that history was about to change them forever."
    );

    speak(
        title, location,
        "KING PRITHIVI NARAYAN SHAH of the Gorkha kingdom dreamt of a united kingdom."
    );

    speak(
        title, location,
        "Driven by courage, ambition, and an unwavering commitment to his vision, "
        "the king embarked upon a historic campaign of unification."
    );

    speak(
        title, location,
        "Despite his unwavering determination, his path was far from easy, "
        "for he faced numerous hurdles on his way."
    );

    speak(
        title, location,
        "Each setback tested his resolve and threatened to bring his grand vision to an end."
    );

    speak(title, location, "Many sacrifices were made.");

    speak(title, location, "Countless obstacles stood in his path.");

    speak(
        title, location,
        "Yet... none proved more challenging than the fortified city of KIRTIPUR, "
        "where he was defeated not once, but twice."
    );

    speak(title, location, "But the king's spirit remained unbroken.");

    speak(
        title, location,
        "Seeking guidance in this time of uncertainty, "
        "the king journeyed to the sacred Temple of Gorakhnath."
    );

    (void)player;
}

// -- Scene 1: The Temple of Desperation --
void Prologue::scene1(Player& player)
{
    const string title = "SCENE 1: THE TEMPLE OF DESPERATION";
    const string location = "Temple of Gorakhnath";

    speak(
        title, location,
        "Three nights after the second defeat at Kirtipur, "
        "the king could not rest."
    );

    speak(
        title, location,
        "Seeking guidance, he made his way to the sacred Temple of Gorakhnath, "
        "nestled among the mist-covered hills."
    );

    speak(title, location, "Candles flickered against the temple walls.");

    speak(title, location, "Thick incense smoke curled through the air.");

    speak(
        title, location,
        "The king fell to his knees before the altar, and prayed for guidance."
    );

    speak(
        title, location,
        "KING: Give me the strength. Give me wisdom. Show me the path. "
        "O God, or take my life if this dream is not meant to be."
    );

    speak(title, location, "He closed his eyes. Silence stretched.");

    speak(title, location, "An old priest approached him.");

    speak(
        title, location,
        "Priest: Your Majesty, your suffering has brought you here for a reason."
    );

    speak(
        title, location,
        "KING: I seek a path to unity. I have failed twice at Kirtipur."
    );

    speak(title, location, "Priest: Then perhaps... you must seek THE SAGE.");

    speak(title, location, "The king looked up with a glimmer of hope in his eyes.");

    speak(title, location, "KING: What Sage?");

    speak(
        title, location,
        "Priest: The holy person who meditates deep in the Sleshmantak Jungle. "
        "They say he has knowledge beyond that of an ordinary person."
    );

    speak(title, location, "If anyone knows the path forward, it is HIM.");

    speak(title, location, "The king stood up. The priest's words had given him hope.");

    speak(
        title, location,
        "At dawn, the king descended the stone steps of Gorakhnath. "
        "The bells behind him faded into the cold mountain air."
    );

    speak(
        title, location,
        "Ahead lay a path, leading towards the dark green borders "
        "of the Sleshmantak jungle."
    );

    speak(
        title, location,
        "The next morning the king and his guards were deep inside "
        "Sleshmantak Jungle."
    );

    speak(
        title, location,
        "Venturing deep into its ancient woods, they eventually came upon "
        "a small, secluded hut where a sage sat in silent meditation."
    );

    speak(
        title, location,
        "The king immediately felt his presence and knelt before the hut "
        "and bowed his head."
    );

    speak(title, location, "The voice came from within.");

    speak(
        title, location,
        "Voice: You seek victory, but do you understand what it requires?"
    );

    speak(
        title, location,
        "From the shadows emerged an old sage. His eyes seemed to see beyond time."
    );

    speak(
        title, location,
        "He wore simple robes, yet... his presence commanded respect."
    );

    speak(
        title, location,
        "SAGE: The battle is not won by weapons alone. It requires sacrifice, "
        "wisdom and essentially..., the courage to walk the path that others fear!"
    );

    speak(title, location, "The king looked up, startled.");

    speak(
        title, location,
        "KING: How did you know why I came here? "
        "Are you the wise sage the priest spoke of?"
    );

    speak(
        title, location,
        "SAGE: Names matter little. Some call me a sage; others, a hermit. "
        "What matters is that you have come seeking answers."
    );

    speak(title, location, "The sage steps forward.");

    speak(
        title, location,
        "SAGE: I have waited centuries for someone whose heart seeks unity "
        "rather than conquest."
    );

    speak(title, location, "For the one worthy to seek what lies hidden.");

    speak(
        title, location,
        "SAGE: There exists a place forgotten by time... "
        "THE HIDDEN CAVE OF DHARMADEVA."
    );

    speak(
        title, location,
        "Within it rests an ancient relic known as Dharmadeva's Blade, "
        "a weapon said to grant victory only to those who wield it with a pure heart."
    );

    speak(title, location, "The king's eyes widen.");

    speak(title, location, "KING: Where is this place? How do I find it?");

    speak(
        title, location,
        "SAGE: The valley is hidden beyond towering mountains and guarded by trials "
        "that have claimed the lives of even the bravest."
    );

    speak(
        title, location,
        "Its path cannot be found on any map. Only those with unwavering resolve "
        "may hope to discover it."
    );

    speak(
        title, location,
        "KING: Then I shall leave at once and retrieve the blade myself."
    );

    speak(title, location, "The sage slowly shook his head.");

    speak(
        title, location,
        "SAGE: No. This is not a path meant for a king. A ruler's duty is to his "
        "people, not to the perils of a forgotten valley."
    );

    speak(
        title, location,
        "SAGE: If you fail, your dream of a united nation dies with you."
    );

    speak(title, location, "The king fell silent.");

    speak(
        title, location,
        "SAGE: Return to your kingdom and summon the Kaji you trust above all others."
    );

    speak(
        title, location,
        "Entrust this quest to him, for only a soul of unwavering courage "
        "and unshakable loyalty can survive the trials that await there."
    );

    speak(
        title, location,
        "Only HE can endure the valley's dangers, recover "
        "\"The Dharmadeva's Blade\" and place it in your hands."
    );

    speak(
        title, location,
        "The king remained silent for a long moment, reflecting on the sage's words."
    );

    speak(title, location, "At last, he bowed his head in respect.");

    speak(
        title, location,
        "KING: Then so it shall be. I will place my faith in the one "
        "that has never failed me."
    );

    speak(title, location, "The sage slowly stepped back into the shadows of the hut.");

    speak(title, location, "Go now. Destiny awaits.");

    speak(
        title, location,
        "Said the sage as he closed his eyes and sank once more into deep meditation."
    );

    speak(title, location, "The king bowed respectfully before the sage before turning away.");

    speak(
        title, location,
        "The cool breeze of Sleshmantak Jungle greeted him as the first rays "
        "of the morning sun filtered through the towering trees."
    );

    speak(
        title, location,
        "Without another word, he and his guards began the journey back to the palace, "
        "carrying with them not the blade, but the hope of one day claiming it."
    );

    speak(title, location, "END OF SCENE 1.");

    // Scene 1 checkpoint - full player state, saveable at this point too.
    saveSystem s;
    s.saveGame(1, currentSlot, player, location);
}

// -- Scene 2: The Royal Palace --
void Prologue::scene2(Player& player)
{
    const string title = "SCENE 2: THE ROYAL PALACE";
    const string location = "Gorkha Palace";

    speak(
        title, location,
        "By nightfall, King Prithivi Narayan Shah had returned to the palace."
    );

    speak(
        title, location,
        "The sage's words echoed in his mind throughout the journey home..."
    );

    speak(title, location, "Without delay, the king summoned his trusted Kaji.");

    speak(
        title, location,
        "The Kaji entered the royal chamber and bowed before the king."
    );

    speak(
        title, location,
        "Kaji: Your Majesty, I await your command. "
        "Whatever your will, I shall see it done."
    );

    speak(
        title, location,
        "KING: I have got a glimpse of hope where I least expected it."
    );

    speak(
        title, location,
        "Guided by a priest, I journeyed deep into the Sleshmantak Jungle, "
        "where I met a sage unlike any other."
    );

    speak(
        title, location,
        "He spoke of an ancient blade hidden in the \"Cave of Dhermadeva\"."
    );

    speak(
        title, location,
        "The blade said to grant victory to those who wield it with pure intention."
    );

    speak(title, location, "The Kaji listened in respectful silence.");

    speak(title, location, "KING: You must go and retrieve this blade!");

    speak(
        title, location,
        "This mission will test your courage, wisdom and your resolve."
    );

    speak(title, location, "It is a dangerous mission... but a necessary one.");

    speak(
        title, location,
        "So.. our dream of a united nation... now rests upon your shoulders."
    );

    speak(title, location, "The Kaji lowered his head.");

    speak(
        title, location,
        "Kaji: Your Majesty, I shall carry out your command without hesitation."
    );

    speak(
        title, location,
        "I shall return with \"The Dharmadeva's blade\"... "
        "or I shall not return at all."
    );

    speak(title, location, "The king nodded solemnly.");

    speak(title, location, "At once, the Kaji began preparing for the expedition.");

    speak(
        title, location,
        "He gathered food, medical herbs, water, a sturdy sword "
        "and other essential supplies for the journey ahead."
    );

    speak(
        title, location,
        "After inspecting his armor and securing his sword at his side, "
        "he made his final preparations."
    );

    speak(
        title, location,
        "Before his departure, he stood for a moment at the palace gate, "
        "looking towards the distant mountains."
    );

    speak(
        title, location,
        "Some where beyond them... laid the HIDDEN CAVE OF DHARMADEVA."
    );

    speak(title, location, "The road ahead was long, and the dangers were many...");

    speak(title, location, "But the mission had begun...");

    speak(title, location, "END OF SCENE 2.");

    // Scene 2 checkpoint - full player state.
    saveSystem s;
    s.saveGame(1, currentSlot, player, location);
}
