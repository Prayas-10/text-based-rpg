#include "game.h"
#include "ui.h"
#include "constants.h"
#include "soundManager.h"

#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

int currentSlot = 1;

Game::Game()
{
    player = nullptr;
    isRunning = false;
    currentState = STATE_MENU;
}

Game::~Game()
{
    delete player;
    player = nullptr;
}

void Game::run()
{
    isRunning = true;

    setupConsole();

    showTitleScreen();

    if (isRunning)
        showMainMenu();

    SoundManager::stop();
}

void Game::showWorldScreen()
{
    if (player == nullptr)
        return;

    saveSystem save;

    vector<string> messages =
    {
        "The journey continues."
    };

    while (isRunning)
    {
        const int progress =
            save.load(currentSlot);

        drawGameLayout(
            "THE JOURNEY",
            map.getLocation()
        );

        drawCharacterPanel(*player);
        drawQuestPanel(
            progress == 1
                ? "Continue Chapter 1."
                : progress == 2
                    ? "Continue Chapter 2."
                    : progress == 3
                        ? "Continue Chapter 3."
                        : progress == 4
                            ? "Continue Chapter 4."
                            : "All currently available chapters complete."
        );

        // TAB switches focus between the main story option
        // (left box, same place the story panel/combat panel
        // always draws in) and the system options on the
        // right (Inventory / Save / Return to Main Menu).
        // Everything stays exactly where it already was -
        // TAB only changes which side has keyboard focus.

        const vector<string> mainOptions =
        {
            "Continue Story"
        };

        const vector<string> systemOptions =
        {
            "Inventory",
            "Save",
            "Return to Main Menu"
        };

        int panel = 0;
        int index = 0;

        const bool chose =
            navigateDualMenu(
                mainOptions,
                systemOptions,
                panel,
                index
            );

        // selected: 0 = Continue Story, 1 = Inventory,
        // 2 = Save, 3 = Return to Main Menu.
        // ESC behaves like it always did - it backs out to
        // the main menu.

        int selected = 3;

        if (chose)
        {
            selected =
                (panel == 0)
                    ? 0
                    : index + 1;
        }

        if (selected == 0)
        {
            // Progress mapping:
            // 1 -> Chapter 1
            // 2 -> Chapter 2
            // 3 -> Chapter 3
            // 4 -> Chapter 4
            // 5 -> complete

            if (progress <= 1)
            {
                story.playChapter1(
                    *player,
                    map
                );

                if (
                    player->getFlag(
                        "chapter1_complete"
                    )
                )
                {
                    save.saveGame(
                        2,
                        currentSlot,
                        *player,
                        "Countryside Village"
                    );

                    map.setLocation(
                        "Countryside Village"
                    );

                    messages.push_back(
                        "Chapter 1 complete. "
                        "Countryside Village unlocked."
                    );
                }
            }
            else if (progress == 2)
            {
                story.playChapter2(
                    *player,
                    map
                );

                if (
                    player->getFlag(
                        "chapter2_complete"
                    )
                )
                {
                    save.saveGame(
                        3,
                        currentSlot,
                        *player,
                        "Forest of Gorkha"
                    );

                    map.setLocation(
                        "Forest of Gorkha"
                    );

                    messages.push_back(
                        "Chapter 2 complete. "
                        "Forest of Gorkha unlocked."
                    );
                }
            }
            else if (progress == 3)
            {
                story.playChapter3(
                    *player,
                    map
                );

                if (
                    player->getFlag(
                        "chapter3_complete"
                    )
                )
                {
                    save.saveGame(
                        4,
                        currentSlot,
                        *player,
                        "Cave of Shadows"
                    );

                    map.setLocation(
                        "Cave of Shadows"
                    );

                    messages.push_back(
                        "Chapter 3 complete. "
                        "Cave of Shadows unlocked."
                    );
                }
            }
            else if (progress == 4)
            {
                story.playChapter4(
                    *player,
                    map
                );

                if (
                    player->getFlag(
                        "chapter4_complete"
                    )
                )
                {
                    save.saveGame(
                        5,
                        currentSlot,
                        *player,
                        map.getLocation()
                    );

                    messages.push_back(
                        "Chapter 4 complete."
                    );
                }
            }
            else
            {
                messages.push_back(
                    "All four chapters are complete."
                );
            }

            // Restore the chapter music only after the
            // chapter/battle sequence has actually ended.
            // Even if the chapter was not completed this pass
            // (e.g. the player lost a fight and story.playChapterN
            // returned early), this still restores whatever
            // track belongs to the current progress, so the
            // world never goes silent.

            SoundManager::stopMusic();

            const int newProgress =
                save.load(currentSlot);

            if (newProgress == 1)
            {
                map.setLocation(
                    "Kingdom of Gorkha"
                );

                SoundManager::playLoop(
                    "data/sounds/chapter1_gorkha.mp3"
                );
            }
            else if (newProgress == 2)
            {
                map.setLocation(
                    "Countryside Village"
                );

                SoundManager::playLoop(
                    "data/sounds/chapter2_countryside.mp3"
                );
            }
            else if (newProgress == 3)
            {
                map.setLocation(
                    "Forest of Gorkha"
                );

                SoundManager::playLoop(
                    "data/sounds/chapter3_forest.mp3"
                );
            }
            else if (newProgress == 4)
            {
                map.setLocation(
                    "Cave of Shadows"
                );

                SoundManager::playLoop(
                    "data/sounds/chapter4_cave.mp3"
                );
            }
        }
        else if (selected == 1)
        {
            drawGameLayout(
                "INVENTORY",
                map.getLocation()
            );

            drawCharacterPanel(*player);
            drawInventoryPanel(
                player->inventory
            );

            typewriterStoryPanel(
                "INVENTORY",
                "Use the inventory through battle's Item action."
            );

            waitForEnter();
        }
        else if (selected == 2)
        {
            // Full save: progress, location, HP/MP, level,
            // gold and every item currently carried. This can
            // be triggered at any point while exploring, not
            // only right after a chapter checkpoint.

            int currentProgress =
                save.load(currentSlot);

            if (currentProgress <= 0)
                currentProgress = 1;

            save.saveGame(
                currentProgress,
                currentSlot,
                *player,
                map.getLocation()
            );

            messages.push_back(
                "Game saved."
            );
        }
        else
        {
            SoundManager::stopMusic();
            showMainMenu();
            return;
        }
    }
}

