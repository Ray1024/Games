#ifndef __FAPAIQI_H__
#define __FAPAIQI_H__

#include "cocos2d.h"
#include "Poker.h"

//---------------------------------------------
// ·¢ÅÆÆ÷
//---------------------------------------------
class FaPaiQi
{
public:

	static FaPaiQi* getInstance();
	static void destroyInstance();

    virtual bool init();

	virtual void faPai();

protected:

	std::vector<PokerInfo> _pokerInfo;
};

#endif // __FAPAIQI_H__
