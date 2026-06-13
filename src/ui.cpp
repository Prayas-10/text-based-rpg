#include "ui.h"
#include "game.h"

void setupConsole()                    {}
void setColor(int code)                {}
void resetColor()                      {}
int  navigateMenu(vector<string> o)    { return 0; }

void printSlow(string text, int delayMs) {
    for (char c : text) {
        cout << c;
        cout.flush();
        Sleep(delayMs);
    }
}

void waitForEnter() {
    cout << "\n                    [ Press ENTER to continue ]";
    while(cin.get() != '\n');
}