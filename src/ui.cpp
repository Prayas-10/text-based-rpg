#include "ui.h"
#include "player.h"
#include "enemy.h"
#include "inventory.h"

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

namespace
{
    HANDLE hOut =
        GetStdHandle(
            STD_OUTPUT_HANDLE
        );

    constexpr int SCREEN_WIDTH = 120;

    int currentScreenMode = -1;

    string trimText(
        const string& text,
        int width
    )
    {
        if (width <= 0)
            return "";

        if (
            static_cast<int>(
                text.size()
            ) <= width
        )
        {
            return text;
        }

        if (width <= 3)
            return text.substr(
                0,
                width
            );

        return text.substr(
            0,
            width - 3
        ) + "...";
    }

    vector<string> wrapText(
        const string& text,
        int width
    )
    {
        vector<string> result;

        if (width <= 0)
            return result;

        string line;
        string word;

        auto flushWord =
            [&]()
        {
            if (word.empty())
                return;

            if (
                !line.empty() &&
                static_cast<int>(
                    line.size() +
                    1 +
                    word.size()
                ) > width
            )
            {
                result.push_back(line);
                line.clear();
            }

            if (!line.empty())
                line += ' ';

            while (
                static_cast<int>(
                    word.size()
                ) > width
            )
            {
                if (!line.empty())
                {
                    result.push_back(line);
                    line.clear();
                }

                result.push_back(
                    word.substr(
                        0,
                        width
                    )
                );

                word.erase(
                    0,
                    width
                );
            }

            line += word;
            word.clear();
        };

        for (char c : text)
        {
            if (c == '\n')
            {
                flushWord();
                result.push_back(line);
                line.clear();
            }
            else if (
                c == ' ' ||
                c == '\t'
            )
            {
                flushWord();
            }
            else
            {
                word += c;
            }
        }

        flushWord();

        if (
            !line.empty() ||
            result.empty()
        )
        {
            result.push_back(line);
        }

        return result;
    }
}

void setupConsole()
{
    HWND console =
        GetConsoleWindow();

    if (console)
        SetConsoleTitleA(
            "Dharmadeva's Blade"
        );

    // The whole layout is drawn on a fixed 0..120 x 0..34 grid.
    // Without explicitly sizing the console, its buffer/window
    // defaults to whatever the terminal started with (often much
    // smaller), so the game only ever occupied a small corner of
    // the window and box-drawing wrapped/clipped unpredictably.
    // Size both the screen buffer and the window to match the
    // layout so it fills the console exactly.

    const SHORT bufferWidth = 122;
    const SHORT bufferHeight = 40;

    // Shrink the window first - Windows refuses to shrink the
    // buffer below the current window size otherwise.
    SMALL_RECT minRect{0, 0, 1, 1};
    SetConsoleWindowInfo(hOut, TRUE, &minRect);

    COORD bufferSize{bufferWidth, bufferHeight};
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowRect
    {
        0,
        0,
        static_cast<SHORT>(bufferWidth - 1),
        static_cast<SHORT>(bufferHeight - 1)
    };

    SetConsoleWindowInfo(hOut, TRUE, &windowRect);

    // Quick Edit Mode is disabled so an accidental click inside
    // the console can't freeze the game's input/output while it
    // waits for a text selection to be released.

    DWORD mode = 0;

    if (
        GetConsoleMode(
            hOut,
            &mode
        )
    )
    {
        mode |=
            ENABLE_EXTENDED_FLAGS;

        mode &=
            ~ENABLE_QUICK_EDIT_MODE;

        SetConsoleMode(
            hOut,
            mode
        );
    }

    hideCursor();

    resetColor();
}

void setColor(int code)
{
    SetConsoleTextAttribute(
        hOut,
        static_cast<WORD>(
            code
        )
    );
}

void resetColor()
{
    setColor(COL_WHITE);
}

void gotoxy(
    int x,
    int y
)
{
    COORD position{};

    position.X =
        static_cast<SHORT>(
            max(0, x)
        );

    position.Y =
        static_cast<SHORT>(
            max(0, y)
        );

    SetConsoleCursorPosition(
        hOut,
        position
    );
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO info{};

    if (
        GetConsoleCursorInfo(
            hOut,
            &info
        )
    )
    {
        info.bVisible = FALSE;

        SetConsoleCursorInfo(
            hOut,
            &info
        );
    }
}

