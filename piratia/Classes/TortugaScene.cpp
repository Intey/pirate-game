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
    auto sprite = Sprite::create("Coasts/TortugaCoast.png");
    sprite->setAnchorPoint({0, 0});
    sprite->setPosition(0, 0);
    this->addChild(sprite);
    return true;
}
