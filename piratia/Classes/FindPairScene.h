#ifndef FINDPAIRSCENE_H
#define FINDPAIRSCENE_H

#include <cocos/2d/CCScene.h>
#include <string>

/**
 * @brief Сцена мини-игры "найди пару".
 */
class FindPairScene: public cocos2d::Scene
{
public:
    CREATE_FUNC(FindPairScene)

    static FindPairScene *createScene();
    virtual bool init();
};


#endif // FINDPAIRSCENE_H
