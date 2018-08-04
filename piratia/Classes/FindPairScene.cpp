#include <iostream>

#include <cocos/base/CCScheduler.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerTouch.h>
#include <cocos/2d/CCLayer.h>

#include "FindPairGame.h"
#include "FindPairScene.h"

using namespace cocos2d;

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
    bool init() {
        m_game = new FindPairGame(60, CARDS_VARIANTS);

        this->renderGame();


        m_game->start();
        return true;
    }
    void update(float delta) {
        m_game->update(delta);

    }

private:
    void renderGame()
    {
        // auto fieldSprite = Sprite::create("Cards/Field.png");
        // fieldSprite->setAnchorPoint({0, 0});
        // fieldSprite->setPosition(0, 0);
        // if (!fieldSprite) {
        //     cout << "error loading find pair cards field image" << endl;
        //     return;
        // }

        this->setColor(Color3B{0, 180, 0});
        // this->addChild(fieldSprite);

        // отрисовать сетку игры, все карты
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
                listener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
                    auto touchLoc = touch->getLocation();
                    auto bbox = event->getCurrentTarget()->getBoundingBox();
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
                        // меняем отображение парной
                        if (firstOpenedCardNode)
                        {
                            auto sprite = dynamic_cast<Sprite*>(firstOpenedCardNode);
                            auto texture = getTextureForCard(firstOpenedCard);
                            sprite->setTexture(texture);
                        }

                    }
                    return false;
                };
                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardShirt);
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
    FindPairGame* m_game;
    static const std::string M_GAME_NAME;
    static const int CARDS_VARIANTS;
};

const std::string FindPairGameLayer::M_GAME_NAME = "FIND_PAIR";
const int FindPairGameLayer::CARDS_VARIANTS = 6;

FindPairScene *FindPairScene::createScene()
{
    return FindPairScene::create();
}

bool FindPairScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    FindPairGameLayer *layer = FindPairGameLayer::create();
    this->addChild(layer);
    return true;
}