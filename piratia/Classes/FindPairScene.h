#ifndef FINDPAIRSCENE_H
#define FINDPAIRSCENE_H

#include <cocos/2d/CCScene.h>
#include <string>

class FindPairGameLayer;

namespace cocos2d {
class Layer;
}

/**
 * @brief Сцена мини-игры "найди пару".
 */
class FindPairScene: public cocos2d::Scene
{
public:
    CREATE_FUNC(FindPairScene)
    virtual ~FindPairScene();

    static FindPairScene *createScene();
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;
public:
    void reward(int score);

private:
    FindPairGameLayer* m_gameLayer;
};


#endif // FINDPAIRSCENE_H
