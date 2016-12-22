#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "cocos2d.h"
#include "AppCommon.h"
#include "ICardManager.h"
#include "CardManager.h"
#include "BottomCardZone.h"

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
    
	void initCards();
	virtual void faPai();

    CREATE_FUNC(SceneGame);

protected:

	cocos2d::Menu* _menuZhunbei;
	cocos2d::Menu* _menuGame;

	CardManager* _cardManager1;
	ICardManager* _cardManager2;
	ICardManager* _cardManager3;
	BottomCardZone* _bottomCardZone;

	std::vector<CardInfo> _cardInfo;
};

#endif // __SCENE_GAME_H__
