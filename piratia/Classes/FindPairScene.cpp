#include "FindPairScene.h"
#include <cocos/base/CCScheduler.h>
#include <functional>

struct Card {
    Card(int value): value(value) {}

    int value;
    bool paired = false;
};
/**
 * @brief Класс логики игры "найди пару". После инициализации должен быть добавлен
 * в "планировщик"(schedule), по шаблону проектирование "Update method"
 */
class FindPairGame {
public:
    FindPairGame(int timeout = 1 * 60, int card_variants_count = 20):
        GAME_TIMEOUT(timeout),
        CARD_VARIANTS_COUNT(card_variants_count)
    {
        assert(CARD_VARIANTS_COUNT %2 == 0
               && "Варианты карт должны быть четным числом, т.к. игра про пары");
        start();
    }

    void update(float dt) {
        if (m_over) return;
        m_elapsed += dt;
        if (m_elapsed >= GAME_TIMEOUT) m_over = true;
    }
    void start() {
        m_openedCard = nullptr;
        m_over = false;
        m_elapsed = 0;

        m_restToOpen = CARD_VARIANTS_COUNT * CARD_VARIANTS_COUNT;
        m_cards.reserve(CARD_VARIANTS_COUNT * CARD_VARIANTS_COUNT);
        for (int i = 0; i < CARD_VARIANTS_COUNT; i++) {
            m_cards[i].reserve(CARD_VARIANTS_COUNT);
            for (int j = 0; i < CARD_VARIANTS_COUNT; j++) {
                m_cards[i][j] = Card { std::rand() % CARD_VARIANTS_COUNT };
            }
        }
    }

    void stop() {
        m_over = true;
    }

    void openCard(int i, int j) {
        if (m_over) return;

        if (!m_openedCard)
        {
            m_openedCard = &m_cards[i][j];
            return;
        }

        if (m_openedCard->value > 0 && m_cards[i][j].value == m_openedCard->value)
        {
            closePair(m_openedCard, &m_cards[i][j]);
            return;
        }

        m_openedCard = nullptr;
    }

    int getScore() { return m_score; }
private:
    void closePair(Card * a, Card * b) {
        a->paired = true;
        b->paired = true;
        m_restToOpen -= 2;
        m_score++;
        if (m_restToOpen == 0) {
            m_over = true;
        }
    }

private:
    /// открытая карта. Если следующая - парная, удаляем пару, иначе - закрываем
    Card* m_openedCard;
    float m_elapsed; /// прошло секунд игры
    bool m_over; /// игра завершена
    int m_restToOpen; /// осталось открыть карт
    int m_score; /// очки выигрышные
    const int GAME_TIMEOUT;
    const int CARD_VARIANTS_COUNT;
private:
    std::vector<std::vector<Card>> m_cards;
};


FindPairScene *FindPairScene::createScene()
{
    return FindPairScene::create();
}

bool FindPairScene::init()
{
    if (!Scene::init()) return false;
    m_game.reset(new FindPairGame());

    using namespace std::placeholders;
    this->schedule(CC_CALLBACK_1(FindPairGame::update, m_game.get()), 1, M_GAME_NAME);
    return true;
}

void FindPairScene::renderGame()
{
    // отрисовать сетку игры, все карты

}
