#include <iostream>

#include <cocos/base/CCScheduler.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerTouch.h>
#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCLabel.h>

#include "FindPairGame.h"
#include "FindPairScene.h"

using namespace cocos2d;

struct Reward {
    Reward(int score): value(score) {}
    int value;
    std::string toString() const {
        return std::string("Score: ") + std::to_string(value);
    }
};

Reward reward(int gameScore) {
    return Reward(gameScore);
}

/**
 * @brief The FindPairGameLayer class
 * # rendering
 * При инициализации рисуются все карты закрытыми. При открытии карты,
 * открываемая перерисовывается. Если открывается вторая, и значения у них не совпадают - обе карты перерисовываются
 */
class FindPairGameLayer : public Layer {

public:
    CREATE_FUNC(FindPairGameLayer)

    // Node interface
public:
    virtual bool init() override {
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

    virtual void onEnter() override {
        Layer::onEnter();
        m_game->start();
        m_restSecondsView->setString(std::to_string(GAME_TIMEOUT));
        m_restSecondsView->setAnchorPoint({0, 0});
        m_restSecondsView->setPosition(0, 320 - 20);
        m_restSecondsView->setTextColor({255, 255, 255, 255});
    }

    virtual void onExit() override {
        Layer::onExit();
        m_game->stop();
    }

    virtual void update(float delta) override {
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

public:
    void setScene(FindPairScene* parentScene) {
        m_parentScene = parentScene;
    }

private:
    bool handleTouch(Touch *touch, Event *event)
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

    void renderGame()
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

    std::string getTextureForCard(Card const& card) {
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
private:
    FindPairScene* m_parentScene;
    FindPairGame* m_game;
    Label* m_restSecondsView;
    static const std::string M_GAME_NAME;
    static const int CARDS_VARIANTS;
    static const int GAME_TIMEOUT;
};

const std::string FindPairGameLayer::M_GAME_NAME = "FIND_PAIR";
const int FindPairGameLayer::CARDS_VARIANTS = 6;
const int FindPairGameLayer::GAME_TIMEOUT = 1;

FindPairScene *FindPairScene::createScene()
{
    return FindPairScene::create();
}

bool FindPairScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    m_gameLayer = FindPairGameLayer::create();
    m_gameLayer->setScene(this);
    if (m_gameLayer)
    {
        this->addChild(m_gameLayer);
    }

    return true;
}

void FindPairScene::onEnter()
{
    Scene::onEnter();
    schedule(CC_CALLBACK_1(FindPairGameLayer::update, m_gameLayer), "updateLayer");
}

void FindPairScene::reward(int score)
{
    unschedule("updateLayer");
    auto reward = Reward(score);
    auto rewardLayer = LayerColor::create({50, 180, 50, 255});
    rewardLayer->setAnchorPoint({0, 0});
    rewardLayer->setPosition(0, 0);

    auto label = Label::createWithTTF(reward.toString(), "fonts/arial.ttf", 16);
    label->setTextColor({255, 255, 255, 255});
    auto size = rewardLayer->getBoundingBox().size;
    // рисуем по центру
    label->setAnchorPoint({0.5, 0.5});
    label->setPosition(size.width/2, size.height/2);
    rewardLayer->addChild(label);
    this->addChild(rewardLayer);
}

// TODO: запустить обновления
