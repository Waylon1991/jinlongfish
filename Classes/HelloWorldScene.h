#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#define kSceneLayer 100

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
	
	//自定义事件
	void refrashCoin(EventCustom* event);
 
	//右上角处理事件
	void rightAboutFunc();
	void rightSoundFunc();
	void rightBaikeFunc();
	void rightFankuiFunc();
	void rightExitFunc();

	void rightSetFunc();
 
	void sche_bgmusic(float dt);
private:
	char scene_char_tmp[100];
	Sprite * right_hall;				//右上角背景
	Menu * right_set_menu;				//右上角设置

	LabelAtlas * left_scene_jinbi;		//金币

	Size visibleSize;
	Vec2 origin;

	bool rightSetStatus;				//菜单项 是否缩起
 
};

#endif // __HELLOWORLD_SCENE_H__
