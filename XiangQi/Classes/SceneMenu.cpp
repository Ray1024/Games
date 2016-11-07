#include "SceneMenu.h"
#include "SceneGame.h"

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

	//创建背景-----------------------------------------------------
	Sprite* bg = Sprite::create("bg.jpg");
	bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	bg->setScaleX(winSize.width / bg->getContentSize().width);
	bg->setScaleY(winSize.height / bg->getContentSize().height);
	addChild(bg,-2);

	//创建Menu-----------------------------------------------------
	Menu* menu = Menu::create();
	this->addChild(menu);
	menu->setPosition(270/SCALE_FACTOR, 480/SCALE_FACTOR);

	//创建选边红菜单
	MenuItem* itemChooseRed = MenuItemImage::create(
		"menu_chosered.png", 
		"menu_chosered.png", 
		CC_CALLBACK_1(SceneMenu::menuChooseRed,this));
	menu->addChild(itemChooseRed);
	itemChooseRed->setPosition(0/SCALE_FACTOR,160/SCALE_FACTOR);

	//创建选边黑菜单
	MenuItem* itemChooseBlack = MenuItemImage::create(
		"menu_choseblack.png", 
		"menu_choseblack.png",
		CC_CALLBACK_1(SceneMenu::menuChooseBlack,this));
	menu->addChild(itemChooseBlack);
	itemChooseBlack->setPosition(0/SCALE_FACTOR,0/SCALE_FACTOR);

	//创建退出菜单
	MenuItem* itemExit = MenuItemImage::create(
		"menu_exit.png",
		"menu_exit.png",
		CC_CALLBACK_1(SceneMenu::menuExit,this));
	menu->addChild(itemExit);
	itemExit->setPosition(0/SCALE_FACTOR,-160/SCALE_FACTOR);

	//注册手机键盘的事件----------------------------------------------
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SceneMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

    return true;
}

void SceneMenu::menuChooseRed(Ref*)
{
	auto transition=TransitionFade::create(1.0f,SceneGame::scene(true));
	Director::getInstance()->replaceScene(transition);
}

void SceneMenu::menuChooseBlack(Ref*)
{
	auto transition=TransitionFade::create(1.0f,SceneGame::scene(false));
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