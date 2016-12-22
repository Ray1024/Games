#ifndef __POKER_H__
#define __POKER_H__

#include "cocos2d.h"

enum CardNum // ÅÆÖµ
{
	NUM_1 = 0,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_10,
	NUM_J,
	NUM_Q,
	NUM_K,
	NUM_XW,
	NUM_DW
};

enum CardTag // »¨É«
{
	FANGKUAI = 0,
	MEIHUA,
	HONGTAO ,
	HEITAO
};

struct CardInfo
{
	CardNum _num;
	CardTag _tag;

	inline bool operator==(const CardInfo &pi) const
	{
		if (_num>=13)
		{
			if (this->_num==pi._num)
				return true;
		}else
		{
			if (this->_num==pi._num &&
				this->_tag==pi._tag)
				return true;
		}

		return false;
	}
};

class Card : public cocos2d::Sprite
{
public:

	static Card* create(CardInfo info);

	virtual bool init(CardInfo info);

	void SetTouchEnabled();

	bool isSelected() { return _isSelected; };
	void click();

	CardInfo getInfo() { return _info; };

	cocos2d::Rect getRect();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

protected:

	bool		_isSelected;

	CardInfo	_info;

	cocos2d::Size _size;
};

#endif // __POKER_H__
