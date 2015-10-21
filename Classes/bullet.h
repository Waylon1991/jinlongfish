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

	int checkBulletCollision();					//��⵱ǰ�ӵ��Ƿ���ǽ����ײ������ײ�򷵻�1 2 3 4�����򷵻�0

	Sprite * _bulletSprite;						//��Ľڵ�
 
	float bullet_type;							//�ӵ�������
	float bullet_width;							//�ӵ��Ŀ��
	float bullet_hight;							//�ӵ��ĸ߶�

	float bullet_angle;							//�ӵ��ĽǶ�
	float m_iX;									//X����λ�ã�ͼƬ���ĵ�
	float m_iY;									//Y����λ�ã�ͼƬ���ĵ�
 
	bool bDead;									//�ӏ��Ƿ�����
 
private:
	char bullet_tmp_char[30];
	Size visibleSize;
};
#endif