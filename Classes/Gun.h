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

	void setType(int type);							//�л��ڵ�ʱ�����
	void shootBy(float angle);						//�����ڵķ���Ͷ���
	Size getContentSize();							//���ؽڵ��С

	void changeFever(int i);						//��������  1 ��� 2 ���� 3 ����
	void changeFeverOver();							//�������  
 
	Sprite * _cannon;								//��̨
	Sprite * _cannon_gun;							//�ڹ�

	Sprite * _cannon_fire1;							//�ڻ�1
	Sprite * _cannon_fire2;							//�ڻ�2
	Sprite * _cannon_fire3;							//�ڻ�3

	Sprite * _cannon_beilv;							//�ڱ���
	Label  * _cannon_beilv_label;					//���ʱ�ǩ 
	
	Menu * qie_pao_menu;							//�˵���
	void jia_pao_fun();								//����
	void jian_pao_fun();							//����

	int _gunType;									//�ڵ�����
	float g_height;									//�ڵ�߶�
	float g_width;
	bool can_play_sound;							//�Ƿ���Բ�����Ч

private:
	char gun_tmp_char[30];	
	Vec2 fire_pos_array[15][3];						//�ڻ��λ������
	
	int soundIndex;									//������Ч����
 
};
#endif