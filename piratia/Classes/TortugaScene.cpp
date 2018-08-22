#include <iostream>

#include "TortugaScene.h"
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventListenerTouch.h>
#include <cocos/base/CCEventDispatcher.h>
#include "../utilities.h"
#include "FindPairScene.h"
#include "ArenaScene.h"
#include "ForgeScene.h"

using namespace cocos2d;


bool TortugaScene::init()
{
    if ( !Scene::init() )
    {
        std::cout << "no base Scene init" << std::endl;
        return false;
    }
    setName("TourtugaScene");
    auto sprite = Sprite::create("Coasts/TortugaCoast.png");
    if (!sprite) {
        std::cout << "no TortugaCoast sprite" << std::endl;
        return false;
    }
    sprite->setAnchorPoint({0, 0});
    sprite->setPosition(0, 0);
    this->addChild(sprite);
    // создаем все объекты на острове

    if (!initMine()) return false;
    if (!initArena()) return false;
    if (!initForge()) return false;
    return true;
}

TortugaScene::~TortugaScene()
{
    m_mineScene->release();
    m_arenaScene->release();
}

bool TortugaScene::initArena()
{
    auto sprite = Sprite::create("Arena.png");
    if (!sprite) {
        std::cout << "no Arena sprite" << std::endl;
        return false;
    }
    sprite->setAnchorPoint({0, 0});
    sprite->setPosition(420-25, 240-25);
    m_arena = sprite;

    // обработка клика по спрайту
    m_arenaScene = ArenaScene::create();
    if (!m_arenaScene) return false;
    m_arenaScene->retain(); // захватыываем, чтобы в лямбдах это не умирало
    auto eventListener = EventListenerTouchOneByOne::create();
    auto handler = createSceneTransitionOnSpriteClick(m_arenaScene);
    eventListener->onTouchBegan = handler;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);

    this->addChild(sprite);

    return true;
}

bool TortugaScene::initMine()
{
    auto sprite = Sprite::create("Mine.png");
    if (!sprite) {
        std::cout << "no Mine sprite" << std::endl;
        return false;
    }
    m_mine = sprite;
    // внизу, слева
    sprite->setAnchorPoint({0,0});
    // 25 - половина размера спрайта шахты
    sprite->setPosition(105-25, 95-25);
    m_mineScene = FindPairScene::create();
    if(!m_mineScene) return false;
    m_mineScene->retain();
    auto eventListener = EventListenerTouchOneByOne::create();
    auto handler = createSceneTransitionOnSpriteClick(m_mineScene);
    eventListener->onTouchBegan = handler;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);

    this->addChild(sprite);
    return true;

}

bool TortugaScene::initForge()
{
    auto sprite = Sprite::create("Forge.png");
    if (!sprite)
    {
        std::cout << "no forge prite" << std::endl;
        return false;
    }

    sprite->setAnchorPoint({0, 0});
    sprite->setPosition(350-25, 95-25);

    m_forgeScene = ForgeScene::create();
    if (!m_forgeScene) return false;
    m_forgeScene->retain();
    auto eventListener = EventListenerTouchOneByOne::create();
    auto handler = createSceneTransitionOnSpriteClick(m_forgeScene);
    eventListener->onTouchBegan = handler;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);
    this->addChild(sprite);
    return true;

}
