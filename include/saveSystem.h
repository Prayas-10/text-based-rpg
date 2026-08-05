#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>

class Player;

class saveSystem
{
    public:
        // quick helpers from before I added full saves - just the
        // progress number. still used for lightweight checks around
        // the game loop, and load() still works fine on files
        // written by saveGame() since progress is always line 1
        void save(int progress, int slot);
        int load(int slot);
        void checkpoint(int progress, int currentSlot);
        void saveLastSlot(int slot);
        int loadLastSlot();

        // Full save: progress, current location, and the complete
        // player state (HP/MP, level, XP, gold, inventory, story
        // flags). Can be called at any point in the game - world
        // screen, mid-battle, or mid-prologue - not only at
        // chapter boundaries.
        void saveGame(
            int progress,
            int slot,
            const Player& player,
            const std::string& location
        );

        // Full load: returns the stored progress (0 if the slot
        // is empty/corrupt), and fills player + location with the
        // saved state.
        int loadGame(
            int slot,
            Player& player,
            std::string& location
        );
};

#endif
