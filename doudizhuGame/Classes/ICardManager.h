#ifndef __I_CARD_MANAGER_H__
#define __I_CARD_MANAGER_H__

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

	std::vector<CardInfo> _cardIndex;

	cocos2d::Label*	_cardCounts;
};

#endif // __I_CARD_MANAGER_H__
