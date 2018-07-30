#include "TortugaScene.h"
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>

USING_NS_CC;

Scene *TortugaScene::createScene()
{
    return TortugaScene::create();
}

bool TortugaScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("Coasts/Tortuga.png");
    auto sw = sprite->getBoundingBox().size.width;
    auto sh = sprite->getBoundingBox().size.height;
    sprite->setScaleX(visibleSize.width/sw);
    sprite->setScaleY(visibleSize.height/sh);
    this->addChild(sprite);
    return true;
}
