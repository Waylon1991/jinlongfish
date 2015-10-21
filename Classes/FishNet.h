#ifndef __FISHNET__
#define __FISHNET__

#include "cocos2d.h"

USING_NS_CC;

class FishNet : public Node
{
public:
	static FishNet * create(int type,Vec2 pos);
	virtual bool init(int type,Vec2 pos);
private:
	char net_tmp_char[30];
};
#endif