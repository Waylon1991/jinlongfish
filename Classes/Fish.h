#ifndef __FISH__
#define __FISH__

#include "cocos2d.h"
#include "FishTrack.h"

USING_NS_CC;

const float cFishGailv[33] = {50,50,50,50,25, 20,16,14,14,14, 12,12,11,11,10, 8.333,6.667,5.556,5.000,5.000, 4.000,3.333,1.250,1.000,0.222, 0.125,10.000,12.500,3.704,3.333, 5.556,2.083,1.333};
const int   fishBeishu[26] = {2,2,2,2,3, 3,3,4,4,5, 5,6,6,7,8, 9,10,15,20,35, 40,60,100,150,200, 300};
const int   yy_fish_distance = 20;
class Fish : public Node
{
public:
	static Fish * create(int type);
	virtual bool init(int type);
 
	Sprite * _fishSprite;						//鱼的节点
	Sprite * _fishSprite_yy;					//鱼的阴影
	Vec2 yy_pianyi;								//阴影鱼的便宜

	bool CreateTrackFish(Fish* pFish,int iFishType,vector<int>vcLimitTrackID);		//创建轨迹鱼
	bool SetFishInfo(int iFishType,int iTrackID,int iNowTrackIndex = -1);			//设定轨迹鱼信息,返回是否有对应轨迹
	bool updateFishPos();															//更新鱼的位置
	bool ifCatch(int beilv);														//判断鱼是否被抓住
	void fishAnimate();																//播放鱼被抓住动画

	//void setFishMov(float mov_x , float mov_y);										//设置鱼偏离当前鱼线的x鱼y的大小
	int   fish_cur_frame;		//当前帧
	float fish_width;			//鱼的宽度
	float fish_hight;			//鱼的高度

	float fish_angle;			//鱼的角度
	float m_iX;					//X坐标位置，图片中心点
	float m_iY;					//Y坐标位置，图片中心点

	float m_iXMov;				//相对鱼轨迹偏移量
	float m_iYMov;				
 
	FishTrack fish_track;		//鱼的轨迹
	int	  Track_id;				//轨迹id
	int	  fish_type;			//鱼的类型

	bool bDead;					//鱼是否死了
 
private:
	char fish_tmp_char[30];
};
#endif