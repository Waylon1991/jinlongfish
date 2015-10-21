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

	//������
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
 
	//��ʼ������
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
	if(m_iX >= visibleSize.width - 6 && m_iX <= visibleSize.width + 6 && m_iY >= 0)  //���ұ߷�����ײ
	{
		return 1;
	}
	if(m_iX <= visibleSize.width  && m_iY > visibleSize.height - 6 && m_iY < visibleSize.height + 6)  //���ϱ߷�����ײ
	{
		return 2;
	}
	if(m_iX >= -6 && m_iX <= 6  && m_iY <= visibleSize.height)  //����߷�����ײ
	{
		return 3;
	}
	if(m_iX >= 0 && m_iY <= 6 && m_iY >= -6)  //���±߷�����ײ
	{
		return 4;
	}
	if(m_iX > 0 &&  m_iX < visibleSize.width && m_iY > 0 && m_iY < visibleSize.height)
	{
		return 0;			//δ����ײ
	}
	return -1;			//���� �����
}
 