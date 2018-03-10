#pragma once

#include "cocos2d.h"
USING_NS_CC;

class PlaySprite;
class EnemySprite;

// ��Ϸ������
class PlaneWarGame :public Layer
{
public:
	enum gameTags
	{
		MENU_1 				/* �˵�1����ͣ/����/ը����		*/	,
		MENU_2 				/* �˵�2������/���¿�ʼ/���أ�	*/	,
		MENU_3 				/* �˵�3�����¿�ʼ/���أ�		*/	,
		
		MENUITEM_SOUND		/* �����˵���					*/	,
		
		MENU2_BG					/* �˵�2����ͼ					*/	,
		MENU3_BG					/* �˵�3����ͼ					*/	,

		BACKGROUND_1 		/* ����1						*/	,
		BACKGROUND_2 		/* ����2						*/	,

		LABEL_BOMBCOUNT		/* ��ʾը�������ı�ǩ			*/	,

		PROP_BULLET			/* �ӵ�����						*/	,
		PROP_BOMB			/* ը������						*/	,

		SPRITE_BULLET		/* �ӵ�����						*/	
	};

	enum zOrder{
		Z_BG					/* ��Ϸ������Z��˳��		*/,
		Z_BULLET					/* ��Ϸ������Z��˳��		*/,
		Z_GAME 				/* ��ϷԪ�ص�Z��˳��		*/	,
		Z_MENU_BG		/* ��Ϸ�˵�������Z��˳��		*/	,
		Z_MENU				/* ��Ϸ�˵���Z��˳��		*/	,
	};

public:
	PlaneWarGame();
	~PlaneWarGame();
	static Scene* scene();
	virtual bool init();
	
	// ��Ϸ����ĳ�ʼ��
	bool initBackground();
	void bg1roll();
	void bg2roll();
	bool initMenu1();
	bool initMenu2();
	bool initMenu3();

	// ��Ϸ�����ڵĲ˵���ص�
	void menuPauseCallback(Ref* pSender);
	void menuSoundCallback(Ref* pSender);
	void menuBombCallback(Ref* pSender);
	void menuResumeCallback(Ref* pSender);
	void menuRestartCallback(Ref* pSender);
	void menuBackCallback(Ref* pSender);

	CREATE_FUNC(PlaneWarGame);

	// �л�����
	void addEnemy(float dt);
	// ��ҷ����ӵ�
	void shoot(float dt);
	// ��Ϸ�߼���ѭ��
	virtual void update(float dt);
	void addBullet(Sprite* bullet, Point pt);
	// ���ߵĲ���
	void addProp(float dt);
	// ��Ϸ����ײ���
	void updateGame(float dt);
	// ������ʾ
	void show();
	// ��Ϸ����
	void gameover();

	void spriteMoveFinished(Node* sender);
	void killAllEnemys();
	void releaseEnemys();

	// ������Ϣ����
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 

protected:
	
	// ��Ϸ��Ա
	PlaySprite*					_player;			// ��ҷɻ�
	Vector<EnemySprite*>		_enemys;			// �з��ɻ�����
	Vector<Sprite*>				_bullets;			// �ӵ�����
	int							_bulletsDestroyed;	// �ӵ�����Ŀ�����

	// ��Ϸ�ؼ�
	Label*						_label;				// ������ǩ
	MenuItemSprite*				_pause;				// ��ͣ��ť
	Menu*						_menu;				// ��Ϸ�����ڵĲ˵�����ͣ/����/ը����
	
	// ��Ҫ��Ϸ����
	bool						_issound;			// �������ֿ���
	Size						_size;				// ��Ϸ�����С����Ļ��С��
	int						_score;				// ����
	bool						_isOver;			// ��Ϸ������־
};