void showCursor()
{
    CONSOLE_CURSOR_INFO info{};

    if (
        GetConsoleCursorInfo(
            hOut,
            &info
        )
    )
    {
        info.bVisible = TRUE;

        SetConsoleCursorInfo(
            hOut,
            &info
        );
    }
}

void clearScreen()
{
    CONSOLE_SCREEN_BUFFER_INFO info{};

    if (
        !GetConsoleScreenBufferInfo(
            hOut,
            &info
        )
    )
    {
        return;
    }

    const DWORD cells =
        static_cast<DWORD>(
            info.dwSize.X
        ) *
        static_cast<DWORD>(
            info.dwSize.Y
        );

    COORD origin{0, 0};

    DWORD written = 0;

    FillConsoleOutputCharacterA(
        hOut,
        ' ',
        cells,
        origin,
        &written
    );

    FillConsoleOutputAttribute(
        hOut,
        static_cast<WORD>(
            COL_WHITE
        ),
        cells,
        origin,
        &written
    );

    gotoxy(0, 0);
}

int readInput()
{
    const int key =
        _getch();

    if (
        key == 'w' ||
        key == 'W'
    )
        return 0;

    if (
        key == 's' ||
        key == 'S'
    )
        return 1;

    if (
        key == 'a' ||
        key == 'A'
    )
        return 2;

    if (
        key == 'd' ||
        key == 'D'
    )
        return 3;

    if (key == 13)
        return 4;

    if (key == 27)
        return 5;

    if (key == 9)
        return 7;

    if (
        key == 0 ||
        key == 224
    )
    {
        const int arrow =
            _getch();

        if (arrow == 72)
            return 0;

        if (arrow == 80)
            return 1;

        if (arrow == 75)
            return 2;

        if (arrow == 77)
            return 3;
    }

    return 6;
}

int navigateMenu(
    vector<string> options
)
{
    if (options.empty())
        return -1;

    int selected = 0;

    while (true)
    {
        clearBox(
            1,
            27,
            87,
            6
        );

        drawText(
            3,
            27,
            "ACTIONS",
            COL_GOLD
        );

        for (
            int i = 0;
            i < static_cast<int>(
                options.size()
            );
            ++i
        )
        {
            const int y =
                29 + i * 1;

            if (y >= 33)
                break;

            drawText(
                5,
                y,
                (
                    i == selected
                        ? "> "
                        : "  "
                ) +
                trimText(
                    options[i],
                    78
                ),
                i == selected
                    ? COL_GOLD
                    : COL_WHITE
            );
        }

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
            return selected;
        }
        else if (input == 5)
        {
            return -1;
        }
    }
}

void setScreenMode(int mode)
{
    if (
        mode !=
        currentScreenMode
    )
    {
        clearScreen();
        currentScreenMode =
            mode;
    }
}

void printSlow(
    string text,
    int delayMs
)
{
    for (char c : text)
    {
        cout << c;
        cout.flush();
        Sleep(delayMs);
    }
}

namespace
{
    // Shared punctuation pacing used by both the raw console
    // typewriter() and the in-panel typewriterStoryPanel().
    // Rules:
    // - comma / semicolon   -> shortest pause
    // - single "."/"!"/"?"/":" -> medium pause
    // - a run of dots ("...")  -> pauses ONCE, after the
    // LAST dot of the run, longer than a single "."
    // - a run of 4+ dots ("....") -> pauses even longer than
    // a plain ellipsis
    // `i` is the index of the character just printed within
    // `line`. The function sleeps for whatever additional pause
    // that character calls for (on top of the normal per-
    // character delay already applied by the caller).

    void applyPunctuationPause(
        const string& line,
        size_t i,
        int delayMs
    )
    {
        const char c = line[i];

        if (c == '.')
        {
            size_t runStart = i;

            while (
                runStart > 0 &&
                line[runStart - 1] == '.'
            )
            {
                --runStart;
            }

            const size_t runLen =
                i - runStart + 1;

            const bool isLastDotOfRun =
                (i + 1 >= line.size()) ||
                (line[i + 1] != '.');

            if (!isLastDotOfRun)
                return;

            if (runLen >= 4)
                Sleep(delayMs * 30);
            else if (runLen == 3)
                Sleep(delayMs * 20);
            else
                Sleep(delayMs * 12);
        }
        else if (c == ',' || c == ';')
        {
            Sleep(delayMs * 6);
        }
        else if (
            c == '!' ||
            c == '?' ||
            c == ':'
        )
        {
            Sleep(delayMs * 12);
        }
    }
}

