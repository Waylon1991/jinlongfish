#include "GameHallLayer.h"
#include "GameData.h"
#include "HelloWorldScene.h"
#include "StaticFunc.h"
#include "GameBegin.h"
  
//*****************   大厅场景  *****************************
Scene* GameHallLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameHallLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
 
bool GameHallLayer::init()
{
	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}
 
	visibleSize = Director::getInstance()->getVisibleSize();//获得可视区域的大小
	origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的起始坐标ori
	hall_cur_room = UserDefault::getInstance()->getIntegerForKey("hall_cur_room");

	room_can_touch = true;
	room_rotate_flag = true;
	rightSetStatus = false;
	roomSize = Size(294,349);
	room_pos[0] = 0; room_pos[1] = 1; room_pos[2] = 2;

	int tmp = CCRANDOM_0_1()*10000;
	sprintf(hall_char_tmp,"hall/hall_bg%d.jpg",tmp % 2 + 1);
    auto sprite = Sprite::create(hall_char_tmp);
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite);
 
	//左上角
	auto left_hall = Sprite::createWithSpriteFrameName("common_info_bg.png");
	left_hall->setAnchorPoint(Vec2(0,1));
	left_hall->setScale(static_Scale * 0.9);
	left_hall->setPosition(Vec2(0,visibleSize.height));
	addChild(left_hall);

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
	sprintf(hall_char_tmp,"%d",StaticFunc::getFileData("gameMoney.txt"));
	auto left_hall_jinbi = LabelAtlas::create(hall_char_tmp,"img/atlas_gold.png",36,44,'0');
	left_hall_jinbi->ignoreAnchorPointForPosition(false);
	left_hall_jinbi->setAnchorPoint(Vec2(0,0.5));
	left_hall_jinbi->setPosition(Vec2(152,40));
	left_hall_jinbi->setScale(0.45);
	left_hall->addChild(left_hall_jinbi);

	//***************************右上角**************************
	right_hall = Sprite::createWithSpriteFrameName("common_set_bg.png");
	right_hall->setAnchorPoint(Vec2(1,1));
	right_hall->setScale(static_Scale * 0.9);
	right_hall->setPosition(Vec2(visibleSize.width,visibleSize.height));
	addChild(right_hall,ANNIULAYER+1);

		//菜单设置
	auto right_hall_set_sp = Sprite::createWithSpriteFrameName("common_set.png");
	auto right_hall_set_item = MenuItemSprite::create(right_hall_set_sp,right_hall_set_sp,CC_CALLBACK_0(GameHallLayer::rightSetFunc,this));
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
	
	auto right_hall_item_1 = MenuItemSprite::create(right_hall_sp_1,right_hall_sp_1,CC_CALLBACK_0(GameHallLayer::rightAboutFunc,this));
	auto right_hall_item_2 = MenuItemSprite::create(right_hall_sp_2,right_hall_sp_2,CC_CALLBACK_0(GameHallLayer::rightSoundFunc,this));
	auto right_hall_item_3 = MenuItemSprite::create(right_hall_sp_3,right_hall_sp_3,CC_CALLBACK_0(GameHallLayer::rightBaikeFunc,this));
	auto right_hall_item_4 = MenuItemSprite::create(right_hall_sp_4,right_hall_sp_4,CC_CALLBACK_0(GameHallLayer::rightFankuiFunc,this));
	auto right_hall_item_5 = MenuItemSprite::create(right_hall_sp_5,right_hall_sp_5,CC_CALLBACK_0(GameHallLayer::rightExitFunc,this));

	auto right_hall_menu = Menu::create(right_hall_item_1,right_hall_item_2,right_hall_item_3,right_hall_item_4,right_hall_item_5,nullptr);
	right_hall_menu->alignItemsHorizontallyWithPadding(28);
	right_hall_menu->setPosition(Vec2(right_hall->getContentSize().width/2 ,  right_hall->getContentSize().height *0.6));
	right_hall->addChild(right_hall_menu);

	right_hall->runAction(Sequence::create( MoveBy::create(1.0f,Vec2(0,80 * static_Scale)),CCCallFunc::create([&]{right_set_menu->setEnabled(true);}),nullptr));
 
	//***********************************中间房间**************************************
	for(int i = 0 ; i < 3 ; i++ )
	{
		sprintf(hall_char_tmp,"hall_room%d_a.png",i + 1);
		auto room_sp = Sprite::createWithSpriteFrameName(hall_char_tmp);
		room_sp->setScale(MinScale);
		room_sp->setPosition(Vec2(visibleSize.width * (i * 0.3 + 0.2) , visibleSize.height / 2));
		addChild(room_sp,ANNIULAYER,1);

		if(i == 1)
		{
			room_sp->setScale(MaxScale);
			sprintf(hall_char_tmp,"hall_room%d_l.png",i + 1);
			room_sp->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}

		room_vec.pushBack(room_sp);
	}
	lightRoom(hall_cur_room);
	
	//************************************底部******************************************
	auto db_tuopan = Sprite::createWithSpriteFrameName("common_dbbg.png");
		db_tuopan->setAnchorPoint(Vec2(0.5,0));
		db_tuopan->setScale(static_Scale);
		db_tuopan->setPosition(Vec2(visibleSize.width * 0.5 , 0));
		addChild(db_tuopan,ANNIULAYER,1);

	for(int i = 0 ; i < 5 ; i++)
	{
		sprintf(hall_char_tmp,"hall_item_%d.png",i + 1);
		auto dibu_sp = Sprite::createWithSpriteFrameName(hall_char_tmp);
		auto dibu_item = MenuItemSprite::create(dibu_sp,dibu_sp,CC_CALLBACK_1(GameHallLayer::dibuFunc,this));
		dibu_item->setScale(0.9);
		dibu_item->setTag(i + 1);
		auto dibu_menu = Menu::create(dibu_item,nullptr);
		dibu_menu->setPosition(Vec2(visibleSize.width * (2*i + 1) * 0.1 , 58));
		addChild(dibu_menu,1);
	}

	//添加触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameHallLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameHallLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameHallLayer::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//添加键盘事件
	EventListenerKeyboard* kblsnr = EventListenerKeyboard::create(); 
	kblsnr->onKeyReleased = CC_CALLBACK_2(GameHallLayer::onKeyReleased, this); 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this); 
 

	return true;
} 
 
