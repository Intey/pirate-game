#ifndef CRAFTABILITY_H
#define CRAFTABILITY_H

#include <memory>
#include <vector>

#include <game_core_export.h>

#include "Recipe.h"
#include "Ore.h"
#include "structures.h"

namespace Game {

class Reward;
class Inventory;


GAME_CORE_EXPORT const std::vector<Ore::Type> LOW_SKILL_ORES {
    Ore::Type::Cooper,
    Ore::Type::Iron
};
GAME_CORE_EXPORT const std::vector<Ore::Type> MID_SKILL_ORES {
    Ore::Type::Silver,
    Ore::Type::Gold
};

GAME_CORE_EXPORT const std::vector<Ore::Type> HIGH_SKILL_ORES {
    Ore::Type::Diamond
};

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
    Reward multiplyReward(Reward const& reward) const;

    unsigned int skill() const;
    /**
     * @brief Получение списка руд, над которыми может работать игрок
     * @return список руд в порядке их уровня
     */
    std::vector<Ore> getAvailableOres() const;

public:
    static const unsigned int LOW_SKILL;
    static const unsigned int MID_SKILL;
private:
    std::shared_ptr<Inventory> m_inventory;
    std::vector<Recipe> m_recipes;
    unsigned int m_skill;
};


} // namespace
#endif // CRAFTABILITY_H
