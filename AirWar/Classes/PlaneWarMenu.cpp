#include "PlaneWarMenu.h"
#include "PlaneWarGame.h"
#include "PlaneWarInfoboard.h"
#include "AppMacros.h"

Scene* PlaneWarMenu::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		PlaneWarMenu *layer = PlaneWarMenu::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PlaneWarMenu::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! Layer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		Size size = Director::getInstance()->getWinSize();

		// 添加背景
		Sprite* bg = Sprite::create("gameui.png");
		bg->setPosition( Point(size.width/2, size.height/2) );
		this->addChild(bg, PlaneWarGame::Z_BG);

		// 添加开始菜单项（是一个自动释放的对象）
		MenuItemSprite* pStartItem = MenuItemSprite::create(
			Sprite::create("menu_start.png"),
			NULL,
			CC_CALLBACK_1(PlaneWarMenu::menuStartCallback,this));
		CC_BREAK_IF(! pStartItem);
		pStartItem->setPosition(Point(0, 50-0));

		// 添加玩法介绍菜单项（是一个自动释放的对象）
		MenuItemSprite* pManualItem = MenuItemSprite::create(
			Sprite::create("menu_manual.png"),
			NULL,
			CC_CALLBACK_1(PlaneWarMenu::menuManualCallback,this));
		CC_BREAK_IF(! pManualItem);
		pManualItem->setPosition(Point(0, 50-(1*pStartItem->getContentSize().height+15/SCALE_FACTOR)));

		// 添加关于按钮（菜单项）（是一个自动释放的对象）
		MenuItemSprite* pAboutItem = MenuItemSprite::create(
			Sprite::create("menu_about.png"),
			NULL,
			CC_CALLBACK_1(PlaneWarMenu::menuAboutCallback,this));
		CC_BREAK_IF(! pAboutItem);
		pAboutItem->setPosition(Point(0, 50-(1*pStartItem->getContentSize().height+15/SCALE_FACTOR)*2));

		// 添加退出按钮（菜单项）（是一个自动释放的对象）
		MenuItemSprite* pExitItem = MenuItemSprite::create(
			Sprite::create("menu_exit.png"),
			NULL,
			CC_CALLBACK_1(PlaneWarMenu::menuBackCallback,this));
		CC_BREAK_IF(! pExitItem);
		pExitItem->setPosition(Point(0, 50-(1*pStartItem->getContentSize().height+15/SCALE_FACTOR)*3));

		// 创建菜单，将菜单项加入
		Menu* pMenu = Menu::create(pManualItem,pAboutItem,pStartItem,pExitItem,NULL);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, PlaneWarGame::Z_MENU);

		bRet = true;
	} while (0);

	return bRet;
}

void PlaneWarMenu::menuStartCallback(Ref* pSender)
{
	Scene * scene = PlaneWarGame::scene();
	Director::getInstance()->pushScene(scene);
}

void PlaneWarMenu::menuManualCallback(Ref* pSender)
{
	Scene * scene = PlaneWarInfoboard::scene();
	Director::getInstance()->pushScene(scene);
}

void PlaneWarMenu::menuAboutCallback(Ref* pSender)
{
	Scene * scene = PlaneWarInfoboard::scene();
	Sprite* context = ((Sprite*)scene->getChildByTag(1)->getChildByTag(1));
	Texture2D* image = new Texture2D;
	Image* im = new Image;
	im->initWithImageFile("about1.png");
	image->initWithImage(im);
	context->setTexture(image);
	Director::getInstance()->pushScene(scene);
}

void PlaneWarMenu::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
