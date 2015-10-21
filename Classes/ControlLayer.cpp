#include "ControlLayer.h"
#include "StaticData.h"
#include "FishNet.h"
#include "StaticFunc.h"
#include "GameData.h"

USING_NS_CC;

void ControlLayer::init_shuzhi()
{
	cont_jinbi_tmp = 0;
	is_touching = false;
	dit_time = 0;
	pos_origin = Vec2(visibleSize.width/2,myGun->getContentSize().height * 0.2);
	bullet_size = 0;
	tianhuo_pos_cd = 0.2f;
}

bool ControlLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
 
	//初始化鱼游动层
	fishLayer = FishLayer::create();
	fishLayer->setPosition(Vec2::ZERO);
	this->addChild(fishLayer);

	//四大技能
	auto left_jineng_1 = Sprite::createWithSpriteFrameName("jineng_icon_1.png");
	auto left_jineng_2 = Sprite::createWithSpriteFrameName("jineng_icon_2.png");
	auto left_jineng_3 = Sprite::createWithSpriteFrameName("jineng_icon_3.png");
	auto left_jineng_4 = Sprite::createWithSpriteFrameName("jineng_icon_4.png");

	jineng_icon_1 = MenuItemSprite::create(left_jineng_1,left_jineng_1,CC_CALLBACK_0(ControlLayer::jineng_call_1,this));
	jineng_icon_2 = MenuItemSprite::create(left_jineng_2,left_jineng_2,CC_CALLBACK_0(ControlLayer::jineng_call_2,this));
	jineng_icon_3 = MenuItemSprite::create(left_jineng_3,left_jineng_3,CC_CALLBACK_0(ControlLayer::jineng_call_3,this));
	jineng_icon_4 = MenuItemSprite::create(left_jineng_4,left_jineng_4,CC_CALLBACK_0(ControlLayer::jineng_call_4,this));

	auto left_jineng_menu = Menu::create(jineng_icon_1,jineng_icon_2,nullptr);
	left_jineng_menu->alignItemsVerticallyWithPadding(20);
	left_jineng_menu->setPosition(Vec2(50 , 100));
	addChild(left_jineng_menu,ANNIULAYER);

	auto right_jineng_menu = Menu::create(jineng_icon_3,jineng_icon_4,nullptr);
	right_jineng_menu->alignItemsVerticallyWithPadding(20);
	right_jineng_menu->setPosition(Vec2(visibleSize.width - 50 , 100));
	addChild(right_jineng_menu,ANNIULAYER);
 
	//初始化炮
	myGun = Gun::create(1);
	Size tmp = myGun->getContentSize();
	myGun->setPosition(Vec2(visibleSize.width/2 , tmp.height/2));
	this->addChild(myGun,ANNIULAYER);

	init_shuzhi();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ControlLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(ControlLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(ControlLayer::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	auto mCustomListener = EventListenerCustom::create("CONTROL_CANCEL",CC_CALLBACK_0( ControlLayer::cancle_fapao,this)); 
	_eventDispatcher->addEventListenerWithFixedPriority(mCustomListener,1);

	this->scheduleUpdate();
	//this->schedule(schedule_selector(ControlLayer::update1),0.032f);
    return true;
}

void ControlLayer::update(float dt)
{
	//下天火雨
	if(StaticFunc::TH_cdtime > 0.4f)
	{
		StaticFunc::TH_cdtime -= dt;
		StaticFunc::TH_cdtime_cha += dt;
		if(StaticFunc::TH_cdtime_cha > 0.8f)
		{
			StaticFunc::TH_cdtime_cha -= 0.8f;
			float xTmp = CCRANDOM_0_1() * visibleSize.width * 0.6 + visibleSize.width * 0.2;
			float yTmp = CCRANDOM_0_1() * visibleSize.height * 0.6 + visibleSize.height * 0.2;

			tianhuo_pos.push_back(Vec2(xTmp,yTmp));

			auto th_sp =  Sprite::create();
			th_sp->setScale(1.5);
			th_sp->setPosition(Vec2(xTmp,yTmp));
			addChild(th_sp,ANNIULAYER);

			th_sp->runAction(Sequence::create( Animate::create(AnimationCache::getInstance()->getAnimation("jineng_tianhuo")),CCCallFunc::create([&]{tianhuo_pos.erase(tianhuo_pos.begin());}), RemoveSelf::create(),nullptr));
			th_sp->runAction(Sequence::create(DelayTime::create(0.24f),
				CCCallFunc::create([&]{StaticFunc::playSound("music/jineng_tianhuo1.mp3");}),DelayTime::create(0.16f),
				CCCallFunc::create([&]{StaticFunc::playSound("music/jineng_tianhuo2.mp3");}),DelayTime::create(0.16f),
				CCCallFunc::create([&]{StaticFunc::playSound("music/jineng_tianhuo3.mp3");}),DelayTime::create(0.16f),
				CCCallFunc::create([&]{StaticFunc::playSound("music/jineng_tianhuo4.mp3");}),DelayTime::create(0.16f),
				CCCallFunc::create([&]{StaticFunc::playSound("music/jineng_tianhuo5.mp3");}),
				nullptr));
		}
	}

	if(tianhuo_pos.size() > 0)
	{

		if(tianhuo_pos_cd <= 0)
		{
			tianhuo_pos_cd = 0.2;
			//循环天火内的所有鱼 进行一次概率判定
			for(int i = 0 ; i < tianhuo_pos.size() ; i++)
			{
				Vec2 tmpPox = tianhuo_pos.at(i);
				Rect checkRect = Rect(tmpPox.x - 200, tmpPox.y - 200, 400 ,400);
				for(int j = fishLayer->m_Fishes.size() - 1;j >= 0; j--)
				{
					if(checkRect.containsPoint(fishLayer->m_Fishes.at(j)->getPosition()))
					{
						if(fishLayer->m_Fishes.at(j)->ifCatch(bullet_type[myGun->_gunType - 1]))
						{
							int tmp_type = fishLayer->m_Fishes.at(j)->fish_type;
							if(tmp_type == 26 || tmp_type == 27)
								tmp_type = 25;
							random_coin(Vec2(fishLayer->m_Fishes.at(j)->m_iX,fishLayer->m_Fishes.at(j)->m_iY),fishBeishu[tmp_type],bullet_type[myGun->_gunType - 1]);
							//删除这条鱼的信息
							fishLayer->m_Fishes.at(j)->_fishSprite->runAction(FadeOut::create(2.0f));
							fishLayer->m_Fishes.at(j)->runAction(Sequence::create(DelayTime::create(2.0f),RemoveSelf::create(),nullptr));
							fishLayer->m_Fishes.erase(j);
						}
					}
				}
			}
		}

		tianhuo_pos_cd -= dt;
	}
	//更新子弹的位置
	if(bullet_size > 0)
	{
		updateBullets();
	}

	//炮友关
	dit_time += dt;
	if(dit_time > 0.15f && is_touching)
	{
		dit_time = 0;

		if(bullet_size > Max_Bullet_Num)
		{
			//提示子弹过多
			log("bullet is lot");
		}else
		{
			
			//计算大炮应该旋转的角度
			float tmp_x_dis = pos_begin.x - pos_origin.x;
			float tmp_y_dis = pos_begin.y - pos_origin.y;

			float gun_angle = atan(tmp_x_dis/tmp_y_dis) * 180 / M_PI;
			if(tmp_y_dis < 0)
				gun_angle += 180; 
			myGun->shootBy(gun_angle);	

			if(bullet_type[myGun->_gunType - 1] > StaticFunc::getFileData("gameMoney.txt"))
			{
				log("no money");
			}else
			{
				//创建一个子弹
				auto bullet = Bullet::create(myGun->_gunType);
				bullet->setPos(pos_origin);
				bullet->setAngel(gun_angle);
				this->addChild(bullet,9);

				my_bullets.pushBack(bullet);

				bullet_size++;

				sprintf( cont_tmp_char1 , "%d" , -bullet_type[myGun->_gunType - 1]);
				//扣相应的金币
				_eventDispatcher->dispatchCustomEvent("REFRASHCOIN",cont_tmp_char1);
			}

		}	
	}

	//检测子弹和鱼的碰撞
	checkBulletAndFishes();
	if(judgeing_fish_info.bullet_pos != -1  && judgeing_fish_info.fish_pos != -1)
	{
		sprintf(cont_tmp_char2,"music/shoot%d.mp3",(int)(CCRANDOM_0_1()*2.99 + 1));
		StaticFunc::playSound(cont_tmp_char2); 
		tmpBullet = my_bullets.at(judgeing_fish_info.bullet_pos);
		//在子弹的位置创建一个渔网
		auto fish_net =FishNet::create(tmpBullet->bullet_type,tmpBullet->getPosition());
		this->addChild(fish_net,9);

		//子弹执行动作后消除
		my_bullets.at(judgeing_fish_info.bullet_pos)->removeFromParentAndCleanup(true);
		my_bullets.erase(judgeing_fish_info.bullet_pos);		
		bullet_size--;

		//当前这条鱼变红		
		Sprite * tempSp = fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->_fishSprite;
		tempSp->runAction(Sequence::create(CCCallFunc::create([tempSp]{tempSp->setColor(Color3B::RED);}),DelayTime::create(0.5f),CCCallFunc::create([tempSp]{tempSp->setColor(Color3B(255,255,255));}),nullptr));
		if(fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->ifCatch(bullet_type[myGun->_gunType - 1]))
		{
			int tmp_type = fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->fish_type;
			if(tmp_type == 26 || tmp_type == 27)
				tmp_type = 25;
			random_coin(Vec2(fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->m_iX,fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->m_iY),fishBeishu[tmp_type],bullet_type[myGun->_gunType - 1]);
			//删除这条鱼的信息
			fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->_fishSprite->runAction(FadeOut::create(2.0f));
			fishLayer->m_Fishes.at(judgeing_fish_info.fish_pos)->runAction(Sequence::create(DelayTime::create(2.0f),RemoveSelf::create(),nullptr));
			fishLayer->m_Fishes.erase(judgeing_fish_info.fish_pos);
		}
	}
}

void ControlLayer::random_coin(Vec2 point,int beilv,int bulletType)
{
	cont_jinbi_tmp = beilv;
	cont_bullet_tmp = bulletType;

	if(beilv < 120)
	{
		//jinbi num
		sprintf(cont_tmp_char2,">%d",0);
		auto left_hall_jinbi = LabelAtlas::create(cont_tmp_char2,"img/atlas_gold.png",36,44,'0');
		left_hall_jinbi->setPosition(point - Vec2(-40 , 20));
		left_hall_jinbi->setScale(0.5);
		//left_hall_jinbi->setTag(2);
		this->getParent()->addChild(left_hall_jinbi,ANNIULAYER + 1);

		left_hall_jinbi->runAction(Spawn::create(ScaleTo::create(0.4f ,0.75) , JumpTo::create(0.4f,point - Vec2(-40 , 40), 30 , 1),nullptr));

		log("point: x = %f , y = %f , beilv = %d" , point.x , point.y , beilv);
		float tmpScale;
		if(bulletType > 0 && bulletType < 10) tmpScale = 0.4;
		else if(bulletType >= 10	&& bulletType < 100) tmpScale = 0.5;
		else if(bulletType >= 100	&& bulletType < 1000) tmpScale = 0.55;
		else if(bulletType >= 1000	&& bulletType < 10000) tmpScale = 0.6;
		else if(bulletType >= 10000 && bulletType < 100000) tmpScale = 0.65;
		else  tmpScale = 0.7;
		float jiangeTime = 0.1f;
		if(beilv > 9)
		{
			jiangeTime = jiangeTime / 2;
		}
	
	
		for(int i = 0 ; i < beilv ; i++)
		{
			//金币精灵
			auto jinbi  = Sprite::createWithSpriteFrameName("jinbi_1.png");
			float tmp_x;float tmp_y;
			if(80*tmpScale*beilv < visibleSize.width)
			{
				tmp_x = point.x + 80*tmpScale*(i-beilv/2 + 0.5);
				tmp_y = point.y;//+ CCRANDOM_0_1()*100*tmpScale*i - 50*tmpScale*i;
			}else
			{
				int row_nums = visibleSize.width / (80*tmpScale);
				tmp_x = 80*tmpScale*(i%row_nums + 0.5);
				tmp_y = point.y - 80*tmpScale*(i/row_nums);
			}


			jinbi->setPosition(Vec2(tmp_x,tmp_y));
			jinbi->setScale(0.001);
			this->getParent()->addChild(jinbi,ANNIULAYER);
			float distance1 = ccpDistance(Vec2(tmp_x,tmp_y),Vec2(129*0.9,visibleSize.height - 80 * 0.9));
			float time1 = distance1/600.0f;

			jinbi->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("jinbi_zhuan"))));

			//金币动作  跳出来
			auto scale0 = ScaleTo::create(0.2f,tmpScale/2);
			auto scale1 = ScaleTo::create(0.2f,tmpScale);
			auto scale2 = ScaleTo::create(0.4f,tmpScale - 0.05);
			auto seq1   = Sequence::create(scale0,CCCallFunc::create([left_hall_jinbi,i,bulletType]{
				log("i = %d , bullet = %d",i,bulletType);

				//更改金币数值
				char tmpchar[20];
				sprintf(tmpchar,">%d",(i+1) * bulletType);
				if(left_hall_jinbi)
					left_hall_jinbi->setString(tmpchar);
				if(i%5 == 0)StaticFunc::playSound("music/coin_huode.mp3");
				else if(i%5 == 1) StaticFunc::playSound("music/coin_huode2.mp3");
				else if(i%5 == 2) StaticFunc::playSound("music/coin_huode3.mp3");
				else if(i%5 == 3) StaticFunc::playSound("music/coin_huode4.mp3");
				else StaticFunc::playSound("music/coin_huode1.mp3");

			}),scale1,scale2,nullptr);

			//金币动作  飞到上方
			auto jump1  = JumpTo::create(0.8f , Vec2(tmp_x,tmp_y) , 120 , 1);
			jinbi->runAction(Sequence::create(DelayTime::create(jiangeTime*i),		
				Spawn::create(seq1,jump1,nullptr),			
				JumpBy::create(0.5f,Vec2::ZERO,5,3),
				DelayTime::create(jiangeTime*(beilv-i)),
				Spawn::create(JumpTo::create(time1 , Vec2(129*0.9,visibleSize.height - 80 * 0.9) , 100 , 1),ScaleTo::create(time1,0.3),nullptr),

				CCCallFunc::create([&,i]{
					if(i % 3 == 0)
						StaticFunc::playSound("music/coin.mp3");
					else if(i % 3 == 1)
						StaticFunc::playSound("music/coin1.mp3");
					else 
						StaticFunc::playSound("music/coin2.mp3");
					//加钱
					if(cont_jinbi_tmp == 300)
						cont_jinbi_tmp = CCRANDOM_0_1()*699.999 + 300;
					sprintf( cont_tmp_char1 , "%d" , cont_bullet_tmp);

					//加上相应的金币
					_eventDispatcher->dispatchCustomEvent("REFRASHCOIN",cont_tmp_char1);

					//jinbi icon
					auto left_hall_jinbi_icon1 = Sprite::createWithSpriteFrameName("bar_coin11.png");
					left_hall_jinbi_icon1->setScale(0.4);
					left_hall_jinbi_icon1->setPosition(Vec2(129*0.9,visibleSize.height - 80 * 0.9));
					this->getParent()->addChild(left_hall_jinbi_icon1);

					left_hall_jinbi_icon1->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2f,1.3),FadeOut::create(0.2f),nullptr),RemoveSelf::create(),nullptr));

			}),
				RemoveSelf::create(),nullptr));
		}
		left_hall_jinbi->runAction(Sequence::create(DelayTime::create(1.5f + beilv * jiangeTime),Spawn::create( MoveBy::create(1.0f,Vec2(0,150)) , FadeOut::create(1.0f), nullptr),DelayTime::create(1.0f),RemoveSelf::create(),nullptr));
	}else
	{
		if(beilv == 150)
		{
			//小富豪
		}
		if(beilv == 200)
		{
			//大富豪
		}
		if(beilv == 300)
		{
			//一步登天
		}
	}
}
 
