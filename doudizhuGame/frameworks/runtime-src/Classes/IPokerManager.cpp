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
	//_exhibitionZone->setPosition(50, 250);
	this->addChild(_exhibitionZone, 1);

    return true;
}

bool IPokerManager::dealer()
{
	if (_children.size()>=17)
	{
		return false;
	}

	int index;
	while (1)
	{
		index = rand()%54;
		auto iter = std::find(_pokersIndex.begin(), _pokersIndex.end(), index);
		if (_pokersIndex.size()==0)
		{
			break;
		} else if (iter == _pokersIndex.end()) //原先不存在
		{
			break;
		}
	}
	_pokersIndex.push_back(index);

	return true;
}

void IPokerManager::chuPai()
{
	std::vector<int> arrayIndexToChuPai;
	arrayIndexToChuPai.push_back(_pokersIndex.back());
	_pokersIndex.pop_back();

	_exhibitionZone->chuPai(arrayIndexToChuPai);
}