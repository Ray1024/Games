#pragma once
#include "cocos2d.h"
#include "Global.h"
#include <vector>

class Poker;
class Player;

USING_NS_CC;

//���� �����������
struct JiShu
{
	int pkZhi;//��ֵ
	int num; //������
	CCArray* arr; //������
};

//�����������
struct PaiXing :public Ref
{
	CARD_TYPE type;
	std::vector<Poker*> vec;
};

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();

	static Scene* scene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	virtual void onEnter();
	virtual void onExit();

private:

	bool initPlayer();//��ʼ�������Ϣ
	bool initAnNiu();//��ʼ���зְ�ť
	Poker* selectPoker(int huaSe,int num);//����һ����
	bool createPokers();//����һ���˿���
	bool xiPai();//ϴ��
	void SendPk();//����
	void MovePk(Player* play,Poker* pk);//�����ƶ�����
	void func(Node* pSender, void* pData);
	void update(float delta);

	void menuChuPai(Ref* sender);
	void menuBuChu(Ref* sender);
	void menuShengLi(Ref* sender);
	void menuShu(Ref* sender);

	bool InitNpcBuChuLable();//��ʼ��NPC"����"��ǩ
	void OutCard(float delta);//����
	//������͵��ж�
	int PaiDuanPaiXing();//�ж�����
	bool IsLianPai();//�Ƿ�Ϊ����
	bool IsLianDui();//�Ƿ�Ϊ����
	int IsFeiJi();//�Ƿ�Ϊ�ɻ�
	bool IsFeiJiLian(std::vector<int> vec);//�ɻ��Ƿ�����
	CRAD_INDEX FenXiFeiJi();//�����ɻ� 
	//�ֲ���Ե���
	void FenChaiNpcPai(Player* npc);
	void TiQuFeiJi(Player* npc,CARD_TYPE type,std::vector<PaiXing> &vec);//��ȡ�ɻ�
	void TiQuLianDui(Player* npc,std::vector<PaiXing> &vec);//��ȡ����
	void TiQuLianPai(Player* npc,std::vector<PaiXing> &vec);//��ȡ����
	void NpcOutPoker(Player* npc,CCArray* out,Player* out1);//���Գ���
	void NpcGenPoker(Player* npc,CCArray* out,Player* out1);//���Ը���
	bool SanDaiYiOrEr(Player* npc,CCArray* out,Player* out1);//������һ��������
	bool FeiJiDaiChiBang(Player* npc,CCArray* out,Player* out1);//�ɻ������
	bool NpcChaiDan(Player* npc,CCArray* out ,Player* out1);//�Ե����Ʋ�����
	bool NpcChaiDui(Player* npc,CCArray* out,Player* out1);//�Ե����Ʋ����
	bool NpcChaiSan(Player* npc,CCArray* out,Player* out1);//�Ե����Ʋ�����
	bool NpcChaiFeiJi(Player* npc,CCArray* out,Player* out1);//�Ե����Ʋ�ɻ�
	bool NpcChaiLianPai(Player* npc,CCArray* out,Player* out1);//�Ե����Ʋ�����
	bool NpcChaiShuangShun(Player* npc,CCArray* out,Player* out1);//�Ե����Ʋ�˫˳
	int GetNpcPxNum(Player* npc,CARD_TYPE cardType);//����NPCĳ���͵ĸ���
	int FenXiFeiJiNum(CCArray* arr);//�����ɻ��м�������
	void ClearOutPk();//������г�����
	bool IsOutPkFinish();//�Ƿ�����ҳ�����
	void IsShengLi();//ʤ�����ж�
	void ReStart();//���¿�ʼ
public:
	void PlayerOutPaiXu(CCArray* m_arrPlayerOut);//�Գ����ƽ�������
private:
	CCArray* m_arrPokers;//���е���
	CC_SYNTHESIZE(Player*,m_player,Player);//���
	Player* m_npcOne;//����1
	Player* m_npcTwo;//����2
	Player* m_Three;//��ʾ����ʣ����
	CC_SYNTHESIZE(Player*,m_playerOut,PlayerOut);//��ҳ�����
	CC_SYNTHESIZE(CCArray*,m_arrPlayerOut,ArrPlayerOut);//���ѡ��Ҫ������
	Player* m_npcOneOut;//����1������
	Player* m_npcTwoOut;//����2������
	Menu* m_chuPaiMenu;//���Ʋ˵�
	Menu* m_menuShengLi;//ʤ���˵�
	Menu* m_menuShu;//��Ĳ˵�
	Label* m_lableDiZhu;//������ǩ
	CCArray* m_arrGenPk;//Ҫ������
	bool m_isSend;//�Ƿ�����
	int m_iSendPk;//�ѷ����ڼ�����
	int m_iState;//��ǰ״̬ 0������״̬ 1���е���״̬ 2������״̬ 3�����״̬
	int m_iOutCard;//�۵�˭����
	int m_type;//���������
	int m_typeTem;//��������͸���
	bool m_isChiBang;//�Ƿ���ϳ��
	int m_count; //������ɻ��Ƶĸ���
	int m_threeNum;//�ɻ������ķɻ���
	Vec2 playerDiZhuLablePt;
	Vec2 npcOneDiZhuLablePt;
	Vec2 npcTwoDiZhuLablePt;
	Player* m_lastOut;//�����Ƶ�һ��

	ValueMap _strings;
};