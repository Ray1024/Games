#include "cocos2d.h"
USING_NS_CC;

// ”Œœ∑ΩÈ…‹¿‡
class PlaneWarInfoboard: public Layer
{
public:
	virtual bool init();  
	static cocos2d::Scene* scene();

	virtual void menuBackCallback(Ref* pSender);

	CREATE_FUNC(PlaneWarInfoboard);
};