#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

class start
{
    private:
            char choice;
            char z;
    public:
            void mainmenu();
            void prologue();
};
void start::mainmenu()
{
    cout<<"1. New Game"<<endl;
    cout<<"2. Continue"<<endl;
    cout<<"3. Load Game"<<endl;
    cout<<"4. Exit"<<endl;
    choice = _getch();
    switch (choice)
    {
        case '1':
            start::prologue();
            break;
                            
    }
}
void start::prologue()
{
    cout<<"Press 'z' to continue..."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"PROLOGUE:  THE DIVIDED LANDS"<<endl;
    z = _getch();
    if (z == 'z')
    cout<<endl<<"It was the time of early 1800s (B.S.)."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"The mighty Himalayas stood silent, witness to a land torn apart."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Countless small kingdoms - Gorkha, Kantipur, Laltipur, Bhaktapur, Patan, and many others - ";
    cout<<"each ruled by its own king, each unaware that history is about to change them forever."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<endl<<"KING PRITHIVI NARAYAN SHAH of the Gorkha kingdom dreamed of a united kingdom."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<endl<<"Driven by courage, ambition, and an unwavering commitment to his vision, "; 
    cout<<"the king embarked upon a historic campaign of unification."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Despite his unwavering determination, his path was far from easy, for he faced numerous hurdles on his way."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Each setback tested his resolve and threatened to bring his grand vision to an end."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Many sacrifices were made."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Countless obstacles stood in his path."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Yet...";
    z = _getch();
    if (z == 'z')
    cout<<"none proved more challenging than the fortified city of KIRTIPUR, where he was defeated not once, but twice."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"But the king's spirit remained unbroken."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"The events of this story unfold in the aftermath of the king's second defeat at Kirtipur."<<endl;
    z = _getch();
    if (z == 'z')
    cout<<"Press any key to continue..."<<endl;
}

int main()
{
    start s;
    s.mainmenu();
    return 0;
}
