#include "CraftAbility.h"
#include "Inventory.h"
#include "Item.h"
#include "Reward.h"

namespace Game {
const unsigned int CraftAbility::LOW_SKILL = 9;
const unsigned int CraftAbility::MID_SKILL = 99;

CraftAbility::CraftAbility(const std::shared_ptr<Inventory> &inventory) noexcept
    :m_inventory(inventory), m_skill(1)
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

unsigned int CraftAbility::skill() const
{
    return m_skill;
}

std::vector<Ore> CraftAbility::getAvailableOres() const
{
    if (m_skill < LOW_SKILL)
    {
        return {
            Ore::Type::Cooper,
            Ore::Type::Iron
        };
    }
    else if (m_skill < MID_SKILL)
    {
        return {
            Ore::Type::Cooper,
            Ore::Type::Iron,
            Ore::Type::Silver,
            Ore::Type::Gold
        };
    }
    else {
        return {
            Ore::Type::Cooper,
            Ore::Type::Iron,
            Ore::Type::Silver,
            Ore::Type::Gold,
            Ore::Type::Diamond
        };
    }

}

} // namespace

