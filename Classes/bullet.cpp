#include "bullet.h"
#include "StaticData.h"
#include "StaticFunc.h"

Bullet * Bullet::create(int type)  //0-20
{
	auto fish = new Bullet();
	fish->init(type);
	fish->autorelease();
	return fish;
}

bool Bullet::init(int type)
{
	srand(time(NULL));
	visibleSize = Director::getInstance()->getVisibleSize();

	//精灵鱼
	sprintf(bullet_tmp_char,"zd%d.png",type);
	if(StaticFunc::isBFing)
	{
		sprintf(bullet_tmp_char,"bullet_fever_2_2.png");
	}
	if(StaticFunc::isTHing)
	{
		sprintf(bullet_tmp_char,"bullet_fever_1_2.png");
	}
		
	_bulletSprite = Sprite::createWithSpriteFrameName(bullet_tmp_char);
	this->addChild(_bulletSprite);
 
	//初始化数据
	bullet_type = type;
	bDead = false;
 
	m_iX = 0;
	m_iY = 0;
 
	bullet_hight = _bulletSprite->getContentSize().height;
	bullet_width = _bulletSprite->getContentSize().width;
	bullet_angle = 0;
	return true;
}

void Bullet::setPos(Vec2 pos)
{
	this->setPosition(pos);
	m_iX = pos.x;
	m_iY = pos.y;
}

void Bullet::setAngel(float angle)
{
	bullet_angle = angle;
	this->setRotation(angle);
}

int Bullet::checkBulletCollision()
{
	if(m_iX >= visibleSize.width - 6 && m_iX <= visibleSize.width + 6 && m_iY >= 0)  //与右边发生碰撞
	{
		return 1;
	}
	if(m_iX <= visibleSize.width  && m_iY > visibleSize.height - 6 && m_iY < visibleSize.height + 6)  //与上边发生碰撞
	{
		return 2;
	}
	if(m_iX >= -6 && m_iX <= 6  && m_iY <= visibleSize.height)  //与左边发生碰撞
	{
		return 3;
	}
	if(m_iX >= 0 && m_iY <= 6 && m_iY >= -6)  //与下边发生碰撞
	{
		return 4;
	}
	if(m_iX > 0 &&  m_iX < visibleSize.width && m_iY > 0 && m_iY < visibleSize.height)
	{
		return 0;			//未发碰撞
	}
	return -1;			//出界 请清除
}
 