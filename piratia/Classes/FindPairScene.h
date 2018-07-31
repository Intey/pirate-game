#ifndef FINDPAIRSCENE_H
#define FINDPAIRSCENE_H

#include <cocos/2d/CCScene.h>
#include <memory>
#include <string>

class FindPairGame;
/**
 * @brief Сцена мини-игры "найди пару".
 */
class FindPairScene: public cocos2d::Scene
{
public:
    CREATE_FUNC(FindPairScene)

    FindPairScene* createScene();
    virtual bool init();

private:
    void renderGame();
private:
    std::unique_ptr<FindPairGame> m_game;
    static const std::string M_GAME_NAME;
};

const std::string FindPairScene::M_GAME_NAME = "FIND_PAIR";

#endif // FINDPAIRSCENE_H