void typewriter(
    const string& text,
    int delayMs
)
{
    // this was my original plain-console typewriter from before I
    // built the panel UI. story text and the prologue go through
    // typewriterStoryPanel() now, this just sticks around for any
    // leftover bare-console text.
    //
    // pressing any key skips the rest of the animation and prints
    // instantly - basically "hold a key to speed it up"
    const vector<string> lines =
        wrapText(
            text,
            80
        );

    bool skip = false;

    for (const string& line : lines)
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            cout << line[i];
            cout.flush();

            if (!skip && _kbhit())
            {
                _getch();
                skip = true;
            }

            if (!skip)
            {
                Sleep(delayMs);

                applyPunctuationPause(
                    line,
                    i,
                    delayMs
                );
            }
        }

        cout << '\n';
    }
}

void waitForEnter()
{
    while (
        _getch() != 13
    )
    {
    }
}

void drawBox(
    int x,
    int y,
    int width,
    int height
)
{
    if (
        width < 2 ||
        height < 2
    )
        return;

    gotoxy(x, y);

    cout << '+';

    for (
        int i = 0;
        i < width - 2;
        ++i
    )
        cout << '-';

    cout << '+';

    for (
        int row = 1;
        row < height - 1;
        ++row
    )
    {
        gotoxy(
            x,
            y + row
        );

        cout << '|';

        gotoxy(
            x + width - 1,
            y + row
        );

        cout << '|';
    }

    gotoxy(
        x,
        y + height - 1
    );

    cout << '+';

    for (
        int i = 0;
        i < width - 2;
        ++i
    )
        cout << '-';

    cout << '+';
}

void clearBox(
    int x,
    int y,
    int width,
    int height
)
{
    for (
        int row = 0;
        row < height;
        ++row
    )
    {
        gotoxy(
            x,
            y + row
        );

        for (
            int col = 0;
            col < width;
            ++col
        )
        {
            cout << ' ';
        }
    }
}

void drawText(
    int x,
    int y,
    const string& text,
    int color
)
{
    setColor(color);

    gotoxy(x, y);

    cout <<
        trimText(
            text,
            max(
                0,
                SCREEN_WIDTH - x
            )
        );

    resetColor();
}

void drawCenteredText(
    int x,
    int y,
    int width,
    const string& text,
    int color
)
{
    const string safe =
        trimText(
            text,
            width
        );

    const int start =
        x +
        max(
            0,
            (
                width -
                static_cast<int>(
                    safe.size()
                )
            ) / 2
        );

    drawText(
        start,
        y,
        safe,
        color
    );
}

void drawHPBar(
    int x,
    int y,
    int current,
    int maximum,
    int width
)
{
    maximum =
        max(1, maximum);

    current =
        max(
            0,
            min(
                current,
                maximum
            )
        );

    const int filled =
        current * width /
        maximum;

    drawText(
        x,
        y,
        "[",
        COL_RED
    );

    gotoxy(
        x + 1,
        y
    );

    setColor(COL_RED);

    for (
        int i = 0;
        i < width;
        ++i
    )
    {
        cout <<
            (
                i < filled
                    ? '#'
                    : '.'
            );
    }

    cout << ']';

    resetColor();

    cout <<
        ' ' <<
        current <<
        '/' <<
        maximum;
}

void drawMPBar(
    int x,
    int y,
    int current,
    int maximum,
    int width
)
{
    maximum =
        max(1, maximum);

    current =
        max(
            0,
            min(
                current,
                maximum
            )
        );

    const int filled =
        current * width /
        maximum;

    drawText(
        x,
        y,
        "[",
        COL_CYAN
    );

    gotoxy(
        x + 1,
        y
    );

    setColor(COL_CYAN);

    for (
        int i = 0;
        i < width;
        ++i
    )
    {
        cout <<
            (
                i < filled
                    ? '#'
                    : '.'
            );
    }

    cout << ']';

    resetColor();

    cout <<
        ' ' <<
        current <<
        '/' <<
        maximum;
}

void drawGameLayout(
    const string& title,
    const string& location
)
{
    clearScreen();

    // Main area:
    // 0..89 x 0..25
    // Status:
    // 90..119 x 0..25
    // Story/action:
    // 0..89 x 26..33
    // Log:
    // 90..119 x 26..33

    drawBox(
        0,
        0,
        90,
        26
    );

    drawBox(
        90,
        0,
        30,
        26
    );

    drawBox(
        0,
        26,
        90,
        8
    );

    drawBox(
        90,
        26,
        30,
        8
    );

    drawCenteredText(
        10,
        1,
        70,
        title,
        COL_GOLD
    );

    drawText(
        92,
        2,
        "LOCATION",
        COL_GOLD
    );

    drawText(
        92,
        3,
        trimText(
            location,
            25
        ),
        COL_WHITE
    );
}

