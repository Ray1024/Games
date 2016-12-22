#include "ICardManager.h"
#include "Card.h"
#include <algorithm>

USING_NS_CC;

ICardManager* ICardManager::create()
{
	ICardManager *sprite = new (std::nothrow) ICardManager();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool ICardManager::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

	_exhibitionZone = CardExhibitionZone::create();
	_exhibitionZone->setPosition(0, -120);
	this->addChild(_exhibitionZone);

	auto back = Sprite::createWithSpriteFrameName("b/poker_back.png");
	back->setScale(0.3);
	this->addChild(back,1);

	_cardCounts = Label::createWithSystemFont("0", "宋体", 150);
	_cardCounts->setPosition(70,110);
	back->addChild(_cardCounts,1);

    return true;
}

bool ICardManager::dealer(CardInfo info)
{
	_cardIndex.push_back(info);

	updateCards();

	return true;
}

void ICardManager::updateCards()
{
	std::stringstream text;
	text << _cardIndex.size();
	_cardCounts->setString(text.str());
}

void ICardManager::chuPai()
{
	if (_cardIndex.empty())
	{
		return ;
	}

	std::vector<CardInfo> arrayIndexToChuPai;
	arrayIndexToChuPai.push_back(_cardIndex.back());
	_cardIndex.pop_back();

	_exhibitionZone->chuPai(arrayIndexToChuPai);

	updateCards();
}