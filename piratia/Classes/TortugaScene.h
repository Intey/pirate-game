#ifndef TORTUGASCENE_H
#define TORTUGASCENE_H
#include <cocos/2d/CCScene.h>

namespace cocos2d {
    class Sprite;
}

class TortugaScene : public cocos2d::Scene
{
public:

    virtual bool init();

    CREATE_FUNC(TortugaScene)
    virtual ~TortugaScene();

    bool initArena();
    bool initMine();
    bool initForge();
private:
    cocos2d::Sprite* m_mine;
    cocos2d::Sprite* m_arena;
    cocos2d::Scene* m_mineScene;
    cocos2d::Scene* m_arenaScene;
    cocos2d::Scene* m_forgeScene;
};

#endif // TORTUGASCENE_H
