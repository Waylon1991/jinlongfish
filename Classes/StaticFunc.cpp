#include "StaticFunc.h"    
#include "SimpleAudioEngine.h"

bool StaticFunc::canPlaySound = true;
bool StaticFunc::canPlayMusic = true;
 
int StaticFunc::musicNum = 1;
int StaticFunc::roomType = 0;

bool StaticFunc::isBFing = false;
bool StaticFunc::isJSing = false;
bool StaticFunc::isTHing = false;
bool StaticFunc::isZDing = false;

float StaticFunc::TH_cdtime = 0;
float StaticFunc::TH_cdtime_cha = 0;

 
void StaticFunc::buttonSound()
{
	int iTemp = CCRANDOM_0_1()* 100;
	if(iTemp < 25)
	{
		iTemp = 1;
	}
	else if(iTemp < 50)
	{
		iTemp = 1;
	}
	else if(iTemp < 75)
	{
		iTemp = 1;
	}
	else 
	{
		iTemp = 1;
	}
	char cSoundBtn[20]; 
	sprintf(cSoundBtn,"music/button%d.mp3",iTemp);
	playSound(cSoundBtn);
}

//���ļ�����
void StaticFunc::setFileData(string tmpPath,int tmpIntData)
{
	FILE * tmpFile;
	string moneypath;
	char  tmpData[20];
	
	moneypath = FileUtils::getInstance()->getWritablePath() + tmpPath;	
 
	sprintf(tmpData,"%d",tmpIntData);
	//log("setfile : %s",tmpData);
 

	//1.���ļ���
	tmpFile = fopen(moneypath.c_str(),"wb");

	//2.��������д
	//rewind(tmpFile);
	fputs(tmpData,tmpFile);

	//3.�ر��ļ���
	fclose(tmpFile);
}

//���ļ�����
int StaticFunc::getFileData(string tmpPath)
{
	FILE * tmpFile;
	int result = 0 ;
	

	//1.���ļ���
	string moneypath = FileUtils::getInstance()->getWritablePath() + tmpPath.c_str();		;
	tmpFile = fopen(moneypath.c_str(),"rb");
	//log("getFile : %s" , moneypath.c_str());

	//2.�������ݶ�д
	if(tmpFile)
    {
		char  tmpData[20];
		fgets(tmpData,100,tmpFile);
		result = atoi(tmpData);   

    }
	else
	{
		tmpFile = fopen(moneypath.c_str(),"wb");
		 
		string tmpData;
		tmpData = "0";
		result = 0;
		if(tmpPath == "gameMoney.txt")
		{
			tmpData = "1000";
			result = 1000;
		}
		if(tmpPath == "gamePlayerlv.txt")
		{
			tmpData = "1";
			result = 1;
		}
		fputs(tmpData.c_str(),tmpFile);
	}
 
	//3.�ر��ļ���
	fclose(tmpFile);

	return result;
}

int StaticFunc::playSound(string soundPath)
{
	int tmp = 0;
	if(canPlaySound)
	{
		tmp = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundPath.c_str());
	}
	return tmp;
}

void StaticFunc::playMusic(int cType)
{
	//srand(time(NULL));
	if(canPlayMusic )
	{
		musicNum = cType;
		if(cType == 0)						//���Ŵ����ı�������
		{
			int tmp = CCRANDOM_0_1() * 100000;
			if(tmp % 2 == 1)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/hall_music1.mp3",true); 
			}else
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/hall_music2.mp3",true); 
			}
		}else  if(cType == 1)				//���ų�����������
		{
			int tmp = CCRANDOM_0_1() * 100000;
			if(tmp % 4 == 0)
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_music1.mp3",true); 
			else if(tmp % 4 == 1)
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_music2.mp3",true); 
			else if(tmp % 4 == 2)
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_music3.mp3",true); 
			else 
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_music4.mp3",true); 
		}
		
	}
}
 
void StaticFunc::stopMusic()
{	 
	 CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();	 
}

//Բ�κ;��� ��ײ��� 
bool StaticFunc::isCollision(Vec2 circle , int radius , Rect box)
{
	float cx;
	float cy;
	if (circle.x < box.origin.x )
        cx = box.origin.x ;
	else if (circle.x > box.origin.x + box.size.width )
        cx = box.origin.x + box.size.width;
    else  
        cx = circle.x ;
 
   if (circle.y < box.origin.y )
        cy = box.origin.y ;
	else if (circle.y > box.origin.y + box.size.width )
        cy = box.origin.y + box.size.width;
    else  
        cy = circle.y;
  
	if(ccpDistance(circle, Vec2(cx, cy)) < radius)
		return true ;
 
    return false ;
}

 