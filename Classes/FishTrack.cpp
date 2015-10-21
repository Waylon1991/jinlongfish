#include "FishTrack.h"

map<int , VectorTrackInfo> FishTrack::m_mapVcSmallTrackPoint;
vector<int> FishTrack::m_vcSmallTrackID;

map<int , VectorTrackInfo> FishTrack::m_mapVcBigTrackPoint;
vector<int> FishTrack::m_vcBigTrackID;

map<int , VectorTrackInfo> FishTrack::m_mapVcTaskTrackPoint;
vector<int> FishTrack::m_vcTaskTrackID;

FishTrack::FishTrack(int track_id, bool fanxiang,int fish_track_type)
{
	srand(time(NULL));
	Reset(track_id,fanxiang,fish_track_type);
	//log("construct FishTrack");
}

FishTrack::~FishTrack()
{
	//log("destruct FishTrack");
}

void FishTrack::Reset(int track_id, bool fanxiang,int trackKind)
{
	fish_track_id = track_id;

	bool bFind = false;
	switch (trackKind)
	{
	case 1:if(m_mapVcSmallTrackPoint.find(fish_track_id) != m_mapVcSmallTrackPoint.end())
		   {
			   bFind = true;
			   m_trackType = TRACK_SMALL;
		   }
		   break;
	case 2:if(m_mapVcBigTrackPoint.find(fish_track_id) != m_mapVcBigTrackPoint.end())
		   {
			   bFind = true;
			   m_trackType = TRACK_BIG;
		   }
		   break;
	case 3: if(m_mapVcTaskTrackPoint.find(fish_track_id) != m_mapVcTaskTrackPoint.end())
			{
				bFind = true;
				m_trackType = TRACK_TASK;
			}
			break;
	default:
		break;
	}
	if(!bFind)
	{
		m_trackType = TRACK_UNKNOW;
	}

	fish_FangXiang = fanxiang;
	if(fish_FangXiang)
	{
		fish_track_index = 0;	
	}else
	{
		fish_track_index = GetTrackPointSize();		
	}

	
}

int FishTrack::GetTrackPointSize()
{
	switch (m_trackType)
	{
	case TRACK_UNKNOW:
		break;
	case TRACK_SMALL:
		return m_mapVcSmallTrackPoint[fish_track_id].vTrackPoint.size();
		break;
	case TRACK_BIG:
		return m_mapVcBigTrackPoint[fish_track_id].vTrackPoint.size();
		break;
	case TRACK_TASK:
		return m_mapVcTaskTrackPoint[fish_track_id].vTrackPoint.size();
		break;
	default:
		break;
	}
	
}

TrackPointDef * FishTrack::getNextTrackPoint()
{
	if(fish_FangXiang)
	{
		fish_track_index++;
	}
	else
	{
		fish_track_index--;
	}

	switch (m_trackType)
	{
	case TRACK_UNKNOW:
		return NULL;
		break;
	case TRACK_SMALL:
		{
			if(fish_track_index >= m_mapVcSmallTrackPoint[fish_track_id].vTrackPoint.size() || fish_track_index <= 0)
				return NULL;
			else
				return &(m_mapVcSmallTrackPoint[fish_track_id].vTrackPoint.at(fish_track_index));
		}
		break;
	case TRACK_BIG:
		{
			if(fish_track_index >= m_mapVcBigTrackPoint[fish_track_id].vTrackPoint.size() || fish_track_index <= 0)
				return NULL;
			else
				return &(m_mapVcBigTrackPoint[fish_track_id].vTrackPoint.at(fish_track_index));
		}
		break;
	case TRACK_TASK:
		{
			if(fish_track_index >= m_mapVcTaskTrackPoint[fish_track_id].vTrackPoint.size() || fish_track_index <= 0)
				return NULL;
			else
				return &(m_mapVcTaskTrackPoint[fish_track_id].vTrackPoint.at(fish_track_index));
		}
		break;
	default:
		break;
	}
	
}

