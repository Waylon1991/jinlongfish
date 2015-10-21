#include "HelloWorldScene.h"
#include "ControlLayer.h"
#include "StaticData.h"
#include "GameHallLayer.h"
#include "StaticFunc.h"
#include "GameData.h"
 
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand(time(NULL));
 
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	char hello_tmp_char[100];
	rightSetStatus = false;

	int tmp = CCRANDOM_0_1()*10000;
	sprintf(hello_tmp_char,"scene/map%d.jpg",tmp % 3 + 1);
    auto sprite = Sprite::create(hello_tmp_char);
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite);

	//左上角
	auto left_hall = Sprite::createWithSpriteFrameName("common_info_bg.png");
	left_hall->setAnchorPoint(Vec2(0,1));
	left_hall->setScale(static_Scale * 0.9);
	left_hall->setTag(1);
	left_hall->setPosition(Vec2(0,visibleSize.height));
	addChild(left_hall,ANNIULAYER);

		//遮罩
	auto left_hall_zhe = Sprite::createWithSpriteFrameName("common_touxiang_bg.png");
	left_hall_zhe->setPosition(Vec2(51,65));
	left_hall->addChild(left_hall_zhe);

		//vip
	auto left_hall_vip = Sprite::createWithSpriteFrameName("common_vip_tiao.png");
	left_hall_vip->setAnchorPoint(Vec2(1,0));
	left_hall_vip->setPosition(Vec2(102,16));
	left_hall->addChild(left_hall_vip);

		//name
	auto left_hall_name =  LabelTTF::create(GAME_DATA_STRING("username"),word_Kind,22);
	left_hall_name->setPosition(Vec2(196,88));
	left_hall->addChild(left_hall_name);

		//jinbi icon
	auto left_hall_jinbi_icon = Sprite::createWithSpriteFrameName("bar_coin11.png");
	left_hall_jinbi_icon->setScale(0.4);
	left_hall_jinbi_icon->setPosition(Vec2(129,40));
	left_hall->addChild(left_hall_jinbi_icon);

	auto jinbi_animate = Animate::create(AnimationCache::getInstance()->getAnimation("jinbi_shan"));
	left_hall_jinbi_icon->runAction(RepeatForever::create(Sequence::create(jinbi_animate,DelayTime::create(3.0f),nullptr)));

		//jinbi num
	sprintf(hello_tmp_char,"%d",StaticFunc::getFileData("gameMoney.txt"));
	left_scene_jinbi = LabelAtlas::create(hello_tmp_char,"img/atlas_gold.png",36,44,'0');
	left_scene_jinbi->ignoreAnchorPointForPosition(false);
	left_scene_jinbi->setAnchorPoint(Vec2(0,0.5));
	left_scene_jinbi->setPosition(Vec2(146,40));
	left_scene_jinbi->setScale(0.45);
	left_hall->addChild(left_scene_jinbi);

	//***************************右上角**************************
	right_hall = Sprite::createWithSpriteFrameName("common_set_bg.png");
	right_hall->setAnchorPoint(Vec2(1,1));
	right_hall->setScale(static_Scale * 0.9);
	right_hall->setPosition(Vec2(visibleSize.width,visibleSize.height));
	addChild(right_hall,ANNIULAYER);

		//菜单设置
	auto right_hall_set_sp = Sprite::createWithSpriteFrameName("common_set.png");
	auto right_hall_set_item = MenuItemSprite::create(right_hall_set_sp,right_hall_set_sp,CC_CALLBACK_0(HelloWorld::rightSetFunc,this));
	right_set_menu = Menu::create(right_hall_set_item,nullptr);
	right_set_menu->setPosition(Vec2(379,-52));
	right_set_menu->setEnabled(false);
	right_hall->addChild(right_set_menu,-1);
		
		//菜单选项
	auto right_hall_sp_1 = Sprite::createWithSpriteFrameName("common_about.png");
	auto right_hall_sp_2 = Sprite::createWithSpriteFrameName("common_sound_k.png");
	auto right_hall_sp_3 = Sprite::createWithSpriteFrameName("common_baike.png");
	auto right_hall_sp_4 = Sprite::createWithSpriteFrameName("common_fankui.png");
	auto right_hall_sp_5 = Sprite::createWithSpriteFrameName("common_tuichu.png");
	
	auto right_hall_item_1 = MenuItemSprite::create(right_hall_sp_1,right_hall_sp_1,CC_CALLBACK_0(HelloWorld::rightAboutFunc,this));
	auto right_hall_item_2 = MenuItemSprite::create(right_hall_sp_2,right_hall_sp_2,CC_CALLBACK_0(HelloWorld::rightSoundFunc,this));
	auto right_hall_item_3 = MenuItemSprite::create(right_hall_sp_3,right_hall_sp_3,CC_CALLBACK_0(HelloWorld::rightBaikeFunc,this));
	auto right_hall_item_4 = MenuItemSprite::create(right_hall_sp_4,right_hall_sp_4,CC_CALLBACK_0(HelloWorld::rightFankuiFunc,this));
	auto right_hall_item_5 = MenuItemSprite::create(right_hall_sp_5,right_hall_sp_5,CC_CALLBACK_0(HelloWorld::rightExitFunc,this));

	auto right_hall_menu = Menu::create(right_hall_item_1,right_hall_item_2,right_hall_item_3,right_hall_item_4,right_hall_item_5,nullptr);
	right_hall_menu->alignItemsHorizontallyWithPadding(28);
	right_hall_menu->setPosition(Vec2(right_hall->getContentSize().width/2 ,  right_hall->getContentSize().height *0.6));
	right_hall->addChild(right_hall_menu);

	right_hall->runAction(Sequence::create( MoveBy::create(1.0f,Vec2(0,80 * static_Scale)),CCCallFunc::create([&]{right_set_menu->setEnabled(true);}),nullptr));
 
	//鱼层
	auto layer = ControlLayer::create();
	this->addChild(layer,FISHLAYER);

	sche_bgmusic(0);
	this->schedule(schedule_selector(HelloWorld::sche_bgmusic),60.0f);

	auto mCustomListener = EventListenerCustom::create("REFRASHCOIN",CC_CALLBACK_1(HelloWorld::refrashCoin,this)); 
	_eventDispatcher->addEventListenerWithFixedPriority(mCustomListener,1);
 
    return true;
}
 
