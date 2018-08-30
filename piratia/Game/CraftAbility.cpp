#include "CraftAbility.h"
#include "Inventory.h"
#include "Item.h"
#include "Reward.h"

namespace Game {
CraftAbility::CraftAbility(const std::shared_ptr<Inventory> &inventory) noexcept
    :m_inventory(inventory)
{

}

Item CraftAbility::craft(const Recipe &recipe) const
{
    if (!m_inventory) return Item();

    if (m_inventory->substract(recipe.sources()))
        return recipe.createTarget();
    else
        return Item();
}

std::vector<Recipe> CraftAbility::recipes() const
{
    return m_recipes;
}

Reward CraftAbility::multiplyReward(const Reward &reward) const
{
    return reward;
}

} // namespace
