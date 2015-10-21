#include "Fish.h"
#include "SimpleAudioEngine.h"
#include "StaticData.h"
#include "StaticFunc.h"

Fish * Fish::create(int type)  //0-20
{
	auto fish = new Fish();
	fish->init(type);
	fish->autorelease();
	return fish;
}

bool Fish::init(int type)
{
	srand(time(NULL));
	//精灵鱼
	if(type < 25)
	{
		sprintf(fish_tmp_char,"fish_%d_0.png",type);
		fish_type = type;
	}else if(type == 25)
	{
		sprintf(fish_tmp_char,"fish_24_%d_0.png",StaticFunc::roomType + 1);
		fish_type = 25 + StaticFunc::roomType;
	}

	yy_pianyi = Vec2(yy_fish_distance * sin(0) , yy_fish_distance * - cos(0) );

	_fishSprite = Sprite::createWithSpriteFrameName(fish_tmp_char);
	_fishSprite_yy = Sprite::createWithSpriteFrameName(fish_tmp_char);
	_fishSprite_yy->setPosition((Vec2)_fishSprite->getContentSize()/2 + yy_pianyi);
	_fishSprite->addChild(_fishSprite_yy,-1);
	this->addChild(_fishSprite);
 
	sprintf(fish_tmp_char,"fish_animation_%d",fish_type);
	_fishSprite->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(fish_tmp_char))));
  
	//鱼的阴影
	auto shader_program = GLProgram::createWithFilenames("shadow.vsh", "shadow.fsh");
	shader_program->use();
	shader_program->setUniformsForBuiltins();
	_fishSprite_yy->setGLProgram(shader_program);
	_fishSprite_yy->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(fish_tmp_char))));
 
 
	//初始化数据
	bDead = false;
	fish_cur_frame = 0;

	m_iX = 0;
	m_iY = 0;
	m_iXMov = 0;
	m_iYMov = 0;

	sprintf(fish_tmp_char,"weight%d",type);
	fish_width = STATIC_DATA_INT(fish_tmp_char);

	sprintf(fish_tmp_char,"height%d",type);
	fish_hight = STATIC_DATA_INT(fish_tmp_char);
 
	return true;
}
 
bool Fish::CreateTrackFish(Fish* pFish,int iFishType,vector<int>vcLimitTrackIDD)
{
	int iTrackID = -1;																	//由鱼类型找到指定的轨迹	
	int trackType = CCRANDOM_0_1()*2.99 + 1;	//										//隨機一条renwu鱼轨迹

 
	if(iFishType < 13)
	{
		iTrackID = FishTrack::GetRandTrackID(iFishType, 1, vcLimitTrackIDD); 
		trackType = 1;
	}else
	{
		iTrackID = FishTrack::GetRandTrackID(iFishType, 2, vcLimitTrackIDD);		//随机指定鱼的轨迹,返回-1为此鱼没有对应轨迹
		trackType = 2;
	}
	
 
	if(iTrackID == -1)
	{
		return false;
	}
 
	pFish->Track_id = iTrackID;
	if(CCRANDOM_0_1() < 0.5)
		pFish->fish_track.Reset(iTrackID,true,trackType);								//正轨迹
	else
		pFish->fish_track.Reset(iTrackID,false,trackType);								//负轨迹
	return true;
}

bool Fish::updateFishPos()
{ 
	if(_fishSprite->isRunning())
	{
		TrackPointDef *pTrackPt = fish_track.getNextTrackPoint();
		if(pTrackPt)
		{
			Point pPoint = pTrackPt->mPoint + Vec2(m_iXMov,m_iYMov); 
			m_iX = pPoint.x;
			m_iY = pPoint.y;
			fish_angle = pTrackPt->dAngleValue;

			this->setPosition(pPoint);
			this->setRotation(fish_angle);

			float tmp_angle = fish_angle * M_PI / 180;
			yy_pianyi.x = yy_fish_distance * sin(tmp_angle);
			yy_pianyi.y = yy_fish_distance * -cos(tmp_angle);
			_fishSprite_yy->setPosition((Vec2)_fishSprite->getContentSize()/2 + yy_pianyi);

			return true;
		}else
		{
			return false;
		}
	}
}

bool Fish::SetFishInfo(int iFishType,int iTrackID, int iNowTrackIndex )
{
	fish_type = iFishType;
	fish_angle = 0;
	Track_id = iTrackID;

	TrackPointDef *pTrackPt = fish_track.getNextTrackPoint();

	fish_cur_frame = 0;
	m_iX = pTrackPt->mPoint.x;
	m_iY = pTrackPt->mPoint.y;

	if(fish_track.fish_FangXiang)
	{	
		
	}else
	{
		_fishSprite->setFlipX(true);
		_fishSprite->setFlipY(true); 

		_fishSprite_yy->setFlipX(true);
		_fishSprite_yy->setFlipY(true); 	
	}
 
	m_iXMov = 0;
	m_iYMov = 0;
 
	return true;
}
 
bool Fish::ifCatch(int beilv)
{

	float tmpGailv = CCRANDOM_0_1() * 100;
	
	
	
	float tmpTTTT = cFishGailv[fish_type];
 
	if(fish_type == 26 || fish_type == 27)
			tmpTTTT = cFishGailv[25] + 50;
	if(tmpGailv < tmpTTTT)
	{
		if(fish_type < 14)
		{
			int tmp_music = CCRANDOM_0_1() * 5.99 + 1;
			sprintf(fish_tmp_char,"music/die%d.mp3",tmp_music);
			StaticFunc::playSound(fish_tmp_char);
		}

		//执行鱼死动画
		sprintf(fish_tmp_char,"dfish_animation_%d",fish_type);
		_fishSprite->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(fish_tmp_char))));

		return  true;
	}
	return false;
}
