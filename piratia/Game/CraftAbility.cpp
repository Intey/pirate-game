#include "CraftAbility.h"
#include "Inventory.h"
#include "Reciepe.h"

namespace Game {
CraftAbility::CraftAbility(const std::shared_ptr<Inventory> &inventory)
    :m_inventory(inventory)
{

}

bool CraftAbility::craft(const Reciepe &reciepe) const
{
    if (!m_inventory->substract(reciepe.sources()).empty())
        return false;

    m_inventory->addItem(reciepe.createTarget());

}

} // namespace
