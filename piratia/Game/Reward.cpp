#include "Reward.h"

namespace Game {
const std::string Reward::TYPE = "MINE";

Reward::Reward() noexcept
{

}

std::string Game::Reward::toString() const {
   std::string result {"You Earn: \n" };
   for (auto& item: m_values)
   {
       auto name = item.first;
       auto value = item.second;
       result += name + ": " + std::to_string(value) + "\n";
   }
   return result;
}

void Reward::add(const std::string &name, int value) {
    m_values[name] = value;
}

std::map<std::string, int> Reward::values() const
{
    return m_values;
}

} // namespace
