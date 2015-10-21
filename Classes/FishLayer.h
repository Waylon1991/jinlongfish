#ifndef __FISHLAYER__
#define __FISHLAYER__

#include "cocos2d.h"
#include "Fish.h"
#include "FishTrack.h"

USING_NS_CC;
const int fishMaxNum = 100;				//屏幕最多能容下鱼的数量
const int addFishNum = 2;				// 每次生成的最大鱼数目
const float fish_move_time = 0.28f;		//更新鱼游动的时间
const int fish_max_type = 23;			//随机生成最大的类型鱼
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

	
	Vector<Fish*> m_Fishes;				//当前生成鱼的容器
 
	Fish* AddTrackFish(Fish *pFish,int iFishType,int iTrackID,int iNowFrameIndex);//增加鱼 

	void updateFishMove_jyw(float dt);		//更新鱼的位置和角度
	void updateAddFish_jyw(float dt);		//判断是否增加轨迹鱼
	void updateGroupFish_jyw(float dt);		//每隔一定时间增加鱼群

private:
	Size visibleSize;
 
	float fish_move_time_tmp;			//鱼已经游动的时间

	float add_up_time;					//当前增加鱼调度 使用时间
	float add_upall_time;					//需要增加鱼的时间
 
	vector <int> track_used;			//已经使用过的鱼线
	vector <int> track_used_num;		//鱼线使用时间 600帧内不允许生成 同一鱼线

	vector <int> delete_fish_id;		//要删除的鱼的id
};
#endif