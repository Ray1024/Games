#pragma once
#include "cocos2d.h"
#include "PlaneWarGame.h"
USING_NS_CC;

// ��ҷɻ����˶�ģʽ
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

// ��ҽ�ɫ��
class PlaySprite: public Node
{
	enum playTag
	{
		ACTION_1	/* ����1 */
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
	// ����
	moveMode	_mode;			// �˶���ʽ�����򰴼���
	bool		_isDragEnabled; // �ɷ������ק������ƶ���

	bulletKind	_bulletKind;	// �ӵ����ͣ��Ե��߿ɱ�˫����
	int			_bombCount;		// ը���������Ե��߻�ã�

protected:
	Sprite*	_sprite;		// ������
	PlaneWarGame* _game;	
};

enum EnemyKind{
	EK_SMALL=0,
	EK_MIDDLE,
	EK_BIG
};

// �л���
class EnemySprite: public Node
{//�л�������������
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
	// ����
	int			_hp;			// Ѫ��
	EnemyKind	_enemyKind;		// �л�����
	bool		_die;			// ������
	bool		_destroy;		// ���ͷ�

protected:
	Sprite*	_sprite;		// ������
};