#include "Stone.h"
 
const char* stonePic[14] = {
	"rshuai.png", //(��ɫ)˧
	"rshi.png",   //(��ɫ)ʿ
	"rxiang.png", //(��ɫ)��
	"rche.png",   //(��ɫ)��
	"rma.png",    //(��ɫ)��
	"rpao.png",   //(��ɫ)��
	"rbing.png",  //(��ɫ)��

	"bjiang.png", //(��ɫ)��
	"bshi.png",   //(��ɫ)ʿ
	"bxiang.png", //(��ɫ)��
	"bche.png",   //(��ɫ)��
	"bma.png",    //(��ɫ)��
	"bpao.png",   //(��ɫ)��
	"bzu.png"     //(��ɫ)��
};

Stone::Stone()
{
}

Stone* Stone::create(int id, bool red)
{
    Stone* s = new Stone();
    
    s->init(id, red);
        
    s->autorelease();
      
    return s;
}

//�ڷ�����
//����������Ƿ�ѡ��췽
void Stone::reset(bool red)
{
	setDead(false);
   
	if (red) // ���ѡ�췽
    {
        if (_id<16) // �ں���
        {
			setX(_initPos[_id]._x);	setY(_initPos[_id]._y);
        }
        else // �ں���
        {
			setX(8 - _initPos[_id-16]._x); setY(9 - _initPos[_id-16]._y);
        }
    }
    else // ���ѡ�ڷ�
    {
        if(_id < 16) // �ں���
        {
			setX(8 - _initPos[_id]._x);	setY(9 - _initPos[_id]._y);
        }
        else // �ں���
        {
			setX(_initPos[_id-16]._x); setY(_initPos[_id-16]._y);
        }
    }
}

//��ʼ������
//�����һ���Գ�ʼ��
bool Stone::init(int id, bool red)
{
     _id = id;

    // idС��16ʱ,�����Ǻ�ɫ��
    _red = _id < 16;

	if(_id < 16)// ��ʼ������
	{
		_type = _initPos[_id]._type;
	}
	else // ��ʼ������
	{
		//����(��������)��ͬ��ɫ��ͬ���������ӵ�id���16
		_type = _initPos[_id-16]._type;
	}

    //����ͼƬ���±�
    //��������Ǻ�ɫ�� idx = _type
    //��������Ǻ�ɫ�� idx = 7 + _type
    //�������ӵ���ɫ���±���� 7
	int idx = (_red ? 0 : 1) * 7 + _type;

    //��������(��������)
    Sprite::initWithFile(stonePic[idx]);
    //setScale(1.1f);

    //������(�������ӵ�λ��)
    reset(red);

    return true;
}

//����һ�ű�
Stone::InitPos Stone::_initPos[16] =
{
    //����λ��(0,0)
    {0, 0, Stone::CHE},

    //���λ��(1,0)
    {1, 0, Stone::MA},

    //���λ��(2,0)
    {2, 0, Stone::XIANG},

    //ʿ��λ��(3,0)
    {3, 0, Stone::SHI},

    //����λ��(4,0)
    {4, 0, Stone::JIANG},

     //ʿ��λ��(5,0)
    {5, 0, Stone::SHI},

    //���λ��(6,0)
    {6, 0, Stone::XIANG},

     //���λ��(7,0)
    {7, 0, Stone::MA},

     //����λ��(8,0)
    {8, 0, Stone::CHE},

    //�ڵ�λ��(1,2)
    {1, 2, Stone::PAO},

     //�ڵ�λ��(7,2)
    {7, 2, Stone::PAO},

    //����λ��(0,3)
    {0, 3, Stone::BING},

     //����λ��(2,3)
    {2, 3, Stone::BING},

     //����λ��(4,3)
    {4, 3, Stone::BING},

     //����λ��(6,3)
    {6, 3, Stone::BING},

     //����λ��(8,3)
    {8, 3, Stone::BING},
};