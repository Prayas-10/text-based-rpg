#include "game.h"
#include <Limits>
#include <conio.h>
// #include "visuals.h"

// ─────────────────────────────────────
// CONSTRUCTOR / DESTRUCTOR
// ─────────────────────────────────────

Game::Game() {
    player = nullptr;
    isRunning = false;
    currentState = STATE_MENU;
}

Game::~Game() {
    if (player != nullptr) delete player;
}

// ─────────────────────────────────────
// RUN — entry point from main()
// ─────────────────────────────────────

void Game::run() {
    isRunning = true;
    setupConsole();
    showTitleScreen();
    showMainMenu();
}

// ─────────────────────────────────────
// PROLOGUE
// ─────────────────────────────────────

void Game::playIntro() {
    playScene1();
    playScene2();
    playScene3();
    playScene4();
    playScene5();
}

void Game::playScene1() {
    setScreenMode(SCREEN_PROLOGUE);

    Sleep(500);
    printSlow("1813 Bikram Sambat.\n", 50);
    Sleep(400);
    printSlow("The hills of Gorkha.\n\n", 50);
    Sleep(800);

    printSlow("The fortress stands as it always has —\n", 35);
    printSlow("stone walls, cold wind, the smell of pine\n", 35);
    printSlow("and distant gunpowder.\n\n", 35);
    Sleep(600);

    printSlow("Below, the Kathmandu Valley sleeps.\n", 35);
    printSlow("Three kingdoms. Three kings.\n", 35);
    printSlow("None of them willing to bend.\n\n", 35);
    Sleep(600);

    printSlow("King Prithvi Narayan Shah has taken Dahachowk.\n", 35);
    printSlow("It was supposed to be the beginning.\n\n", 35);
    Sleep(400);

    printSlow("The first attack on Kirtipur failed.\n", 40);
    Sleep(300);
    printSlow("The second attack on Kirtipur failed.\n\n", 40);
    Sleep(800);

    printSlow("Kalu Pande died at Kirtipur.\n\n", 40);
    pause_aftermath();

    printSlow("The King was close enough\n", 35);
    printSlow("to watch it happen.\n\n", 35);
    pause_weight();

    printSlow("He kept his feet.\n", 50);
    Sleep(400);
    printSlow("He does not know how.\n\n", 50);
    pause_revelation();

    printSlow("The army retreated.\n", 35);
    Sleep(300);
    printSlow("The King did not speak\n", 35);
    printSlow("for what remained of that day.\n\n", 35);
    pause_weight();

    printSlow("Kirtipur still stood.\n", 40);
    pause_aftermath();

    waitForEnter();
}

/* void Game::playScene2() {}
void Game::playScene3() {}
void Game::playScene4() {}
void Game::playScene5() {} */

// ─────────────────────────────────────
// SAVE EXISTS CHECK
// ─────────────────────────────────────

bool Game::saveExists() {
    ifstream f(AUTOSAVE_FILE);
    return f.good();
}

// ─────────────────────────────────────
// TITLE SCREEN
// ─────────────────────────────────────

void Game::showTitleScreen() {
    setScreenMode(SCREEN_TITLE);
    Sleep(300);

    // get console center
    int cx = 40; // adjust to your console width / 2

    // top spacing
    cout << "\n\n\n\n\n\n";

    // title assembles letter by letter
    setColor(COL_DARK);
    string title = "P R A T I V I N D H Y A";
    int titleX = cx - title.length() / 2;

    // print dim first
    gotoxy(titleX, 8);
    setColor(COL_DARK);
    cout << title;
    Sleep(200);

    // brighten progressively
    int colors[] = {COL_DARK, COL_GOLD, 
                    COL_YELLOW, COL_WHITE,
                    COL_YELLOW, COL_GOLD};

    for(int c : colors) {
        gotoxy(titleX, 8);
        setColor(c);
        cout << title;
        cout.flush();
        Sleep(150);
    }

    // subtitle fades in
    Sleep(300);
    string sub = "A Historical RPG  —  1813 Bikram Sambat";
    gotoxy(cx - sub.length()/2, 10);
    setColor(COL_DARK);
    printSlow(sub, 25);

    // divider
    Sleep(300);
    gotoxy(cx - 20, 12);
    setColor(COL_DARK);
    printSlow("────────────────────────────────────────", 10);

    // studio name
    Sleep(200);
    string studio = "P R A Y A S";
    gotoxy(cx - studio.length()/2, 14);
    setColor(COL_DARK);
    printSlow(studio, 40);

    Sleep(800);

    // blink prompt
    string prompt = "[ Press ENTER to begin ]";
    int promptX = cx - prompt.length()/2;
    bool visible = true;

    for(int i = 0; i < 8; i++) {
        gotoxy(promptX, 17);
        setColor(visible ? COL_GOLD : 0);
        cout << prompt;
        cout.flush();
        visible = !visible;
        Sleep(400);
    }

    // wait for enter
    gotoxy(promptX, 17);
    setColor(COL_GOLD);
    cout << prompt;

    while(cin.get() != '\n');
}

