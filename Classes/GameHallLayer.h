#ifndef _GAME_HALL_H
#define _GAME_HALL_H

#include "cocos2d.h"
#include "cocos-ext.h"
 
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std; 

const float MinScale = 0.75;
const float MaxScale = 0.95;
 
class GameHallLayer : public cocos2d::Layer, public ScrollViewDelegate, public EditBoxDelegate
{
public:
	//创建场景
	static cocos2d::Scene * createScene();
	virtual bool init();              //初始化
	CREATE_FUNC(GameHallLayer);		  //创建层
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	//ScrollView中必须实现的2个虚函数方法
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
	virtual void scrollViewMoveOver(ScrollView* view) ;
 
	//触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
 
	//预约函数
	void update(float dt);

	//右上角处理事件
	void rightAboutFunc();
	void rightSoundFunc();
	void rightBaikeFunc();
	void rightFankuiFunc();
	void rightExitFunc();

	void rightSetFunc();

	//换房间事件
	void lightRoom(int i);  //取值  0 1 2

	//底部处理事件
	void dibuFunc(Object * psender);

private:
	Size visibleSize;
	Size roomSize;
	Point origin;

	Point touch_p1;						//begin pos
	Point touch_p2;						//end pos

	Vector <Sprite * > room_vec;		//房间的精灵
	int room_pos[3];					//房间的位置序号
	char hall_char_tmp[100];
 
	Sprite * right_hall;				//右上角背景
	Menu * right_set_menu;				//右上角设置

	bool rightSetStatus;				//菜单项 是否缩起
	int hall_cur_room;					//当前房间号序列号
	bool room_rotate_flag;				//房间旋转方向  默认向右
	bool room_can_touch;				//房间触摸开关 默认开启
};
#endif