#pragma once

#include "cocos2d.h"
USING_NS_CC;

class PlaySprite;
class EnemySprite;

// 游戏界面类
class PlaneWarGame :public Layer
{
public:
	enum gameTags
	{
		MENU_1 				/* 菜单1（暂停/声音/炸弹）		*/	,
		MENU_2 				/* 菜单2（继续/重新开始/返回）	*/	,
		MENU_3 				/* 菜单3（重新开始/返回）		*/	,
		
		MENUITEM_SOUND		/* 声音菜单项					*/	,
		
		MENU2_BG					/* 菜单2背景图					*/	,
		MENU3_BG					/* 菜单3背景图					*/	,

		BACKGROUND_1 		/* 背景1						*/	,
		BACKGROUND_2 		/* 背景2						*/	,

		LABEL_BOMBCOUNT		/* 显示炸弹数量的标签			*/	,

		PROP_BULLET			/* 子弹道具						*/	,
		PROP_BOMB			/* 炸弹道具						*/	,

		SPRITE_BULLET		/* 子弹精灵						*/	
	};

	enum zOrder{
		Z_BG					/* 游戏背景的Z轴顺序		*/,
		Z_BULLET					/* 游戏背景的Z轴顺序		*/,
		Z_GAME 				/* 游戏元素的Z轴顺序		*/	,
		Z_MENU_BG		/* 游戏菜单背景的Z轴顺序		*/	,
		Z_MENU				/* 游戏菜单的Z轴顺序		*/	,
	};

public:
	PlaneWarGame();
	~PlaneWarGame();
	static Scene* scene();
	virtual bool init();
	
	// 游戏界面的初始化
	bool initBackground();
	void bg1roll();
	void bg2roll();
	bool initMenu1();
	bool initMenu2();
	bool initMenu3();

	// 游戏界面内的菜单项回调
	void menuPauseCallback(Ref* pSender);
	void menuSoundCallback(Ref* pSender);
	void menuBombCallback(Ref* pSender);
	void menuResumeCallback(Ref* pSender);
	void menuRestartCallback(Ref* pSender);
	void menuBackCallback(Ref* pSender);

	CREATE_FUNC(PlaneWarGame);

	// 敌机产生
	void addEnemy(float dt);
	// 玩家发射子弹
	void shoot(float dt);
	// 游戏逻辑的循环
	virtual void update(float dt);
	void addBullet(Sprite* bullet, Point pt);
	// 道具的产生
	void addProp(float dt);
	// 游戏的碰撞检测
	void updateGame(float dt);
	// 数据显示
	void show();
	// 游戏结束
	void gameover();

	void spriteMoveFinished(Node* sender);
	void killAllEnemys();
	void releaseEnemys();

	// 键盘消息处理
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 

protected:
	
	// 游戏成员
	PlaySprite*					_player;			// 玩家飞机
	Vector<EnemySprite*>		_enemys;			// 敌方飞机数组
	Vector<Sprite*>				_bullets;			// 子弹数组
	int							_bulletsDestroyed;	// 子弹击中目标个数

	// 游戏控件
	Label*						_label;				// 分数标签
	MenuItemSprite*				_pause;				// 暂停按钮
	Menu*						_menu;				// 游戏界面内的菜单（暂停/声音/炸弹）
	
	// 主要游戏属性
	bool						_issound;			// 背景音乐开关
	Size						_size;				// 游戏界面大小（屏幕大小）
	int						_score;				// 分数
	bool						_isOver;			// 游戏结束标志
};