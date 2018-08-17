
#include "utilities.h"

#include <cocos/base/CCTouch.h>
#include <cocos/base/CCVector.h>
#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/2d/CCScene.h>
#include <cocos/base/CCEventListenerTouch.h>

using namespace cocos2d;

EventListenerTouchOneByOne::ccTouchBeganCallback
createSceneTransitionOnSpriteClick(cocos2d::Scene *scene)
{
    return [scene](Touch* touch, Event* event) -> bool {
        auto bb = event->getCurrentTarget()->getBoundingBox();
        auto loc = touch->getLocation();
        if(bb.containsPoint(loc))
        {
            auto director = Director::getInstance();
            director->pushScene(scene);
            return true;
        }
        return false;
    };
}
