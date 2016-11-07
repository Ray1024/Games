/**********************************************************************
@file		SceneGame.h
@brief		游戏场景
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

//创建一个类
//记录走一步棋的信息
class Step : public Ref
{
public:
	int _moveid;	// 移动的棋子ID
	int _killid;	// 吃掉的棋子ID
	int _xFrom;		// 棋子移动前的X索引
	int _yFrom;		// 棋子移动前的Y索引
	int _xTo;		// 棋子移动后的X索引
	int _yTo;		// 棋子移动后的Y索引

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

    // 参数：是否选择红方
    static SceneGame* create(bool red);

	// 根据输入索引返回真实坐标
	Point getStonePos(int x, int y);

	// 根据输入真实坐标得到索引坐标，如果真实坐标在棋盘外返回false
	bool getClickPos(Point pt, int &x, int &y);

	// 通过坐标的下标获取棋子的ID
	int getStone(int x, int y);

	// 选择棋子
	void setSelectId(int id);

	//移动棋子
	//参数1：移动的棋子
	//参数2：被杀掉的棋子
	void moveStone(int moveId, int killId, int x, int y);

	void moveComplete(Node*, void*);

	//计算(xo,yo)和(x,y)之间的棋子数
	//如果棋子数为-1,表示(xo,yo)和(x,y)不在一条直线上
	int getStoneCount(int xo, int yo, int x, int y);

    //悔棋
    void Back(Ref*);

    //开始游戏
    void Start(Ref*);

    //播放背景音乐
     void Voice(Ref* sender);
          
    //通过点击选择棋子，走棋子
	bool onTouchBegan(Touch *touch, Event *unused_event); 
    void onTouchEnded(Touch *touch, Event *unused_event); 

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//走棋规则
	bool canMove(int moveid, int killid, int x, int y);

	//将的走棋规则
	bool canMoveJiang(int moveid, int killid, int x, int y);

	//士的走棋规则
	bool canMoveShi(int moveid, int x, int y);

	//相的走棋规则
	bool canMoveXiang(int moveid, int x, int y);

	//车的走棋规则
	bool canMoveChe(int moveid, int x, int y);

	//马的走棋规则
	bool canMoveMa(int moveid, int x, int y);

	//炮的走棋规则
	bool canMovePao(int moveid, int killid, int x, int y);

	//兵的走棋规则
	bool canMoveBing(int moveid, int x, int y);

	void updateAutoGo(float delay);

	void aiGostep();

	void fakeMove(Step* step);
	void unfakeMove(Step* step);

public:

	Point		_plateOffset;		// 棋盘的偏移量
	Point		_stoneOffset;		// 棋子的偏移量
	bool		_redSide;			// 玩家是否是红方
	Sprite*		_select;			// 棋子的蓝色选择框
	Sprite*		_result;			// 显示游戏结果
	Sprite*		_lose;				// 负
	int			_selectid;			// 选中的棋子id
	bool		_redTurn;			// 标记是否该红方走
	Vector<Step*>_steps;			// 保存每步走的信息
	AIPlayer*	_ai;				// 保存电脑AI
	Stone*		_s[32];				// 棋子对象数组(32颗棋子)
};

#endif // __SCENEGAME_H__
