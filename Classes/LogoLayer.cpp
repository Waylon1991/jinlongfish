#include "LogoLayer.h"  
#include "GameData.h"
#include "GameBegin.h"
#include "StaticFunc.h"
#include "SimpleAudioEngine.h"
#include "StaticData.h"
#include "FishTrack.h"
 
Scene* LogoLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LogoLayer::init()
{
 
	if ( !Layer::init() )	
	{
		return false;
	}
 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	xulie = 0;

	auto LogoBack = Sprite::create("begin/logopng.png");
	LogoBack->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	addChild(LogoBack);
  
	schedule(schedule_selector(LogoLayer::updataDisplay), 0.01f);
	cocos2d::log("init end");
	return true;
}
 
void LogoLayer::updataDisplay(float dt)
{
	cocos2d::log("updataDisplay start");
	if(xulie == 0)
	{
		//通过精灵缓存帧对象 添加 gamehall 所需的资源 
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/scene1.plist","scene/scene1.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/pao.plist","scene/pao.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/fishlist.plist","scene/fishlist.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene/fishbosslist.plist","scene/fishbosslist.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hall/gamehall.plist","hall/gamehall.png"); 
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/common.plist","common/common.png"); 	
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/common1.plist","common/common1.png");
	}else if(xulie == 1)
	{
		load_Animate_re();
	}
	else if(xulie == 2)
	{
		load_sound_re();
	}
	else if(xulie == 3)
	{
		load_particle();
	}
	else if(xulie == 4)
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 

	std::string mimi = "mimi.zip"; 
	std::string mimiwritelujin =  FileUtils::getInstance()->getWritablePath()+mimi; 
	std::string mimiziplujin = FileUtils::getInstance()->fullPathForFilename("mimi.zip");

	Data data = FileUtils::getInstance()->getDataFromFile(mimiziplujin);
	if (!data.isNull())
	{
		cocos2d::log("datehave");
	} 


	//从zip中读取图片数据 
	FILE *fpTemp = fopen(mimiwritelujin.c_str(),"r");
	if(fpTemp)
	{ 
 
		fclose(fpTemp);

	}
	else 
	{ 
		unsigned long len = 0;
		unsigned char *datazip = NULL;
		datazip = (unsigned char*)malloc(sizeof(unsigned char) * data.getSize());
		memcpy(datazip, data.getBytes(),  data.getSize());
		if(datazip != NULL)
		{
			cocos2d::log("zipcpy");

			FILE *fp = fopen(mimiwritelujin.c_str(),"w+");
			fwrite(datazip,sizeof(char), data.getSize(),fp);
			fclose(fp);
			delete []datazip;
			datazip = NULL; 
		} 

	} 

#endif 
	}
	else if(xulie == 5)
	{
		FishTrack::LoadAllTrackData(); 
		//FishScript::LoadAllScriptData();
		//FishLineup::LoadAllFishLieupData();
		//FishRandSwatch::LoadAllRandSwatchData();
	}else
	{
		this->removeAllChildrenWithCleanup(true);
		this->unscheduleAllSelectors();

		Scene* scene = GameBegin::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	xulie++;
	cocos2d::log("updataDisplay end");
}

