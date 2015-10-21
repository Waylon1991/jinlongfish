#ifndef _LOGO_LAYER_H_
#define _LOGO_LAYER_H_

#include"cocos2d.h" 
 
USING_NS_CC;
using namespace std;
  
class LogoLayer : public cocos2d::Layer   //用于资源的加载 和 logo的显示
{
public:	 
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LogoLayer);

	virtual bool init(); 
 
	void load_Animate_re();						//加载动画缓存
	void load_sound_re();						//加载声音缓存
	void load_particle();						//加载粒子缓存
 
	void updataDisplay(float dt);
private: 
	int xulie;
};

#endif

