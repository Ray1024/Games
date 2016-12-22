#ifndef __I_POKER_MANAGER_H__
#define __I_POKER_MANAGER_H__

#include "cocos2d.h"
#include "CardExhibitionZone.h"

class ICardManager : public cocos2d::Sprite
{

public:

	static ICardManager* create();

    virtual bool init();

	virtual bool dealer(CardInfo info);

	virtual void updateCards();

	virtual void chuPai();

protected:

	CardExhibitionZone* _exhibitionZone;

	std::vector<CardInfo> _pokersIndex;

	cocos2d::Label*	_pokerCounts;
};

#endif // __I_POKER_MANAGER_H__
