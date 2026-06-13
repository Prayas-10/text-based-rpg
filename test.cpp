#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void printSlow(string text, int delayMs = 35) {
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

void scene1() {
    printSlow("The late medieval period\n", 40);
    Sleep(400);
    printSlow("The hills of Gorkha...\n\n", 40);
    Sleep(800);

    printSlow("The fortress stands as it always has...\n", 35);
    Sleep(600);

    printSlow("Below, the Kathmandu Valley sleeps...\n", 35);
    printSlow("Three kingdoms. Three kings...\n", 35);
    printSlow("None of them willing to bend...\n\n", 35);
    Sleep(600);

    printSlow("King Prithvi Narayan Shah has taken Dahachowk.\n", 35);
    printSlow("It was the beginning of the greatest conquest the lands would ever see...\n\n", 35);
    Sleep(400);

    printSlow("The first attack on Kirtipur failed....\n", 40);
    Sleep(300);
    printSlow("The second attack on Kirtipur...", 40);
    Sleep(1500);
    printSlow("  failed.\n\n", 40);
    Sleep(800);
    printSlow("Two hundred men did not come home.\n\n", 35);
    Sleep(600);

    printSlow("The King does not speak of it.\n", 35);
    printSlow("But the fortress remembers.\n", 35);
    printSlow("The walls remember.\n", 35);
    printSlow("The wind carries their names.\n", 35);

    waitForEnter();
}

void scene2(){
    printSlow("The King leaves in the night.\n", 35);
    waitForEnter();

}

void scene3(){

}

void scene4(){

}
void scene5(){

}


int main() {
    scene1();
    scene2();
    scene3();
    scene4();
    scene5();
    return 0;
}