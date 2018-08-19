#include "Player.h"

namespace Game {
Player *Player::getInstance()
{
    static Player* instance;

    if(!instance)
        instance = new Player();
    return instance;
}

Player::Player() noexcept
{

}

} // namespace
