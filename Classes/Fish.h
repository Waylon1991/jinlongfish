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
 
	Sprite * _fishSprite;						//��Ľڵ�
	Sprite * _fishSprite_yy;					//�����Ӱ
	Vec2 yy_pianyi;								//��Ӱ��ı���

	bool CreateTrackFish(Fish* pFish,int iFishType,vector<int>vcLimitTrackID);		//�����켣��
	bool SetFishInfo(int iFishType,int iTrackID,int iNowTrackIndex = -1);			//�趨�켣����Ϣ,�����Ƿ��ж�Ӧ�켣
	bool updateFishPos();															//�������λ��
	bool ifCatch(int beilv);														//�ж����Ƿ�ץס
	void fishAnimate();																//�����㱻ץס����

	//void setFishMov(float mov_x , float mov_y);										//������ƫ�뵱ǰ���ߵ�x��y�Ĵ�С
	int   fish_cur_frame;		//��ǰ֡
	float fish_width;			//��Ŀ��
	float fish_hight;			//��ĸ߶�

	float fish_angle;			//��ĽǶ�
	float m_iX;					//X����λ�ã�ͼƬ���ĵ�
	float m_iY;					//Y����λ�ã�ͼƬ���ĵ�

	float m_iXMov;				//�����켣ƫ����
	float m_iYMov;				
 
	FishTrack fish_track;		//��Ĺ켣
	int	  Track_id;				//�켣id
	int	  fish_type;			//�������

	bool bDead;					//���Ƿ�����
 
private:
	char fish_tmp_char[30];
};
#endif