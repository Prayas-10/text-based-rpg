#include "saveSystem.h"
#include "player.h"

#include <fstream>
#include <string>
#include <limits>

using namespace std;

namespace
{
    string slotFilename(int slot)
    {
        if (slot < 1 || slot > 3)
            slot = 1;

        return "save" + to_string(slot) + ".txt";
    }
}

void saveSystem::save(
    int progress,
    int slot
)
{
    ofstream file(slotFilename(slot));

    if (file)
        file << progress;
}

int saveSystem::load(
    int slot
)
{
    ifstream file(slotFilename(slot));

    if (!file)
        return 0;

    int progress = 0;

    file >> progress;

    return progress;
}

void saveSystem::checkpoint(
    int progress,
    int currentSlot
)
{
    // used to call clearScreen() here, which wiped the whole layout
    // every time you hit a checkpoint - looked jarring, removed it
    save(
        progress,
        currentSlot
    );
}

void saveSystem::saveLastSlot(
    int slot
)
{
    ofstream file("lastSlot.txt");

    if (file)
        file << slot;
}

int saveSystem::loadLastSlot()
{
    ifstream file("lastSlot.txt");

    if (!file)
        return 1;

    int slot = 1;

    file >> slot;

    if (
        slot < 1 ||
        slot > 3
    )
    {
        slot = 1;
    }

    return slot;
}

void saveSystem::saveGame(
    int progress,
    int slot,
    const Player& player,
    const string& location
)
{
    ofstream file(slotFilename(slot));

    if (!file)
        return;

    // file layout:
    //   line 1: progress (kept first so the old load() helper
    //           still works fine on these files without changes)
    //   line 2: current location
    //   rest:   whatever Player::saveToFile() dumps out
    //           (stats, level, gold, inventory, flags)
    file << progress << '\n';
    file << location << '\n';

    player.saveToFile(file);
}

int saveSystem::loadGame(
    int slot,
    Player& player,
    string& location
)
{
    ifstream file(slotFilename(slot));

    if (!file)
        return 0;

    int progress = 0;

    file >> progress;

    if (!file)
        return 0;

    file.ignore(
        (numeric_limits<streamsize>::max)(),
        '\n'
    );

    if (!getline(file, location) || location.empty())
    {
        // old save files from before I added this only stored the
        // progress number, so there's no location/player data to read
        location = "Kingdom of Gorkha";
        return progress;
    }

    player.loadFromFile(file);

    return progress;
}