void GameHallLayer::lightRoom(int i)
{
	float tmp_x1 = room_vec.at(i)->getPositionX();
	float tmp_time = (abs(tmp_x1 - visibleSize.width / 2) / (visibleSize.width * 0.3));
	tmp_time = tmp_time * 0.5f;

	if(room_pos[i] == 1)
	{
		room_can_touch = false;
		hall_cur_room = i;
		UserDefault::getInstance()->setIntegerForKey("hall_cur_room",hall_cur_room);
		UserDefault::getInstance()->flush();

		room_vec.at(i)->setZOrder(10);
		room_pos[i] = 1;

		auto act_11 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.5 , visibleSize.height/2));
		auto act_12 = ScaleTo::create(tmp_time,MaxScale);
		auto spa_11 = Spawn::create(act_11 ,act_12,nullptr );
		room_vec.at(i)->runAction(Sequence::create(
			spa_11,
			CCCallFunc::create([&]{
				sprintf(hall_char_tmp,"hall_room%d_l.png",hall_cur_room + 1);
				log("hall_char_tmp = %s , hall_cur_room = %d",hall_char_tmp,hall_cur_room);
				room_vec.at(hall_cur_room)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));

		room_vec.at((i+2) % 3)->setZOrder(1);
		room_pos[(i+2) % 3] = 0;
		auto act_21 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.2 , visibleSize.height/2));
		auto act_22 = ScaleTo::create(tmp_time,MinScale);
		auto spa_21 = Spawn::create(act_21 ,act_22,nullptr );
 
		room_vec.at((i+2) % 3)->runAction(Sequence::create(
			spa_21,
			CCCallFunc::create([&]{
				room_can_touch = true;
				sprintf(hall_char_tmp,"hall_room%d_a.png",(hall_cur_room+2) % 3 + 1);
				room_vec.at((hall_cur_room+2) % 3)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));

		room_vec.at((i+1) % 3)->setZOrder(5);
		room_pos[(i+1) % 3] = 2;
		auto act_31 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.8 , visibleSize.height/2));
		auto act_32 = ScaleTo::create(tmp_time,MinScale);
		auto spa_31 = Spawn::create(act_31 ,act_32,nullptr );
		room_vec.at((i+1) % 3)->runAction(Sequence::create(
			spa_31,
			CCCallFunc::create([&]{
				sprintf(hall_char_tmp,"hall_room%d_a.png",(hall_cur_room+1) % 3 + 1);
				room_vec.at((hall_cur_room+1) % 3)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));
	}else if(room_pos[i] == 0)
	{
		room_can_touch = false;
		hall_cur_room = i;
		UserDefault::getInstance()->setIntegerForKey("hall_cur_room",hall_cur_room);
		UserDefault::getInstance()->flush();

		room_vec.at(i)->setZOrder(10);
		room_pos[i] = 1;

		auto act_11 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.5 , visibleSize.height/2));
		auto act_12 = ScaleTo::create(tmp_time,MaxScale);
		auto spa_11 = Spawn::create(act_11 ,act_12,nullptr );
		room_vec.at(i)->runAction(Sequence::create(
			spa_11,
			CCCallFunc::create([&]{
				sprintf(hall_char_tmp,"hall_room%d_l.png",hall_cur_room + 1);
				log("hall_char_tmp = %s , hall_cur_room = %d",hall_char_tmp,hall_cur_room);
				room_vec.at(hall_cur_room)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));

		room_vec.at((i+2) % 3)->setZOrder(1);
		room_pos[(i+2) % 3] = 0;
		auto act_21 = MoveTo::create(tmp_time/2,Vec2(visibleSize.width * 0.5 , visibleSize.height/2));
		auto act_22 = ScaleTo::create(tmp_time/2,0.1);
		auto spa_21 = Spawn::create(act_21 ,act_22,nullptr );

		auto act_23 = MoveTo::create(tmp_time/2,Vec2(visibleSize.width * 0.2 , visibleSize.height/2));
		auto act_24 = ScaleTo::create(tmp_time/2,MinScale);
		auto spa_22 = Spawn::create(act_23 ,act_24,nullptr );

		room_vec.at((i+2) % 3)->runAction(Sequence::create(
			spa_21,spa_22,
			CCCallFunc::create([&]{
				room_can_touch = true;
				sprintf(hall_char_tmp,"hall_room%d_a.png",(hall_cur_room+2) % 3 + 1);
				room_vec.at((hall_cur_room+2) % 3)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));

		room_vec.at((i+1) % 3)->setZOrder(5);
		room_pos[(i+1) % 3] = 2;
		auto act_31 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.8 , visibleSize.height/2));
		auto act_32 = ScaleTo::create(tmp_time,MinScale);
		auto spa_31 = Spawn::create(act_31 ,act_32,nullptr );
		room_vec.at((i+1) % 3)->runAction(Sequence::create(
			spa_31,
			CCCallFunc::create([&]{
				sprintf(hall_char_tmp,"hall_room%d_a.png",(hall_cur_room+1) % 3 + 1);
				room_vec.at((hall_cur_room+1) % 3)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));
	}else
	{
		room_can_touch = false;
		hall_cur_room = i;
		UserDefault::getInstance()->setIntegerForKey("hall_cur_room",hall_cur_room);
		UserDefault::getInstance()->flush();

		room_vec.at(i)->setZOrder(10);
		room_pos[i] = 1;

		auto act_11 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.5 , visibleSize.height/2));
		auto act_12 = ScaleTo::create(tmp_time,MaxScale);
		auto spa_11 = Spawn::create(act_11 ,act_12,nullptr );
		room_vec.at(i)->runAction(Sequence::create(
			spa_11,
			CCCallFunc::create([&]{
				sprintf(hall_char_tmp,"hall_room%d_l.png",hall_cur_room + 1);
				log("hall_char_tmp = %s , hall_cur_room = %d",hall_char_tmp,hall_cur_room);
				room_vec.at(hall_cur_room)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));

		room_vec.at((i+2) % 3)->setZOrder(5);
		room_pos[(i+2) % 3] = 0;
 
		auto act_23 = MoveTo::create(tmp_time,Vec2(visibleSize.width * 0.2 , visibleSize.height/2));
		auto act_24 = ScaleTo::create(tmp_time,MinScale);
		auto spa_22 = Spawn::create(act_23 ,act_24,nullptr );

		room_vec.at((i+2) % 3)->runAction(Sequence::create(
			spa_22,
			CCCallFunc::create([&]{
				room_can_touch = true;
				sprintf(hall_char_tmp,"hall_room%d_a.png",(hall_cur_room+2) % 3 + 1);
				room_vec.at((hall_cur_room+2) % 3)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));

		room_vec.at((i+1) % 3)->setZOrder(1);
		room_pos[(i+1) % 3] = 2;

		auto act_31 = MoveTo::create(tmp_time/2,Vec2(visibleSize.width * 0.5 , visibleSize.height/2));
		auto act_32 = ScaleTo::create(tmp_time/2,0.1);
		auto spa_31 = Spawn::create(act_31 ,act_32,nullptr );

		auto act_33 = MoveTo::create(tmp_time/2,Vec2(visibleSize.width * 0.8 , visibleSize.height/2));
		auto act_34 = ScaleTo::create(tmp_time/2,MinScale);
		auto spa_32 = Spawn::create(act_33 ,act_34,nullptr );

		room_vec.at((i+1) % 3)->runAction(Sequence::create(
			spa_31,spa_32,
			CCCallFunc::create([&]{
				sprintf(hall_char_tmp,"hall_room%d_a.png",(hall_cur_room+1) % 3 + 1);
				room_vec.at((hall_cur_room+1) % 3)->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hall_char_tmp));
		}),nullptr));
	}
	
}

void GameHallLayer::dibuFunc(Object * psender)
{
	StaticFunc::buttonSound();
}

//右上角处理函数
void GameHallLayer::rightAboutFunc()
{
	StaticFunc::buttonSound();
}

void GameHallLayer::rightSoundFunc()
{
	StaticFunc::buttonSound();
}

void GameHallLayer::rightBaikeFunc()
{
	StaticFunc::buttonSound();
}

void GameHallLayer::rightFankuiFunc()
{
	StaticFunc::buttonSound();
}

void GameHallLayer::rightExitFunc()
{
	StaticFunc::buttonSound();

	this->removeAllChildrenWithCleanup(true);
	this->unscheduleAllSelectors();
	this->stopAllActions();

	auto scene = GameBegin::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameHallLayer::rightSetFunc()
{	
	if(rightSetStatus)
	{
		StaticFunc::buttonSound();
		rightSetStatus = false;
		right_set_menu->setEnabled(false);
		right_hall->runAction(Sequence::create( MoveBy::create(0.8f,Vec2(0,80 * static_Scale)),CCCallFunc::create([&]{right_set_menu->setEnabled(true);}),nullptr));
	}else
	{
		StaticFunc::buttonSound();
		rightSetStatus = true;
		right_set_menu->setEnabled(false);
		right_hall->runAction(Sequence::create( MoveBy::create(0.8f,Vec2(0,-80 * static_Scale)),CCCallFunc::create([&]{right_set_menu->setEnabled(true);}),nullptr));
	}
}

void GameHallLayer::editBoxReturn(EditBox *editBox)
{

}

void GameHallLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{    
	switch(keyCode)     
	{     
		//监听返回键        
	case EventKeyboard::KeyCode::KEY_ESCAPE:     
		{
			rightExitFunc();
		}
		break;        
 
	default:break;
	}
}
  
  
//***********继承的函数实现
//滑动板函数
void GameHallLayer::scrollViewDidScroll(extension::ScrollView* view) 
{
}

void GameHallLayer::scrollViewDidZoom(ScrollView* view) 
{
}

void GameHallLayer::scrollViewMoveOver(ScrollView* view)  
{  
 
}

//触摸函数
bool GameHallLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	if(!room_can_touch)
		return true;
	touch_p1 = touch->getLocation();
	return true;
}

void GameHallLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	if(!room_can_touch)
		return;
	 touch_p2 = touch->getLocation();
	 float tmp_x = touch_p2.x - touch_p1.x;
	 float tmp_x_abs = abs(tmp_x);
	 float tmp_scale = tmp_x_abs / 100;
	 if(tmp_scale > 1) tmp_scale = 1;
	 if(tmp_x <= 0 && tmp_x >= -visibleSize.width * 0.3) //向左
	 {
		 room_vec.at(hall_cur_room)->setZOrder(5);
		 room_vec.at(hall_cur_room)->setScale(MaxScale - (MaxScale - MinScale) * tmp_scale);
		 room_vec.at(hall_cur_room)->setPosition(Vec2(visibleSize.width/2 - tmp_x_abs , visibleSize.height/2));

		 room_vec.at((hall_cur_room + 1)% 3)->setZOrder(10);
		 room_vec.at((hall_cur_room + 1)% 3)->setScale(MinScale + (MaxScale - MinScale) * tmp_scale);
		 room_vec.at((hall_cur_room + 1)% 3)->setPosition(Vec2(visibleSize.width * 0.8 - tmp_x_abs , visibleSize.height/2));

		 room_vec.at((hall_cur_room + 2)% 3)->setZOrder(1);
		 room_vec.at((hall_cur_room + 2)% 3)->setScale(MinScale - (MaxScale - MinScale) * tmp_scale);
		 room_vec.at((hall_cur_room + 2)% 3)->setPosition(Vec2(visibleSize.width * 0.2 + tmp_x_abs , visibleSize.height/2));
	 }else  if(tmp_x > 0 && tmp_x < visibleSize.width * 0.3)     //向右
	 {
		 room_vec.at(hall_cur_room)->setZOrder(5);
		 room_vec.at(hall_cur_room)->setScale(MaxScale - (MaxScale - MinScale) * tmp_scale);
		 room_vec.at(hall_cur_room)->setPosition(Vec2(visibleSize.width/2 + tmp_x_abs , visibleSize.height/2));

		 room_vec.at((hall_cur_room + 1)% 3)->setZOrder(1);
		 room_vec.at((hall_cur_room + 1)% 3)->setScale(MinScale - (MaxScale - MinScale) * tmp_scale);
		 room_vec.at((hall_cur_room + 1)% 3)->setPosition(Vec2(visibleSize.width * 0.8 - tmp_x_abs , visibleSize.height/2));
		  
		 room_vec.at((hall_cur_room + 2)% 3)->setZOrder(10);
		 room_vec.at((hall_cur_room + 2)% 3)->setScale(MinScale + (MaxScale - MinScale) * tmp_scale);
		 room_vec.at((hall_cur_room + 2)% 3)->setPosition(Vec2(visibleSize.width * 0.2 + tmp_x_abs , visibleSize.height/2));
	 }else
	 {

	 }
}

void GameHallLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event *unused_event)
{
	if(!room_can_touch)
		return;
	touch_p2 = touch->getLocation();

	if(abs(touch_p2.x - touch_p1.x) < 4 && abs(touch_p2.y - touch_p1.y) < 4)  
	{
		int leftRoom;
		int rightRoom;
		for(int i = 0; i < 3 ; i ++)
		{
			if(room_pos[i] == 0)
				leftRoom = i;
			if(room_pos[i] == 2)
				rightRoom = i;
		}

		float x1 = visibleSize.width * 0.2 - roomSize.width * MinScale / 2;
		float y1 = visibleSize.height * 0.5 - roomSize.height * MinScale / 2 ;

		float x2 = visibleSize.width * 0.5 - roomSize.width * MaxScale / 2;
		float y2 = visibleSize.height * 0.5 - roomSize.height * MaxScale / 2 ;

		float x3 = visibleSize.width * 0.8 - roomSize.width * MinScale / 2;
		float y3 = visibleSize.height * 0.5 - roomSize.height * MinScale / 2 ;

		Rect enter_domain1 = Rect(x1,y1,roomSize.width * MinScale,roomSize.height * MinScale);
		Rect enter_domain2 = Rect(x2,y2,roomSize.width * MaxScale,roomSize.height * MaxScale);
		Rect enter_domain3 = Rect(x3,y3,roomSize.width * MinScale,roomSize.height * MinScale);
		if(enter_domain2.containsPoint(touch_p2))   //如果在当前房间 就进入房间
		{
			StaticFunc::buttonSound();
			StaticFunc::roomType = hall_cur_room;
			log("roomType = %d " , StaticFunc::roomType);
			this->removeAllChildren();
			this->unscheduleAllSelectors();
			this->stopAllActions();
 
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		if(enter_domain1.containsPoint(touch_p2))
		{
			StaticFunc::buttonSound();
			lightRoom(leftRoom);
		}
		if(enter_domain3.containsPoint(touch_p2))
		{
			StaticFunc::buttonSound();
			lightRoom(rightRoom);
		}

	}else if(touch_p2.x - touch_p1.x > 30)
	{
		//向右划
		StaticFunc::buttonSound();
		lightRoom((hall_cur_room+2) % 3);
	}else if(touch_p2.x - touch_p1.x < -30)
	{
		//向左划
		StaticFunc::buttonSound();
		lightRoom((hall_cur_room+1) % 3);
	}else
	{
		//并没有冻
		StaticFunc::buttonSound();
		lightRoom(hall_cur_room);
	}
	log("touchesEnded");
}

//****************预约函数
void GameHallLayer::update(float dt)
{
	 
}
 