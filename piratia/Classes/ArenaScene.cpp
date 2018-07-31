#include "ArenaScene.h"

cocos2d::Scene *ArenaScene::createScene()
{
    return ArenaScene::create();
}

bool ArenaScene::init()
{
    if (!Scene::init()) return false;
    return true;
}
