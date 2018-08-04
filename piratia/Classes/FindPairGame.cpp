#include <iostream>

#include <cocos/base/CCScheduler.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerTouch.h>
#include <cocos/2d/CCLayer.h>

#include "FindPairGame.h"

using namespace cocos2d;
using namespace std;

FindPairGame::FindPairGame(int timeout, int card_variants_count):
    GAME_TIMEOUT(timeout),
    CARD_VARIANTS_COUNT(card_variants_count)
{
    assert(CARD_VARIANTS_COUNT %2 == 0
           && "Варианты карт должны быть четным числом, т.к. игра про пары");
    start();
}

void FindPairGame::update(float dt) {
    if (m_over) return;
    m_elapsed += dt;
    if (m_elapsed >= GAME_TIMEOUT) stop();
}

void FindPairGame::start() {
    m_over = false;
    m_elapsed = 0;

    m_restToOpen = CARD_VARIANTS_COUNT * CARD_VARIANTS_COUNT;
    for (int i = 0; i < CARD_VARIANTS_COUNT; i++) {
        std::vector<Card> cards = std::vector<Card>{};
        cards.reserve(CARD_VARIANTS_COUNT);
        for (int j = 0; j < CARD_VARIANTS_COUNT; j++) {
            int value = std::rand() % CARD_VARIANTS_COUNT + 1;
            cards.push_back({ value, i, j });
        }
        m_cards.push_back(cards);
    }
}

std::vector<Card> FindPairGame::getCards() {
    std::vector<Card> result;
    result.reserve(CARD_VARIANTS_COUNT*CARD_VARIANTS_COUNT);
    for (int i = 0; i < CARD_VARIANTS_COUNT; ++i) {
        for (int j = 0; j < CARD_VARIANTS_COUNT; ++j) {
            result.push_back(m_cards[i][j]);
        }
    }
    return result;
}

Card FindPairGame::getCard(int i, int j) {
    return m_cards[i][j];
}

void FindPairGame::openCard(int i, int j) {
    if (m_over) return;

    // если первая карта есть(закрыта) или это старый кеш
    if (!m_firstCard.opened || m_firstCard.paired)
    {
        m_firstCard = m_cards[i][j];
        m_firstCard.opened = true;
        return;
    }

    if (m_firstCard.value > 0 && !(m_firstCard.i == i && m_firstCard.j == j)
            && m_cards[i][j].value == m_firstCard.value)
    {
        closePair(m_firstCard, m_cards[i][j]);
        return;
    }

    m_firstCard.opened = false;
}

void FindPairGame::closePair(Card & a, Card & b) {
    a.pair();
    b.pair();
    m_restToOpen -= 2;
    m_score++;
    if (m_restToOpen == 0) {
        m_over = true;
    }
}

Card FindPairGame::getOpenedCard() const
{
    return m_firstCard;
}
