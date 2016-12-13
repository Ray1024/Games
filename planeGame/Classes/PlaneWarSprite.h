#pragma once
#include "cocos2d.h"
#include "PlaneWarGame.h"
USING_NS_CC;

// 玩家飞机的运动模式
enum moveMode{
	MM_NONE = 0,
	MM_UP,
	MM_DOWN,
	MM_LEFT,
	MM_RIGHT
};

enum bulletKind{
	BK_SINGLE=0,
	BK_DOUBLE
};

// 玩家角色类
class PlaySprite: public Node
{
	enum playTag
	{
		ACTION_1	/* 动作1 */
	};
public:
	virtual void onEnter();

	PlaySprite();
	~PlaySprite();

	Rect	getRect();
	Point getPlayerPt();
	void	setPlayerPt(Point pt);

	void	move(float dt);
	void	die();
	void	destroy();

	void	setGame(PlaneWarGame* game) { _game = game; _game->retain();};

public:
	// 属性
	moveMode	_mode;			// 运动方式（方向按键）
	bool		_isDragEnabled; // 可否被鼠标拖拽（鼠标移动）

	bulletKind	_bulletKind;	// 子弹类型（吃道具可变双发）
	int			_bombCount;		// 炸弹数量（吃道具获得）

protected:
	Sprite*	_sprite;		// 代表精灵
	PlaneWarGame* _game;	
};

enum EnemyKind{
	EK_SMALL=0,
	EK_MIDDLE,
	EK_BIG
};

// 敌机类
class EnemySprite: public Node
{//敌机可有三种类型
public:
	EnemySprite();
	~EnemySprite();

	virtual void onEnter();

	Rect getRect();

	void spriteMoveFinished(Node* sender);

	void die();
	void destroy();

	bool isNull();
public:
	// 属性
	int			_hp;			// 血量
	EnemyKind	_enemyKind;		// 敌机种类
	bool		_die;			// 已死亡
	bool		_destroy;		// 已释放

protected:
	Sprite*	_sprite;		// 代表精灵
};