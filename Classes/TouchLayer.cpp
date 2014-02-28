//
//  TouchLayer.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "TouchLayer.h"
#include "GameScene.h"
USING_NS_CC;

bool TouchLayer::init()
{
    this->setTouchEnabled(true);
    return true;
}

GameScene* TouchLayer::getGameScene()
{
    return (GameScene*)this->getParent();
}

bool TouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    this->getGameScene()->addDotsBegan(this->locationFromTouch(touch));
    return true;
}

void TouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    this->getGameScene()->addDotsMoved(this->locationFromTouch(touch));
}

void TouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    this->getGameScene()->addDotsEnded(this->locationFromTouch(touch));
}

void TouchLayer::setTouchEnabled(bool flag)
{
    if (m_bTouchEnabled != flag){
        m_bTouchEnabled = flag;
        if(flag){
            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        }else{
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}
CCPoint TouchLayer::locationFromTouch(CCTouch* touch)
{
    return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}