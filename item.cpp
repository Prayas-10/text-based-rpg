#include "item.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

// -- DEFAULT CONSTRUCTOR --
Item::Item()
{
    id = 0;
    name = "";
    category = "";
    effectType = "";
    power = 0;
}

// -- CONSTRUCTOR --
Item::Item(
    int id,
    string name,
    string category,
    string effectType,
    int power
)
{
    this->id = id;
    this->name = name;
    this->category = category;
    this->effectType = effectType;
    this->power = power;
}

// -- GETTERS --
int Item::getId() const
{
    return id;
}

string Item::getName() const
{
    return name;
}

string Item::getCategory() const
{
    return category;
}

string Item::getEffectType() const
{
    return effectType;
}

int Item::getPower() const
{
    return power;
}

// -- USABLE --
bool Item::isUsable() const
{
    if (effectType.empty())
        return false;
    if (effectType == "none")
        return false;
    return true;
}

// -- LOAD ITEMS --
vector<Item> loadItems(
    const string& filename
)
{
    vector<Item> items;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open item file: "
            << filename << endl;
        return items;
    }
    try
    {
        json data;
        file >> data;
        if (!data.contains("items"))
        {
            cerr << "Error: JSON does not contain "
                "\"items\"." << endl;
            return items;
        }
        for (const auto& itemData : data["items"])
        {
            Item item(
                itemData.value("id", 0),
                itemData.value(
                    "name",
                    "Unknown Item"
                ),
                itemData.value(
                    "category",
                    "Miscellaneous"
                ),
                itemData.value(
                    "effectType",
                    "none"
                ),
                itemData.value(
                    "power",
                    0
                )
            );
            items.push_back(item);
        }
    }
    catch (const json::exception& e)
    {
        cerr << "Error reading "
            << filename
            << ": "
            << e.what()
            << endl;
    }
    return items;
}

