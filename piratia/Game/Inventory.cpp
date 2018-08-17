#include "Inventory.h"

namespace Game {

Inventory::Inventory()
{

}

void Inventory::addItem(const Item &item) {
    m_items.push_back(item);
}

std::vector<Item> Inventory::substract(const std::vector<Item> &items)
{

}

} // namespace
