#include "MineScene.h"

cocos2d::Scene *MineScene::createScene()
{
    return MineScene::create();
}

bool MineScene::init()
{
    if (!Scene::init()) return false;
    return true;
}