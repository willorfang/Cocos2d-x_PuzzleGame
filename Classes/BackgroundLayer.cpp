//
//  BackgroundLayer.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "BackgroundLayer.h"
#include "StaticData.h"
USING_NS_CC;

bool BackgroundLayer::init()
{
    if(CCLayer::init()){
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCTexture2D* cache = CCTextureCache::sharedTextureCache()->addImage(STATIC_DATA_STRING("background"));
        _background = CCSprite::createWithTexture(cache);
        _background->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
        this->addChild(_background);
        return true;
    }
    return false;
}

void BackgroundLayer::setOpacity(GLubyte opa)
{
    _background->setOpacity(opa);
}