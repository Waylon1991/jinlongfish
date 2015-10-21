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
	Vec2 mPoint;			//λ��
	double dAngleValue;		//�Ƕ�
}TrackPointDef;

struct VectorTrackInfo
{
	vector<int>				vFishType;		//�������
	vector<TrackPointDef>	vTrackPoint;	//����
};

enum TrackType{TRACK_UNKNOW = 0,TRACK_SMALL,TRACK_BIG,TRACK_TASK};

class FishTrack
{
public:
	FishTrack(int fish_track_id = 0,  bool fish_FanXiang = true,int fish_track_type = 0 );
	~FishTrack();

	void Reset(int fish_track_id, bool fanxiang,int trackKind);		//���ö���

	int GetTrackPointSize();									//��ȡ��ǰ���ߵ����Ĵ�С
	TrackPointDef * getNextTrackPoint();						//��ȡ��һ��λ����Ϣ
 
	static void LoadAllTrackData();								//һ���Լ������й켣�ļ���Ϣ
	static void initMap(string kindPage);						//��ʼ������

	static void GetTrackIDByFishType(int iFishType,int iTrackType, vector<int> &vTrackID);//ȡ��ָ��������й켣
	static int GetRandTrackID(int iFishType,int iTrackType,const vector<int> &vNoRandTrackID);//���ָ����Ĺ켣,����-1Ϊ����û�ж�Ӧ�켣

	static vector<int> m_vcSmallTrackID;						//С������������Ϣ  ��SmallTrackIndex[]
	static map<int,VectorTrackInfo> m_mapVcSmallTrackPoint;		//С��������Ϣ

	static vector<int> m_vcBigTrackID;							//��������������Ϣ  ��BigTrackIndex[]
	static map<int,VectorTrackInfo> m_mapVcBigTrackPoint;		//����������Ϣ

	static vector<int> m_vcTaskTrackID;							//��������������Ϣ  ��TaskTrackIndex[]
	static map<int,VectorTrackInfo> m_mapVcTaskTrackPoint;		//����������Ϣ

	int fish_track_id;				//����id
	int fish_track_index;			//�����е�λ������
	bool fish_FangXiang;			//��ķ���  true Ϊ��   false Ϊ��
	TrackType m_trackType;			//�켣������
private:
	
};
#endif