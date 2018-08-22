#ifndef CRAFTABILITY_H
#define CRAFTABILITY_H

#include <memory>
#include <vector>

#include <game_core_export.h>

#include "Recipe.h"
#include "structures.h"

namespace Game {

class Inventory;

/**
 * @brief Управление способностью крафтить
 * @details Создает объекты по рецепту из предметов из инвентаря игрока. Так же
 * пределяет список доступных игроку рецептов и уровень этого навыка
 */
class GAME_CORE_EXPORT CraftAbility
{
public:
    CraftAbility() = default; // invalid ability
    explicit CraftAbility(std::shared_ptr<Inventory> const& inventory) noexcept;
    Item craft(Recipe const& recipe) const;

    std::vector<Recipe> recipes() const;

private:
    std::shared_ptr<Inventory> m_inventory;
    std::vector<Recipe> m_recipes;
};


} // namespace
#endif // CRAFTABILITY_H