void drawCharacterPanel(
    const Player& player
)
{
    clearBox(
        92,
        5,
        27,
        8
    );

    drawText(
        92,
        5,
        "PLAYER",
        COL_GOLD
    );

    drawText(
        92,
        7,
        trimText(
            player.name,
            25
        ),
        COL_WHITE
    );

    drawText(
        92,
        8,
        "LEVEL " +
        to_string(
            player.level
        ),
        COL_CYAN
    );

    drawText(
        92,
        9,
        "HP",
        COL_WHITE
    );

    drawHPBar(
        96,
        9,
        player.hp,
        player.maxHp,
        10
    );

    drawText(
        92,
        10,
        "MP",
        COL_WHITE
    );

    drawMPBar(
        96,
        10,
        player.mp,
        player.maxMp,
        10
    );

    drawText(
        92,
        11,
        "GOLD " +
        to_string(
            player.gold
        ),
        COL_YELLOW
    );
}

void drawEnemyPanel(
    const Enemy& enemy
)
{
    // starts at y=14 on purpose - any higher and it overlaps the
    // player's HP/MP panel above it, learned that the hard way
    clearBox(
        92,
        14,
        27,
        10
    );

    drawText(
        92,
        14,
        "ENEMY",
        COL_RED
    );

    drawText(
        92,
        16,
        trimText(
            enemy.getName(),
            25
        ),
        COL_WHITE
    );

    drawText(
        92,
        17,
        "HP",
        COL_WHITE
    );

    drawHPBar(
        96,
        17,
        enemy.getHp(),
        enemy.getMaxHp(),
        10
    );

    drawText(
        92,
        19,
        trimText(
            enemy.getDifficulty(),
            25
        ),
        COL_GRAY
    );
}

void drawQuestPanel(
    const string& objective
)
{
    clearBox(
        92,
        14,
        27,
        10
    );

    drawText(
        92,
        14,
        "QUEST",
        COL_GOLD
    );

    int y = 16;

    const vector<string> lines =
        wrapText(
            objective,
            25
        );

    for (
        const string& line :
        lines
    )
    {
        if (y >= 24)
            break;

        drawText(
            92,
            y++,
            line,
            COL_WHITE
        );
    }
}

void drawInventoryPanel(
    const Inventory& inventory
)
{
    clearBox(
        92,
        14,
        27,
        10
    );

    drawText(
        92,
        14,
        "INVENTORY",
        COL_GOLD
    );

    const auto& items =
        inventory.getItems();

    if (items.empty())
    {
        drawText(
            92,
            16,
            "Empty",
            COL_GRAY
        );

        return;
    }

    int y = 16;

    for (
        const auto& entry :
        items
    )
    {
        if (y >= 24)
            break;

        drawText(
            92,
            y++,
            trimText(
                entry.item.getName(),
                18
            ) +
            " x" +
            to_string(
                entry.quantity
            ),
            COL_WHITE
        );
    }
}

void drawMessageLog(
    const vector<string>& messages
)
{
    clearBox(
        91,
        27,
        28,
        6
    );

    drawText(
        92,
        27,
        "MESSAGE LOG",
        COL_GOLD
    );

    const int visible =
        4;

    const int start =
        max(
            0,
            static_cast<int>(
                messages.size()
            ) - visible
        );

    int y = 28;

    for (
        int i = start;
        i < static_cast<int>(
            messages.size()
        );
        ++i
    )
    {
        drawText(
            92,
            y++,
            "> " +
            trimText(
                messages[i],
                25
            ),
            COL_GRAY
        );
    }
}

namespace
{
    // Pull a leading "Name: ..." speaker out of a dialogue line
    // and pick its color:
    // red   = enemy
    // gold  = royalty (the King)
    // brown = any other NPC
    // green = the player (Kaji)
    // If no "Name:" prefix is found, the whole line is treated as
    // narration under the passed-in default speaker/color.

    bool isEnemyName(const string& lower)
    {
        static const vector<string> names =
        {
            "thief", "bandit", "bandit leader", "wolf",
            "wild boar", "boar", "gharial", "river gharial",
            "shadow wolf", "cave serpent", "serpent",
            "guardian tiger", "tiger", "ancient guardian"
        };

        for (const string& n : names)
            if (lower == n || lower.find(n) != string::npos)
                return true;

        return false;
    }

