#ifndef __GUN__
#define __GUN__

#include "cocos2d.h"
USING_NS_CC;

const float GUN_HEIGHT_BI = 0.2;
const int GUN_TYPE_MAX = 15;
const int BEILV_TYPE[15] = {1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000};
class Gun : public Node
{
public:
	static Gun * create(int type);
	virtual bool init(int type);

	void setType(int type);							//切换炮的时候调用
	void shootBy(float angle);						//调整炮的方向和动作
	Size getContentSize();							//返回节点大小

	void changeFever(int i);						//变身技能炮  1 天火 2 冰封 3 导弹
	void changeFeverOver();							//变身结束  
 
	Sprite * _cannon;								//炮台
	Sprite * _cannon_gun;							//炮管

	Sprite * _cannon_fire1;							//炮火1
	Sprite * _cannon_fire2;							//炮火2
	Sprite * _cannon_fire3;							//炮火3

	Sprite * _cannon_beilv;							//炮倍率
	Label  * _cannon_beilv_label;					//倍率标签 
	
	Menu * qie_pao_menu;							//菜单项
	void jia_pao_fun();								//加炮
	void jian_pao_fun();							//减炮

	int _gunType;									//炮的类型
	float g_height;									//节点高度
	float g_width;
	bool can_play_sound;							//是否可以播放音效

private:
	char gun_tmp_char[30];	
	Vec2 fire_pos_array[15][3];						//炮火的位置数组
	
	int soundIndex;									//播放音效索引
 
};
#endif