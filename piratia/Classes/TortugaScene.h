#ifndef TORTUGASCENE_H
#define TORTUGASCENE_H
#include <cocos/2d/CCScene.h>


class TortugaScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(TortugaScene);
};

#endif // TORTUGASCENE_H
