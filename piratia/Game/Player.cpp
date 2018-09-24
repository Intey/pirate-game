#include "Player.h"
#include "Reward.h"
#include "Ore.h"

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

void Player::ownReward(const Reward &reward)
{
        if(reward.TYPE == "MINE")
        {
            ownMineReward(reward);
        }
    // reward.value()
    // m_inventory->addItem()
}

void Player::ownMineReward(const Reward &reward)
{
    for (auto & item: reward.values())
    {
        // ждем с++17 и потом делаем так: for(auto [name, value]: reward.values());;
        auto name = item.first;
        auto value = item.second;

        Ore ore(Ore::typeFromString(name));
        m_inventory->addItem(ore, value);
    }

}

std::shared_ptr<Inventory> Player::getInventory() const
{
    return m_inventory;
}

Player::Player()
{
    m_inventory.reset(new Inventory());
    m_craftAbility.reset(new CraftAbility(m_inventory));
}

} // namespace
