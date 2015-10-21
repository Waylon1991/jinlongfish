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
	//*********声音相关**************
	static int playSound(string soundPath);								//播放声音
	static void buttonSound();											//按钮点击声音
	static void playMusic(int cType = 0);								//播放音乐
	static void stopMusic();											//播放音乐

	static bool canPlaySound;											//是否播放声音
	static bool canPlayMusic;											//是否播放音乐
	static int  musicNum;	
 
	static void setFileData(string tmpPath,int tmpIntData);				//写文件操作
	static int getFileData(string tmpPath);								//读文件操作

	static bool isCollision(Vec2 circle , int radius , Rect box);		//检测圆形与矩形是否碰撞

	static int roomType;												//当前房间类型 0 1 2

	static bool isBFing;				//冰封状态
	static bool isJSing;				//急速状态

	static bool isTHing;				//天火状态
	static float TH_cdtime;				//天火cd时间
	static float TH_cdtime_cha;			//天火cd时间cha

	static bool isZDing;				//炸弹状态
private:
 
};

#endif

