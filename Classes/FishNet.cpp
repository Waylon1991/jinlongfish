#include "FishNet.h"
#include "StaticFunc.h"
 
FishNet * FishNet::create(int type , Vec2 pos)  //0-20
{
	auto fish = new FishNet();
	fish->init(type , pos);
	fish->autorelease();
	return fish;
}

bool FishNet::init(int type , Vec2 pos)
{
	StaticFunc::playSound("music/sfx_net.mp3");
	//ÓæÍø¾«Áé
	if(type  == 1  || type  == 4 || type  == 7 || type  == 10 || type  == 13)
	{
		sprintf(net_tmp_char,"net_%d.png",(type+2) / 3);
		auto fishnet1 = Sprite::createWithSpriteFrameName(net_tmp_char);
		fishnet1->setScale(0.8);
		this->addChild(fishnet1);

		ScaleTo *ac1=ScaleTo::create(0.1f, 1.0f);  
		ScaleTo *ac2=ScaleTo::create(0.1f, 0.8f);  
		ScaleTo *ac3=ScaleTo::create(0.1f, 0.9);  

		auto * seq = Sequence::create(ac1,ac2,ac3, FadeOut::create(1.0f),NULL);
		fishnet1->runAction(seq);
	}

	if(type == 2 || type  == 5 || type  == 8 || type  == 11 || type  == 14)
	{
		sprintf(net_tmp_char,"net_%d.png",(int)(type - 1) / 3 + 1);
		auto fishnet1 = Sprite::createWithSpriteFrameName(net_tmp_char);
		fishnet1->setPosition(Vec2(-fishnet1->getContentSize().width * 0.3 , 0));
		fishnet1->setScale(0.8);
		this->addChild(fishnet1);

		ScaleTo *ac1=ScaleTo::create(0.1f, 1.0f);  
		ScaleTo *ac2=ScaleTo::create(0.1f, 0.8f);  
		ScaleTo *ac3=ScaleTo::create(0.1f, 0.9);  

		auto * seq = Sequence::create(ac1,ac2,ac3, FadeOut::create(1.0f),NULL);
		fishnet1->runAction(seq);

		auto fishnet2 = Sprite::createWithSpriteFrameName(net_tmp_char);
		fishnet2->setPosition(Vec2(fishnet2->getContentSize().width * 0.2 , 0));
		fishnet2->setScale(0.6);
		this->addChild(fishnet2);

		ScaleTo *ac11=ScaleTo::create(0.1f, 0.8f);  
		ScaleTo *ac21=ScaleTo::create(0.1f, 0.6f);  
		ScaleTo *ac31=ScaleTo::create(0.1f, 0.7);  

		auto * seq1 = Sequence::create(ac11,ac21,ac31,FadeOut::create(1.0f),NULL);
		fishnet2->runAction(seq1);
	}

	if(type == 3 || type  == 6 || type  == 9 || type  == 12 || type  == 15)
	{
		sprintf(net_tmp_char,"net_%d.png",(int)(type - 1) / 3 + 1);
		auto fishnet1 = Sprite::createWithSpriteFrameName(net_tmp_char);
		fishnet1->setPosition(Vec2( 0 , fishnet1->getContentSize().height * 0.4));
		fishnet1->setScale(0.8);
		this->addChild(fishnet1);

		auto * seq = Sequence::create(ScaleTo::create(0.1f,1.0f),ScaleTo::create(0.1f, 0.8f),ScaleTo::create(0.1f, 0.9),NULL);
		fishnet1->runAction(seq);

		auto fishnet2 = Sprite::createWithSpriteFrameName(net_tmp_char);
		fishnet2->setPosition(Vec2(-fishnet2->getContentSize().width * 0.2 , -fishnet2->getContentSize().width * 0.15 ));
		fishnet2->setScale(0.6);
		this->addChild(fishnet2);

		auto * seq1 = Sequence::create(ScaleTo::create(0.1f, 0.8f),ScaleTo::create(0.1f, 0.6f),ScaleTo::create(0.1f, 0.7),NULL);
		fishnet2->runAction(seq1);

		auto fishnet3 = Sprite::createWithSpriteFrameName(net_tmp_char);
		fishnet3->setPosition(Vec2(fishnet3->getContentSize().width * 0.25 , 0 ));
		fishnet3->setScale(0.7);
		this->addChild(fishnet3);

		auto * seq2 = Sequence::create(ScaleTo::create(0.1f, 0.9f),ScaleTo::create(0.1f, 0.7f),ScaleTo::create(0.1f, 0.8), NULL);
		fishnet3->runAction(seq2);
	}
 

	this->setPosition(pos);
	this->runAction(Sequence::create(DelayTime::create(0.3f),RemoveSelf::create(), NULL));
	return true;
}

 