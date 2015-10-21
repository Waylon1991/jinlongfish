#ifndef __CONTROLLAYER__
#define __CONTROLLAYER__

#include "cocos2d.h"
#include "FishLayer.h"
#include "Gun.h"
#include "bullet.h"
#include "Fish.h"

USING_NS_CC;
 
const int Max_Bullet_Num = 100;
const int Bullet_Speed = 12;
const int bullet_type[15] = {1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000};
struct CollisionInfo
{
	int			fish_pos;		//���������λ��
	int			bullet_pos;		//�������ӵ���λ��
};

class ControlLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(ControlLayer);
    virtual bool init();
	void init_shuzhi();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	//�Զ����¼�
	void cancle_fapao();						//ȡ���Զ�����	

	void random_coin(Vec2 point,int beilv,int bulletType);		//������
 
	void update(float dt);						//������

	void updateBullets();						//�����ӵ�
	int bullet_size;							//�ӵ�������

	void checkBulletAndFishes();				//�������ӵ�����ײ
	CollisionInfo judgeing_fish_info;			//������ײ���ӵ�����Ķ�Ӧ��Ϣ
	Bullet * tmpBullet;							//������ײʱ�ӵ�����Ϣ
	Fish   * tmpFish;							//������ײʱ�����Ϣ

	//�Ĵ��ܰ�ť�¼�
	void jineng_call_1();
	void jineng_call_2();
	void jineng_call_3();
	void jineng_call_4();
	
private:
	Size visibleSize;
	FishLayer * fishLayer;					//���ζ���
	Vector <Bullet *> my_bullets;			//�ӵ�����
	vector <int> my_delete_bullets;			//��ɾ�����ӵ�index����
	Gun *       myGun;						//����node

	Vec2 pos_origin;
	Vec2 pos_begin;							//��ʼ�����λ��
	bool is_touching;						//�Ƿ����ڵ��
	float dit_time;							//�����ϴε��ʱ��

	char cont_tmp_char1[50];
	char cont_tmp_char2[100];
	int  cont_tmp_int;						//�ӵ��߽�
	int  cont_jinbi_tmp;					//��ǰ��ұ���
	int  cont_bullet_tmp;					//��ǰzidan����

	//�Ĵ��ܰ�ť
	MenuItemSprite * jineng_icon_1;		//����
	MenuItemSprite * jineng_icon_2;		//���ٵ���
	MenuItemSprite * jineng_icon_3;		//���
	MenuItemSprite * jineng_icon_4;		//�ը��

	vector <Vec2> tianhuo_pos;			//�������
	float tianhuo_pos_cd;				//�������cd
};

#endif  