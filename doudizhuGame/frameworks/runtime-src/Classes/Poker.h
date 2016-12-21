#ifndef __POKER_H__
#define __POKER_H__

#include "cocos2d.h"

USING_NS_CC;

#define POKER_W 95
#define POKER_H 130

class Poker : public cocos2d::Sprite
{
	enum Type
	{
		HONG1 = 0,	//红桃
		HONG2,
		HONG3,
		HONG4,
		HONG5,
		HONG6,
		HONG7,
		HONG8,
		HONG9,
		HONG10,
		HONG11,
		HONG12,
		HONG13,

		HEI1,		//黑桃
		HEI2,
		HEI3,
		HEI4,
		HEI5,
		HEI6,
		HEI7,
		HEI8,
		HEI9,
		HEI10,
		HEI11,
		HEI12,
		HEI13,

		FANG1,		//方片
		FANG2,
		FANG3,
		FANG4,
		FANG5,
		FANG6,
		FANG7,
		FANG8,
		FANG9,
		FANG10,
		FANG11,
		FANG12,
		FANG13,

		MEI1,		//梅花
		MEI2,
		MEI3,
		MEI4,
		MEI5,
		MEI6,
		MEI7,
		MEI8,
		MEI9,
		MEI10,
		MEI11,
		MEI12,
		MEI13,

		DW,	//大王
		XW	//小王
	};

public:

	static Poker* create(int pokerIndex);

    virtual bool init(int pokerIndex);

	bool isSelected() { return _isSelected; }
	void click();

	int getTypeIndex() { return (int)_typeIndex; }

	Rect getRect();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

protected:
	Sprite*	_front;
	Type		_typeIndex;
	bool		_isSelected;
};

#endif // __POKER_H__