bool Game::saveExists()
{
    for (int slot = 1; slot <= 3; ++slot)
    {
        ifstream file(
            "save" +
            to_string(slot) +
            ".txt"
        );

        if (file.good())
            return true;
    }

    return false;
}

void Game::showTitleScreen()
{
    SoundManager::stop();

    setScreenMode(
        SCREEN_TITLE
    );

    clearScreen();

    SoundManager::playOnce(
        "data/sounds/title_screen.mp3"
    );

    // Double ornamental frame around the whole title block,
    // with dividers and flourishes instead of just two lines
    // of plain centered text on a blank screen.

    drawBox(2, 1, 116, 23);
    drawBox(4, 2, 112, 19);

    drawCenteredText(
        0, 4, 120,
        string(60, '-'),
        COL_DARK
    );

    drawCenteredText(
        0, 6, 120,
        "~  THE HIDDEN CAVE OF DHARMADEVA  ~",
        COL_GRAY
    );

    drawCenteredText(
        0, 9, 120,
        "D H A R M A D E V A ' S   B L A D E",
        COL_GOLD
    );

    drawCenteredText(
        0, 11, 120,
        string(46, '='),
        COL_GOLD
    );

    drawCenteredText(
        0, 13, 120,
        "A Historical Game  --  1813 Bikram Sambat",
        COL_GRAY
    );

    drawCenteredText(
        0, 14, 120,
        "The Unification of Nepal",
        COL_GRAY
    );

    drawCenteredText(
        0, 17, 120,
        string(30, '*'),
        COL_CYAN
    );

    drawCenteredText(
        0, 18, 120,
        "P R A Y A S",
        COL_CYAN
    );

    drawCenteredText(
        0, 22, 120,
        "[ Press ENTER to begin ]",
        COL_GOLD
    );

    waitForEnter();

    SoundManager::stopMusic();
    clearScreen();
}

void Game::showMainMenu()
{
    SoundManager::stopMusic();

    SoundManager::playLoop(
        "data/sounds/menu_background.mp3"
    );

    setScreenMode(
        SCREEN_TITLE
    );

    vector<string> options;

    if (saveExists())
        options.push_back("Continue");

    options.push_back("New Game");
    options.push_back("Load Game");
    options.push_back("Exit");

    int selected = 0;

    while (isRunning)
    {
        clearScreen();

        drawCenteredText(
            0,
            5,
            120,
            "D H A R M A D E V A ' S   B L A D E",
            COL_GOLD
        );

        drawCenteredText(
            0,
            7,
            120,
            "MAIN MENU",
            COL_CYAN
        );

        for (
            int i = 0;
            i < static_cast<int>(
                options.size()
            );
            ++i
        )
        {
            drawCenteredText(
                0,
                11 + i * 2,
                120,
                (
                    i == selected
                        ? "> "
                        : "  "
                ) +
                options[i],
                i == selected
                    ? COL_GOLD
                    : COL_WHITE
            );
        }

        drawCenteredText(
            0,
            21,
            120,
            "Arrow keys / WASD to navigate",
            COL_GRAY
        );

        drawCenteredText(
            0,
            22,
            120,
            "ENTER select    ESC exit",
            COL_GRAY
        );

        const int input =
            readInput();

        if (input == 0)
        {
            --selected;

            if (selected < 0)
                selected =
                    static_cast<int>(
                        options.size()
                    ) - 1;
        }
        else if (input == 1)
        {
            ++selected;

            if (
                selected >=
                static_cast<int>(
                    options.size()
                )
            )
            {
                selected = 0;
            }
        }
        else if (input == 4)
        {
            const string choice =
                options[selected];

            if (choice == "Continue")
            {
                continueGame();
                return;
            }

            if (choice == "New Game")
            {
                startNewGame();
                return;
            }

            if (choice == "Load Game")
            {
                loadGame();
                return;
            }

            if (choice == "Exit")
            {
                isRunning = false;
                return;
            }
        }
        else if (input == 5)
        {
            isRunning = false;
            return;
        }
    }
}

