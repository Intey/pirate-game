#ifndef REWARD_H
#define REWARD_H

#include <game_core_export.h>
#include <string>

namespace Game {

/**
 * @brief Класс "добычи" из игры.
 * @details Используется для создания вида-отображения для экрана
 */
class GAME_CORE_EXPORT Reward {
public:
    Reward() noexcept;
    Reward(int score);
    std::string toString() const;
    int value() const;

private:
    int m_value;
};

} // namespace

#endif // REWARD_H
