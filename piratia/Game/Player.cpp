#include "Player.h"

namespace Game {
Player *Player::getInstance()
{
    static Player* instance;

    if(!instance)
        instance = new Player();
    return instance;
}

std::shared_ptr<CraftAbility> Player::getCraftAbility() const
{
    return m_craftAbility;
}

Player::Player()
{
    m_inventory.reset(new Inventory());
    m_craftAbility.reset(new CraftAbility(m_inventory));
}

} // namespace
