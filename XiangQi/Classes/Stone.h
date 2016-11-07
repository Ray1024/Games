/**********************************************************************
@file		Stone.h
@brief		����
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef  __STONE_H__
#define  __STONE_H__

#include "cocos2d.h"
#include "AppMacros.h"
USING_NS_CC;


//������
class Stone : public Sprite
{
public:
	static const int DIAMETER = 56/SCALE_FACTOR;

    Stone();

    //���ӵ�����:����ʿ���ࡢ�������ڡ���
    enum TYPE {JIANG,SHI,XIANG,CHE,MA,PAO,BING};

    // ��������
    // ����1�����ӵ�����
    // ����2�����ӵ���ɫ
    static Stone* create(int id, bool red);
    
    bool init(int id, bool red);

    //������
    void reset(bool red);

    //����ÿ�����ӵĳ�ʼλ��
    static struct InitPos
    {
        int _x;
        int _y;
		Stone::TYPE _type;
    }_initPos[16];

	CC_SYNTHESIZE(TYPE, _type, Type);	// ��������
	CC_SYNTHESIZE(int, _x, X);			// ����X����λ��
	CC_SYNTHESIZE(int, _y, Y);			// ����Y����λ��
	CC_SYNTHESIZE(int, _id, ID);		// ����ID(0~31)
	CC_SYNTHESIZE(bool, _dead, Dead);	// �����Ƿ񱻳�
	CC_SYNTHESIZE(bool, _red, Red);		// ������ɫ���졢�ڣ�
};

#endif	// !__STONE_H__
