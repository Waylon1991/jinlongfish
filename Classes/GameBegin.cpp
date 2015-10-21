#include "GameBegin.h"    
#include "GameData.h"
#include "StaticFunc.h"
#include "GameHallLayer.h"
 
Scene* GameBegin::createScene()
{
	auto scene = Scene::create();
	auto layer =  GameBegin::create() ;
	scene->addChild(layer);

	return scene;
}

bool GameBegin::init()
{
	// 1. super init first
	if ( !Layer::init() )	
	{
		return false;
	}
	srand(time(NULL));
  
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
 
	UserDefault::getInstance()->setIntegerForKey("firstLogin",0);
	if(UserDefault::getInstance()->getIntegerForKey("firstLogin") == 0)
	{
		StaticFunc::setFileData("gameMoney.txt",7777777);
		StaticFunc::setFileData("vipLevel.txt",4);
		UserDefault::getInstance()->setIntegerForKey("firstLogin",1);
		UserDefault::getInstance()->setIntegerForKey("hall_cur_room",0);  // 0 1 2
	}

	StaticFunc::stopMusic();
	StaticFunc::playMusic(0);
 
	//±³¾°
	auto begin = Sprite::create("begin/begin_bg.png");
	begin->setPosition(Vec2(visibleSize/2));
	addChild(begin);

	//logo
	auto logo = Sprite::create("begin/begin_logo.png");
	logo->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.75));
	logo->setScale(4);
	addChild(logo);

	logo->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2f,0.9),CCCallFunc::create([&]{StaticFunc::playSound("music/begin_logo.mp3");}),nullptr),ScaleTo::create(0.05f,0.94),ScaleTo::create(0.05f,0.9),ScaleTo::create(0.05f,0.92),ScaleTo::create(0.05f,0.9),nullptr));

	auto logo1 = Sprite::create("begin/begin_logo.png");
	logo1->setPosition(Vec2(visibleSize.width/2 , visibleSize.height * 0.75));
	logo1->setVisible(false);
	addChild(logo1);

	logo1->runAction(Sequence::create(DelayTime::create(0.2f),Show::create(), Spawn::create(ScaleTo::create(0.2f,4),FadeOut::create(0.2f),nullptr),nullptr));

	//²Ëµ¥
	auto item = MenuItemImage::create("begin/begin_button.png","begin/begin_button.png",CC_CALLBACK_0(GameBegin::startGame,this));
	item->setScale(static_Scale);
	auto menu = Menu::create(item,nullptr);
	menu->setPosition(Vec2(visibleSize.width * 0.5 , visibleSize.height * 0.25));
	addChild(menu);


	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameBegin::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameBegin::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameBegin::onTouchEnded,this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	EventListenerKeyboard* kblsnr = EventListenerKeyboard::create(); 
	kblsnr->onKeyReleased = CC_CALLBACK_2(GameBegin::onKeyReleased, this); 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kblsnr, this); 
 
	return true;
}

void GameBegin::startGame()
{
	StaticFunc::buttonSound();
 
	this->removeAllChildrenWithCleanup(true);
	this->stopAllActions();
	this->unscheduleAllSelectors();

	auto scene = GameHallLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}
  
void GameBegin::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{   
	StaticFunc::buttonSound();
	switch(keyCode)     
	{     
		//¼àÌý·µ»Ø¼ü        
	case EventKeyboard::KeyCode::KEY_ESCAPE:     
		Director::getInstance()->end();           
		break;        
		//¼àÌýmenu¼ü   
	case EventKeyboard::KeyCode::KEY_MENU:   
		break;   
	}
}

bool GameBegin::onTouchBegan(Touch* touch, Event* event) 
{  
	return true;
}

void GameBegin::onTouchEnded(Touch* touch, Event* event)
{

}	

void GameBegin::onTouchMoved(Touch* touch, Event* event)
{
}