//
//  PanelLayer.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "PanelLayer.h"
#include "GameScene.h"

#define TIME_MAX 60

USING_NS_CC;

bool PanelLayer::init()
{
    if (CCLayer::init()) {
        _curTime = TIME_MAX;
        _curScore = 0;
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCString *timeStr = CCString::createWithFormat("Time: %d", _curTime);
        _time  = CCLabelTTF::create(timeStr->getCString(), "Thonburi", 20);
        _time->setColor(ccc3(165, 42, 42));
        this->addChild(_time);
        _score = CCLabelTTF::create("Score: 0", "Thonburi", 20);
        _score->setColor(ccc3(165, 42, 42));
        this->addChild(_score);
        CCMenuItemFont* back = CCMenuItemFont::create("Back", this, menu_selector(PanelLayer::back));
        back->setFontName("Thonburi");
        back->setFontSize(24);
        
        _menu = CCMenu::create(back, NULL);
        this->addChild(_menu);
        
        _time->setPosition(ccp(winSize.width*0.2, winSize.height*0.95));
        _score->setPosition(ccp(winSize.width*0.55, winSize.height*0.95));
        _menu->setPosition(ccp(winSize.width*0.85, winSize.height*0.95));
        
        this->scheduleStart();
        return true;
    }
    
    return false;
}

void PanelLayer::setTouchEnabled(bool enabled)
{
    CCObject* item;
    CCARRAY_FOREACH(_menu->getChildren() , item)
    {
        ((CCMenuItem*)item)->setEnabled(enabled);
    }
}

void PanelLayer::back() {
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->pause();
}

void PanelLayer::scheduleTimeUp()
{
    _curTime--;
    if (_curTime >= 0) {
        this->updateTime();
        if (_curTime == 0) {
            //TODO
            CCLOG("Game Over");
            GameScene* gameScene = (GameScene*)this->getParent();
            gameScene->end();
        }
    } else {
        this->unschedule(schedule_selector(PanelLayer::scheduleTimeUp));
    }
}

void PanelLayer::scheduleStart()
{
    this->schedule(schedule_selector(PanelLayer::scheduleTimeUp), 1.0f);
}

void PanelLayer::reset()
{
    _curTime = TIME_MAX;
    _curScore = 0;
    this->updateScore(_curScore);
    this->updateTime();
}

void PanelLayer::updateScore(int score)
{
    _curScore += score;
    CCString *scoreStr = CCString::createWithFormat("Score: %d", _curScore);
    _score->setString(scoreStr->getCString());
}

void PanelLayer::updateTime()
{
    CCString *timeStr = CCString::createWithFormat("Time: %d", _curTime);
    _time->setString(timeStr->getCString());
}