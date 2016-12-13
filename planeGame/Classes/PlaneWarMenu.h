#include "cocos2d.h"
USING_NS_CC;

// 游戏菜单界面类
class PlaneWarMenu: public Layer
{
public:
	virtual bool init();  
	static cocos2d::Scene* scene();

	virtual void menuStartCallback(Ref* pSender);
	virtual void menuManualCallback(Ref* pSender);
	virtual void menuAboutCallback(Ref* pSender);
	virtual void menuBackCallback(Ref* pSender);

	CREATE_FUNC(PlaneWarMenu);
};