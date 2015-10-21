#include "Gun.h"
#include "GameData.h"
#include <math.h>
#include "SimpleAudioEngine.h"
#include "StaticFunc.h"
#include "ControlLayer.h"
 
Gun * Gun::create(int type)  //1-3
{
	auto fish = new Gun();
	fish->init(type);
	fish->autorelease();
	return fish;
}

bool Gun::init(int type)
{
	//³õÊ¼»¯Êý¾Ý
	srand(time(NULL));
	auto visibleSize = Director::getInstance()->getVisibleSize();

	fire_pos_array[0][0]  = Vec2(42,123); fire_pos_array[0][1]  = Vec2(42,123); fire_pos_array[0][2]  = Vec2(42,123);
	fire_pos_array[1][0]  = Vec2(42,123); fire_pos_array[1][1]  = Vec2(42,123); fire_pos_array[1][2]  = Vec2(94,123);
	fire_pos_array[2][0]  = Vec2(35,113); fire_pos_array[2][1]  = Vec2(70,123); fire_pos_array[2][2]  = Vec2(105,113);
	fire_pos_array[3][0]  = Vec2(42,123); fire_pos_array[3][1]  = Vec2(42,123); fire_pos_array[3][2]  = Vec2(42,123);
	fire_pos_array[4][0]  = Vec2(43,123); fire_pos_array[4][1]  = Vec2(43,123); fire_pos_array[4][2]  = Vec2(99,123);
	fire_pos_array[5][0]  = Vec2(34,113); fire_pos_array[5][1]  = Vec2(70,123); fire_pos_array[5][2]  = Vec2(105,113);
	fire_pos_array[6][0]  = Vec2(40,123); fire_pos_array[6][1]  = Vec2(40,123); fire_pos_array[6][2]  = Vec2(40,123);
	fire_pos_array[7][0]  = Vec2(45,113); fire_pos_array[7][1]  = Vec2(45,113); fire_pos_array[7][2]  = Vec2(107,113);
	fire_pos_array[8][0]  = Vec2(41,113); fire_pos_array[8][1]  = Vec2(77,123); fire_pos_array[8][2]  = Vec2(114,113);
	fire_pos_array[9][0]  = Vec2(45,123);  fire_pos_array[9][1] = Vec2(45,123); fire_pos_array[9][2]  = Vec2(45,123);
	fire_pos_array[10][0] = Vec2(42,113); fire_pos_array[10][1] = Vec2(42,113); fire_pos_array[10][2] = Vec2(109,113);
	fire_pos_array[11][0] = Vec2(37,113); fire_pos_array[11][1] = Vec2(69,123); fire_pos_array[11][2] = Vec2(100,113);
	fire_pos_array[12][0] = Vec2(45,123);fire_pos_array[12][1] = Vec2(45,123);fire_pos_array[12][2] = Vec2(45,123);
	fire_pos_array[13][0] = Vec2(42,113);fire_pos_array[13][1] = Vec2(42,113);fire_pos_array[13][2] = Vec2(109,113);
	fire_pos_array[14][0] = Vec2(37,113);fire_pos_array[14][1] = Vec2(69,123);fire_pos_array[14][2] = Vec2(100,113);

	_gunType	   = type;
	soundIndex	   = 1;
	this->setContentSize(Size(0,0));
	g_height = 103;//_cannon->getContentSize().height * 0.7;
	g_width  = 357;//_cannon->getContentSize().width;

	//beijing 
	auto beijing_s = Sprite::create();
	this->addChild(beijing_s);

	//ÅÚÌ¨
	//sprintf(gun_tmp_char,"pao%d_bg",_gunType);
	//std::string tmppng = GAME_DATA_STRING(gun_tmp_char);
	_cannon = Sprite::createWithSpriteFrameName("paobg1.png");
	//_cannon->setAnchorPoint(Vec2(0.5,0));
	_cannon->setPosition(Vec2(0,0));
	beijing_s->addChild(_cannon);

	//ÇÐ»»ÅÚ²Ëµ¥
	auto jia_pao_sp = Sprite::createWithSpriteFrameName("paoonejia.png");
	auto jia_pao_sp1 = Sprite::createWithSpriteFrameName("paoonejia_d.png");
	auto jia_pao_item = MenuItemSprite::create(jia_pao_sp,jia_pao_sp1,CC_CALLBACK_0(Gun::jia_pao_fun,this));
	auto jian_pao_sp = Sprite::createWithSpriteFrameName("paoonejian.png");
	auto jian_pao_sp1 = Sprite::createWithSpriteFrameName("paoonejian_d.png");
	auto jian_pao_item = MenuItemSprite::create(jian_pao_sp,jian_pao_sp1,CC_CALLBACK_0(Gun::jian_pao_fun,this));
	qie_pao_menu = Menu::create(jian_pao_item,jia_pao_item,nullptr);
	qie_pao_menu->alignItemsHorizontallyWithPadding(130);
	qie_pao_menu->setPosition(Vec2(_cannon->getContentSize().width/2, 28));
	_cannon->addChild(qie_pao_menu);
 
	//ÅÚ¹Ü
	sprintf(gun_tmp_char,"pao%d.png",_gunType);
	_cannon_gun = Sprite::createWithSpriteFrameName(gun_tmp_char);
	_cannon_gun->setAnchorPoint(Vec2(0.5,0.2));
	_cannon_gun->setPosition(Vec2(_cannon->getContentSize().width/2 , _cannon->getContentSize().height * GUN_HEIGHT_BI));
	_cannon->addChild(_cannon_gun);

	//ÅÚ»ð
//	sprintf(gun_tmp_char,"fire%d.png",(int)(CCRANDOM_0_1()*1.99 + 1));
	_cannon_fire1 = Sprite::createWithSpriteFrameName("cannon_fire.png");
	_cannon_fire1->setAnchorPoint(Vec2(0.5,0));
	_cannon_fire1->setPosition(fire_pos_array[_gunType-1][0]);
	_cannon_fire1->setVisible(false);
	_cannon_gun->addChild(_cannon_fire1,-1);

	_cannon_fire2 = Sprite::createWithSpriteFrameName("cannon_fire.png");
	_cannon_fire2->setAnchorPoint(Vec2(0.5,0));
	_cannon_fire2->setPosition(fire_pos_array[_gunType-1][1]);
	_cannon_fire2->setVisible(false);
	_cannon_gun->addChild(_cannon_fire2,-1);

	_cannon_fire3 = Sprite::createWithSpriteFrameName("cannon_fire.png");
	_cannon_fire3->setAnchorPoint(Vec2(0.5,0));
	_cannon_fire3->setPosition(fire_pos_array[_gunType-1][2]);
	_cannon_fire3->setVisible(false);
	_cannon_gun->addChild(_cannon_fire3,-1);

	//ÅÚ±¶ÂÊ
	sprintf(gun_tmp_char,"pao_fenshu_%d.png",(_gunType + 2)/3);
	_cannon_beilv = Sprite::createWithSpriteFrameName(gun_tmp_char);
	_cannon_beilv->setPosition(Vec2(_cannon->getContentSize().width/2,23));
	_cannon->addChild(_cannon_beilv);

	//label
	_cannon_beilv_label = Label::createWithCharMap("img/fengshunum.png",11,17,'0');
	sprintf(gun_tmp_char,"%d",BEILV_TYPE[_gunType-1]);
	_cannon_beilv_label->setString(gun_tmp_char);
	_cannon_beilv_label->setPosition(_cannon->getContentSize().width/2,23);
	_cannon->addChild(_cannon_beilv_label);

	return true;
}

