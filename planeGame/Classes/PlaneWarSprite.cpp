#include "PlaneWarSprite.h"

PlaySprite::PlaySprite()
	:_sprite(NULL)
	,_mode(MM_NONE)
	,_isDragEnabled(false)
	,_bulletKind(BK_SINGLE)
	,_bombCount(0)
{

}
PlaySprite::~PlaySprite()
{
	_game->release();
}

void PlaySprite::onEnter()
{
	Node::onEnter();

	Size size = Director::getInstance()->getWinSize();
	_sprite = Sprite::create("hero1.png");
	_sprite->setContentSize(Size(62,68));
	_sprite->setPosition( Point(size.width/2,_sprite->getContentSize().height*4) );
	addChild(_sprite,PlaneWarGame::Z_GAME);

	Animation * animation = Animation::create();
	animation->addSpriteFrameWithFile("hero1.png");
	animation->addSpriteFrameWithFile("hero2.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(false);
	Action* action = RepeatForever::create(
		Animate::create(animation));
	action->setTag(ACTION_1);
	_sprite->runAction(action);

	// 调度器
	schedule( schedule_selector(PlaySprite::move), 0.002f );
}

Rect PlaySprite::getRect()
{
	if (_sprite!=NULL)
		return Rect(
		_sprite->getPosition().x - (_sprite->getContentSize().width/2),
		_sprite->getPosition().y - (_sprite->getContentSize().height/2),
		_sprite->getContentSize().width,
		_sprite->getContentSize().height);
}	

Point PlaySprite::getPlayerPt()
{
	if (_sprite!=NULL)
		return _sprite->getPosition();
}

void PlaySprite::setPlayerPt(Point pt)
{
	if (_sprite!=NULL)
		_sprite->setPosition(pt);
}

void PlaySprite::move(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	switch(_mode)
	{
	case MM_NONE:
		break;
	case MM_UP:
		if (getPlayerPt().y<winSize.height)
			setPlayerPt(Point(getPlayerPt().x,getPlayerPt().y+2));
		break;
	case MM_DOWN:
		if (getPlayerPt().y>0)
			setPlayerPt(Point(getPlayerPt().x,getPlayerPt().y-2));
		break;
	case MM_LEFT:
		if (getPlayerPt().x>0)
			setPlayerPt(Point(getPlayerPt().x-2,getPlayerPt().y));
		break;
	case  MM_RIGHT:
		if (getPlayerPt().x<winSize.width)
			setPlayerPt(Point(getPlayerPt().x+2,getPlayerPt().y));
		break;
	}
}

void PlaySprite::die()
{
	if (_sprite==NULL)return;

	_sprite->stopActionByTag(ACTION_1);
	Animation * animation = Animation::create();
	animation->addSpriteFrameWithFile("hero_blowup_n1.png");
	animation->addSpriteFrameWithFile("hero_blowup_n2.png");
	animation->addSpriteFrameWithFile("hero_blowup_n3.png");
	animation->addSpriteFrameWithFile("hero_blowup_n4.png");
	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(false);
	_sprite->runAction(Sequence::create(
		Animate::create(animation),
		CallFunc::create(CC_CALLBACK_0(PlaySprite::destroy,this)),
		CallFunc::create(CC_CALLBACK_0(PlaneWarGame::gameover, _game)),
		NULL));
}

void PlaySprite::destroy()
{
	if (_sprite==NULL)return;
	
	removeChild(_sprite,true);
	_sprite = NULL;
}

//////////////////////////////////////////////////////////////////////////

EnemySprite::EnemySprite()
	:_hp(0)
	,_enemyKind(EK_SMALL)
	,_die(false)
	,_destroy(false)
{

}

EnemySprite::~EnemySprite()
{

}

void EnemySprite::onEnter()
{
	Node::onEnter();

	Size size = Director::getInstance()->getWinSize();

	int i = rand()%20;
	if (i<13)
	{
		_enemyKind = EK_SMALL;
		_hp = 1;
		_sprite = Sprite::create("enemy1.png");
	}else if (i<18)
	{
		_enemyKind = EK_MIDDLE;
		_hp = 4;
		_sprite = Sprite::create("enemy2.png");
	}else if(i<20)
	{
		_enemyKind = EK_BIG;
		_hp = 20;
		_sprite = Sprite::create("enemy3_n1.png");
	}

	// 计算目标精灵即将放到什么位置(Y坐标固定，X坐标变化)
	float minX = _sprite->getContentSize().width/2;
	float maxX = size.width -  _sprite->getContentSize().width/2;
	int rangeX = (int)(maxX - minX);
	// srand( TimGetTicks() );
	int actualX = ( rand() % rangeX ) + (int)minX;

	// 放置目标精灵
	_sprite->setPosition( 
		Point(actualX,size.height+_sprite->getContentSize().height/2) );
	this->addChild(_sprite, PlaneWarGame::Z_GAME);

	// 计算目标精灵的速度
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// 添加动作
	ActionInterval*  moveTo = 
		CCMoveTo::create(4, Point(actualX, 0 - _sprite->getContentSize().height/2 ));

	FiniteTimeAction* actionMoveDone = CallFuncN::create( 
		CC_CALLBACK_1(EnemySprite::spriteMoveFinished,this));

	_sprite->runAction( Sequence::create(moveTo, actionMoveDone, NULL) );

}

bool EnemySprite::isNull()
{
	return _sprite==NULL;
}

Rect EnemySprite::getRect()
{
	if (_sprite!=NULL)
		return Rect(
		_sprite->getPosition().x - (_sprite->getContentSize().width/2),
		_sprite->getPosition().y - (_sprite->getContentSize().height/2),
		_sprite->getContentSize().width,
		_sprite->getContentSize().height);
}

void EnemySprite::spriteMoveFinished(Node* sender)
{// 在回扫中检查
	removeChild(_sprite,true);
	_sprite = NULL;
	_die = true;
	_destroy = true;
}

void EnemySprite::destroy()
{
	if (_sprite==NULL)return;

	removeChild(_sprite,true);
	_sprite = NULL;
	_destroy = true;
}

void EnemySprite::die()
{
	if (_sprite==NULL)return;

	_sprite->stopAllActions();
	Animation * animation = Animation::create();
	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(false);
	if (_enemyKind==EK_SMALL)
	{
		animation->addSpriteFrameWithFile("enemy1_down1.png");
		animation->addSpriteFrameWithFile("enemy1_down2.png");
		animation->addSpriteFrameWithFile("enemy1_down3.png");
		animation->addSpriteFrameWithFile("enemy1_down4.png");
	}else if (_enemyKind==EK_MIDDLE)
	{
		animation->addSpriteFrameWithFile("enemy2_down1.png");
		animation->addSpriteFrameWithFile("enemy2_down2.png");
		animation->addSpriteFrameWithFile("enemy2_down3.png");
		animation->addSpriteFrameWithFile("enemy2_down4.png");
	}else if (_enemyKind==EK_BIG)
	{
		animation->addSpriteFrameWithFile("enemy3_down1.png");
		animation->addSpriteFrameWithFile("enemy3_down2.png");
		animation->addSpriteFrameWithFile("enemy3_down3.png");
		animation->addSpriteFrameWithFile("enemy3_down4.png");
		animation->addSpriteFrameWithFile("enemy3_down5.png");
		animation->addSpriteFrameWithFile("enemy3_down6.png");
	}
	_sprite->runAction(Sequence::create(
		Animate::create(animation),
		CallFunc::create(CC_CALLBACK_0(EnemySprite::destroy,this)),
		NULL));
}