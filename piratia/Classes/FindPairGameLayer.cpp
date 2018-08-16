#include <string>

#include "FindPairGameLayer.h"
#include "FindPairGame.h"
#include "FindPairScene.h"

#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerTouch.h>

using namespace cocos2d;

const std::string FindPairGameLayer::M_GAME_NAME = "FIND_PAIR";
const int FindPairGameLayer::CARDS_VARIANTS = 6;
const int FindPairGameLayer::GAME_TIMEOUT = 60;

FindPairGameLayer::~FindPairGameLayer()
{
    m_parentScene->release();
}

bool FindPairGameLayer::init() {
    if (!Layer::init()) return false;
    m_game = new FindPairGame(GAME_TIMEOUT, CARDS_VARIANTS);
    this->renderGame();
    m_restSecondsView = Label::createWithTTF(std::to_string(GAME_TIMEOUT),
                                             "fonts/arial.ttf", 16);
    if (!m_restSecondsView) {
        CCLOGERROR("problem with fonts fonts/arial.ttf");
        return false;
    }
    this->addChild(m_restSecondsView);
    return true;
}

void FindPairGameLayer::onEnter() {
    Layer::onEnter();
    m_game->start();
    m_restSecondsView->setString(std::to_string(GAME_TIMEOUT));
    m_restSecondsView->setAnchorPoint({0, 0});
    m_restSecondsView->setPosition(0, 320 - 20);
    m_restSecondsView->setTextColor({255, 255, 255, 255});
}

void FindPairGameLayer::onExit() {
    m_game->stop();
    Layer::onExit();
}

void FindPairGameLayer::update(float delta) {
    m_game->update(delta);
    if (m_game->isOver())
    {
        m_parentScene->reward(m_game->getScore());
        removeFromParent();
    }
    else {
        int restSeconds = m_game->restSeconds();
        auto text = std::to_string(restSeconds);
        m_restSecondsView->setString(text);
        if (restSeconds <= 10)
            m_restSecondsView->setTextColor({255, 0, 0, 255});
    }
}

void FindPairGameLayer::setScene(FindPairScene *parentScene) {
    m_parentScene = parentScene;
    m_parentScene->retain();
}

bool FindPairGameLayer::handleTouch(Touch *touch, Event *event)
{
    auto touchLoc = touch->getLocation();
    auto bbox = event->getCurrentTarget()->getBoundingBox();
    // Если мы жмакнули по карте
    if (bbox.containsPoint(touchLoc))
    {
        auto sprite = dynamic_cast<Sprite*>(event->getCurrentTarget());
        int id = sprite->getTag();
        int i = id / 100;
        int j = id % 100;

        // меняем отображение текущей карты
        m_game->openCard(i, j);
        auto currentCard = m_game->getCard(i, j);
        auto texture = getTextureForCard(currentCard);
        sprite->setTexture(texture);

        auto firstOpenedCard = m_game->getOpenedCard();
        auto tag = m_game->getCardId(firstOpenedCard);
        auto firstOpenedCardNode = this->getChildByTag(tag);
        // меняем отображение парной(т.е. первой открытой) карты
        if (firstOpenedCardNode)
        {
            auto sprite = dynamic_cast<Sprite*>(firstOpenedCardNode);
            auto texture = getTextureForCard(firstOpenedCard);
            sprite->setTexture(texture);
        }

    }
    return false;
}

void FindPairGameLayer::renderGame()
{
    this->setColor(Color3B{0, 180, 0});
    int const marginX = 15;
    int const marginY = 10;
    int x = 0;
    int y = 0;
    for (int i = 0; i < CARDS_VARIANTS - 1; i++)
    {
        y += marginY;
        x = 0;
        for(int j = 0; j < CARDS_VARIANTS; j++)
        {
            auto cardShirt = Sprite::create("Cards/CardShirt.png");
            if (!cardShirt) return;
            cardShirt->setAnchorPoint({0, 0});

            x += marginX;
            cardShirt->setPosition(x, y);
            x += 30; // размер спрайта карты
            x += marginX;
            // добавляем спрайт с id, чтобы при клике вытащить координаты карты в
            // игре
            int id = m_game->getCardId(i, j);
            this->addChild(cardShirt, 1, id);

            // создаем обработчик клика по каждой карте. Можно наверно сделать 1
            // обработчик на все поле, но тогда нужно где-то хранить связку
            // спрайт-карта чтобы в этом обработчике искать опять же пересечение
            // клика с нужной картой
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            listener->onTouchBegan =
                    CC_CALLBACK_2(FindPairGameLayer::handleTouch, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,
                                                                     cardShirt);
        }
        y += 40; // размер спрайта карты
        y += marginY;
    }
}

std::string FindPairGameLayer::getTextureForCard(const Card &card) {
    // открытая карта
    std::string filename;
    if (card.opened && !card.paired)
    {
        switch (card.value) {
        case 1:
            filename = "Cards/One.png";
            break;
        case 2:
            filename = "Cards/Two.png";
            break;
        case 3:
            filename = "Cards/Three.png";
            break;
        case 4:
            filename = "Cards/Four.png";
            break;
        case 5:
            filename = "Cards/Five.png";
            break;
        case 6:
            filename = "Cards/Six.png";
            break;
        default:
            break;
        }
    }
    // закрытая карта
    else if (!card.opened)
    {
        filename = "Cards/CardShirt.png";
    }
    // else {} // запаренная. Не показываем

    return filename;
}
