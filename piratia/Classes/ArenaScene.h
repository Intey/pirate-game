#ifndef ARENASCENE_H
#define ARENASCENE_H

#include <cocos/2d/CCScene.h>

class ArenaScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(ArenaScene)

};

#endif // ARENASCENE_H
