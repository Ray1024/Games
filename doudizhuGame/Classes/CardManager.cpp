#include "CardManager.h"
#include "Card.h"
#include <algorithm>

USING_NS_CC;

CardManager* CardManager::create()
{
	CardManager *sprite = new (std::nothrow) CardManager();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool CardManager::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

	_exhibitionZone = CardExhibitionZone::create();
	_exhibitionZone->setPosition(50, 250);
	this->addChild(_exhibitionZone, 1);

    return true;
}

bool CardManager::dealer(CardInfo info)
{
	_pokersIndex.push_back(info);

	//添加精灵
	auto card = Card::create(info);
	this->addChild(card, 100-info._num);
	card->SetTouchEnabled();
	card->setScale(0.8);

	sortAllChildren();

	updateCards();

	return true;
}

void CardManager::updateCards()
{
	int count = _children.size();
	int zeroPoint = count/2;
	for (int i=0; i<_children.size(); i++)
	{
		Card* card = dynamic_cast<Card*>(_children.at(i));
		if (card != NULL)
		{
			card->setPosition((i-zeroPoint)*50, card->getPosition().y);
		}
	}
}

void CardManager::chuPai()
{
	if (_pokersIndex.empty())
	{
		return ;
	}

	std::vector<CardInfo> arrayIndexToChuPai;
	for (auto it=_children.begin(); it!=_children.end(); it++)
	{
		Card* card = dynamic_cast<Card*>(*it);
		if (card != NULL && card->isSelected())
		{
			arrayIndexToChuPai.push_back(card->getInfo());
		}
	}

	for (int j=0; j<arrayIndexToChuPai.size(); j++)
	{
		for (auto it=_children.begin(); it!=_children.end(); it++)
		{
			Card* card = dynamic_cast<Card*>(*it);
			if (card != NULL && 
				card->getInfo() == arrayIndexToChuPai.at(j))
			{
				removeChild(card, true);
				_pokersIndex.erase(
					std::remove(_pokersIndex.begin(),_pokersIndex.end(),card->getInfo()),_pokersIndex.end());
				break;
			}
		}
	}

	_exhibitionZone->chuPai(arrayIndexToChuPai);

	updateCards();
}