void Game::startNewGame()
{
    setScreenMode(
        SCREEN_PROLOGUE
    );

    delete player;

    player =
        new Player(
            KAJI_NAME
        );

    clearScreen();

    cout
        << "=====================================\n"
        << "          CHOOSE SAVE SLOT\n"
        << "=====================================\n\n"
        << "1. Save 1\n"
        << "2. Save 2\n"
        << "3. Save 3\n"
        << "4. Back\n";

    const char choice =
        static_cast<char>(
            _getch()
        );

    switch (choice)
    {
    case '1':
        currentSlot = 1;
        break;

    case '2':
        currentSlot = 2;
        break;

    case '3':
        currentSlot = 3;
        break;

    case '4':
        showMainMenu();
        return;

    default:
        showMainMenu();
        return;
    }

    saveSystem save;

    save.saveLastSlot(
        currentSlot
    );

    // Start with chapter 1 after the prologue. Full state
    // (fresh stats + starting location) is saved immediately
    // so the slot is valid even if the player quits mid-prologue.

    save.saveGame(
        1,
        currentSlot,
        *player,
        "Kingdom of Gorkha"
    );

    SoundManager::stopMusic();

    story.playPrologue(*player);

    SoundManager::stopMusic();

    map.setLocation(
        "Kingdom of Gorkha"
    );

    SoundManager::playLoop(
        "data/sounds/chapter1_gorkha.mp3"
    );

    // The permanent RPG layout appears only now,
    // after the prologue has finished.

    showWorldScreen();
}

void Game::continueGame()
{
    saveSystem save;

    currentSlot =
        save.loadLastSlot();

    delete player;

    player =
        new Player(
            KAJI_NAME
        );

    string location;

    const int progress =
        save.loadGame(
            currentSlot,
            *player,
            location
        );

    if (progress <= 0)
    {
        showMainMenu();
        return;
    }

    SoundManager::stopMusic();

    if (progress == 1)
    {
        map.setLocation(
            location.empty()
                ? "Kingdom of Gorkha"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter1_gorkha.mp3"
        );
    }
    else if (progress == 2)
    {
        map.setLocation(
            location.empty()
                ? "Countryside Village"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter2_countryside.mp3"
        );
    }
    else if (progress == 3)
    {
        map.setLocation(
            location.empty()
                ? "Forest of Gorkha"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter3_forest.mp3"
        );
    }
    else
    {
        map.setLocation(
            location.empty()
                ? "Cave of Shadows"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter4_cave.mp3"
        );
    }

    showWorldScreen();
}

void Game::loadGame()
{
    clearScreen();

    cout
        << "=====================================\n"
        << "             LOAD GAME\n"
        << "=====================================\n\n"
        << "1. Save 1\n"
        << "2. Save 2\n"
        << "3. Save 3\n"
        << "4. Back\n";

    const char choice =
        static_cast<char>(
            _getch()
        );

    switch (choice)
    {
    case '1':
        currentSlot = 1;
        break;

    case '2':
        currentSlot = 2;
        break;

    case '3':
        currentSlot = 3;
        break;

    case '4':
        showMainMenu();
        return;

    default:
        showMainMenu();
        return;
    }

    saveSystem save;

    save.saveLastSlot(
        currentSlot
    );

    delete player;

    player =
        new Player(
            KAJI_NAME
        );

    string location;

    const int progress =
        save.loadGame(
            currentSlot,
            *player,
            location
        );

    if (progress <= 0)
    {
        showMainMenu();
        return;
    }

    SoundManager::stopMusic();

    if (progress == 1)
    {
        map.setLocation(
            location.empty()
                ? "Kingdom of Gorkha"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter1_gorkha.mp3"
        );
    }
    else if (progress == 2)
    {
        map.setLocation(
            location.empty()
                ? "Countryside Village"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter2_countryside.mp3"
        );
    }
    else if (progress == 3)
    {
        map.setLocation(
            location.empty()
                ? "Forest of Gorkha"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter3_forest.mp3"
        );
    }
    else
    {
        map.setLocation(
            location.empty()
                ? "Cave of Shadows"
                : location
        );

        SoundManager::playLoop(
            "data/sounds/chapter4_cave.mp3"
        );
    }

    showWorldScreen();
}

void Game::autoSave()
{
    // Manual checkpoint saves are currently used.
    // This function remains intentionally harmless.

}
