#ifndef CRAFTABILITY_H
#define CRAFTABILITY_H

#include <memory>

#include <game_core_export.h>

#include "structures.h"

namespace Game {

class Inventory;
class Recipe;

/**
 * @brief Создает объект - удаляет объекты из инвентаря и добавляет в него созданный
 */
class GAME_CORE_EXPORT CraftAbility
{
public:
    explicit CraftAbility(std::shared_ptr<Inventory> const& inventory) noexcept;
    Item craft(Recipe const& recipe) const;

private:
    std::shared_ptr<Inventory> m_inventory;
};


} // namespace
#endif // CRAFTABILITY_H
