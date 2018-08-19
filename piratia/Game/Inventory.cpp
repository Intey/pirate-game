#include "Inventory.h"

#include <algorithm>
#include <map>
#include "structures.h"

namespace Game {

Inventory::Inventory()
{

}

void Inventory::addItem(const Item &item, int count /* = 1 */) {
    if (m_items.count(item) == 0)
        m_items[item] = count;
    else
        m_items[item] += count;
}

bool Inventory::substract(const ItemPacks &items)
{
    if (!has(items)) return false;
    
    for (auto & item: items)
    {
        auto count = m_items[item.first] - item.second;
        if (count < 0)
            return false;

    }
    return true;
}

bool Inventory::has(const ItemPacks &packs) const
{
    for (auto & pack: packs)
    {
        if (m_items.count(pack.first) == 0 ||
            m_items.at(pack.first) - pack.second < 0) return false;
    }
    return true;
}

ItemPacks Inventory::diff(const ItemPacks &sources) const
{
    ItemPacks diff;
    // двух-шаговое удаление.
    for (auto & item: sources)
    {
        if (m_items.count(item.first) == 0)
            diff[item.first] = item.second;
        else if (m_items.count(item.first) != 0 && (m_items.at(item.first) - item.second) < 0)
            diff[item.first] = item.second - m_items.at(item.first);

    }
    return diff;
}

} // namespace
