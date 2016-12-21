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
	if (_pokersIndex.size()>=17)
	{
		return false;
	}

	PokerInfo info;
	while (1)
	{
		info._num = (PokerNum)(rand()%15);
		info._tag = (PokerTag)(rand()%4);
		auto iter = std::find(_pokersIndex.begin(), _pokersIndex.end(), info);
		if (_pokersIndex.size()==0)
		{
			break;
		} else if (iter == _pokersIndex.end()) //原先不存在
		{
			break;
		}
	}
	_pokersIndex.push_back(info);

	//添加精灵
	auto block = Poker::create(info);
	this->addChild(block, 100-info._num);
	block->setScale(0.8);

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
			poker->setPosition((i-zeroPoint)*50, poker->getPosition().y);
		}
	}
}

void PokerManager::chuPai()
{
	if (_pokersIndex.empty())
	{
		return ;
	}

	std::vector<PokerInfo> arrayIndexToChuPai;
	for (auto it=_children.begin(); it!=_children.end(); it++)
	{
		Poker* poker = dynamic_cast<Poker*>(*it);
		if (poker != NULL && poker->isSelected())
		{
			arrayIndexToChuPai.push_back(poker->getInfo());
		}
	}

	for (int j=0; j<arrayIndexToChuPai.size(); j++)
	{
		for (auto it=_children.begin(); it!=_children.end(); it++)
		{
			Poker* poker = dynamic_cast<Poker*>(*it);
			if (poker != NULL && 
				poker->getInfo() == arrayIndexToChuPai.at(j))
			{
				removeChild(poker, true);
				_pokersIndex.erase(
					std::remove(_pokersIndex.begin(),_pokersIndex.end(),poker->getInfo()),_pokersIndex.end());
				break;
			}
		}
	}

	_exhibitionZone->chuPai(arrayIndexToChuPai);

	updatePokers();
}