void ControlLayer::cancle_fapao()
{
	is_touching = false;
}
 
void ControlLayer::updateBullets()
{
	my_delete_bullets.clear();
	for(int i = 0 ; i < bullet_size ; i++)
	{
		cont_tmp_int = my_bullets.at(i)->checkBulletCollision();
		if(cont_tmp_int == -1)
		{
			my_delete_bullets.push_back(i);
			continue;
		}
		if(cont_tmp_int == 1)
		{
			my_bullets.at(i)->setAngel( -my_bullets.at(i)->bullet_angle );
		}
		if(cont_tmp_int == 2)
		{
			my_bullets.at(i)->setAngel( 180 - my_bullets.at(i)->bullet_angle );  
		}
		if(cont_tmp_int == 3)
		{
			my_bullets.at(i)->setAngel( 360 - my_bullets.at(i)->bullet_angle );
		}
		if(cont_tmp_int == 4)
		{
			my_bullets.at(i)->setAngel( 180 - my_bullets.at(i)->bullet_angle);
		}

		float angel = my_bullets.at(i)->bullet_angle;
		float x_tmp = Bullet_Speed * sin( angel * M_PI / 180);
		float y_tmp = Bullet_Speed * cos( angel * M_PI / 180);

		my_bullets.at(i)->setPos(Vec2(my_bullets.at(i)->m_iX + x_tmp , my_bullets.at(i)->m_iY + y_tmp));
	}

	if(my_delete_bullets.size() > 0)
	{
		for(int j = 0 ; j < my_delete_bullets.size(); j++ )
		{
			my_bullets.at(my_delete_bullets.at(j))->removeFromParentAndCleanup(true);
			my_bullets.erase(my_delete_bullets.at(j));		
			bullet_size--;
			for(int k = j ; k < my_delete_bullets.size() ; k++)
			{
				my_delete_bullets.at(j)--;
			}
		}
	}
	
}

