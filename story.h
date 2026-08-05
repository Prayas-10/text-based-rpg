#ifndef STORY_H
#define STORY_H

#include "prologue.h"
#include <string>
#include <vector>

class Player;
class Map;

class Story
{
private:
    Prologue prologue;

    // Set once at the top of each chapter (and updated by fight(),
    // which already knows the chapter's location) so speak() can
    // show the Kaji's actual current location instead of a fixed
    // placeholder.
    mutable std::string currentLocation = "Journey";

    void speak(const std::string& text) const;

    bool fight(
        Player& player,
        Map& map,
        int enemyId,
        const std::string& chapterMusic
    ) const;

    int choose(
        const std::vector<std::string>& options
    ) const;

    // Shops (chapter 1) - buying something deducts gold and adds
    // it to the inventory, even stuff like sharpening/repairs that
    // don't really "do" anything in battle yet.
    void buy(
        Player& player,
        const std::string& label,
        int itemId,
        const std::string& itemName,
        const std::string& category,
        const std::string& effectType,
        int power,
        int price
    ) const;

    void sellItem(Player& player) const;

    void blacksmith(Player& player) const;
    void herbalist(Player& player) const;
    void market(Player& player) const;

public:
    void playPrologue(Player& player);

    void playChapter1(
        Player& player,
        Map& map
    );

    void playChapter2(
        Player& player,
        Map& map
    );

    void playChapter3(
        Player& player,
        Map& map
    );

    void playChapter4(
        Player& player,
        Map& map
    );
};

#endif
