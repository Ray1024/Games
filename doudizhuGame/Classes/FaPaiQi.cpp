#include "FaPaiQi.h"

USING_NS_CC;

static FaPaiQi *s_SharedFaPaiQi = nullptr;

FaPaiQi* FaPaiQi::getInstance()
{
	if (!s_SharedFaPaiQi)
	{
		s_SharedFaPaiQi = new (std::nothrow) FaPaiQi();
		s_SharedFaPaiQi->init();
	}

	return s_SharedFaPaiQi;
}

void FaPaiQi::destroyInstance()
{
	if (s_SharedFaPaiQi)
	{
		delete s_SharedFaPaiQi;
		s_SharedFaPaiQi = NULL;
	}
}

bool FaPaiQi::init()
{
	for (int i=0; i<13; i++)
	{
		for (int j=0; j<4; j++)
		{
			PokerInfo info;
			info._num = (PokerNum)i;
			info._tag = (PokerTag)j;
			_pokerInfo.push_back(info);
		}
	}

	PokerInfo info;
	info._num = (PokerNum)13;
	info._tag = (PokerTag)0;
	_pokerInfo.push_back(info);
	info._num = (PokerNum)14;
	_pokerInfo.push_back(info);

    return true;
}

void FaPaiQi::faPai()
{
	std::random_shuffle(_pokerInfo.begin(), _pokerInfo.end());

	for (int i=0; i<_pokerInfo.size(); i++)
	{
		PokerInfo info = _pokerInfo.at(i);
// 		if ()
// 		{
// 		}
	}
}