#include "PokerExhibitionZone.h"
#include "Poker.h"
#include <algorithm>

USING_NS_CC;

PokerExhibitionZone* PokerExhibitionZone::create()
{
	PokerExhibitionZone *sprite = new (std::nothrow) PokerExhibitionZone();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool PokerExhibitionZone::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

    return true;
}

void PokerExhibitionZone::chuPai(std::vector<int> arrayIndexs)
{
	removeAllChildrenWithCleanup(true);

	//添加精灵
	for (int i=0; i<arrayIndexs.size(); ++i)
	{
		auto poker = Poker::create(arrayIndexs.at(i));
		poker->setScale(0.6);
		this->addChild(poker, 100-(arrayIndexs.at(i)%13));
	}

	sortAllChildren();

	int count = _children.size();
	int zeroPoint = count/2;
	for (int i=0; i<_children.size(); i++)
	{
		Poker* poker = dynamic_cast<Poker*>(_children.at(i));
		if (poker != NULL)
		{
			poker->setPosition((i-zeroPoint)*15, 0);
		}
	}
}