void FishTrack::initMap(string kindPage)
{
	//声明要用的变量
	std::string mimi = "mimi.zip"; 
	std::string fullminizip =  FileUtils::getInstance()->getWritablePath()+mimi; 

	//取得mimi.zip里面的.dat文件路径
	char cLujin [50] = {0};
	if(kindPage == "big")
		sprintf(cLujin,"track/big/%s.dat","big");
	if(kindPage == "small")
		sprintf(cLujin,"track/small/%s.dat","small"); 
	if(kindPage == "task")
		sprintf(cLujin,"track/task/%s.dat","task");
 
	ssize_t fZize ;
	unsigned char * DatBuf = NULL;  
	DatBuf =FileUtils::getInstance()->getFileDataFromZip(fullminizip,cLujin,&fZize);//获取.dat文件内容
	char * DatBuf2 = (char *)DatBuf;
 
	char *line;
	int temp = 0;
	char  token[50];
	line = strtok( DatBuf2,"\n");//获取.dat文件内容的每一行
	int index=0;

	while(line[0]!='\n'&&isdigit(line[0]))
	{
		VectorTrackInfo tempVec;
		TrackPointDef tempTrackPoint;
 
		for(int i = 0 ; i < strlen(line) ;i++)//将第一行的数字，以逗号分开分别存进vecTemp.vFishType中
		{
			if((line[i]==','||line[i]=='\r')&&token!=NULL)
			{
				tempVec.vFishType.push_back(atoi(token));
				memset(token,0,sizeof(token));
				temp = 0;
				continue;
			}
			char c = line[i];
			token[temp] = c;
			temp++;
		}
		memset(token,0,sizeof(token));//将token清零
		line = strtok(NULL,"\n");//获取.dat文件的下一行文件

		while(line[0] == '(')//对.dat文件接下来的数据逐行读取,并取得相关数据存入相应变量当中
		{
			if(line == NULL)
				break;
			if (strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0) 
				continue;
			memset(&tempTrackPoint,0,sizeof(TrackPointDef));
			int tempFlag = 0;
			temp = 0;
			if(line[0]=='(')
			{
				for(int i = 1 ; i < strlen(line) ;i++)
				{
					if((line[i]==','||line[i]=='\r')&&token!=NULL)
					{ 
						switch (tempFlag)
						{
						case 0:tempTrackPoint.mPoint.x = atoi(token);break;
						case 1:tempTrackPoint.mPoint.y = atoi(token);;break;
						case 2:tempTrackPoint.dAngleValue = atof(token);break;
						default:
							break;
						}
						memset(token,0,sizeof(token));
						temp = 0;
						tempFlag++;
						continue;
					}

					char c = line[i];
					token[temp] = c;
					temp++;
				}
			}
			tempVec.vTrackPoint.push_back(tempTrackPoint);


			line = strtok(NULL,"\n");//获取.dat文件的下一行文件
			if(line[0] == '?')
			{  
				break;
			}


		}

		if(tempVec.vTrackPoint.size() > 0 && kindPage == "big")
		{
			m_mapVcBigTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)BigTrackIndex[index],(VectorTrackInfo&&)tempVec));
			m_vcBigTrackID.push_back(BigTrackIndex[index]);

		}
		if(tempVec.vTrackPoint.size() > 0 && kindPage == "small")
		{
			m_mapVcSmallTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)SmallTrackIndex[index],(VectorTrackInfo&&)tempVec));
			m_vcSmallTrackID.push_back(SmallTrackIndex[index]);
		}

		if(tempVec.vTrackPoint.size() > 0 && kindPage == "task")
		{
			m_mapVcTaskTrackPoint.insert(make_pair<int,VectorTrackInfo>((int&&)TaskTrackIndex[index],(VectorTrackInfo&&)tempVec));
			m_vcTaskTrackID.push_back(TaskTrackIndex[index]);
		}
		index++;
		if(line[0] == '?')
		{
			break;
		}
	} 
}

void FishTrack::LoadAllTrackData( )
{
	if(m_mapVcSmallTrackPoint.size() == 0)
		initMap("small");
	if(m_mapVcBigTrackPoint.size() == 0)
		initMap("big");
	if(m_mapVcTaskTrackPoint.size() == 0)
		initMap("task");
}

void FishTrack::GetTrackIDByFishType( int iFishType, int iTrackType,vector<int> &vTrackID )
{
	std::map<int,VectorTrackInfo>::iterator pos;
	vTrackID.clear();
	if(iTrackType == TRACK_SMALL)
	{
		for (pos=m_mapVcSmallTrackPoint.find(1000); pos!=m_mapVcSmallTrackPoint.find(3000);pos++)   //调控随机小鱼轨迹的范围
		{
			bool isVal = true;
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					for(int k = 0 ; k < 18 ; k++)
					{
						if(pos->first == NotValible_small[k])
						{	
							isVal = false;
							break;
						}
					}	
					if(isVal)
					{
						vTrackID.push_back(pos->first);
						break;
					}
				}
			}
		} 
	}
	
	if(iTrackType == TRACK_BIG)
	{
		for (pos=m_mapVcBigTrackPoint.find(4000); pos!=m_mapVcBigTrackPoint.find(4521);pos++)   //调控随机打鱼轨迹的范围
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;			
				}
			}
		}
	}

	if(iTrackType == TRACK_TASK)
	{
		for (pos=m_mapVcTaskTrackPoint.find(7000); pos!=m_mapVcTaskTrackPoint.find(7508);pos++)   //调控随机打鱼轨迹的范围
		{
			for (int i=0; i<pos->second.vFishType.size(); i++)
			{
				if (pos->second.vFishType[i] == iFishType)
				{
					vTrackID.push_back(pos->first);
					break;
				}
			}
		}
	}
}

int FishTrack::GetRandTrackID( int iFishType,int iTrackType, const vector<int> &vNoRandTrackID )
{
	vector<int> vTrackID;
	GetTrackIDByFishType(iFishType,iTrackType, vTrackID);
	
	int i,j;
	for (i=0; i<vTrackID.size();)
	{
		for (j=0; j<vNoRandTrackID.size(); j++)
		{
			if (vNoRandTrackID[j] == vTrackID[i])
			{
				vTrackID.erase(vTrackID.begin()+i);
				break;
			}
		}
		if (j == vNoRandTrackID.size())
		{
			i++;
		}
	}

	if (vTrackID.size() == 0)
	{
		return -1;
	}
	else
	{
		int iRandTrackID;
		iRandTrackID = CCRANDOM_0_1()*vTrackID.size()-0.001;
		return vTrackID[iRandTrackID];
	}
}