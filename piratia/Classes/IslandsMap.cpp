#include "IslandsMap.h"
#include <cocos/2d/CCScene.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>
#include <cocos/math/Vec2.h>
#include <cocos/base/CCEventListenerTouch.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCVector.h>
#include "../utilities.h"

#include "TortugaScene.h"

using namespace cocos2d;

IslandsMap::IslandsMap(Scene * scene)
{
    // привязываем обработчик событий к сцене. Только на сцене карты мы обрабатываем
    // нажатия на острова
    EventListenerTouchOneByOne * elm { EventListenerTouchOneByOne::create() };
    auto dispatcher = scene->getEventDispatcher(); //new EventDispatcher();

    // наполняем карту спрайтами островов
    Sprite * tortugaSprite { Sprite::create("Coasts/Tortuga.png") };
    if (tortugaSprite)
    {
        tortugaSprite->setAnchorPoint(Vec2(0, 0));
        // auto w = sprite->getBoundingBox().size.width;
        // auto h = sprite->getBoundingBox().size.height;
        tortugaSprite->setPosition(Vec2(0, 0));
        this->m_coastSprites.push_back( tortugaSprite );
        auto tortugaScene = TortugaScene::create();
        if (!tortugaScene)
        {
            printf("cant create tortuga scene");
            return;
        }
        m_tortugaScene = tortugaScene;
        if (!m_tortugaScene) return;
        m_tortugaScene->retain();
        elm->onTouchBegan = createSceneTransitionOnSpriteClick(tortugaScene); // handler;
        dispatcher->addEventListenerWithSceneGraphPriority(elm, tortugaSprite);
    }
    else
        printf("Problem loading %s", "Coasts/Tortuga.png");
}

void IslandsMap::renderOnScene(Scene *scene)
{
    for (auto const& coast: this->m_coastSprites)
    {
        scene->addChild(coast);
    }
}
