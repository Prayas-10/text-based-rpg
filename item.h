#ifndef ITEM_H
#define ITEM_H
#include "constants.h"
#include <string>
#include <vector>
class Item
{
private:
    int id;
    string name;
    string category;
    string effectType;
    int power;
public:
    Item();
    Item(
        int id,
        string name,
        string category,
        string effectType,
        int power
    );
    int getId() const;
    string getName() const;
    string getCategory() const;
    string getEffectType() const;
    int getPower() const;
    bool isUsable() const;
};
// Load item definitions from items.json
vector<Item> loadItems(
    const string& filename
);
#endif

