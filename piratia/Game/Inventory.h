#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "Item.h"

namespace Game {


class Inventory
{
public:
    Inventory();

    void addItem(Item const& item);
    /**
     * @brief вычитает ресурсы из инвенторя
     * @param items вычитаемое
     * @return список не удаленных (не достающих) предметов.
     * Если список пуст - значит удаление прошло успешно
     */
    std::vector<Item> substract(std::vector<Item> const& items);
private:
    std::vector<Item> m_items;
};

} // namespace

#endif // INVENTORY_H
