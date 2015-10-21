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
	
	//�Զ����¼�
	void refrashCoin(EventCustom* event);
 
	//���ϽǴ����¼�
	void rightAboutFunc();
	void rightSoundFunc();
	void rightBaikeFunc();
	void rightFankuiFunc();
	void rightExitFunc();

	void rightSetFunc();
 
	void sche_bgmusic(float dt);
private:
	char scene_char_tmp[100];
	Sprite * right_hall;				//���ϽǱ���
	Menu * right_set_menu;				//���Ͻ�����

	LabelAtlas * left_scene_jinbi;		//���

	Size visibleSize;
	Vec2 origin;

	bool rightSetStatus;				//�˵��� �Ƿ�����
 
};

#endif // __HELLOWORLD_SCENE_H__
