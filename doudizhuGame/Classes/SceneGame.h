#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "cocos2d.h"
#include "AppCommon.h"
#include "IPokerManager.h"
#include "PokerManager.h"

//---------------------------------------------
// 游戏场景
//---------------------------------------------
class SceneGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // 菜单回调
    void menuBackCallback(cocos2d::Ref* pSender);
	void menuZhunbeiCallback(cocos2d::Ref* pSender);
	void menuTishiCallback(cocos2d::Ref* pSender);
	void menuChongxuanCallback(cocos2d::Ref* pSender);
	void menuBuchuCallback(cocos2d::Ref* pSender);
	void menuChuPaiCallback(cocos2d::Ref* pSender);
    
	void initPokers();
	virtual void faPai();

    CREATE_FUNC(SceneGame);

protected:

	cocos2d::Menu* _menuZhunbei;
	cocos2d::Menu* _menuGame;

	PokerManager* _pokerManager1;
	IPokerManager* _pokerManager2;
	IPokerManager* _pokerManager3;

	std::vector<PokerInfo> _pokerInfo;
};

#endif // __SCENE_GAME_H__
