#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include <game_core_export.h>
#include "CraftAbility.h"
#include "Inventory.h"


namespace Game {

class Reward;

class GAME_CORE_EXPORT Player
{
public:
    static Player* getInstance();
    std::shared_ptr<CraftAbility> getCraftAbility() const;

    void ownReward(Reward const& reward);
    // думаю не стоит размещать на стеке данные синглтона: только потратим стек на
    // всю игру, а выигрыша от выделений не будет
    std::shared_ptr<Inventory> getInventory() const;

private:
    void ownMineReward(Reward const& reward);
private:
    std::shared_ptr<Inventory> m_inventory;
    std::shared_ptr<CraftAbility> m_craftAbility;

//singleton часть
private:
    Player();
    Player(Player const& other) = delete;
    Player operator=(Player const& other) = delete;
    ~Player();
};

} // namespace
#endif // PLAYER_H