void ControlLayer::checkBulletAndFishes()
{
	//清空要比对的子弹和鱼的信息
	judgeing_fish_info.bullet_pos = -1 ; 
	judgeing_fish_info.fish_pos = -1;
	//对子弹进行循环
	for(int i = 0 ; i < my_bullets.size() ; i++)
	{
		//对每条鱼进行判断
		for(int j = fishLayer->m_Fishes.size() - 1;j >= 0; j--)
		{
			int fishTmpType = fishLayer->m_Fishes.at(j)->fish_type;
			if(fishTmpType < 13)
			{
				//******************旋转矩形和圆形碰撞*********************
				//如果子弹的位置 在鱼的被击范围内 则将此子弹和此鱼放入 coll_info_vectore
				float fish_w = fishLayer->m_Fishes.at(j)->fish_width;
				float fish_h = fishLayer->m_Fishes.at(j)->fish_hight;
				float fish_x = fishLayer->m_Fishes.at(j)->m_iX - fish_w/2;
				float fish_y = fishLayer->m_Fishes.at(j)->m_iY - fish_h/2;
				Rect roomRect = Rect(fish_x, fish_y, fish_w ,fish_h);

				float origin_x = fishLayer->m_Fishes.at(j)->m_iX;
				float origin_y = fishLayer->m_Fishes.at(j)->m_iY;
				float bullet_x = my_bullets.at(i)->m_iX;
				float bullet_y = my_bullets.at(i)->m_iY;
				float radius = my_bullets.at(i)->bullet_hight/3;

				float distance = ccpDistance(Vec2(origin_x,origin_y),Vec2(bullet_x,bullet_y));

				float angle1 = asin((bullet_y - origin_y ) / distance);
				float angle2 = fishLayer->m_Fishes.at(j)->fish_angle;
				float angle3 = angle2 * M_PI / 180;

				float x1 = origin_x + distance * cos(angle1 + angle3);
				float y1 = origin_y + distance * sin(angle1 + angle3);

				if(StaticFunc::isCollision(Vec2(x1,y1),radius,roomRect))
				{
					judgeing_fish_info.bullet_pos = i;
					judgeing_fish_info.fish_pos = j;
					return;
				}
			}else
			{
				sprintf(cont_tmp_char1,"yuanNum%d",fishTmpType);
				int yuanNum = STATIC_DATA_INT(cont_tmp_char1);

				float origin_x = fishLayer->m_Fishes.at(j)->m_iX;
				float origin_y = fishLayer->m_Fishes.at(j)->m_iY;

				float bullet_x = my_bullets.at(i)->m_iX;
				float bullet_y = my_bullets.at(i)->m_iY;
				float radius_b = my_bullets.at(i)->bullet_hight/3;

				for(int k = 0 ; k < yuanNum ; k ++)
				{
					sprintf(cont_tmp_char1,"yuanxin%d_%d_x",fishTmpType,k+1);
					int x_pianyi =  STATIC_DATA_INT(cont_tmp_char1);
					x_pianyi += origin_x ;

					sprintf(cont_tmp_char1,"yuanxin%d_%d_y",fishTmpType,k+1);
					int y_pianyi =  STATIC_DATA_INT(cont_tmp_char1);
					y_pianyi += origin_y;

					float distance = ccpDistance(Vec2(origin_x,origin_y),Vec2(x_pianyi,y_pianyi));

					float angle1;
					if(distance == 0 )
					{
						angle1 = 0;
					}else
					{
						angle1 = asin((y_pianyi - origin_y ) / distance);
					}

					float angle2 = fishLayer->m_Fishes.at(j)->fish_angle;
					float angle3 = angle2 * M_PI / 180;

					float x1 = origin_x + distance * cos(angle1 - angle3);
					float y1 = origin_y + distance * sin(angle1 - angle3);

					sprintf(cont_tmp_char1,"yuanxin%d_%d_r",fishTmpType,k+1);
					int r_pianyi = STATIC_DATA_INT(cont_tmp_char1);

					if(ccpDistance(Vec2(x1,y1),Vec2(bullet_x,bullet_y)) < r_pianyi + radius_b )
					{
						judgeing_fish_info.bullet_pos = i;
						judgeing_fish_info.fish_pos = j;
						return;
					}
				}
			}
			
		}
	}
}