void Gun::jia_pao_fun()
{
	if(_gunType%2 == 0)
		StaticFunc::playSound("music/sfx_switch.mp3");
	else
		StaticFunc::playSound("music/sfx_switch1.mp3");
	_gunType++;
	if(_gunType == GUN_TYPE_MAX + 1)
		_gunType = 1;

	//»»ÅÚ¹Ü
	sprintf(gun_tmp_char,"pao%d.png",_gunType);
	_cannon_gun->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char ));

	//»»ÅÚÌ¨
	//sprintf(gun_tmp_char,"paobg%d.png",1);  //(_gunType+2)/3
	//_cannon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char));

	//ÅÜ±¶ÂÊlabel  bg
	sprintf(gun_tmp_char,"pao_fenshu_%d.png",(_gunType + 2)/3);
	_cannon_beilv->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char));

	//ÅÜ±¶ÂÊlabel
	sprintf(gun_tmp_char,"%d",BEILV_TYPE[_gunType-1]);
	_cannon_beilv_label->setString(gun_tmp_char);

}

void Gun::jian_pao_fun()
{
	if(_gunType%2 == 0)
		StaticFunc::playSound("music/sfx_switch.mp3");
	else
		StaticFunc::playSound("music/sfx_switch1.mp3");

	_gunType--;
	if(_gunType == 0)
		_gunType = GUN_TYPE_MAX;

	//»»ÅÚ¹Ü
	sprintf(gun_tmp_char,"pao%d.png",_gunType);
	_cannon_gun->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char ));

	//»»ÅÚÌ¨
	//sprintf(gun_tmp_char,"paobg%d.png",(_gunType+2)/3);
	//_cannon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char));

	//ÅÜ±¶ÂÊlabel  bg
	sprintf(gun_tmp_char,"pao_fenshu_%d.png",(_gunType + 2)/3);
	_cannon_beilv->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char));

	//ÅÜ±¶ÂÊlabel
	sprintf(gun_tmp_char,"%d",BEILV_TYPE[_gunType-1]);
	_cannon_beilv_label->setString(gun_tmp_char);
}
 
