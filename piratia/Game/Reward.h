#ifndef REWARD_H
#define REWARD_H

#include <game_core_export.h>
#include <string>
#include <map>

namespace Game {

/**
 * @brief Класс "добычи" из игры.
 * @details Используется для создания вида-отображения для экрана
 */
class GAME_CORE_EXPORT Reward {
public:
    Reward() noexcept;
    std::string toString() const;
    void add(std::string const& name, int value);

    std::map<std::string, int> values() const;

    static const std::string TYPE;
private:
    /// тип награды. В зависимости от нее, будет выбран набор предметов, которые можно
    /// выиграть в игру
    std::map<std::string, int> m_values;
};

} // namespace

#endif // REWARD_H