//四大技能事件
void ControlLayer::jineng_call_1()
{
	if(StaticFunc::isTHing)
		return;
	//冰封
	StaticFunc::playSound("music/ice.mp3");
	StaticFunc::isBFing = true;
	jineng_icon_1->setEnabled(false);
	myGun->changeFever(2);
 
	int vipLevel = StaticFunc::getFileData("vipLevel.txt");
	sprintf(cont_tmp_char1,"jineng_cd_%d",vipLevel);
	float cdtime = GAME_DATA_FLOAT(cont_tmp_char1);

	//出现技能cd效果
	auto cdSprite = Sprite::createWithSpriteFrameName("jineng_icon_cd.png");
	auto progressCD = ProgressTimer::create(cdSprite);
	progressCD->setPosition(Vec2(jineng_icon_1->getContentSize()/2));
	progressCD->setType(ProgressTimerType::RADIAL);
	jineng_icon_1->addChild(progressCD);

	progressCD->runAction(Sequence::create( ProgressTo::create(cdtime,100.0f),RemoveSelf::create(),nullptr));

	float tmpF = CCRANDOM_0_1();

	//出现冰封效果
	auto bfSprite = Sprite::create("scene/jinneg_bing_bg.png");
	auto progressBF = ProgressTimer::create(bfSprite);
	progressBF->setPosition(Vec2(visibleSize/2));
	progressBF->setType(ProgressTimerType::BAR);
	progressBF->setMidpoint(Vec2(0.5,0.5));
	
	this->addChild(progressBF,ANNIULAYER - 1);
	
	progressBF->runAction(Sequence::create( ProgressTo::create(0.5f,100.0f),DelayTime::create(cdtime - 0.5),FadeOut::create(0.5f),RemoveSelf::create(),nullptr));

	this->runAction(Sequence::create(DelayTime::create(cdtime),CCCallFunc::create([&]{jineng_icon_1->setEnabled(true);StaticFunc::isBFing = false;myGun->changeFeverOver();}),nullptr ) );
}

