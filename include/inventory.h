#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"
#include "constants.h"
#include <iostream>
class Inventory
{
public:
    // -- INVENTORY ENTRY --
    struct InventoryEntry
    {
        Item item;
        int quantity;
        InventoryEntry() = default;
        InventoryEntry(
            const Item& i,
            int q
        )
            : item(i), quantity(q)
        {}
    };
private:
    vector<InventoryEntry> items;
public:
    // -- ADD / REMOVE --
    void addItem(
        const Item& item,
        int quantity = 1
    );
    bool removeItem(
        int itemId,
        int quantity = 1
    );
    bool removeItem(
        const string& itemName,
        int quantity = 1
    );
    // -- SEARCH --
    bool hasItem(
        int itemId
    ) const;
    bool hasItem(
        const string& itemName
    ) const;
    const Item* findItem(
        int itemId
    ) const;
    const Item* findItem(
        const string& itemName
    ) const;
    // -- QUANTITY --
    int getItemQuantity(
        int itemId
    ) const;
    int getItemQuantity(
        const string& itemName
    ) const;
    // -- ACCESS --
    const vector<InventoryEntry>& getItems() const;
    // -- UTILITY --
    bool empty() const;
    int size() const;
    void clear();
    // -- SAVE / LOAD --
    void saveToFile(
        ostream& out
    ) const;
    void loadFromFile(
        istream& in
    );
};
#endif

