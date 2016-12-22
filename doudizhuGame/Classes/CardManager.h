#ifndef __CARD_MANAGER_H__
#define __CARD_MANAGER_H__

#include "cocos2d.h"
#include "CardExhibitionZone.h"

class CardManager : public cocos2d::Sprite
{

public:

	static CardManager* create();

    virtual bool init();

	bool dealer(CardInfo info);

	void updateCards();

	void chuPai();

protected:

	CardExhibitionZone* _exhibitionZone;

	std::vector<CardInfo> _cardIndex;
};

#endif // __CARD_MANAGER_H__
