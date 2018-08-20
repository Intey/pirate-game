#include "CraftAbility.h"
#include "Inventory.h"
#include "Recipe.h"
#include "Item.h"

namespace Game {
CraftAbility::CraftAbility(const std::shared_ptr<Inventory> &inventory) noexcept
    :m_inventory(inventory)
{

}

Item CraftAbility::craft(const Recipe &recipe) const
{
    if (m_inventory->substract(recipe.sources()))
        return recipe.createTarget();
    else
        return Item();
}

} // namespace
