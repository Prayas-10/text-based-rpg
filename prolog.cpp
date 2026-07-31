#include "saveSystem.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;
/*void saveProgress(int progress)
{
    ofstream file ("save.txt");
    file<<progress;
    file.close();
}
int loadProgress()
{
    ifstream file("save.txt");
    int progress = 0;
    file>>progress;
    file.close();
    return progress;
}*/

class start
{
    private:
            char choice;
            char z;
    public:
            void mainmenu();
            void prologue();
            void scene1();
            void scene2();
            inline void waitForZ()
            {
                char z;

                do
                {
                    z = _getch();
                } while(z != 'z' && z != 'Z');
            }
            void typewriter(string text)
            {
                for(char c : text)
                {
                    bool fast = false;
                    cout << c;
                    if (_kbhit())
                    {
                        char key = _getch();

                        if (key == 'z' || key == 'Z')
                        {
                            fast = true;
                        }
                    }

                    if (fast)
                    {
                        Sleep(1);
                    }
                    else if(c=='.' || c=='!' || c=='?')
                        Sleep(450);

                    else if(c==',')
                        Sleep(180);

                    else
                        Sleep(40);
                }

                cout<<endl;
            }
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
        case '2':
        {    
            system("cls");
            /*typewriter("Continue feature coming soon.");
            typewriter("Returning to main menu...");
                start::mainmenu();*/
            saveSystem s;

            int progress = s.load();
            switch(progress)
            {
                case 1:
                    scene1();
                    break;
                case 2:
                    scene2();
                    break;
                case 3:
                    typewriter("End of available content.");
                    break;
                default: 
                    system("cls");
                    typewriter("No save file found!");
                    typewriter("Press any key to return to the main menu...");
                    _getch();
                    system("cls");
                    start::mainmenu();
                    break;
            }
            break;
        }
        case '3':
            system("cls");
            typewriter("Load Game feature coming soon.");
            typewriter("Returning to main menu...");
            start::mainmenu();
            break;
        case '4':
        {
            system("cls");
            cout<<"Are you sure you want to exit? (y/n): "<<endl;
            char confirm = _getch();
            if (confirm == 'y' || confirm == 'Y')
            {
                typewriter("Exiting game...");
                exit(0);
            }
            else
            {
                system("cls");
                typewriter("Returning to main menu...");
                start::mainmenu();
            }
            break;
        }
        default:
        {
            system("cls");
            cout << "\nPlease select one of the options given options (1-4)." << endl;
            start::mainmenu();
            break;  
        }          
                            
    }
}
void start::prologue()
{
    cout<<"Press 'z' to continue..."<<endl;
    waitForZ();
    system("cls");
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("\t\t\tPROLOGUE:  THE DIVIDED LANDS");
    cout<<endl;
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("Press 'z' to continue...");
    waitForZ();
    typewriter("It was the time of early 1800s (BS).");
    waitForZ();
    typewriter("The mighty Himalayas stood silent, witness to a land torn apart.");
    waitForZ();

    typewriter("Countless small kingdoms - Gorkha, Kantipur, Laltipur, Bhaktapur, Patan, and many others - each ruled by its own king, each unaware that history was about to change them forever.");
    waitForZ();

    typewriter("KING PRITHIVI NARAYAN SHAH of the Gorkha kingdom dreamt of a united kingdom.");
    waitForZ();

    typewriter("Driven by courage, ambition, and an unwavering commitment to his vision, the king embarked upon a historic campaign of unification.");
    waitForZ();

    typewriter("Despite his unwavering determination, his path was far from easy, for he faced numerous hurdles on his way.");
    waitForZ();

    typewriter("Each setback tested his resolve and threatened to bring his grand vision to an end.");
    waitForZ();

    typewriter("Many sacrifices were made.");
    waitForZ();

    typewriter("Countless obstacles stood in his path.");
    waitForZ();

    typewriter("Yet... none proved more challenging than the fortified city of KIRTIPUR, where he was defeated not once, but twice.");
    waitForZ();

    typewriter("But the king's spirit remained unbroken.");
    waitForZ();

    typewriter("Seeking guidance in this time of uncertainty, the king journeyed to the sacred Temple of Gorakhnath.");
    waitForZ();
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("\t\t\t\tEND OF PROLOGUE.");
    cout<<endl;
    typewriter("\t\t------------------------------------------------");
    waitForZ();

    typewriter("Press any key to continue...");
    _getch();

    saveSystem s;
    s.save(1);

    start::scene1();
}

