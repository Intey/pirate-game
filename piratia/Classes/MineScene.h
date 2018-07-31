#ifndef MINESCENE_H
#define MINESCENE_H

#include <cocos/2d/CCScene.h>


class MineScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MineScene)
};

#endif // MINESCENE_H