    int speakerColor(const string& name)
    {
        string lower = name;

        for (char& c : lower)
            c = static_cast<char>(tolower(c));

        if (isEnemyName(lower))
            return COL_RED;

        if (lower.find("king") != string::npos)
            return COL_YELLOW;

        if (lower == "kaji")
            return COL_GREEN;

        return COL_GOLD;
    }

    void splitSpeaker(
        const string& defaultSpeaker,
        const string& dialogue,
        string& label,
        string& body,
        int& color
    )
    {
        label = defaultSpeaker;
        body = dialogue;
        color = COL_GOLD;

        const size_t colonPos = dialogue.find(':');

        if (
            colonPos == string::npos ||
            colonPos == 0 ||
            colonPos > 28
        )
        {
            return;
        }

        const string candidate = dialogue.substr(0, colonPos);

        bool looksLikeName = true;

        for (char c : candidate)
        {
            if (
                c == '.' || c == '!' ||
                c == '?' || c == '"'
            )
            {
                looksLikeName = false;
                break;
            }
        }

        if (
            !looksLikeName ||
            candidate.empty() ||
            !isupper(
                static_cast<unsigned char>(candidate[0])
            )
        )
        {
            return;
        }

        label = candidate;
        body = dialogue.substr(colonPos + 1);

        while (!body.empty() && body.front() == ' ')
            body.erase(body.begin());

        color = speakerColor(label);
    }
}

void drawStoryPanel(
    const string& speaker,
    const string& dialogue
)
{
    // The dialogue is drawn inside the big STORY viewport
    // (the same box drawGameLayout titles "STORY"), not the
    // bottom action box - that box is reserved for Continue
    // Story / Attack / Defend / etc. Wrapped by words, not
    // characters, so long dialogue never runs beyond the box.

    clearBox(
        1,
        2,
        87,
        22
    );

    string label;
    string body;
    int color;

    splitSpeaker(
        speaker,
        dialogue,
        label,
        body,
        color
    );

    drawText(
        3,
        3,
        trimText(label, 84),
        color
    );

    const vector<string> lines =
        wrapText(
            body,
            84
        );

    int y = 5;

    for (const string& line : lines)
    {
        if (y >= 23)
            break;

        drawText(
            3,
            y++,
            line,
            COL_WHITE
        );
    }

    drawText(
        76,
        24,
        "[ENTER]",
        COL_GRAY
    );
}

void typewriterStoryPanel(
    const string& speaker,
    const string& dialogue,
    int delayMs
)
{
    // Same box/coordinates as drawStoryPanel, but the dialogue
    // is animated in character-by-character (with punctuation
    // pacing) instead of appearing instantly. This is what both
    // Story::speak() and the prologue render through, so every
    // line of narrative in the game plays out inside the STORY
    // viewport - never the bottom action box.

    clearBox(
        1,
        2,
        87,
        22
    );

    string label;
    string body;
    int color;

    splitSpeaker(
        speaker,
        dialogue,
        label,
        body,
        color
    );

    drawText(
        3,
        3,
        trimText(label, 84),
        color
    );

    const vector<string> lines =
        wrapText(
            body,
            84
        );

    int y = 5;

    setColor(COL_WHITE);

    bool skip = false;

    for (const string& line : lines)
    {
        if (y >= 23)
            break;

        gotoxy(3, y);

        for (size_t i = 0; i < line.size(); ++i)
        {
            cout << line[i];
            cout.flush();

            if (!skip && _kbhit())
            {
                _getch();
                skip = true;
            }

            if (!skip)
            {
                Sleep(delayMs);

                applyPunctuationPause(
                    line,
                    i,
                    delayMs
                );
            }
        }

        ++y;
    }

    resetColor();

    drawText(
        76,
        24,
        "[ENTER]",
        COL_GRAY
    );
}

