#ifndef __FISHLAYER__
#define __FISHLAYER__

#include "cocos2d.h"
#include "Fish.h"
#include "FishTrack.h"

USING_NS_CC;
const int fishMaxNum = 100;				//��Ļ����������������
const int addFishNum = 2;				// ÿ�����ɵ��������Ŀ
const float fish_move_time = 0.28f;		//�������ζ���ʱ��
const int fish_max_type = 23;			//�����������������
const Vec2 zixing_O[6] = {Vec2::ZERO,Vec2(-20,20),Vec2(20,20),Vec2(-20,40),Vec2(20,40),Vec2(0,60)};
const Vec2 zixing_L[7] = {Vec2::ZERO,Vec2(0,20),Vec2(0,40),Vec2(0,60),Vec2(0,80),Vec2(20,0),Vec2(40,0)};
const Vec2 zixing_V[8] = {Vec2::ZERO,Vec2(-10,20),Vec2(-20,40),Vec2(-30,60),Vec2(0,0),Vec2(15,20),Vec2(25,40),Vec2(35,60)};
const Vec2 zixing_U[9] = {Vec2::ZERO,Vec2(-20,0),Vec2(-20,20),Vec2(-20,40),Vec2(-20,60),Vec2(20,0),Vec2(20,20),Vec2(20,40),Vec2(20,60)};
const Vec2 zixing_E[10] = {Vec2::ZERO,Vec2(-15,10),Vec2(-15,-10),Vec2(15,0),Vec2(-15,30),Vec2(-15,-30),Vec2(5,30),Vec2(5,-30),Vec2(25,30),Vec2(25,-30)};
class FishLayer : public Layer
{
public:
	CREATE_FUNC(FishLayer);
	virtual bool init();
	void init_ShuZhi();

	
	Vector<Fish*> m_Fishes;				//��ǰ�����������
 
	Fish* AddTrackFish(Fish *pFish,int iFishType,int iTrackID,int iNowFrameIndex);//������ 

	void updateFishMove_jyw(float dt);		//�������λ�úͽǶ�
	void updateAddFish_jyw(float dt);		//�ж��Ƿ����ӹ켣��
	void updateGroupFish_jyw(float dt);		//ÿ��һ��ʱ��������Ⱥ

private:
	Size visibleSize;
 
	float fish_move_time_tmp;			//���Ѿ��ζ���ʱ��

	float add_up_time;					//��ǰ��������� ʹ��ʱ��
	float add_upall_time;					//��Ҫ�������ʱ��
 
	vector <int> track_used;			//�Ѿ�ʹ�ù�������
	vector <int> track_used_num;		//����ʹ��ʱ�� 600֡�ڲ��������� ͬһ����

	vector <int> delete_fish_id;		//Ҫɾ�������id
};
#endif