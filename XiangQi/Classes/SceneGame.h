/**********************************************************************
@file		SceneGame.h
@brief		��Ϸ����
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __SCENEGAME_H__
#define __SCENEGAME_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Stone.h"
USING_NS_CC;

class AIPlayer;

//����һ����
//��¼��һ�������Ϣ
class Step : public Ref
{
public:
	int _moveid;	// �ƶ�������ID
	int _killid;	// �Ե�������ID
	int _xFrom;		// �����ƶ�ǰ��X����
	int _yFrom;		// �����ƶ�ǰ��Y����
	int _xTo;		// �����ƶ����X����
	int _yTo;		// �����ƶ����Y����

	static Step* create(int moveid, int killid, int xFrom, int yFrom, int xTo, int yTo)
	{
		Step* step = new Step;

		step->_moveid = moveid;
		step->_killid = killid;
		step->_xFrom = xFrom;
		step->_yFrom = yFrom;
		step->_xTo = xTo;
		step->_yTo = yTo;

		step->autorelease();

		return step;
	}
};

class SceneGame : public Layer
{
public:
     SceneGame();

    ~SceneGame();

    static Scene* scene(bool red);

    bool init(bool red);

    // �������Ƿ�ѡ��췽
    static SceneGame* create(bool red);

	// ������������������ʵ����
	Point getStonePos(int x, int y);

	// ����������ʵ����õ��������꣬�����ʵ�����������ⷵ��false
	bool getClickPos(Point pt, int &x, int &y);

	// ͨ��������±��ȡ���ӵ�ID
	int getStone(int x, int y);

	// ѡ������
	void setSelectId(int id);

	//�ƶ�����
	//����1���ƶ�������
	//����2����ɱ��������
	void moveStone(int moveId, int killId, int x, int y);

	void moveComplete(Node*, void*);

	//����(xo,yo)��(x,y)֮���������
	//���������Ϊ-1,��ʾ(xo,yo)��(x,y)����һ��ֱ����
	int getStoneCount(int xo, int yo, int x, int y);

    //����
    void Back(Ref*);

    //��ʼ��Ϸ
    void Start(Ref*);

    //���ű�������
     void Voice(Ref* sender);
          
    //ͨ�����ѡ�����ӣ�������
	bool onTouchBegan(Touch *touch, Event *unused_event); 
    void onTouchEnded(Touch *touch, Event *unused_event); 

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//�������
	bool canMove(int moveid, int killid, int x, int y);

	//�����������
	bool canMoveJiang(int moveid, int killid, int x, int y);

	//ʿ���������
	bool canMoveShi(int moveid, int x, int y);

	//����������
	bool canMoveXiang(int moveid, int x, int y);

	//�����������
	bool canMoveChe(int moveid, int x, int y);

	//����������
	bool canMoveMa(int moveid, int x, int y);

	//�ڵ��������
	bool canMovePao(int moveid, int killid, int x, int y);

	//�����������
	bool canMoveBing(int moveid, int x, int y);

	void updateAutoGo(float delay);

	void aiGostep();

	void fakeMove(Step* step);
	void unfakeMove(Step* step);

public:

	Point		_plateOffset;		// ���̵�ƫ����
	Point		_stoneOffset;		// ���ӵ�ƫ����
	bool		_redSide;			// ����Ƿ��Ǻ췽
	Sprite*		_select;			// ���ӵ���ɫѡ���
	Sprite*		_result;			// ��ʾ��Ϸ���
	Sprite*		_lose;				// ��
	int			_selectid;			// ѡ�е�����id
	bool		_redTurn;			// ����Ƿ�ú췽��
	Vector<Step*>_steps;			// ����ÿ���ߵ���Ϣ
	AIPlayer*	_ai;				// �������AI
	Stone*		_s[32];				// ���Ӷ�������(32������)
};

#endif // __SCENEGAME_H__
