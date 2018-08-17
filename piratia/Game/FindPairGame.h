#ifndef FINDPAIRGAME_H
#define FINDPAIRGAME_H

#include <vector>
#include <string>

namespace Game {

/**
 * @brief Класс "добычи" из игры.
 * @details Используется для создания вида-отображения для экрана
 */
struct Reward {
    Reward(int score): value(score) {}
    int value;
    std::string toString() const {
        return std::string("Score: ") + std::to_string(value);
    }
};

struct Card {
    Card(): i(-1), j(-1), opened(false), paired(true) {}
    Card(int value, int i, int j): value(value), i(i), j(j) {}
public:
    int value = -1;
    bool opened = false; // карта в данный момент открыта и видна игроку
    bool paired = false; // карта "запарена", т.е. ее не нужно отображать
    int i;
    int j;

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

    int getScore() { return m_score; }

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
    int m_score = 0; /// очки выигрышные
    const int GAME_TIMEOUT;
    const int CARD_VARIANTS_COUNT;
private:
    std::vector<std::vector<Card>> m_cards;
};

} // namespace
#endif // FINDPAIRGAME_H
