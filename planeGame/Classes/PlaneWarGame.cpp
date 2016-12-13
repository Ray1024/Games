#include "PlaneWarGame.h"
#include "PlaneWarMenu.h"
#include "SimpleAudioEngine.h"
#include "PlaneWarSprite.h"

PlaneWarGame::~PlaneWarGame()
{
	_enemys.clear();
	_bullets.clear();
}

PlaneWarGame::PlaneWarGame()
	:_player(NULL)
	,_bulletsDestroyed(0)
	,_score(0)
	,_label(NULL)
	,_pause(NULL)
	,_menu(NULL)
	,_isOver(false)
{
}

Scene* PlaneWarGame::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PlaneWarGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool PlaneWarGame::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! Layer::init());

		_size = Director::getInstance()->getWinSize();

		// 初始化游戏背景
		CC_BREAK_IF(!initBackground());
		// 菜单1（暂停/声音/炸弹）
		CC_BREAK_IF(!initMenu1());
		// 菜单2（继续/重新开始/返回）
		CC_BREAK_IF(!initMenu2());
		// 菜单3（重新开始/返回）
		CC_BREAK_IF(!initMenu3());

		// 创建玩家飞机
		_player = new PlaySprite;
		_player->setPosition(Point::ZERO);
		_player->setGame(this);
		addChild(_player, Z_GAME);

		// 调度器:定时调用自定义的回扫函数
		this->scheduleUpdate();
		this->schedule( schedule_selector(PlaneWarGame::shoot), 0.1f );
		this->schedule( schedule_selector(PlaneWarGame::addEnemy), 0.5f );
		this->schedule( schedule_selector(PlaneWarGame::addProp), 5.f );
		
		// 键盘消息可用
		auto listenerKey = EventListenerKeyboard::create();
		listenerKey->onKeyPressed = CC_CALLBACK_2(PlaneWarGame::onKeyPressed, this);
		listenerKey->onKeyReleased = CC_CALLBACK_2(PlaneWarGame::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);

		// 触摸可用
		auto listenerTouch = EventListenerTouchOneByOne::create();
		listenerTouch->setSwallowTouches(true);
		listenerTouch->onTouchBegan = CC_CALLBACK_2(PlaneWarGame::onTouchBegan, this);
		listenerTouch->onTouchMoved = CC_CALLBACK_2(PlaneWarGame::onTouchMoved, this);
		listenerTouch->onTouchEnded = CC_CALLBACK_2(PlaneWarGame::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

		// 背景音乐
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/game_music.wav", true);

		bRet = true;
	} while (0);

	return bRet;
}

