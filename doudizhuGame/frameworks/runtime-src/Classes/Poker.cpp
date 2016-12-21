#include "Poker.h"

USING_NS_CC;

Poker* Poker::create(int pokerIndex)
{
	Poker *sprite = new (std::nothrow) Poker();
	if (sprite && sprite->init(pokerIndex))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Poker::init(int pokerIndex)
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

	_typeIndex = (Poker::Type)pokerIndex;

	// 根据类型获取行列索引

	int line, row;

	if (_typeIndex == Poker::Type::DW)
	{
		line = 0;
		row = 13;
	} 
	else if (_typeIndex == Poker::Type::XW)
	{
		line = 1;
		row = 13;
	}
	else 
	{
		line = _typeIndex/13;
		row = _typeIndex%13;
	}

	// 牌面
	_front = Sprite::create("poker.png", Rect(105 * row, 142 * line,POKER_W,POKER_H));
	this->addChild(_front);

	_isSelected = false;

	// 触摸事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(Poker::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Poker::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Poker::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Poker::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

Rect Poker::getRect()
{
// 	auto s = _front->getTexture()->getContentSize();
// 	return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
	return Rect(-95 / 2, -130 / 2, 95, 130);
}

bool Poker::onTouchBegan(Touch* touch, Event* event)
{
	if (getRect().containsPoint(convertTouchToNodeSpaceAR(touch)))
	{
		click();

		return true;
	}

	return false;
}

void Poker::onTouchEnded(Touch* touch, Event* event)
{

}

void Poker::onTouchCancelled(Touch* touch, Event* event)
{

}

void Poker::onTouchMoved(Touch* touch, Event* event)
{

}

void Poker::click()
{
	if (_isSelected)
	{
		setPosition(_position.x,_position.y -10);
	} else
	{
		setPosition(_position.x,_position.y +10);
	}
	_isSelected = !_isSelected;
}