#ifndef FINDPAIRGAME_H
#define FINDPAIRGAME_H

#include <vector>
#include <string>
#include "Reward.h"

namespace Game {


class Card {
public:
    Card() = default;
    explicit Card(int i, int j, int value, std::string type):
        i(i), j(j), value(value), type(type) {}
public:
    int i = -1;
    int j = -1;
    bool opened = false; // карта в данный момент открыта и видна игроку
    bool paired = false; // карта "запарена", т.е. ее не нужно отображать
    int value = -1;
    std::string type;
public:
    void pair() { opened = true; paired = true; }

    operator bool() const {
        return value > 0;
    }
};


/**
 * @brief Класс логики игры "найди пару". После инициализации должен быть добавлен
 * в "планировщик"(schedule), по шаблону проектирование "Update method"
 */
class FindPairGame {
public:
    FindPairGame(int timeout = 1 * 60, int card_variants_count = 20);

    void update(float dt);
    void start();
    void stop() { m_over = true; m_elapsed = 0; }
    bool isOver() const { return m_over; }
    int restSeconds() const {
        // вычитаем прошедшее время из таймаута. Делаем "+1", потому что округление
        // в меньшую сторону, а мы не хотим видеть 0 целую секунду
        return static_cast<int>(GAME_TIMEOUT - m_elapsed + 1);
    }
    std::vector<Card> getCards();

    Card getCard(int i, int j);
    void openCard(int i, int j);

    Reward getReward();

    Card getOpenedCard() const;

    int getCardId(int i, int j) { return i*100 + j; }
    int getCardId(Card const& card) { return card.i*100 + card.j; }

private:
    void closePair(Card &a, Card &b);

protected:
    /// открытая карта. Если следующая - парная, удаляем пару, иначе - закрываем
    Card m_firstCard;
    float m_elapsed; /// прошло секунд игры
    bool m_over; /// игра завершена
    /// осталось открыть карт
    int m_restToOpen = CARD_VARIANTS_COUNT*CARD_VARIANTS_COUNT;
    const int GAME_TIMEOUT;
    const int CARD_VARIANTS_COUNT;
private:
    Reward m_reward;
    std::vector<std::vector<Card>> m_cards;
};

} // namespace
#endif // FINDPAIRGAME_H
