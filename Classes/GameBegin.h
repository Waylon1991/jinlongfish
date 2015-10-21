#ifndef _GAMEBEGIN_H_
#define _GAMEBEGIN_H_

#include"cocos2d.h" 
 
USING_NS_CC;
using namespace std;
 
class GameBegin : public cocos2d::Layer
{
public:	 
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameBegin);

	virtual bool init(); 
 
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
 
	void startGame();													//开始游戏
private:
	Size visibleSize ;
	Point origin ;
};

#endif

