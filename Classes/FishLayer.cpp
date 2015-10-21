#include "FishLayer.h"
#include "FishTrack.h"
#include "StaticFunc.h"
#include <math.h>

bool FishLayer::init()
{
	if( !Layer::init())
	{
		return false;
	}
	init_ShuZhi();
	visibleSize = Director::getInstance()->getVisibleSize();
 
	this->schedule(schedule_selector(FishLayer::updateAddFish_jyw),0.01f);
	this->schedule(schedule_selector(FishLayer::updateFishMove_jyw),0.01f);
	updateGroupFish_jyw(1);
	this->schedule(schedule_selector(FishLayer::updateGroupFish_jyw),10);

	return true;
}

void FishLayer::init_ShuZhi()
{
	srand(time(NULL));
	fish_move_time_tmp = 0;
	add_up_time = 1.0f ;
	add_upall_time = 1.0f;
}

void FishLayer::updateGroupFish_jyw(float dt)
{
	if(m_Fishes.size() < fishMaxNum)
	{
		int g_fish_type;
		float tmp_glv =  CCRANDOM_0_1();
		if(tmp_glv < 0.4) g_fish_type = 0;
		else if(tmp_glv < 0.5) g_fish_type = 1;
		else if(tmp_glv < 0.6) g_fish_type = 2;
		else if(tmp_glv < 0.7) g_fish_type = 3;
		else if(tmp_glv < 0.8) g_fish_type = 4;
		else if(tmp_glv < 0.9) g_fish_type = 5;
		else g_fish_type = 6;

		int g_fish_num = CCRANDOM_0_1() * 5.99 + 5;  //5 - 10

		int g_fish_track_id = FishTrack::GetRandTrackID(g_fish_type,1,track_used);
		bool g_fish_fanxiang ;
		

		if(g_fish_track_id != -1)
		{
			track_used.push_back(g_fish_track_id);
			track_used_num.push_back(0);

			if(CCRANDOM_0_1() < 0.5)
				g_fish_fanxiang = true;									//正轨迹
			else
				g_fish_fanxiang = false;								//负轨迹

			for(int j = 0;j<g_fish_num;j++)
			{
				Fish* fish =Fish::create(g_fish_type); 
				fish->fish_track.Reset(g_fish_track_id,true,1);	
				AddTrackFish(fish,fish->fish_type,fish->Track_id,0); 	
				if(g_fish_num == 5)  //一字型
				{
					fish->m_iXMov = j * 0;
					fish->m_iYMov = j * 25;
				}
				if(g_fish_num == 6)  //O字型
				{
					fish->m_iXMov = zixing_O[j].x;
					fish->m_iYMov = zixing_O[j].y;
				}
				if(g_fish_num == 7)  //L字型
				{
					fish->m_iXMov = zixing_L[j].x;
					fish->m_iYMov = zixing_L[j].y;
				}
				if(g_fish_num == 8)  //V字型
				{
					fish->m_iXMov = zixing_V[j].x;
					fish->m_iYMov = zixing_V[j].y;
				}
				if(g_fish_num == 9)  //U字型
				{
					fish->m_iXMov = zixing_U[j].x;
					fish->m_iYMov = zixing_U[j].y;
				}
				if(g_fish_num == 10)  //E字型
				{
					fish->m_iXMov = zixing_E[j].x;
					fish->m_iYMov = zixing_E[j].y;
				}

				fish->m_iXMov = fish->m_iXMov * 2;
				fish->m_iYMov = fish->m_iYMov * 2;
			} 
		}
	}
}
 
void FishLayer::updateFishMove_jyw(float dt)
{
	if(StaticFunc::isBFing)
		return;
	fish_move_time_tmp += dt;
	if(fish_move_time_tmp >= fish_move_time) // 0.028)
	{  
		if (!m_Fishes.empty()) 
		{
			delete_fish_id.clear();
			for(int i = 0 ; i < m_Fishes.size() ; i++)
			{
				if(m_Fishes.at(i)->bDead == false)
				{  
					if(m_Fishes.at(i)->updateFishPos())
					{

					}else
					{
						delete_fish_id.push_back(i);
					}
				}
			}
			for(int j = 0 ; j < delete_fish_id.size() ;  j++)
			{
				//this->removeChild(m_Fishes.at(delete_fish_id.at(j)));
				m_Fishes.at(delete_fish_id.at(j))->_fishSprite->runAction(FadeOut::create(2.0f));
				m_Fishes.at(delete_fish_id.at(j))->runAction(Sequence::create(DelayTime::create(2.0f),RemoveSelf::create(),nullptr));
				m_Fishes.erase(delete_fish_id.at(j));	
				for(int k = j ; k < delete_fish_id.size(); k ++)
				{
					delete_fish_id.at(k) -- ;
				}
			}
		}  
		fish_move_time_tmp -= 0.024;		
	} 
}

void FishLayer::updateAddFish_jyw(float dt) 
{
	for(int i = 0;i<track_used.size();) //更新已使用的轨迹运行帧数
	{
		track_used_num[i]++;
		if(track_used_num[i] >= 600)//10s以内不随机同一条轨迹
		{
			track_used_num.erase(track_used_num.begin()+i);
			track_used.erase(track_used.begin()+i);
		}
		else
		{
			i++;
		}
	}

	add_up_time += dt;
	if(add_up_time >= add_upall_time )
	{
		add_up_time = 0;

		if(m_Fishes.size() < fishMaxNum)
		{
			for(int j = 0;j<addFishNum;j++)
			{
				float iIndex = CCRANDOM_0_1() * 0.999;  //1~23
				int tmp_a = (sqrt(4*fish_max_type*(fish_max_type + 1)*iIndex + 1) - 1 )/2; // 0 ~ fish_max_type
				int fish_type_t = fish_max_type - tmp_a;	//随机鱼的概率i^2 - i + p * n * (n+1) = 0    n为最大的鱼类型

				Fish* fish =Fish::create(fish_type_t);

				if(fish->CreateTrackFish(fish,fish_type_t,track_used))
				{
					track_used.push_back(fish->Track_id);
					track_used_num.push_back(0);
					AddTrackFish(fish,fish->fish_type,fish->Track_id,0); 	
				}
				else
				{
					log("create guiji fish failed");
				}
			} 
		}
	}
}
 
Fish* FishLayer::AddTrackFish(Fish *pFish,int iFishType,int iTrackID, int iNowFrameIndex)
{
 
	if(pFish != NULL)
	{
		if(pFish->SetFishInfo(iFishType,iTrackID,iNowFrameIndex))
		{
			pFish->setPosition(Vec2(-200,-200));
			this->addChild(pFish,iFishType);			
			m_Fishes.pushBack(pFish); 
		}
	}   
	return pFish;
 }