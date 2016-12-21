#include "IPokerManager.h"
#include "Poker.h"
#include <algorithm>

USING_NS_CC;

IPokerManager* IPokerManager::create()
{
	IPokerManager *sprite = new (std::nothrow) IPokerManager();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool IPokerManager::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

	_exhibitionZone = PokerExhibitionZone::create();
	_exhibitionZone->setPosition(0, -100);
	this->addChild(_exhibitionZone);

	auto back = Sprite::createWithSpriteFrameName("b/poker_back.png");
	back->setScale(0.3);
	this->addChild(back,1);

	_pokerCounts = Label::createWithSystemFont("0", "宋体", 150);
	_pokerCounts->setPosition(50,90);
	back->addChild(_pokerCounts,1);

    return true;
}

bool IPokerManager::dealer(PokerInfo info)
{
	_pokersIndex.push_back(info);

	updatePokers();

	return true;
}

void IPokerManager::updatePokers()
{
	std::stringstream text;
	text << _pokersIndex.size();
	_pokerCounts->setString(text.str());
}

void IPokerManager::chuPai()
{
	if (_pokersIndex.empty())
	{
		return ;
	}

	std::vector<PokerInfo> arrayIndexToChuPai;
	arrayIndexToChuPai.push_back(_pokersIndex.back());
	_pokersIndex.pop_back();

	_exhibitionZone->chuPai(arrayIndexToChuPai);

	updatePokers();
}