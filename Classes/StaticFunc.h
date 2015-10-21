#ifndef _STATICFUNC_
#define _STATICFUNC_
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
 
#define FISHLAYER 10
#define ANNIULAYER 100
#define TISHILAYER 1000

const float static_Scale = 1;
const string word_Kind = "Arial";
class StaticFunc 
{
public:
	//*********�������**************
	static int playSound(string soundPath);								//��������
	static void buttonSound();											//��ť�������
	static void playMusic(int cType = 0);								//��������
	static void stopMusic();											//��������

	static bool canPlaySound;											//�Ƿ񲥷�����
	static bool canPlayMusic;											//�Ƿ񲥷�����
	static int  musicNum;	
 
	static void setFileData(string tmpPath,int tmpIntData);				//д�ļ�����
	static int getFileData(string tmpPath);								//���ļ�����

	static bool isCollision(Vec2 circle , int radius , Rect box);		//���Բ��������Ƿ���ײ

	static int roomType;												//��ǰ�������� 0 1 2

	static bool isBFing;				//����״̬
	static bool isJSing;				//����״̬

	static bool isTHing;				//���״̬
	static float TH_cdtime;				//���cdʱ��
	static float TH_cdtime_cha;			//���cdʱ��cha

	static bool isZDing;				//ը��״̬
private:
 
};

#endif

