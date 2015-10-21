#ifndef __BULLET__
#define __BULLET__

#include "cocos2d.h"

USING_NS_CC;

class Bullet : public Node
{
public:
	static Bullet * create(int type);
	virtual bool init(int type);

	void setPos(Vec2 pos);
	void setAngel(float angle);

	int checkBulletCollision();					//检测当前子弹是否与墙壁碰撞，若碰撞则返回1 2 3 4，否则返回0

	Sprite * _bulletSprite;						//鱼的节点
 
	float bullet_type;							//子弹的类型
	float bullet_width;							//子弹的宽度
	float bullet_hight;							//子弹的高度

	float bullet_angle;							//子弹的角度
	float m_iX;									//X坐标位置，图片中心点
	float m_iY;									//Y坐标位置，图片中心点
 
	bool bDead;									//子彈是否死了
 
private:
	char bullet_tmp_char[30];
	Size visibleSize;
};
#endif