void drawBattlePanel(
    const Player& player,
    const Enemy& enemy,
    const vector<string>& battleLog
)
{
    // Battle state lives inside the same STORY viewport that
    // narrative dialogue uses - not the narrow right-hand
    // sidebar - so HP/MP bars and the fight log have real room
    // instead of being crammed into a 27-column strip.

    clearBox(
        1,
        2,
        87,
        22
    );

    drawText(3, 3, "PLAYER", COL_GOLD);

    drawText(
        3,
        4,
        trimText(player.name, 40) +
        "  (Lv " +
        to_string(player.level) +
        ")",
        COL_WHITE
    );

    drawText(3, 5, "HP", COL_WHITE);
    drawHPBar(7, 5, player.hp, player.maxHp, 24);

    drawText(3, 6, "MP", COL_WHITE);
    drawMPBar(7, 6, player.mp, player.maxMp, 24);

    drawText(3, 8, "ENEMY", COL_RED);

    drawText(
        3,
        9,
        trimText(enemy.getName(), 40),
        COL_WHITE
    );

    drawText(3, 10, "HP", COL_WHITE);
    drawHPBar(7, 10, enemy.getHp(), enemy.getMaxHp(), 24);

    drawText(
        3,
        11,
        trimText(enemy.getDifficulty(), 40),
        COL_GRAY
    );

    drawText(3, 13, "BATTLE LOG", COL_GOLD);

    const int visible = 9;

    const int start =
        max(
            0,
            static_cast<int>(battleLog.size()) - visible
        );

    int y = 14;

    for (
        int i = start;
        i < static_cast<int>(battleLog.size());
        ++i
    )
    {
        if (y >= 23)
            break;

        drawText(
            3,
            y++,
            "> " + trimText(battleLog[i], 80),
            COL_GRAY
        );
    }
}

void drawSystemPanel(
    const vector<string>& options,
    int selected,
    bool focused
)
{
    // Bottom-right box - the same area drawMessageLog uses
    // during exploration. When focused (TAB has switched here),
    // it becomes a navigable menu (Inventory / Save / Return to
    // Main Menu, etc.) instead of a static log.

    clearBox(
        91,
        27,
        28,
        6
    );

    drawText(
        92,
        27,
        "SYSTEM",
        focused
            ? COL_GOLD
            : COL_GRAY
    );

    int y = 29;

    for (
        int i = 0;
        i < static_cast<int>(
            options.size()
        );
        ++i
    )
    {
        if (y >= 32)
            break;

        const bool isSelected =
            focused && i == selected;

        drawText(
            92,
            y++,
            (
                isSelected
                    ? "> "
                    : "  "
            ) +
            trimText(
                options[i],
                22
            ),
            isSelected
                ? COL_GOLD
                : (
                    focused
                        ? COL_WHITE
                        : COL_GRAY
                )
        );
    }

    if (!focused)
    {
        drawText(
            92,
            31,
            "[TAB]",
            COL_GRAY
        );
    }
}

bool navigateDualMenu(
    const vector<string>& mainOptions,
    const vector<string>& sideOptions,
    int& outPanel,
    int& outIndex
)
{
    int panel = 0;
    int mainSelected = 0;
    int sideSelected = 0;

    while (true)
    {
        drawCombatPanel(
            mainOptions,
            panel == 0
                ? mainSelected
                : -1
        );

        drawSystemPanel(
            sideOptions,
            sideSelected,
            panel == 1
        );

        const int input =
            readInput();

        if (input == 7)
        {
            panel = 1 - panel;
            continue;
        }

        int& selected =
            (panel == 0)
                ? mainSelected
                : sideSelected;

        const int count =
            static_cast<int>(
                (panel == 0
                    ? mainOptions
                    : sideOptions
                ).size()
            );

        if (count == 0)
            continue;

        if (input == 0)
        {
            --selected;

            if (selected < 0)
                selected = count - 1;
        }
        else if (input == 1)
        {
            ++selected;

            if (selected >= count)
                selected = 0;
        }
        else if (input == 4)
        {
            outPanel = panel;
            outIndex = selected;
            return true;
        }
        else if (input == 5)
        {
            return false;
        }
    }
}

void drawCombatPanel(
    const vector<string>& actions,
    int selected
)
{
    clearBox(
        1,
        27,
        88,
        6
    );

    drawText(
        3,
        27,
        "ACTIONS",
        COL_GOLD
    );

    for (
        int i = 0;
        i < static_cast<int>(
            actions.size()
        );
        ++i
    )
    {
        const int column =
            i % 2;

        const int row =
            i / 2;

        const int x =
            5 +
            column * 39;

        const int y =
            29 +
            row * 2;

        if (y >= 33)
            continue;

        drawText(
            x,
            y,
            (
                i == selected
                    ? "> "
                    : "  "
            ) +
            trimText(
                actions[i],
                34
            ),
            i == selected
                ? COL_GOLD
                : COL_WHITE
        );
    }
}

void pause_aftermath()
{
    Sleep(600);
}

void pause_weight()
{
    Sleep(700);
}

void pause_revelation()
{
    Sleep(500);
}
