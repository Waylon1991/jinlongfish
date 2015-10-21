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
	//��������
	static cocos2d::Scene * createScene();
	virtual bool init();              //��ʼ��
	CREATE_FUNC(GameHallLayer);		  //������
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	//ScrollView�б���ʵ�ֵ�2���麯������
	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);
	virtual void scrollViewMoveOver(ScrollView* view) ;
 
	//�����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
 
	//ԤԼ����
	void update(float dt);

	//���ϽǴ����¼�
	void rightAboutFunc();
	void rightSoundFunc();
	void rightBaikeFunc();
	void rightFankuiFunc();
	void rightExitFunc();

	void rightSetFunc();

	//�������¼�
	void lightRoom(int i);  //ȡֵ  0 1 2

	//�ײ������¼�
	void dibuFunc(Object * psender);

private:
	Size visibleSize;
	Size roomSize;
	Point origin;

	Point touch_p1;						//begin pos
	Point touch_p2;						//end pos

	Vector <Sprite * > room_vec;		//����ľ���
	int room_pos[3];					//�����λ�����
	char hall_char_tmp[100];
 
	Sprite * right_hall;				//���ϽǱ���
	Menu * right_set_menu;				//���Ͻ�����

	bool rightSetStatus;				//�˵��� �Ƿ�����
	int hall_cur_room;					//��ǰ��������к�
	bool room_rotate_flag;				//������ת����  Ĭ������
	bool room_can_touch;				//���䴥������ Ĭ�Ͽ���
};
#endif