bool PlaneWarGame::initMenu1()
{
	_pause = MenuItemSprite::create(
		Sprite::create("button_pause.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuPauseCallback,this) );
	if(! _pause)return false;
	_pause->setPosition( Point(50, _size.height-50) );

	MenuItemSprite* bombItem = MenuItemSprite::create(
		Sprite::create("bomb.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuBombCallback,this));
	if (!bombItem)return false;
	bombItem->setAnchorPoint(Point(0,0));
	bombItem->setPosition( Point(0, 0) );

	MenuItemSprite* pSoundItem = MenuItemSprite::create(
		Sprite::create("bkmusic_play.png"),
		Sprite::create("bkmusic_close.png"),
		CC_CALLBACK_1(PlaneWarGame::menuSoundCallback,this));
	if(! pSoundItem)return false;
	pSoundItem->setPosition(Point(_size.width-50, _size.height-50));
	pSoundItem->setTag(MENUITEM_SOUND);
	_issound = true;

	_menu = Menu::create(_pause,pSoundItem,bombItem,NULL);
	if(! _menu)return false;
	_menu->setPosition( Point::ZERO );
	this->addChild(_menu, Z_MENU,MENU_1);
	return true;
}

bool PlaneWarGame::initMenu3()
{
	MenuItemSprite* restartItem1 = MenuItemSprite::create(
		Sprite::create("menu_restart.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuRestartCallback,this));
	if(! restartItem1)return false;
	restartItem1->setPosition(Point(0, 0));

	MenuItemSprite* backItem1 = MenuItemSprite::create(
		Sprite::create("menu_back1.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuBackCallback,this));
	if(! backItem1)return false;
	backItem1->setPosition(Point(0, -100));

	Menu* pOverMenu = Menu::create(restartItem1,backItem1,NULL);
	pOverMenu->setPosition(Point(_size.width/2,_size.height/2));
	addChild(pOverMenu,100,MENU_3);
	pOverMenu->setVisible(false);

	Size size = Director::getInstance()->getWinSize();
	// 显示分数的标签
	Label* scoreLabel = Label::createWithSystemFont("1","YouYuan",60);
	if(! scoreLabel)return false;
	scoreLabel->setColor(Color3B(100,100,100));
	scoreLabel->setAnchorPoint(Point(0,0));
	scoreLabel->setPosition(Point(300,385));
	// 菜单背景图
	auto _bg = Sprite::create("menu_bg_over.png");
	MenuItemSprite* bgItem = MenuItemSprite::create(_bg,_bg);
	if(! bgItem)return false;
	bgItem->setPosition(Point(0, 0));
	bgItem->addChild(scoreLabel,100);
	pOverMenu->addChild(bgItem,-1,MENU3_BG);

	return true;
}

bool PlaneWarGame::initMenu2()
{
	auto _bg = Sprite::create("menu_bg_pause.png");
	//_bg->setScaleY(2.0);
	MenuItemSprite* bgItem = MenuItemSprite::create(_bg,_bg);
	if(! bgItem)return false;
	bgItem->setPosition(Point(0, 0));

	MenuItemSprite* resumeItem = MenuItemSprite::create(
		Sprite::create("menu_resume.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuResumeCallback,this));
	if(! resumeItem)return false;
	resumeItem->setPosition(Point(0, 100));

	MenuItemSprite* restartItem = MenuItemSprite::create(
		Sprite::create("menu_restart.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuRestartCallback,this));
	if(! restartItem)return false;
	restartItem->setPosition(Point(0, 0));

	MenuItemSprite* backItem = MenuItemSprite::create(
		Sprite::create("menu_back1.png"),
		NULL,
		CC_CALLBACK_1(PlaneWarGame::menuBackCallback,this));
	if(! backItem)return false;
	backItem->setPosition(Point(0, -100));

	Menu* pPauseMenu = Menu::create(bgItem,resumeItem,restartItem,backItem,NULL);
	if(!pPauseMenu)return false;
	pPauseMenu->setPosition(Point(_size.width/2,_size.height/2));
	addChild(pPauseMenu,100,MENU_2);
	pPauseMenu->setVisible(false);

	return true;
}

bool PlaneWarGame::initBackground()
{
	// 显示分数
	_label = Label::createWithBMFont("font/font.fnt","0123456789");
	_label->setPosition(Point(_size.width/2,_size.height-50));
	_label->setColor(Color3B(0,0,0));
	this->addChild(_label, Z_MENU);

	// 显示炸弹数量
	Label* bombcount = Label::createWithBMFont("font/font.fnt","X09");
	bombcount->setAnchorPoint(Point(0,0));
	bombcount->setPosition(Point(150,30));
	bombcount->setColor(Color3B(0,0,0));
	addChild(bombcount, Z_MENU,LABEL_BOMBCOUNT);

	// 添加背景
	Sprite* bg1 = Sprite::create("bg1.png");
	if (!bg1)return false;
	bg1->setAnchorPoint(Point(0,1));
	bg1->setPosition( Point(0, _size.height) );
	this->addChild(bg1, Z_BG, BACKGROUND_1);

	bg1->runAction(
		Sequence::create(
		MoveBy::create(5,Point(0,-1*_size.height)),
		CallFunc::create(CC_CALLBACK_0(PlaneWarGame::bg1roll,this)),NULL));

	Sprite* bg2 = Sprite::create("bg2.png");
	if (!bg1)return false;
	bg2->setAnchorPoint(Point(0,1));
	bg2->setPosition( Point(0, _size.height*2) );
	this->addChild(bg2, Z_BG, BACKGROUND_2);

	bg2->runAction(
		Sequence::create(
		MoveBy::create(10,Point(0,-1*_size.height*2)),
		CallFunc::create(CC_CALLBACK_0(PlaneWarGame::bg2roll,this)),NULL));
	return true;
}

void PlaneWarGame::bg1roll(){
	//运动出屏幕重设位置，运动
	Sprite * bg = (Sprite *)getChildByTag(BACKGROUND_1);
	bg->setPosition(Point(0,_size.height*2));
	Action* seq = Sequence::create(
		MoveBy::create(10,Point(0,-1*_size.height*2)),
		CallFunc::create(CC_CALLBACK_0(PlaneWarGame::bg1roll,this)),NULL);
	bg->runAction(seq);
}

void PlaneWarGame::bg2roll(){
	//运动出屏幕重设位置，运动
	Sprite * bg = (Sprite *)getChildByTag(BACKGROUND_2);
	bg->setPosition(Point(0,_size.height*2));
	Action* seq = Sequence::create(
		MoveBy::create(10,Point(0,-1*_size.height*2)),
		CallFunc::create(CC_CALLBACK_0(PlaneWarGame::bg2roll,this)),NULL);
	bg->runAction(seq);
}

void PlaneWarGame::menuPauseCallback(Ref* pSender)
{
	Menu* menu = (Menu*)getChildByTag(MENU_2);
	menu->setVisible(true);
	menu->setEnabled(true);

	menu = (Menu*)getChildByTag(MENU_1);
	menu->setEnabled(false);

	CocosDenshion::SimpleAudioEngine::getInstance()->
		pauseBackgroundMusic();
	Director::getInstance()->pause();
}

void PlaneWarGame::menuResumeCallback(Ref* pSender)
{
	Menu* menu = (Menu*)getChildByTag(MENU_2);
	menu->setVisible(false);
	menu->setEnabled(false);

	menu = (Menu*)getChildByTag(MENU_1);
	menu->setEnabled(true);

	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->resume();
}

void PlaneWarGame::menuRestartCallback(Ref* pSender)
{
	Scene* scene = PlaneWarGame::scene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);

	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->resume();
}

void PlaneWarGame::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	CocosDenshion::SimpleAudioEngine::getInstance()->end();
	Director::getInstance()->resume();
}

void PlaneWarGame::menuSoundCallback(Ref* pSender)
{
	MenuItemSprite* soundItem = (MenuItemSprite*)getChildByTag(MENU_1)->getChildByTag(MENUITEM_SOUND);

	auto soundN = Sprite::create("bkmusic_play.png");
	auto soundD = Sprite::create("bkmusic_close.png");

	//设置声音
	if(! _issound){
		soundItem->setNormalImage(soundN);
		soundItem->setDisabledImage(soundD);
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			"music/game_music.wav", true);
		_issound = true;
	}else{
		soundItem->setNormalImage(soundD);
		soundItem->setDisabledImage(soundN);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		_issound = false;
	}
}

void PlaneWarGame::menuBombCallback(Ref* pSender)
{
	if (_player->_bombCount<=0)return;
	
	killAllEnemys();

	CocosDenshion::SimpleAudioEngine::getInstance()->
		playEffect("music/use_bomb.wav",false);
	_player->_bombCount--;
}

void PlaneWarGame::killAllEnemys()
{
	for (int i=0; i<_enemys.size(); ++i)
	{
		EnemySprite* enemy = _enemys.at(i);
		if (enemy!=NULL)
		{
			enemy->die();
			if (!_isOver)
				_bulletsDestroyed++;
		}
	}
}

void PlaneWarGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(_player==NULL) return;

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_player->_mode = MM_LEFT;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_player->_mode = MM_RIGHT;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		_player->_mode = MM_UP;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_player->_mode = MM_DOWN;
		break;
	default:
		break;
	}
}

void PlaneWarGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(_player==NULL) return;
	if (   keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW 
		|| keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW 
		|| keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW
		|| keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		_player->_mode = MM_NONE;
}

void PlaneWarGame::show()
{
	if (_isOver)return;
	// 显示分数
	_score = _bulletsDestroyed*100;
	char str[255] = {0};
	sprintf(str,"%012d",_score);
	_label->setString(str);

	sprintf(str,"X%02d",_player->_bombCount);
	((Label*)getChildByTag(LABEL_BOMBCOUNT))->setString(str);
}

void PlaneWarGame::update(float dt)
{
	releaseEnemys();
	show();
	updateGame(dt);
}

void PlaneWarGame::releaseEnemys()
{
	// 删除无效敌机
	for (int i = 0; i < _enemys.size(); i++)
	{
		EnemySprite* enemy = _enemys.at(i);
		if (enemy!=NULL && enemy->_destroy)
		{
			removeChild(enemy,true);
			_enemys.erase(i);
			enemy = NULL;
			return;
		}
	}
}

void PlaneWarGame::addProp(float dt)
{
	if (_isOver)return;

	int propkind = rand()%2;
	Sprite *prop = NULL;
	if (propkind == 0)
	{
		prop = Sprite::create("ufo1.png");
		prop->setTag(PROP_BULLET);//bullet
	}else if (propkind == 1)
	{
		prop = Sprite::create("ufo2.png");
		prop->setTag(PROP_BOMB);//bomb
	}

	// 计算道具即将放到什么位置(Y坐标固定，X坐标变化)
	float minX = prop->getContentSize().width/2;
	float maxX = _size.width -  prop->getContentSize().width/2;
	int rangeX = (int)(maxX - minX);
	// srand( TimGetTicks() );
	int actualX = ( rand() % rangeX ) + (int)minX;

	// 放置目标精灵
	prop->setPosition( 
		Point(actualX,_size.height+prop->getContentSize().height/2) );
	this->addChild(prop, Z_GAME);

	// 计算目标精灵的速度
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// 添加动作
	ActionInterval*  moveTo = 
		CCMoveTo::create(
		4, Point(actualX, 0 - prop->getContentSize().height/2 ));

	FiniteTimeAction* actionMoveDone = CallFuncN::create( 
		CC_CALLBACK_1(PlaneWarGame::spriteMoveFinished,this));

	prop->runAction( Sequence::create(moveTo, actionMoveDone, NULL) );

	CocosDenshion::SimpleAudioEngine::getInstance()->
		playEffect("music/out_porp.wav",false);
}

void PlaneWarGame::updateGame(float dt)
{
	if(_player==NULL) return;

	Vector<Sprite*>* bulletsToDelete = new Vector<Sprite*>;
	
	Rect playerRect = _player->getRect();
	// 己方飞机和敌方飞机的碰撞
	for (int i=0; i<_enemys.size(); ++i)
	{
		EnemySprite *enemy = _enemys.at(i);
		if (!enemy->isNull() && playerRect.intersectsRect(enemy->getRect()))
		{
			_player->die();
			//gameover(false);
			return;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	Sprite* prop = (Sprite*)getChildByTag(PROP_BULLET);//子弹
	if (NULL != prop)
	{
		Rect propRect = Rect(
			prop->getPosition().x - (prop->getContentSize().width/2),
			prop->getPosition().y - (prop->getContentSize().height/2),
			prop->getContentSize().width,
			prop->getContentSize().height);
		if (playerRect.intersectsRect(propRect))
		{
			_player->_bulletKind = BK_DOUBLE;
			removeChild(prop,true);
			CocosDenshion::SimpleAudioEngine::getInstance()->
				playEffect("music/get_double_laser.wav",false);
		}
	}
	Sprite* prop1 = (Sprite*)getChildByTag(PROP_BOMB);//炸弹
	if (NULL != prop1)
	{
		Rect prop1Rect = Rect(
			prop1->getPosition().x - (prop1->getContentSize().width/2),
			prop1->getPosition().y - (prop1->getContentSize().height/2),
			prop1->getContentSize().width,
			prop1->getContentSize().height);
		if (playerRect.intersectsRect(prop1Rect))
		{
			_player->_bombCount++;
			removeChild(prop1,true);
			CocosDenshion::SimpleAudioEngine::getInstance()->
				playEffect("music/get_bomb.wav",false);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	for (int i=0; i<_bullets.size(); i++)
	{
		Sprite *bullet = _bullets.at(i);
		Rect bulletRect = Rect(
			bullet->getPosition().x - (bullet->getContentSize().width/2),
			bullet->getPosition().y - (bullet->getContentSize().height/2),
			bullet->getContentSize().width,
			bullet->getContentSize().height);

		Vector<EnemySprite*>* enemysToDelete = new Vector<EnemySprite*>;

		// 子弹和地方飞机碰撞检测
		for (int j=0; j<_enemys.size(); ++j)
		{
			EnemySprite *enemy = _enemys.at(j);
			if (!enemy->_die && bulletRect.intersectsRect(enemy->getRect()))
			{
				if (enemy->_hp>0)
				{
					enemy->_hp--;
					bulletsToDelete->pushBack(bullet);
					_bullets.eraseObject(bullet,true);
					removeChild(bullet,true);
				}
				else if (enemy->_hp<=0)
				{
					bulletsToDelete->pushBack(bullet);
					_bullets.eraseObject(bullet,true);
					removeChild(bullet,true);
					enemysToDelete->pushBack(enemy);
				}
			}
		}

		for (int k=0; k<enemysToDelete->size(); ++k)
		{
			EnemySprite *enemy = enemysToDelete->at(k);
			enemy->_die = true;
			enemy->die();
			_bulletsDestroyed++;
		}

		// 如果敌方飞机有死亡的，说明子弹死亡了，要释放
		if (enemysToDelete->size() > 0)
		{
			bulletsToDelete->pushBack(bullet);
		}

		delete enemysToDelete;
	}

	// 释放已死亡的子弹
	while (!bulletsToDelete->empty())
	{
		Sprite* projectile = bulletsToDelete->at(0);
		bulletsToDelete->erase(0);
		this->removeChild(projectile, true);
	}
	delete bulletsToDelete;
}

void PlaneWarGame::addEnemy(float dt)
{
	if	(_isOver)return;

	EnemySprite* enemy = new EnemySprite;
	enemy->setPosition(Point::ZERO);
	addChild(enemy,Z_GAME);
	_enemys.pushBack(enemy);
}

void PlaneWarGame::gameover()
{
	_isOver = true;
	// 释放屏幕内所有游戏对象
	killAllEnemys();

	//暂停背景
	Sprite * bg = (Sprite *)getChildByTag(BACKGROUND_2);
	bg->stopAllActions();
	bg = (Sprite *)getChildByTag(BACKGROUND_1);
	bg->stopAllActions();
	
	CocosDenshion::SimpleAudioEngine::getInstance()->
		playEffect("music/game_over.wav",false);
	CocosDenshion::SimpleAudioEngine::getInstance()->
		pauseBackgroundMusic();

	Menu* menu = (Menu*)getChildByTag(MENU_1);
	menu->setEnabled(false);
	menu = (Menu*)getChildByTag(MENU_3);
	menu->setVisible(true);
	menu->setEnabled(true);

	Label* label = (Label*)((Sprite*)menu->getChildByTag(MENU3_BG))->getChildren().back();
	// 显示分数
	_score = _bulletsDestroyed*100;
	char str[255] = {0};
	sprintf(str,"%d",_score);
	label->setString(str);
}

bool PlaneWarGame::onTouchBegan(Touch *touch, Event *unused_event)
{
	if(_player==NULL) return false;

	Point pt = Director::getInstance()->convertToGL(	touch->getLocationInView());

	Rect rt = _player->getRect();
	if (rt.containsPoint(pt))
		_player->_isDragEnabled = true;
	return true;
}

void PlaneWarGame::onTouchMoved(Touch *touch, Event *unused_event)
{
	if(_player==NULL) return;

	Size size = Director::getInstance()->getWinSize();
	Point pt = Director::getInstance()->convertToGL(touch->getLocationInView());
	
	Rect rt = Rect(0,0,size.width,size.height);

	if (_player->_isDragEnabled && rt.containsPoint(pt))
		_player->setPlayerPt(pt);
}

void PlaneWarGame::onTouchEnded(Touch *touch, Event *unused_event)
{
	_player->_isDragEnabled = false;
}
// 确定子弹类型
void PlaneWarGame::shoot(float dt)
{
	if (_isOver)return;
	if(_player==NULL) return;

	if(_player->_bulletKind == BK_SINGLE)
	{
		Sprite *bullet = Sprite::create("bullet1.png");
		addBullet(bullet,_player->getPlayerPt());
	}else if (_player->_bulletKind == BK_DOUBLE)
	{
		Sprite *bullet = Sprite::create("bullet2.png");
		addBullet(bullet,Point(_player->getPlayerPt().x-20,_player->getPlayerPt().y));

		Sprite *bullet1 = Sprite::create("bullet2.png");
		addBullet(bullet1,Point(_player->getPlayerPt().x+20,_player->getPlayerPt().y));
	}
}
// 添加子弹
void PlaneWarGame::addBullet(Sprite* bullet, Point pt)
{	
	if (!bullet) return;

	bullet->setPosition(pt);
	this->addChild(bullet, Z_GAME);

	bullet->runAction( Sequence::create(
		CCMoveTo::create(0.5, Point(pt.x,_size.height+bullet->getContentSize().height/2)),
		CallFuncN::create(CC_CALLBACK_1(PlaneWarGame::spriteMoveFinished,this)), 
		NULL) );

	bullet->setTag(SPRITE_BULLET);
	_bullets.pushBack(bullet);
}
// 回收
void PlaneWarGame::spriteMoveFinished(Node* sender)
{
	Sprite *sprite = (Sprite *)sender;
	this->removeChild(sprite, true);
	if (sprite->getTag()==SPRITE_BULLET)//子弹
		_bullets.eraseObject(sprite, true);
}