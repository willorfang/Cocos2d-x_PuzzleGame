//
//  StaticData.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "StaticData.h"

USING_NS_CC;
using namespace std;

#define STATIC_DATA_PATH "staticData.plist"

static StaticData* _sharedStaticData = NULL;

StaticData* StaticData::sharedStaticData()
{
    if(_sharedStaticData == NULL){
        _sharedStaticData = new StaticData();
        _sharedStaticData->init();
    }
    return _sharedStaticData;
}

StaticData::StaticData()
{
    _staticDataPath = STATIC_DATA_PATH;
}

StaticData::~StaticData()
{
    CC_SAFE_RELEASE_NULL(_dictionary);
}

bool StaticData::init()
{
    _dictionary = CCDictionary::createWithContentsOfFile(_staticDataPath.c_str());
    CC_SAFE_RETAIN(_dictionary);
    return true;
}

const char* StaticData::stringFromKey(string key)
{
    return _dictionary->valueForKey(key)->getCString();
}
int StaticData::intFromKey(string key)
{
    return _dictionary->valueForKey(key)->intValue();
}
float StaticData::floatFromKey(string key)
{
    return _dictionary->valueForKey(key)->floatValue();
}
bool StaticData::booleanFromKey(string key)
{
    return _dictionary->valueForKey(key)->boolValue();
}
cocos2d::CCPoint StaticData::pointFromKey(string key)
{
    return CCPointFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::CCRect StaticData::rectFromKey(string key)
{
    return CCRectFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::CCSize StaticData::sizeFromKey(string key)
{
    return CCSizeFromString(_dictionary->valueForKey(key)->getCString());
}
cocos2d::CCArray* StaticData::arrayFromKey(string key)
{
    return (cocos2d::CCArray*) _dictionary->objectForKey(key);
}

void StaticData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedStaticData);
}