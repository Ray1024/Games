#include "Card.h"

USING_NS_CC;

std::vector<CardInfo> g_pokerInfo;

Card* Card::create(CardInfo info)
{
	Card *sprite = new (std::nothrow) Card();
	if (sprite && sprite->init(info))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Card::init(CardInfo info)
{
	// 初始化基类--------------------------------------------------------------
	if ( !Sprite::init() )
	{
		return false;
	}

	_info = info;

	auto cardFront = Sprite::createWithSpriteFrameName("b/bg.png");
	this->addChild(cardFront);
	_size = cardFront->getContentSize();

	if (_info._num == CardNum::NUM_DW)
	{
		auto cardNum = Sprite::createWithSpriteFrameName("b/smalltag_4.png");
		cardNum->setPosition(-50,10);
		this->addChild(cardNum);

		auto cardTag = Sprite::createWithSpriteFrameName("b/bigtag_6.png");
		cardTag->setPosition(20,-30);
		this->addChild(cardTag);
	} 
	else if (_info._num == CardNum::NUM_XW)
	{
		auto cardNum = Sprite::createWithSpriteFrameName("b/smalltag_5.png");
		cardNum->setPosition(-50,10);
		this->addChild(cardNum);

		auto cardTag = Sprite::createWithSpriteFrameName("b/bigtag_6.png");
		cardTag->setPosition(20,-30);
		this->addChild(cardTag);
	}
	else 
	{
		std::stringstream strNum;
		strNum << "b/black_" << _info._num << ".png";
		auto cardNum = Sprite::createWithSpriteFrameName(strNum.str());
		cardNum->setPosition(-50,70);
		this->addChild(cardNum);

		std::stringstream strTag;
		strTag << "b/bigtag_" << _info._tag << ".png";
		auto cardSmallTag = Sprite::createWithSpriteFrameName(strTag.str());
		cardSmallTag->setScale(0.5);
		cardSmallTag->setPosition(-50,20);
		this->addChild(cardSmallTag);

		auto cardTag = Sprite::createWithSpriteFrameName(strTag.str());
		cardTag->setPosition(20,-30);
		this->addChild(cardTag);
	}

	_isSelected = false;

	return true;
}

void Card::SetTouchEnabled()
{
	// 触摸事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Card::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

Rect Card::getRect()
{
	return Rect(-_size.width / 2, -_size.height / 2, _size.width, _size.height);
}

bool Card::onTouchBegan(Touch* touch, Event* event)
{
	if (getRect().containsPoint(convertTouchToNodeSpaceAR(touch)))
	{
		click();

		return true;
	}

	return false;
}

void Card::onTouchEnded(Touch* touch, Event* event)
{

}

void Card::onTouchCancelled(Touch* touch, Event* event)
{

}

void Card::onTouchMoved(Touch* touch, Event* event)
{

}

void Card::click()
{
	if (_isSelected)
	{
		setPosition(_position.x,_position.y -20);
	} else
	{
		setPosition(_position.x,_position.y +20);
	}
	_isSelected = !_isSelected;
}