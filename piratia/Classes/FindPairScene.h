#ifndef FINDPAIRSCENE_H
#define FINDPAIRSCENE_H

#include <cocos/2d/CCScene.h>
#include <string>

class FindPairGameLayer;

namespace Game {
class Reward;
}

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

    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;
public:
    void reward(const Game::Reward &rawReward);

private:
    FindPairGameLayer* m_gameLayer;
};


#endif // FINDPAIRSCENE_H
