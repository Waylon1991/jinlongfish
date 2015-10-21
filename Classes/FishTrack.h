#ifndef __FISHTRACK__
#define __FISHTRACK__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

const int SmallTrackIndex[75] = {1000,1001,1003,1004,1005,1008,1010,1013,1014,1015,1016,1017,1018,1019,1020,1500,1502,1503,1504,1505,1506,1507,1508,
	2000,2001,2002,2003,2004,2005,2007,2010,2015,2016,2017,2022,2500,2501,2502,2503,3000,3001,3002,3003,3004,3005,3006,3007,3008,3009,3010,3011,3012,
	3013,3014,3015,3016,3017,3500,3501,3502,3503,3504,3505,3506,3507,3508,3509,3510,3511,3512,3513,3514,3515,3516,3517};

const int BigTrackIndex[44] = {4000,4001,4002,4003,4004,4005,4006,4007,4008,4009,4010,4011,4012,4013,4014,4015,4016,4017,4018,4019,4020,4021,
	4500,4501,4502,4503,4504,4505,4506,4507,4508,4509,4510,4511,4512,4513,4514,4515,4516,4517,4518,4519,4520,4521};

const int TaskTrackIndex[16] = {7000,7001,7002,7003,7004,7005,7006,7007,7500,7501,7502,7503,7504,7505,7506,7507};

const int NotValible_small[18] = {1010,1013,1019,1507,2004, 2010,2015,3000,3005,3007,  3010,3011,3012,3013,3506, 3511,3514,3517};
typedef struct TrackPoint
{
	Vec2 mPoint;			//位置
	double dAngleValue;		//角度
}TrackPointDef;

struct VectorTrackInfo
{
	vector<int>				vFishType;		//鱼的类型
	vector<TrackPointDef>	vTrackPoint;	//鱼线
};

enum TrackType{TRACK_UNKNOW = 0,TRACK_SMALL,TRACK_BIG,TRACK_TASK};

class FishTrack
{
public:
	FishTrack(int fish_track_id = 0,  bool fish_FanXiang = true,int fish_track_type = 0 );
	~FishTrack();

	void Reset(int fish_track_id, bool fanxiang,int trackKind);		//重置对象

	int GetTrackPointSize();									//获取当前鱼线的鱼点的大小
	TrackPointDef * getNextTrackPoint();						//获取下一个位置信息
 
	static void LoadAllTrackData();								//一次性加载所有轨迹文件信息
	static void initMap(string kindPage);						//初始化鱼线

	static void GetTrackIDByFishType(int iFishType,int iTrackType, vector<int> &vTrackID);//取得指定鱼的所有轨迹
	static int GetRandTrackID(int iFishType,int iTrackType,const vector<int> &vNoRandTrackID);//随机指定鱼的轨迹,返回-1为此鱼没有对应轨迹

	static vector<int> m_vcSmallTrackID;						//小鱼鱼线索引信息  即SmallTrackIndex[]
	static map<int,VectorTrackInfo> m_mapVcSmallTrackPoint;		//小鱼鱼线信息

	static vector<int> m_vcBigTrackID;							//大鱼鱼线索引信息  即BigTrackIndex[]
	static map<int,VectorTrackInfo> m_mapVcBigTrackPoint;		//大鱼鱼线信息

	static vector<int> m_vcTaskTrackID;							//任务鱼线索引信息  即TaskTrackIndex[]
	static map<int,VectorTrackInfo> m_mapVcTaskTrackPoint;		//任务鱼线信息

	int fish_track_id;				//鱼线id
	int fish_track_index;			//鱼线中的位置序列
	bool fish_FangXiang;			//鱼的方向  true 为正   false 为负
	TrackType m_trackType;			//轨迹的类型
private:
	
};
#endif