Size Gun::getContentSize()
{
	return Size(g_width,g_height);
}

void Gun::setType(int type)					//ÉèÖÃÅÚÌ¨info
{
	 _gunType = type;
	 sprintf(gun_tmp_char,"pao%d_bg",type);
	 _cannon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(gun_tmp_char));

	  sprintf(gun_tmp_char,"pao%d_can",type);
	 _cannon_gun->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(gun_tmp_char));
}

void Gun::shootBy(float angle)
{
	_cannon_gun->setRotation(angle);
	if(bullet_type[_gunType - 1] > StaticFunc::getFileData("gameMoney.txt"))
	{
		sprintf(gun_tmp_char,"music/shootok1%d.mp3",soundIndex);
		soundIndex = soundIndex%3 + 1;
		StaticFunc::playSound(gun_tmp_char);
	}else
	{
		if(!StaticFunc::isBFing && !StaticFunc::isTHing && StaticFunc::isJSing)
		{
			_cannon_fire1->setVisible(true);
			_cannon_fire1->setPosition(fire_pos_array[_gunType-1][0] );
			_cannon_fire2->setVisible(true);
			_cannon_fire2->setPosition(fire_pos_array[_gunType-1][1] );
			_cannon_fire3->setVisible(true);
			_cannon_fire3->setPosition(fire_pos_array[_gunType-1][2] );
		}
		

		sprintf(gun_tmp_char,"music/shootok2%d.mp3",soundIndex);
		soundIndex = soundIndex%3 + 1;
		StaticFunc::playSound(gun_tmp_char);
	}
 
	//¼ÆËã½Ç¶È
	float x_tmp = -10 * sin(angle * M_PI /180 );
	float y_tmp = -10 * cos(angle * M_PI /180);

	_cannon_gun->setPosition(Vec2(_cannon->getContentSize().width/2 + x_tmp,_cannon->getContentSize().height * GUN_HEIGHT_BI + y_tmp));
	_cannon_gun->runAction(MoveTo::create(0.05f,Vec2(_cannon->getContentSize().width/2 , _cannon->getContentSize().height * GUN_HEIGHT_BI)));

	_cannon_fire1->runAction(Sequence::create(DelayTime::create(0.05f),Hide::create(),nullptr));
	_cannon_fire2->runAction(Sequence::create(DelayTime::create(0.05f),Hide::create(),nullptr));
	_cannon_fire3->runAction(Sequence::create(DelayTime::create(0.05f),Hide::create(),nullptr));
}

void Gun::changeFever(int i)
{
	// i = 1 Ìì»ð 2 ±ù·â 3 µ¼µ¯
	 sprintf(gun_tmp_char,"pao_fever_%d_%d.png",(_gunType + 2) / 3 , i);
	_cannon_gun->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( gun_tmp_char ));

	_cannon_beilv->setVisible(false);
	_cannon_beilv_label->setVisible(false);
}

void Gun::changeFeverOver()
{
	 sprintf(gun_tmp_char,"pao%d.png",_gunType);
	 _cannon_gun->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(gun_tmp_char));

	_cannon_beilv->setVisible(true);
	_cannon_beilv_label->setVisible(true);
}


 