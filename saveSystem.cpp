#include "saveSystem.h"
#include <iostream>
#include <fstream>

using namespace std;

/*0 = Main Menu
  1 = prologue
  2 = scene 1
  3 = scene 2
  4 = chapter 1 */
void saveSystem::save(int progress)
{
    ofstream file("save.txt");
    file << progress;
    file.close();
}
int saveSystem::load()
{
    ifstream file("save.txt");
    if(!file)
    {
        return 0;
    }
    int progress = 0;
    file>> progress;
    file.close();
    return progress;
}

