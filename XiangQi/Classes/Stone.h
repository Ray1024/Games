/**********************************************************************
@file		Stone.h
@brief		棋子
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef  __STONE_H__
#define  __STONE_H__

#include "cocos2d.h"
#include "AppMacros.h"
USING_NS_CC;


//棋子类
class Stone : public Sprite
{
public:
	static const int DIAMETER = 56/SCALE_FACTOR;

    Stone();

    //棋子的类型:将、士、相、车、马、炮、兵
    enum TYPE {JIANG,SHI,XIANG,CHE,MA,PAO,BING};

    // 创建棋子
    // 参数1：棋子的类型
    // 参数2：棋子的颜色
    static Stone* create(int id, bool red);
    
    bool init(int id, bool red);

    //摆棋子
    void reset(bool red);

    //保存每个棋子的初始位置
    static struct InitPos
    {
        int _x;
        int _y;
		Stone::TYPE _type;
    }_initPos[16];

	CC_SYNTHESIZE(TYPE, _type, Type);	// 棋子类型
	CC_SYNTHESIZE(int, _x, X);			// 棋子X索引位置
	CC_SYNTHESIZE(int, _y, Y);			// 棋子Y索引位置
	CC_SYNTHESIZE(int, _id, ID);		// 棋子ID(0~31)
	CC_SYNTHESIZE(bool, _dead, Dead);	// 棋子是否被吃
	CC_SYNTHESIZE(bool, _red, Red);		// 棋子颜色（红、黑）
};

#endif	// !__STONE_H__
