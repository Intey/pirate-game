#include <iostream>

#include "TortugaScene.h"
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventListenerTouch.h>
#include <cocos/base/CCEventDispatcher.h>
#include "../utilities.h"
#include "MineScene.h"
#include "ArenaScene.h"

using namespace cocos2d;

Scene *TortugaScene::createScene()
{
    return TortugaScene::create();
}

bool TortugaScene::init()
{
    if ( !Scene::init() )
    {
        std::cout << "no base Scene init" << std::endl;
        return false;
    }
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
    return true;
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
    m_arenaScene = ArenaScene::createScene();
    auto eventListener = EventListenerTouchOneByOne::create();
    auto handler = createSceneTransitionOnSpriteClick(sprite, m_arenaScene);
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
    m_mineScene = MineScene::createScene();
    auto eventListener = EventListenerTouchOneByOne::create();
    auto handler = createSceneTransitionOnSpriteClick(sprite, m_mineScene);
    eventListener->onTouchBegan = handler;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);

    this->addChild(sprite);
    return true;

}
