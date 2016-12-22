#include "CardExhibitionZone.h"
#include <algorithm>

USING_NS_CC;

CardExhibitionZone* CardExhibitionZone::create()
{
	CardExhibitionZone *sprite = new (std::nothrow) CardExhibitionZone();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool CardExhibitionZone::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

    return true;
}

void CardExhibitionZone::chuPai(std::vector<CardInfo> arrayIndexs)
{
	removeAllChildrenWithCleanup(true);

	//添加精灵
	for (int i=0; i<arrayIndexs.size(); ++i)
	{
		auto card = Card::create(arrayIndexs.at(i));
		card->setScale(0.5);
		this->addChild(card, 100-arrayIndexs.at(i)._num);
	}

	sortAllChildren();

	int count = _children.size();
	int zeroPoint = count/2;
	for (int i=0; i<_children.size(); i++)
	{
		Card* card = dynamic_cast<Card*>(_children.at(i));
		if (card != NULL)
		{
			card->setPosition((i-zeroPoint)*30, 0);
		}
	}
}