void LogoLayer::load_Animate_re()
{
	Vector<SpriteFrame*> sp_vec;  

	////动画加载模版
	//天火动画
	if(AnimationCache::getInstance()->getAnimation("jineng_tianhuo") == NULL)
	{ 
		sp_vec.clear(); 
		for(int j = 0;j < 18;j++)	
		{ 
			char cTempFishSprite[30];
			sprintf(cTempFishSprite,"tianhuo (%d).png" ,j + 1); 
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
			sp_vec.pushBack(spriteFrame); 
		}
		auto animation = Animation::createWithSpriteFrames(sp_vec);
		animation->setDelayPerUnit(0.08f);  
		AnimationCache::getInstance()->addAnimation(animation, "jineng_tianhuo");  
	}

	//金币旋转动画
	if(AnimationCache::getInstance()->getAnimation("jinbi_zhuan") == NULL)
	{ 
		sp_vec.clear(); 
		for(int j = 0;j < 5;j++)	
		{ 
			char cTempFishSprite[30];
			sprintf(cTempFishSprite,"jinbi_%d.png" ,j + 1); 
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
			sp_vec.pushBack(spriteFrame); 
		}
		auto animation = Animation::createWithSpriteFrames(sp_vec);
		animation->setDelayPerUnit(0.08f);  
		AnimationCache::getInstance()->addAnimation(animation, "jinbi_zhuan");  
	}

	//金币闪光动画
	if(AnimationCache::getInstance()->getAnimation("jinbi_shan") == NULL)
	{ 
		sp_vec.clear(); 
		for(int j = 0;j < 7;j++)	
		{ 
			char cTempFishSprite[30];
			sprintf(cTempFishSprite,"bar_coin1%d.png" ,j + 1); 
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishSprite); 
			sp_vec.pushBack(spriteFrame); 
		}
		auto animation = Animation::createWithSpriteFrames(sp_vec);
		animation->setDelayPerUnit(0.1f);  
		AnimationCache::getInstance()->addAnimation(animation, "jinbi_shan");  
	}

	if(AnimationCache::getInstance()->getAnimation("fish_animation_0") == NULL )//若没有鱼动画，加载每条鱼的动画
	{
		//根据infoplist来加载小鱼的动画
		for (int i=0; i<25; i++)
		{  
			char cTempFishFrame[20];
			sprintf(cTempFishFrame,"fish_%d_num",i);
			int fishFrame = STATIC_DATA_INT(cTempFishFrame); 

			//得到第i+1种鱼的游动动画
			Vector<SpriteFrame*> sp_vec; 
			for(int j = 0;j < fishFrame;j++)
			{ 
				char cTempFishSprite[40];
				sprintf(cTempFishFrame,"fish_%d_%d.png",i,j);  
				SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishFrame); 
				sp_vec.pushBack(spriteFrame); 
			} 
			Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
			fishAnimation->setDelayPerUnit(0.1f);//设置两帧之间的时间间隔

			//添加鱼动画到动画缓冲池中
			char cTempFishAniName[40];
			sprintf(cTempFishAniName,"fish_animation_%d",i);
			AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);


			//得到第i+1种鱼的死动画
			Animation* dfishAnimation = Animation::createWithSpriteFrames(sp_vec);
			dfishAnimation->setDelayPerUnit(0.01f);//设置两帧之间的时间间隔

			//添加死鱼动画到动画缓冲池中
			char dcTempFishAniName[30];
			sprintf(dcTempFishAniName,"dfish_animation_%d",i);
			AnimationCache::getInstance()->addAnimation(dfishAnimation, dcTempFishAniName); 
		} 
		//加载三个boss的动画
		for (int i=1; i<4; i++)
		{  
			char cTempFishFrame[20];
			sprintf(cTempFishFrame,"fish_%d_num",24 + i);
			int fishFrame = STATIC_DATA_INT(cTempFishFrame); 

			//得到第i+1种鱼的游动动画
			Vector<SpriteFrame*> sp_vec; 
			for(int j = 0;j < fishFrame;j++)
			{ 
				char cTempFishSprite[40];
				sprintf(cTempFishFrame,"fish_24_%d_%d.png",i,j);  
				SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cTempFishFrame); 
				sp_vec.pushBack(spriteFrame); 
			} 
			Animation* fishAnimation = Animation::createWithSpriteFrames(sp_vec);
			fishAnimation->setDelayPerUnit(0.1f);//设置两帧之间的时间间隔

			//添加鱼动画到动画缓冲池中
			char cTempFishAniName[40];
			sprintf(cTempFishAniName,"fish_animation_%d",i + 24);
			AnimationCache::getInstance()->addAnimation(fishAnimation, cTempFishAniName);


			//得到第i+1种鱼的死动画
			Animation* dfishAnimation = Animation::createWithSpriteFrames(sp_vec);
			dfishAnimation->setDelayPerUnit(0.01f);//设置两帧之间的时间间隔

			//添加死鱼动画到动画缓冲池中
			char dcTempFishAniName[30];
			sprintf(dcTempFishAniName,"dfish_animation_%d",i + 24);
			AnimationCache::getInstance()->addAnimation(dfishAnimation, dcTempFishAniName); 
		} 
	}	   
}

void LogoLayer::load_sound_re()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/die1.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/die2.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/die3.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/die4.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/die5.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/die6.mp3"); 

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/button1.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/button2.mp3"); 

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shoot1.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shoot2.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shoot3.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shootok11.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shootok12.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shootok13.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shootok21.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shootok22.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shootok23.mp3"); 

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/jiguanyu.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin1.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin2.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin_huode.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin_huode1.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin_huode2.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin_huode3.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/coin_huode4.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/qipao.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/shengji.mp3"); 

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sfx_levelup.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sfx_net.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sfx_slot_appear.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sfx_slot_rolling.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sfx_switch.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/sfx_switch1.mp3"); 

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/begin_logo.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/ice.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/jineng_tianhuo1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/jineng_tianhuo2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/jineng_tianhuo3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/jineng_tianhuo4.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/jineng_tianhuo5.mp3");
}

void LogoLayer::load_particle()
{

}
 