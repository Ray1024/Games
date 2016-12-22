#include "BottomCardZone.h"

USING_NS_CC;

BottomCardZone* BottomCardZone::create()
{
	BottomCardZone *sprite = new (std::nothrow) BottomCardZone();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool BottomCardZone::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

	setScale(0.5);

	auto bg = Sprite::create("bottomCardZone.png");
	this->addChild(bg);

    return true;
}

void BottomCardZone::Show(CardInfo pokerInfo)
{
	//removeAllChildrenWithCleanup(true);

	//添加精灵
	auto card = Card::create(pokerInfo);
	card->setScale(0.6);
	this->addChild(card, 100-pokerInfo._num);

	sortAllChildren();

	int count = _children.size();
	int zeroPoint = count/2;
	for (int i=0; i<_children.size(); i++)
	{
		Card* card = dynamic_cast<Card*>(_children.at(i));
		if (card != NULL)
		{
			card->setPosition((i-zeroPoint)*100, 0);
		}
	}
}