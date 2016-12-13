#include "SceneGame.h"
#include "SceneMenu.h"
#include "AppMacros.h"

#include "ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocostudio::timeline;

Scene* SceneGame::scene()
{
    auto scene = Scene::create();
    
    SceneGame *layer = SceneGame::create();

    scene->addChild(layer);

    return scene;
}

bool SceneGame::init()
{
	// 初始化基类-----------------------------------------------------
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    //菜单------------------------------------------------------------
    auto backItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(SceneGame::menuBackCallback,this));
    
    backItem->setPosition(origin + Vec2(visibleSize) - Vec2(backItem->getContentSize() / 2));
    auto menu = Menu::create(backItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
	//----------------------------------------------------------------

	return true;
}

void SceneGame::menuBackCallback(Ref* sender)
{
	auto transition=TransitionFade::create(1.0f,SceneMenu::scene());
	Director::getInstance()->replaceScene(transition);
}