// ─────────────────────────────────────
// MAIN MENU
// ─────────────────────────────────────

void Game::showMainMenu() {
    setScreenMode(SCREEN_TITLE);

    // build options based on save state
    vector<string> options;
    if(saveExists()) options.push_back("Continue");
    options.push_back("New Game");
    options.push_back("Load Game");
    options.push_back("Exit");

    int selected = 0;
    int total = options.size();

    // positions
    int cx = 40;
    int menuStartY = 12;

    while(true) {
        system("cls");

        // title
        gotoxy(cx - 11, 6);
        setColor(COL_GOLD);
        cout << "P R A T I V I N D H Y A";

        gotoxy(cx - 19, 8);
        setColor(COL_DARK);
        cout << "────────────────────────────────────────";

        // menu options
        for(int i = 0; i < total; i++) {
            gotoxy(cx - options[i].length()/2 - 2,
                   menuStartY + i * 2);

            if(i == selected) {
                setColor(COL_YELLOW);
                cout << "►  " << options[i];
            } else {
                setColor(COL_DARK);
                cout << "   " << options[i];
            }
        }

        // bottom line
        gotoxy(cx - 19, menuStartY + total * 2 + 1);
        setColor(COL_DARK);
        cout << "────────────────────────────────────────";

        gotoxy(cx - 18, menuStartY + total * 2 + 2);
        setColor(COL_DARK);
        cout << "Arrow keys to navigate  |  Enter to select";

        resetColor();

        // input
        int key = _getch();

        if(key == 224) {
            key = _getch();
            if(key == 72 && selected > 0)
                selected--;
            if(key == 80 && selected < total - 1)
                selected++;

            // menu move sound
            Beep(600, 30);
        }

        if(key == 13) {
            // Enter pressed
            Beep(800, 60);
            string choice = options[selected];

            if(choice == "Continue")  { continueGame(); break; }
            if(choice == "New Game")  { startNewGame();  break; }
            if(choice == "Load Game") { loadGame();      break; }
            if(choice == "Exit") {
                isRunning = false;
                break;
            }
        }
    }
}

// ─────────────────────────────────────
// GAME START OPTIONS
// ─────────────────────────────────────

void Game::startNewGame() {
    system("cls");
    setScreenMode(SCREEN_PROLOGUE);

    // ask for name — optional
    // for now use default name
    // change [KAJI_NAME] in constants.h when decided
    player = new Player(KAJI_NAME);

    playIntro();
    // after prologue — goes to first location
    // showCurrentLocation() goes here later
}

void Game::continueGame() {
    ifstream file(AUTOSAVE_FILE);
    if(!file.is_open()) {
        startNewGame();
        return;
    }
    if(player != nullptr) delete player;
    player = new Player(KAJI_NAME);
    player->loadFromFile(file);
    file.close();

    setScreenMode(SCREEN_AREA);
    // resume from saved location
    // showCurrentLocation() goes here later
}

void Game::loadGame() {
    ifstream file(SAVE_FILE);
    if(!file.is_open()) {
        // no save found
        gotoxy(20, 15);
        setColor(COL_RED);
        printSlow("No save file found.\n", 35);
        Sleep(1500);
        showMainMenu();
        return;
    }
    if(player != nullptr) delete player;
    player = new Player(KAJI_NAME);
    player->loadFromFile(file);
    file.close();

    setScreenMode(SCREEN_AREA);
    // showCurrentLocation() goes here later
}