#include "PokerManager.h"
#include "Poker.h"
#include <algorithm>

USING_NS_CC;

PokerManager* PokerManager::create()
{
	PokerManager *sprite = new (std::nothrow) PokerManager();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool PokerManager::init()
{
	// 初始化基类--------------------------------------------------------------
    if ( !Sprite::init() )
    {
        return false;
    }

	_exhibitionZone = PokerExhibitionZone::create();
	_exhibitionZone->setPosition(50, 250);
	this->addChild(_exhibitionZone, 1);

    return true;
}

bool PokerManager::dealer()
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

	//添加精灵
	auto block = Poker::create(index);
	this->addChild(block, 100-(index%13));

	sortAllChildren();

	updatePokers();

	return true;
}

void PokerManager::updatePokers()
{
	int count = _children.size();
	int zeroPoint = count/2;
	for (int i=0; i<_children.size(); i++)
	{
		Poker* poker = dynamic_cast<Poker*>(_children.at(i));
		if (poker != NULL)
		{
			poker->setPosition((i-zeroPoint)*30, poker->getPosition().y);
		}
	}
}

void PokerManager::chuPai()
{
	std::vector<int> arrayIndexToChuPai;
	for (auto it=_children.begin(); it!=_children.end(); it++)
	{
		Poker* poker = dynamic_cast<Poker*>(*it);
		if (poker != NULL && poker->isSelected())
		{
			arrayIndexToChuPai.push_back(poker->getTypeIndex());
		}
	}

	for (int j=0; j<arrayIndexToChuPai.size(); j++)
	{
		for (auto it=_children.begin(); it!=_children.end(); it++)
		{
			Poker* poker = dynamic_cast<Poker*>(*it);
			if (poker != NULL && poker->getTypeIndex()==arrayIndexToChuPai.at(j))
			{
				removeChild(poker, true);
				_pokersIndex.erase(
					std::remove(_pokersIndex.begin(),_pokersIndex.end(),poker->getTypeIndex()),_pokersIndex.end());
				break;
			}
		}
	}

	_exhibitionZone->chuPai(arrayIndexToChuPai);

	updatePokers();
}