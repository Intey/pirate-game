#include <iostream>

#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/base/CCDirector.h>

#include "../Game/FindPairGame.h"
#include "FindPairScene.h"
#include "FindPairGameLayer.h"

using namespace cocos2d;
using namespace Game;

/**
 * @brief The FindPairGameLayer class
 * # rendering
 * При инициализации рисуются все карты закрытыми. При открытии карты,
 * открываемая перерисовывается. Если открывается вторая, и значения у них не совпадают - обе карты перерисовываются
 */
FindPairScene *FindPairScene::createScene()
{
    return FindPairScene::create();
}

bool FindPairScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    setName("FindPairScene");
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
    init();
    schedule(CC_CALLBACK_1(FindPairGameLayer::update, m_gameLayer), "updateLayer");
}

void FindPairScene::onExit()
{
    unschedule("updateLayer");
    Scene::onExit();
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
    this->scheduleOnce([this, rewardLayer](float) {
        Director::getInstance()->popScene(); // завершаем текущую сцену
        this->removeChild(rewardLayer);
    }, 2, "exitFindPairScene");

    this->addChild(rewardLayer);
}

// TODO: запустить обновления