void ControlLayer::jineng_call_2()
{
	//急速导弹
	StaticFunc::buttonSound();
}

void ControlLayer::jineng_call_3()
{
	//天火	
	if(StaticFunc::isBFing)
		return;
	StaticFunc::buttonSound();
	StaticFunc::isTHing = true;
	jineng_icon_3->setEnabled(false);
	myGun->changeFever(1);
 
	int vipLevel = StaticFunc::getFileData("vipLevel.txt");
	sprintf(cont_tmp_char1,"jineng_cd_%d",vipLevel);
	float cdtime = GAME_DATA_FLOAT(cont_tmp_char1);

	StaticFunc::TH_cdtime = cdtime;

	//出现技能cd效果
	auto cdSprite = Sprite::createWithSpriteFrameName("jineng_icon_cd.png");
	auto progressCD = ProgressTimer::create(cdSprite);
	progressCD->setPosition(Vec2(jineng_icon_3->getContentSize()/2));
	progressCD->setType(ProgressTimerType::RADIAL);
	jineng_icon_3->addChild(progressCD);

	progressCD->runAction(Sequence::create( ProgressTo::create(cdtime,100.0f),RemoveSelf::create(),nullptr));

	float tmpF = CCRANDOM_0_1();

	//出现天火效果
	auto thSprite = Sprite::create("scene/jinneg_huo_bg.png");
	thSprite->setPosition(Vec2(visibleSize/2));
	thSprite->setOpacity(0);
	this->addChild(thSprite,ANNIULAYER - 1);
	
	thSprite->runAction(Sequence::create(FadeIn::create(0.5f), Repeat::create(Sequence::create(FadeTo::create(0.5f,125),FadeTo::create(0.5f,255),nullptr),cdtime),CCCallFunc::create([&]{jineng_icon_3->setEnabled(true);StaticFunc::isTHing = false;myGun->changeFeverOver();}),FadeOut::create(0.5f),RemoveSelf::create(),nullptr));
}

void ControlLayer::jineng_call_4()
{
	//深海炸弹
	StaticFunc::buttonSound();
}
 
bool ControlLayer::onTouchBegan(Touch* touch, Event* event) 
{  
	pos_begin = touch->getLocation();
	is_touching = true;
	
	return true;
}

void ControlLayer::onTouchMoved(Touch* touch, Event* event)
{
	pos_begin = touch->getLocation();	
}

void ControlLayer::onTouchEnded(Touch* touch, Event* event)
{
	is_touching = false;
}	
 