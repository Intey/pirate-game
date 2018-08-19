#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <vector>
#include <string>
#include "Item.h"
#include "structures.h"
#include <game_core_export.h>

namespace Game {

class GAME_CORE_EXPORT Inventory
{
public:

    Inventory();

    void addItem(Item const& item, int count=1);
    bool substract(const ItemPacks &diff);
    bool has(const ItemPacks & diff) const;
    ItemPacks diff(const ItemPacks &sources) const;
private:
    ItemPacks m_items;
};

} // namespace

#endif // INVENTORY_H
