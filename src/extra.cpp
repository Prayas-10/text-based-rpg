#include <iostream>
#include <conio.h>
#include <string>
#include <thread> // Required for sleep delay
#include <chrono> // Required for milliseconds time tracking

using namespace std;

class start
{
    private:
        char choice;
    public:
        void mainmenu();
        void prologue();
        void animateText(const string& text, int speed = 30); // Typing effect function
};

// Function to create the animated typing effect
void start::animateText(const string& text, int speed)
{
    for (char c : text)
    {
        cout << c << flush; // flush ensures character prints immediately
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

void start::mainmenu()
{
    cout << "1. New Game" << endl;
    cout << "2. Continue" << endl;
    cout << "3. Load Game" << endl;
    cout << "4. Exit" << endl;
    
    choice = _getch();
    switch (choice)
    {
        case '1':
            system("cls"); // Optional: Clears the menu screen for the prologue
            start::prologue();
            break;
        default:
            break;
    }
}

void start::prologue()
{
    // Sentences print automatically line-by-line with a typing effect
    animateText("PROLOGUE: THE DIVIDED LANDS\n\n", 50);
    this_thread::sleep_for(chrono::milliseconds(800)); // Pause between paragraphs

    animateText("It was the time of early 1800s (B.S.).\n", 30);
    this_thread::sleep_for(chrono::milliseconds(600));

    animateText("The mighty Himalayas stood silent, witness to a land torn apart.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(600));

    animateText("Countless small kingdoms - Gorkha, Kantipur, Laltipur, Bhaktapur, Patan, and many others - \n", 30);
    animateText("each ruled by its own king, each unaware that history is about to change them forever.\n\n", 30);
    this_thread::sleep_for(chrono::milliseconds(1000));

    animateText("KING PRITHIVI NARAYAN SHAH of the Gorkha kingdom dreamed of a united kingdom.\n\n", 30);
    this_thread::sleep_for(chrono::milliseconds(800));

    animateText("Driven by courage, ambition, and an unwavering commitment to his vision, \n", 30);
    animateText("the king embarked upon a historic campaign of unification.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(600));

    animateText("Despite his unwavering determination, his path was far from easy, for he faced numerous hurdles on his way.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(600));

    animateText("Each setback tested his resolve and threatened to bring his grand vision to an end.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(600));

    animateText("Many sacrifices were made.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(500));

    animateText("Countless obstacles stood in his path.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(500));

    animateText("Yet... ", 70); // Slower typing for dramatic effect
    this_thread::sleep_for(chrono::milliseconds(800));

    animateText("none proved more challenging than the fortified city of KIRTIPUR, where he was defeated not once, but twice.\n\n", 30);
    this_thread::sleep_for(chrono::milliseconds(1000));

    animateText("But the king's spirit remained unbroken.\n", 30);
    this_thread::sleep_for(chrono::milliseconds(600));

    animateText("The events of this story unfold in the aftermath of the king's second defeat at Kirtipur.\n\n", 30);
    this_thread::sleep_for(chrono::milliseconds(1000));

    animateText("Press any key to continue...\n", 30);
    _getch(); // One final keypress at the very end so the game doesn't close instantly
}

int main()
{
    start s;
    s.mainmenu();
    return 0;
}
