#include "inventory.h"
using namespace std;

// -- ADD ITEM --
void Inventory::addItem(
    const Item& item,
    int quantity
)
{
    if (quantity <= 0)
        return;
    for (auto& entry : items)
    {
        if (entry.item.getId() == item.getId())
        {
            entry.quantity += quantity;
            return;
        }
    }
    InventoryEntry entry;
    entry.item = item;
    entry.quantity = quantity;
    items.push_back(entry);
}

// -- REMOVE BY ID --
bool Inventory::removeItem(
    int itemId,
    int quantity
)
{
    if (quantity <= 0)
        return false;
    for (auto it = items.begin();
        it != items.end();
        ++it)
    {
        if (it->item.getId() == itemId)
        {
            if (it->quantity < quantity)
                return false;
            it->quantity -= quantity;
            if (it->quantity == 0)
                items.erase(it);
            return true;
        }
    }
    return false;
}

// -- REMOVE BY NAME --
bool Inventory::removeItem(
    const string& itemName,
    int quantity
)
{
    if (quantity <= 0)
        return false;
    for (auto it = items.begin();
        it != items.end();
        ++it)
    {
        if (it->item.getName() == itemName)
        {
            if (it->quantity < quantity)
                return false;
            it->quantity -= quantity;
            if (it->quantity == 0)
                items.erase(it);
            return true;
        }
    }
    return false;
}

// -- HAS ITEM --
bool Inventory::hasItem(
    int itemId
) const
{
    return getItemQuantity(itemId) > 0;
}

bool Inventory::hasItem(
    const string& itemName
) const
{
    return getItemQuantity(itemName) > 0;
}

// -- FIND ITEM --
const Item* Inventory::findItem(
    int itemId
) const
{
    for (const auto& entry : items)
    {
        if (entry.item.getId() == itemId)
            return &entry.item;
    }
    return nullptr;
}

const Item* Inventory::findItem(
    const string& itemName
) const
{
    for (const auto& entry : items)
    {
        if (entry.item.getName() == itemName)
            return &entry.item;
    }
    return nullptr;
}

// -- QUANTITY --
int Inventory::getItemQuantity(
    int itemId
) const
{
    for (const auto& entry : items)
    {
        if (entry.item.getId() == itemId)
            return entry.quantity;
    }
    return 0;
}

int Inventory::getItemQuantity(
    const string& itemName
) const
{
    for (const auto& entry : items)
    {
        if (entry.item.getName() == itemName)
            return entry.quantity;
    }
    return 0;
}

// -- GET ITEMS --
const vector<Inventory::InventoryEntry>&
Inventory::getItems() const
{
    return items;
}

// -- EMPTY --
bool Inventory::empty() const
{
    return items.empty();
}

// -- SIZE --
int Inventory::size() const
{
    return static_cast<int>(
        items.size()
        );
}

// -- CLEAR --
void Inventory::clear()
{
    items.clear();
}

// -- SAVE --
void Inventory::saveToFile(
    ostream& out
) const
{
    out << items.size() << '\n';

    for (const auto& entry : items)
    {
        out << entry.item.getId() << '\n';
        out << entry.item.getName() << '\n';
        out << entry.item.getCategory() << '\n';
        out << entry.item.getEffectType() << '\n';
        out << entry.item.getPower() << '\n';
        out << entry.quantity << '\n';
    }
}

// -- LOAD --
void Inventory::loadFromFile(
    istream& in
)
{
    items.clear();

    size_t count = 0;

    in >> count;
    in.ignore(
        (numeric_limits<streamsize>::max)(),
        '\n'
    );

    for (size_t i = 0; i < count; ++i)
    {
        int id = 0;
        string name;
        string category;
        string effectType;
        int power = 0;
        int quantity = 0;

        in >> id;
        in.ignore(
            (numeric_limits<streamsize>::max)(),
            '\n'
        );

        getline(in, name);
        getline(in, category);
        getline(in, effectType);

        in >> power;
        in.ignore(
            (numeric_limits<streamsize>::max)(),
            '\n'
        );

        in >> quantity;
        in.ignore(
            (numeric_limits<streamsize>::max)(),
            '\n'
        );

        if (!in)
            break;

        items.push_back(
            InventoryEntry(
                Item(id, name, category, effectType, power),
                quantity
            )
        );
    }
}

