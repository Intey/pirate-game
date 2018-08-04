#ifndef FINDPAIRGAME_H
#define FINDPAIRGAME_H

#include <vector>

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
    void stop() {
        m_over = true;
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
    int m_restToOpen; /// осталось открыть карт
    int m_score; /// очки выигрышные
    const int GAME_TIMEOUT;
    const int CARD_VARIANTS_COUNT;
private:
    std::vector<std::vector<Card>> m_cards;
};

#endif // FINDPAIRGAME_H
