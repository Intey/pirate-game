#ifndef FINDPAIRGAMELAYER_H
#define FINDPAIRGAMELAYER_H

#include <cocos/2d/CCLayer.h>

namespace cocos2d {
class Label;
class Event;
class Touch;

}

class FindPairScene;
class Card;
class FindPairGame;

class FindPairGameLayer : public cocos2d::Layer {

public:
    CREATE_FUNC(FindPairGameLayer)

    virtual ~FindPairGameLayer();
    // Node interface
public:
    virtual bool init() override;

    virtual void onEnter() override;

    virtual void onExit() override;

    virtual void update(float delta) override;

public:
    void setScene(FindPairScene* parentScene);

private:
    bool handleTouch(cocos2d::Touch *touch, cocos2d::Event *event);

    void renderGame();

    std::string getTextureForCard(Card const& card);
private:
    FindPairScene* m_parentScene;
    FindPairGame* m_game;
    cocos2d::Label* m_restSecondsView;
    static const std::string M_GAME_NAME;
    static const int CARDS_VARIANTS;
    static const int GAME_TIMEOUT;
};


#endif // FINDPAIRGAMELAYER_H
