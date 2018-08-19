#include "CraftAbility.h"
#include "Inventory.h"
#include "Reciepe.h"
#include "Item.h"

namespace Game {
CraftAbility::CraftAbility(const std::shared_ptr<Inventory> &inventory) noexcept
    :m_inventory(inventory)
{

}

Item CraftAbility::craft(const Reciepe &reciepe) const
{
    if (m_inventory->substract(reciepe.sources()))
        return reciepe.createTarget();
    else
        return Item();
}

} // namespace
