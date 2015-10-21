#ifndef __FishingJoy__StaticData__
#define __FishingJoy__StaticData__

#include "cocos2d.h"

#define STATIC_DATA_STRING(key) StaticData::sharedStaticData()->stringFromKey(key)
#define STATIC_DATA_INT(key) StaticData::sharedStaticData()->intFromKey(key)
#define STATIC_DATA_FLOAT(key) StaticData::sharedStaticData()->floatFromKey(key)
#define STATIC_DATA_BOOLEAN(key) StaticData::sharedStaticData()->booleanFromKey(key)
#define STATIC_DATA_POINT(key) StaticData::sharedStaticData()->pointFromKey(key)
#define STATIC_DATA_RECT(key) StaticData::sharedStaticData()->rectFromKey(key)
#define STATIC_DATA_SIZE(key) StaticData::sharedStaticData()->sizeFromKey(key)
 
class StaticData : public cocos2d::Object
{
public:    
    static StaticData* sharedStaticData();
 
    const char* stringFromKey(std::string key);
    int intFromKey(std::string key);
    float floatFromKey(std::string key);
    bool booleanFromKey(std::string key);
    cocos2d::Point pointFromKey(std::string key);
    cocos2d::Rect rectFromKey(std::string key);
    cocos2d::Size sizeFromKey(std::string key);
    
	static int roomread;
 
    void purge();
    
    CC_SYNTHESIZE_READONLY(std::string, _staticDataPath, StaticDataPath);

protected:
    cocos2d::Dictionary* _dictionary;
 
private:

    StaticData();
    ~StaticData();
    bool init();
};
#endif 