//自定义事件 更新金币
void HelloWorld::refrashCoin(EventCustom* event)
{
	auto data = static_cast<char*>(event->getUserData());
	int num = atoi(data);

	int mycoin = StaticFunc::getFileData("gameMoney.txt") + num;
	StaticFunc::setFileData("gameMoney.txt",mycoin);

	sprintf(scene_char_tmp,"%d",mycoin);
	left_scene_jinbi->setString(scene_char_tmp);
 
}

//菜单按钮事件
void HelloWorld::rightAboutFunc()
{
	StaticFunc::buttonSound();
}

void HelloWorld::rightSoundFunc()
{
	StaticFunc::buttonSound();
}

void HelloWorld::rightBaikeFunc()
{
	StaticFunc::buttonSound();
}

void HelloWorld::rightFankuiFunc()
{
	StaticFunc::buttonSound();
}

void HelloWorld::rightExitFunc()
{
	StaticFunc::buttonSound();

	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();
	this->stopAllActions();

	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
	StaticFunc::playMusic(0);
}

void HelloWorld::rightSetFunc()
{
	StaticFunc::buttonSound();
	if(rightSetStatus)
	{
		rightSetStatus = false;
		right_set_menu->setEnabled(false);
		right_hall->runAction(Sequence::create( MoveBy::create(1.0f,Vec2(0,80 * static_Scale)),CCCallFunc::create([&]{right_set_menu->setEnabled(true);}),nullptr));
	}else
	{
		rightSetStatus = true;
		right_set_menu->setEnabled(false);
		right_hall->runAction(Sequence::create( MoveBy::create(1.0f,Vec2(0,-80 * static_Scale)),CCCallFunc::create([&]{right_set_menu->setEnabled(true);}),nullptr));
	}
}
 
void HelloWorld::sche_bgmusic(float dt)
{
	StaticFunc::playMusic(1);
}
 