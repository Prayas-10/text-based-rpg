#include "game.h"
#include "map.h"

NPC::NPC(string n, string d) {}
Area::Area() {}
Map::Map()   {}
Area& Map::getArea(int id) { return areas[id]; }