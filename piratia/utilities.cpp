
#include "utilities.h"

#include <cocos/base/CCTouch.h>
#include <cocos/base/CCVector.h>
#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCScene.h>
#include <cocos/base/CCEventListenerTouch.h>

using namespace cocos2d;

EventListenerTouchOneByOne::ccTouchBeganCallback createSceneTransitionOnSpriteClick(cocos2d::Sprite *sprite, cocos2d::Scene *scene)
{
    // захватываем владение сценой. Без этого будет падать на pushScene, мол счетчик
    // ссылок нулевой
    scene->retain();
    return [=](Touch* touch, Event* event) -> bool {
        auto bb = event->getCurrentTarget()->getBoundingBox();
        auto loc = touch->getLocation();
        if(bb.containsPoint(loc))
        {
            auto director = Director::getInstance();
            director->pushScene(scene);
            scene->release();
            return true;
        }
        return false;
    };
}
