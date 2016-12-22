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

	_pokerCounts = Label::createWithSystemFont("0", "宋体", 150);
	_pokerCounts->setPosition(70,110);
	back->addChild(_pokerCounts,1);

    return true;
}

bool ICardManager::dealer(CardInfo info)
{
	_pokersIndex.push_back(info);

	updateCards();

	return true;
}

void ICardManager::updateCards()
{
	std::stringstream text;
	text << _pokersIndex.size();
	_pokerCounts->setString(text.str());
}

void ICardManager::chuPai()
{
	if (_pokersIndex.empty())
	{
		return ;
	}

	std::vector<CardInfo> arrayIndexToChuPai;
	arrayIndexToChuPai.push_back(_pokersIndex.back());
	_pokersIndex.pop_back();

	_exhibitionZone->chuPai(arrayIndexToChuPai);

	updateCards();
}