#include "Reward.h"

namespace Game {

Reward::Reward() noexcept: m_value(-1)
{

}

Reward::Reward(int score): m_value(score) {}

std::string Game::Reward::toString() const {
    return std::string("Score: ") + std::to_string(m_value);
}

int Reward::value() const
{
    return m_value;
}

} // namespace
