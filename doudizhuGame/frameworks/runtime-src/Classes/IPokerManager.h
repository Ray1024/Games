#ifndef __I_POKER_MANAGER_H__
#define __I_POKER_MANAGER_H__

#include "cocos2d.h"
#include "PokerExhibitionZone.h"

class IPokerManager : public cocos2d::Sprite
{

public:

	static IPokerManager* create();

    virtual bool init();

	virtual bool dealer();

	virtual void chuPai();

protected:

	PokerExhibitionZone* _exhibitionZone;

	std::vector<int> _pokersIndex;
};

#endif // __I_POKER_MANAGER_H__
