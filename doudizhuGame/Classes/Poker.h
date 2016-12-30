#pragma once
#include "cocos2d.h"
#include "Global.h"


class GameScene;
USING_NS_CC;

class Poker : public Sprite
{
public:
	Poker();
	~Poker();

	static Poker* create(const char *pszFileName, const Rect& rect);

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);

	void showFront();//��ʾ����
	void showLast();//��ʾ����
	Poker* copy();//����
	void setTouchPriority(int num);
	void SelectPkLuTou();//���ѡ�����ƾ�¶��ͷ
	void SelectPkSuoTou();//���ѡ�����ƾ���ͷ
private:
	CC_SYNTHESIZE(bool,m_isSelect,Select);//�Ƿ���ѡ
	CC_SYNTHESIZE(GameScene*,m_gameMain,GameMain);
	CC_SYNTHESIZE(bool,m_isDianJi,DianJi);//�Ƿ��ܱ����
	CC_SYNTHESIZE(int,m_huaSe,HuaSe);//��ɫ
	CC_SYNTHESIZE(int,m_num,Num);//��ֵ
	EventListenerTouchOneByOne* touchListener;
};