void start::scene1()
{
    system("cls");
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("\t\t\tSCENE 1: THE TEMPLE OF DESPERATION");
   
    cout<<endl;
    typewriter("\t\t------------------------------------------------");
    waitForZ();
    typewriter("Press 'z' to continue...");
    typewriter("Three nights after the second defeat at Kirtipur,the king could not rest.");
    waitForZ();
    
    typewriter("Seeking guidance, he made his way to the sacred Temple of Gorakhnath, nestled among the mist-covered hills.");
    waitForZ();

    typewriter("Candles flickered against the temple walls.");
    waitForZ();

    typewriter("Thick incense smoke curled through the air.");
    waitForZ();

    typewriter("The king fell to his knees before the altar, and prayed for guidance.");
    waitForZ();
    typewriter("KING: Give me the strength. Give me wisdom. Show me the path. O God, or take my life if this dream is not meant to be.");
    waitForZ();
    typewriter("He closed his eyes. Silence stretched.");
    waitForZ();
    typewriter("An old priest approached him.");
    waitForZ();
    typewriter("Priest: Your Majesty, your suffering has brought you here for a reason.");
    waitForZ();
    typewriter("KING: I seek a path to unity. I have failed twice at Kirtipur.");
    waitForZ();
    typewriter("Priest: Then perhaps... you must seek THE SAGE.");
    waitForZ();
    typewriter("The king looked up with a glimmer of hope in his eyes.");
    waitForZ();
    typewriter("KING: What Sage?");
    waitForZ();
    typewriter("Priest: The holy person who meditates deep in the Sleshmantak Jungle. They say he has knowledge beyond that of an ordinary person.");
    waitForZ();
    typewriter("If anyone knows the path forward, it is HIM.");
    waitForZ();
    typewriter("The king stood up. The priest's words had given him hope.");
    waitForZ();
    typewriter("At dawn, the king descended the stone steps of Gorakhnath. The bells behind him faded into the cold mountain air.");
    typewriter("Ahead laid a path, leading towards the dark green borders of the Sleshmantak jungle.");
    waitForZ();
    typewriter("The next morning the king and his guards were deep inside Sleshmantak Jungle.");
    waitForZ();
    typewriter("Venturing deep into its ancient woods, they eventually came upon a small, secluded hut where a sage sat in silent meditation.");
    waitForZ();
    typewriter("The king immediately felt his presence and knelt before the hut and bowed his head.");
    waitForZ();
    typewriter("The voice came from within.");
    waitForZ();
    typewriter("Voice: You seek victory, but do you understand what it requires?.");
    waitForZ();
    typewriter("From the shadows emerged an old sage. His eyes seemed to see beyond time.");
    waitForZ();
    typewriter("He wore simple robes, yet... his presence commanded respect.");
    waitForZ();
    typewriter("SAGE: The battle is not won by weapons alone. It requires sacrifice, wisdom and essentially..., the courage to walk the path that others fear!.");
    waitForZ();
    typewriter("The king looked up, startled.");
    waitForZ();
    typewriter("KING: How did you know why I came here? Are you the wise sage the priest spoke of?");
    waitForZ();
    typewriter("SAGE: Names matter little. Some call me a sage; others, a hermit. What matters is that you have come seeking answers.");
    waitForZ();
    typewriter("The sage steps forward.");
    waitForZ();
    typewriter("SAGE: I have waited centuries for someone whose heart seeks unity rather than conquest. "); 
    waitForZ();
    typewriter("For the one worthy to seek what lies hidden.");
    waitForZ();
    typewriter("SAGE: There exists a place forgotten by time... THE HIDDEN CAVE OF DHARMADEVA.");
    waitForZ();
    typewriter("Within it rests an ancient relic known as Dharmadeva's Blade, a weapon said to grant victory only to those who wield it with a pure heart.");
    waitForZ();
    typewriter("The king's eyes widen.");
    waitForZ();
    typewriter("KING: Where is this place? How do I find it?");
    waitForZ();
    typewriter("SAGE: The valley is hidden beyond towering mountains and guarded by trials that have claimed the lives of even the bravest.");
    waitForZ();
    typewriter("Its path cannot be found on any map. Only those with unwavering resolve may hope to discover it.");
    waitForZ();
    typewriter("KING: Then I shall leave at once and retrieve the blade myself.");
    waitForZ();
    typewriter("The sage slowly shook his head.");
    waitForZ();
    typewriter("SAGE: No. This is not a path meant for a king. A ruler's duty is to his people, not to the perils of a forgotten valley.");
    waitForZ();
    typewriter("SAGE: If you fail, your dream of a united nation dies with you.");
    waitForZ();
    typewriter("The king fell silent.");
    waitForZ();
    typewriter("SAGE: Return to your kingdom and summon the Kaji you trust above all others.");
    waitForZ();
    typewriter("Entrust this quest to him, for only a soul of unwavering courage and unshakable loyalty can survive the trials that await there.");
    waitForZ();
    typewriter("Only HE can endure the valley's dangers, recover \"The Dharmadeva's Blade\" and place it in your hands.");
    waitForZ();
    typewriter("The king remained silent for a long moment, reflecting on the sage's words.");
    waitForZ();
    typewriter("At last, he bowed his head in respect.");
    waitForZ();
    typewriter("KING: Then so it shall be. I will place my faith in the one that has never failed me.");
    waitForZ();
    typewriter("The sage slowly stepped back into the shadows of the hut.");
    waitForZ();
    typewriter("Go now. Destiny awaits.");
    waitForZ();
    typewriter("Said the sage as he closed his eyes and sank once more into deep meditation.");

    waitForZ();
    typewriter("The king bowed respectfully before the sage before turning away.");
    waitForZ();
    typewriter("The cool breeze of Sleshmantak Jungle greeted him as the first rays of the morning sun filtered through the towering trees.");
    waitForZ();
    typewriter("Without another word, he and his guards began the journey back to the palace, carry with them not the blade, but the hope of one day claiming it.");
    waitForZ();
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("\t\t\t\tEND OF SCENE 1.");
    cout<<endl;
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    waitForZ();
    typewriter("Press any key to continue...");
    _getch();

    saveSystem s;
    s.save(2);
    
    start::scene2();
}
void start::scene2()
{
    system("cls");
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("\t\t\tSCENE 2: THE ROYAL PALACE ");
    cout<<endl;
    typewriter("\t\t------------------------------------------------");
    
    typewriter("Press 'z' to continue...");
    waitForZ();
    typewriter("By nightfall, King Prithivi Narayan Shah had returned to the palace.");
    waitForZ();
    typewriter("The sage's words echoed in his mind throughout the journey home...");
    waitForZ();
    typewriter("Without delay, the king summoned his trusted Kaji.");
    waitForZ();
    typewriter("The Kaji entered the royal chamber and bowed before the king.");
    waitForZ();
    typewriter("Kaji: Your Majesty, I await your command. Whatever your will, I shall see it done.");
    waitForZ();
    typewriter("KING: I have got a glimpse of hope where I least expected it.");
    waitForZ();
    typewriter("Guided by a priest, I journeyed deep into the Sleshmantak Jungle, where I met a sage unlike any other.");
    waitForZ();
    typewriter("He spoke of an ancient blade hidden in the \"Cave of Dhermadeva\".");
    waitForZ();
    typewriter("The blade said to grant victory to those who wield it with pure intention.");
    waitForZ();
    typewriter("The Kaji listened in respectful silence.");
    waitForZ();
    typewriter("KING: You must go and retrieve this blade!");
    waitForZ();
    typewriter("This mission will test your courage, wisdom and your resolve. ");
    waitForZ();
    typewriter("It is a dangerous mission... but a necessary one.");
    waitForZ();
    typewriter("So.. our dream of a united nation... now rests upon your shoulders.");
    waitForZ();
    typewriter("The Kaji lowered his head.");
    waitForZ();
    typewriter("Kaji: Your Majesty, I shall carry out your command without hesitation.");
    waitForZ();
    typewriter("I shall return with \"The Dharmadeva's blade\"... or I shall not return at all.");
    waitForZ();
    typewriter("The king nodded solemnly.");
    waitForZ();
    typewriter("At once, the Kaji began preparing for the expedition. ");
    waitForZ();
    typewriter("He gathered food, medical herbs, water, a sturdy sword and other essential supplies for the journey ahead.");
    waitForZ();
    typewriter("After inspecting his armor and securing his sword at his side, he made his final preparations.");
    waitForZ();
    typewriter("Before his departure, he stood for a moment at the palace gate, looking towards the distant mountains.");
    waitForZ();
    typewriter("Some where beyond them... laid the HIDDEN CAVE OF DHARMADEVA.");
    waitForZ();
    typewriter("The road ahead was long, and the dangers were many...");
    waitForZ();
    typewriter("But the mission had begun...");
    waitForZ();
    typewriter("\t\t------------------------------------------------");
    cout<<endl;
    typewriter("\t\t\t\tEND OF SCENE 2.");
    cout<<endl;
    typewriter("\t\t------------------------------------------------");

    cout<<endl;
    typewriter("Press any key to continue...");

    _getch();

    saveSystem s;
    s.save(3);
}
int main()
{
    start s;
    system("cls");
    s.mainmenu();
    return 0;
}