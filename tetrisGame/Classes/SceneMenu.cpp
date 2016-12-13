#include "SceneMenu.h"
#include "SceneGame.h"
#include "AppMacros.h"

Scene* SceneMenu::scene()
{
    Scene* scene = Scene::create();

    SceneMenu* layer = SceneMenu::create();

    scene->addChild(layer);

    return scene;
}

bool SceneMenu::init()
{
    Layer::init();

    Size winSize = Director::getInstance()->getWinSize();

	//背景-----------------------------------------------------
	Sprite* bg = Sprite::create("bg.png");
	bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	bg->setScaleX(winSize.width / bg->getContentSize().width);
	bg->setScaleY(winSize.height / bg->getContentSize().height);
	addChild(bg,-2);

	//菜单-----------------------------------------------------
	Menu* menu = Menu::create();
	this->addChild(menu);

	MenuItem* itemBeginGame = MenuItemImage::create(
		"menu_chosered.png", 
		"menu_chosered.png", 
		CC_CALLBACK_1(SceneMenu::menuBeginGame,this));
	menu->addChild(itemBeginGame);
	itemBeginGame->setPosition(0/SCALE_FACTOR,0/SCALE_FACTOR);

	MenuItem* itemExit = MenuItemImage::create(
		"menu_exit.png",
		"menu_exit.png",
		CC_CALLBACK_1(SceneMenu::menuExit,this));
	menu->addChild(itemExit);
	itemExit->setPosition(0/SCALE_FACTOR,-160/SCALE_FACTOR);

	//注册手机键盘的事件-----------------------------------------
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SceneMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

    return true;
}

void SceneMenu::menuBeginGame(Ref*)
{
	auto transition=TransitionFade::create(1.0f,SceneGame::scene());
	Director::getInstance()->replaceScene(transition);
}

void SceneMenu::menuExit(Ref*)
{
	Director::getInstance()->end();
}

void SceneMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	// 安卓键盘事件处理
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //返回
	{
		Director::getInstance()->end();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_MENU)
	{
		// TODO: 设置菜单
	}
}