#ifndef __CONTROLLAYER__
#define __CONTROLLAYER__

#include "cocos2d.h"
#include "FishLayer.h"
#include "Gun.h"
#include "bullet.h"
#include "Fish.h"

USING_NS_CC;
 
const int Max_Bullet_Num = 100;
const int Bullet_Speed = 12;
const int bullet_type[15] = {1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000};
struct CollisionInfo
{
	int			fish_pos;		//容器中鱼的位置
	int			bullet_pos;		//容器中子弹的位置
};

class ControlLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(ControlLayer);
    virtual bool init();
	void init_shuzhi();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	//自定义事件
	void cancle_fapao();						//取消自动发炮	

	void random_coin(Vec2 point,int beilv,int bulletType);		//随机金币
 
	void update(float dt);						//调度器

	void updateBullets();						//更新子弹
	int bullet_size;							//子弹的数量

	void checkBulletAndFishes();				//检测鱼和子弹的碰撞
	CollisionInfo judgeing_fish_info;			//发生碰撞的子弹和鱼的对应信息
	Bullet * tmpBullet;							//储存碰撞时子弹的信息
	Fish   * tmpFish;							//储存碰撞时鱼的信息

	//四大技能按钮事件
	void jineng_call_1();
	void jineng_call_2();
	void jineng_call_3();
	void jineng_call_4();
	
private:
	Size visibleSize;
	FishLayer * fishLayer;					//鱼游动层
	Vector <Bullet *> my_bullets;			//子弹容器
	vector <int> my_delete_bullets;			//该删除的子弹index容器
	Gun *       myGun;						//武器node

	Vec2 pos_origin;
	Vec2 pos_begin;							//开始点击的位置
	bool is_touching;						//是否正在点击
	float dit_time;							//距离上次点击时间

	char cont_tmp_char1[50];
	char cont_tmp_char2[100];
	int  cont_tmp_int;						//子弹边界
	int  cont_jinbi_tmp;					//当前金币倍数
	int  cont_bullet_tmp;					//当前zidan倍数

	//四大技能按钮
	MenuItemSprite * jineng_icon_1;		//冰封
	MenuItemSprite * jineng_icon_2;		//急速导弹
	MenuItemSprite * jineng_icon_3;		//天火
	MenuItemSprite * jineng_icon_4;		//深海炸弹

	vector <Vec2> tianhuo_pos;			//天火容器
	float tianhuo_pos_cd;				//天火容器cd
};

#endif  