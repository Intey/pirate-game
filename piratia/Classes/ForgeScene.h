#ifndef FORGESCENE_H
#define FORGESCENE_H

#include <cocos/2d/CCScene.h>
#include <vector>

namespace Game {
class Recipe;
}

namespace cocos2d {
namespace ui {
class Widget;

}
}

class ForgeScene: public cocos2d::Scene
{
public:
    ForgeScene();
    // Node interface
public:
    CREATE_FUNC(ForgeScene)
    virtual bool init();
    virtual void onEnter();
public:
    void setRecipes(const std::vector<Game::Recipe> &recipes);
    bool initAll();
// rendering
public:
    cocos2d::ui::Widget* renderRecipesList(std::vector<Game::Recipe> const& reciepes);
    cocos2d::ui::Widget* renderRecipeItem(Game::Recipe const& recipe) const;
    cocos2d::ui::Widget* renderReciepePreview(const Game::Recipe &recipe);
    cocos2d::ui::Widget* renderReciepePreview();
    cocos2d::ui::Widget* renderCraftLevelProgressbar();
    cocos2d::ui::Widget* renderCraftButton();

};

#endif // FORGESCENE_H
