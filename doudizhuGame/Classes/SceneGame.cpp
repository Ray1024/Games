#include "SceneGame.h"
#include "SceneMenu.h"

USING_NS_CC;

Scene* SceneGame::createScene()
{
    auto scene = Scene::create();
    auto layer = SceneGame::create();
    scene->addChild(layer);

    return scene;
}

bool SceneGame::init()
{
    // 初始化基类----------------------------------------
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 背景----------------------------------------------
	auto bg = Sprite::create("bg_table.jpg");
	bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bg, 0);

	// 创建返回菜单---------------------------------------------
	auto itemBack = createCustomMenuItem("item_back.png", "item_back.png");
	itemBack->setCallback(CC_CALLBACK_1(SceneGame::menuBackCallback, this));
	itemBack->setPosition(visibleSize.width/2+200, visibleSize.height-50);

    auto menuBack = Menu::create(itemBack, NULL);
	menuBack->setPosition(origin);
    this->addChild(menuBack, 1);

	// 创建准备菜单---------------------------------------------
	auto itemZhunbei = createCustomMenuItem("item_zhunbei.png", "item_zhunbei.png");
	itemZhunbei->setCallback(CC_CALLBACK_1(SceneGame::menuZhunbeiCallback, this));

	_menuZhunbei = Menu::create(itemZhunbei, NULL);
	this->addChild(_menuZhunbei, 1);

	// 创建游戏菜单---------------------------------------------
	auto itemTishi = createCustomMenuItem("item_tishi.png", "item_tishi_d.png");
	itemTishi->setCallback(CC_CALLBACK_1(SceneGame::menuTishiCallback, this));
	itemTishi->setPosition(-400 , -180);

	auto itemChongxuan = createCustomMenuItem("item_chongxuan.png", "item_chongxuan_d.png");
	itemChongxuan->setCallback(CC_CALLBACK_1(SceneGame::menuChongxuanCallback, this));
	itemChongxuan->setPosition(-200 , -180);

	auto itemBuchu = createCustomMenuItem("item_buchu.png", "item_buchu_d.png");
	itemBuchu->setCallback(CC_CALLBACK_1(SceneGame::menuBuchuCallback, this));
	itemBuchu->setPosition(0 , -180);

	auto itemChupai = createCustomMenuItem("item_chupai.png", "item_chupai_d.png");
	itemChupai->setCallback(CC_CALLBACK_1(SceneGame::menuChuPaiCallback, this));
	itemChupai->setPosition(200 , -180);

	_menuGame = Menu::create(itemTishi, itemChongxuan, itemBuchu, itemChupai, NULL);
	_menuGame->setScale(0.7);
	//_menuGame->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(_menuGame, 1);
	_menuGame->setVisible(false);

	// 玩家头像----------------------------------------------
	auto player1 = Sprite::create("touxiang_dizhu.png");
	player1->setScale(0.8);
	player1->setPosition(player1->getContentSize().width/2, player1->getContentSize().height/2 + 200 - 20);
	this->addChild(player1, 0);

	auto player2 = Sprite::create("touxiang_nongmin.png");
	player2->setScale(0.8);
	player2->setPosition(visibleSize.width - player2->getContentSize().width/2, visibleSize.height - player2->getContentSize().height/2 + 10);
	this->addChild(player2, 0);

	auto player3 = Sprite::create("touxiang_nongmin.png");
	player3->setScale(0.8);
	player3->setPosition(player3->getContentSize().width/2, visibleSize.height - player3->getContentSize().height/2 + 10);
	this->addChild(player3, 0);

	// 牌堆-----------------------------------------------
	_pokerManager1 = PokerManager::create();
	_pokerManager1->setPosition(visibleSize.width/2, visibleSize.height/6);
	this->addChild(_pokerManager1, 1);

	_pokerManager2 = IPokerManager::create();
	_pokerManager2->setPosition(800,485);
	this->addChild(_pokerManager2, 1);

	_pokerManager3 = IPokerManager::create();
	_pokerManager3->setPosition(150,485);
	this->addChild(_pokerManager3, 1);

	initPokers();
    
    return true;
}

void SceneGame::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(SceneMenu::createScene());
}

void SceneGame::menuZhunbeiCallback(Ref* pSender)
{
	((MenuItem*)pSender)->setVisible(false);
    _menuGame->setVisible(true);
	faPai();
}

void SceneGame::menuTishiCallback(Ref* pSender)
{

}

void SceneGame::menuChongxuanCallback(Ref* pSender)
{

}

void SceneGame::menuBuchuCallback(Ref* pSender)
{

}

void SceneGame::menuChuPaiCallback(Ref* pSender)
{
	_pokerManager1->chuPai();
	_pokerManager2->chuPai();
	_pokerManager3->chuPai();
}

void SceneGame::initPokers()
{
	for (int i=0; i<13; i++)
	{
		for (int j=0; j<4; j++)
		{
			PokerInfo info;
			info._num = (PokerNum)i;
			info._tag = (PokerTag)j;
			_pokerInfo.push_back(info);
		}
	}

	PokerInfo info;
	info._num = (PokerNum)13;
	info._tag = (PokerTag)0;
	_pokerInfo.push_back(info);
	info._num = (PokerNum)14;
	_pokerInfo.push_back(info);
}

void SceneGame::faPai()
{
	std::random_shuffle(_pokerInfo.begin(), _pokerInfo.end());

	for (int i=0; i<_pokerInfo.size(); i++)
	{
		if (i<=16)
		{
			// 角色1
			_pokerManager1->dealer(_pokerInfo.at(i));
		} else if (i>16 &&i<=33)
		{
			// 角色2
			_pokerManager2->dealer(_pokerInfo.at(i));
		} else if (i>33 &&i<=50)
		{
			// 角色3
			_pokerManager3->dealer(_pokerInfo.at(i));
		}else
		{
			//底牌
		}
	}
}