#ifndef __POKER_EXHIBITION_ZONE_H__
#define __POKER_EXHIBITION_ZONE_H__

#include "cocos2d.h"

class PokerExhibitionZone : public cocos2d::Sprite
{

public:

	static PokerExhibitionZone* create();

    virtual bool init();

	void chuPai(std::vector<int> arrayIndexs);
};

#endif // __POKER_EXHIBITION_ZONE_H__
