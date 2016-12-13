#include "PlaneWarInfoboard.h"
#include "PlaneWarGame.h"

Scene* PlaneWarInfoboard::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		PlaneWarInfoboard *layer = PlaneWarInfoboard::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer,0,1);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PlaneWarInfoboard::init()
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

		// ��ӱ���
		Sprite* pBackG = Sprite::create("gameui_info.png");
		pBackG->setPosition( Point(size.width/2, size.height/2) );
		this->addChild(pBackG, PlaneWarGame::Z_BG);

		// ��ӿ�ʼ�˵����һ���Զ��ͷŵĶ���
		MenuItemSprite* pBackItem = MenuItemSprite::create(
			Sprite::create("menu_back.png"),
			NULL,
			CC_CALLBACK_1(PlaneWarInfoboard::menuBackCallback,this));
		CC_BREAK_IF(! pBackItem);
		pBackItem->setPosition(Point(0, 100));

		// �����˵������˵������
		Menu* pMenu = Menu::create(pBackItem, NULL);
		pMenu->setPosition(Point(size.width/2, 100));
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, PlaneWarGame::Z_MENU);

		// ��ʾ����
		Sprite* context = Sprite::create("manual.png");
		context->setPosition( Point(size.width/2, size.height*1/2) );
		this->addChild(context, PlaneWarGame::Z_MENU, 1);

		bRet = true;
	} while (0);

	return bRet;
}

void PlaneWarInfoboard::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}