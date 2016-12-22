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
	_cardManager1 = CardManager::create();
	_cardManager1->setPosition(visibleSize.width/2, visibleSize.height/6);
	this->addChild(_cardManager1, 1);

	_cardManager2 = ICardManager::create();
	_cardManager2->setPosition(800,485);
	this->addChild(_cardManager2, 1);

	_cardManager3 = ICardManager::create();
	_cardManager3->setPosition(150,485);
	this->addChild(_cardManager3, 1);

	_bottomCardZone = BottomCardZone::create();
	_bottomCardZone->setPosition(450, 480);
	this->addChild(_bottomCardZone, 1);

	initCards();
    
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
	_cardManager1->chuPai();
	_cardManager2->chuPai();
	_cardManager3->chuPai();
}

void SceneGame::initCards()
{
	for (int i=0; i<13; i++)
	{
		for (int j=0; j<4; j++)
		{
			CardInfo info;
			info._num = (CardNum)i;
			info._tag = (CardTag)j;
			_cardInfo.push_back(info);
		}
	}

	CardInfo info;
	info._num = (CardNum)13;
	info._tag = (CardTag)0;
	_cardInfo.push_back(info);
	info._num = (CardNum)14;
	_cardInfo.push_back(info);
}

void SceneGame::faPai()
{
	std::random_shuffle(_cardInfo.begin(), _cardInfo.end());

	for (int i=0; i<_cardInfo.size(); i++)
	{
		if (i<=16)
		{
			// 角色1
			_cardManager1->dealer(_cardInfo.at(i));
		} else if (i>16 &&i<=33)
		{
			// 角色2
			_cardManager2->dealer(_cardInfo.at(i));
		} else if (i>33 &&i<=50)
		{
			// 角色3
			_cardManager3->dealer(_cardInfo.at(i));
		}else
		{
			//底牌
			_bottomCardZone->Show(_cardInfo.at(i));
		}
	}
}