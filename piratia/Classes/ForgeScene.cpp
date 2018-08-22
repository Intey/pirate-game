#include "ForgeScene.h"
#include <cocos/2d/CCSprite.h>

#include <cocos/ui/UIListView.h>
#include <cocos/ui/UIVBox.h>
#include <cocos/ui/UIHBox.h>
#include <cocos/ui/UIText.h>
#include <cocos/ui/UILayoutManager.h> // for Margin
#include <cocos/2d/CCLayer.h>
#include <cocos/ui/UIButton.h>
#include "../Game/Recipe.h"
#include "../Game/Player.h"

using namespace cocos2d;

ForgeScene::ForgeScene()
{

}

bool ForgeScene::init()
{
    if (!Scene::init())
    {
        CCLOGERROR("bitch");
        return false;
    }
    initAll();
    return true;
}

void ForgeScene::onEnter()
{
    Scene::onEnter();
}

bool ForgeScene::initAll()
{
    // create gui
    //
    auto player = Game::Player::getInstance();

    auto rootLayout = ui::VBox::create();
    if (!rootLayout)
    {
        CCLOGERROR("rootlayout fail");
        return false;
    }
    rootLayout->setAnchorPoint({0, 1});
    rootLayout->setPosition({0, 320});


    auto recipesView = renderRecipesList(player->getCraftAbility()->recipes());
    if (!recipesView) {
        CCLOGERROR("RENDER");
        return false;
    }

    rootLayout->addChild(recipesView);
    auto layer = LayerColor::create({100, 100, 255, 50});
    layer->setAnchorPoint({0, 0});

    this->addChild(rootLayout);
    this->addChild(layer);
    return true;
}

ui::Widget* ForgeScene::renderRecipesList(std::vector<Game::Recipe> const& recipes)
{
    auto recipesView = ui::ListView::create();
    recipesView->setDirection(ui::ListView::Direction::VERTICAL);
    recipesView->setAnchorPoint({0, 0});
    recipesView->setPosition({100, 320});
    recipesView->setContentSize({100, 300});
    if (!recipesView)
    {
        CCLOGERROR("view fail");
        return nullptr;
    }

    if (recipes.empty())
    {
           auto text = ui::Text::create("no recipes", "fonts/arial.ttf", 14);
           if (!text) return recipesView;
           recipesView->pushBackCustomItem(text);
    }
    else
    {
        for (auto & recipe: recipes)
        {
            auto item = renderRecipeItem(recipe);
            if (item)
                recipesView->pushBackCustomItem(item);
            else
                CCLOGERROR("Wrong child");
        }
    }
    return recipesView;
}

ui::Widget *ForgeScene::renderRecipeItem(const Game::Recipe &recipe) const
{
    int const MARGIN = 5;
    auto text1 = ui::Text::create(recipe.name(), "fonts/arial.ttf", 14);
    if (!text1)
    {
        CCLOGERROR("no text for recipe %s", recipe.name().c_str());
        return text1;
    }
    text1->setTextColor({255, 0, 255, 255});
    auto margin1 = ui::Margin(MARGIN, 0, MARGIN, MARGIN);
    auto lp = ui::LinearLayoutParameter::create();
    if (!lp) CCLOGERROR("lp not");
    lp->setMargin(margin1);
    text1->setLayoutParameter(lp);
    return text1;
}

ui::Widget *ForgeScene::renderReciepePreview()
{
    return nullptr;
}

ui::Widget *ForgeScene::renderCraftLevelProgressbar()
{
    return nullptr;
}

ui::Widget *ForgeScene::renderCraftButton()
{
    return nullptr;
}

void ForgeScene::setRecipes(std::vector<Game::Recipe> const& recipes)
{

}
