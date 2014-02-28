//
//  GameScene.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "GameScene.h"
#include "StaticData.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void GameScene::onEnterTransitionDidFinish()
{
    _musicVolume = 0.5;
    _soundVolume = 0.5;
    _musicOn = true;
    _soundOn = true;
    CCScene::onEnterTransitionDidFinish();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("music"),true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(_musicVolume);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(_soundVolume);
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(_menuMainLayer);
    CC_SAFE_RELEASE(_menuGameEndLayer);
}

bool GameScene::init()
{
    if (CCScene::init()) {
        _backgroundLayer = BackgroundLayer::create();
        this->addChild(_backgroundLayer);
        _dotsLayer = DotsLayer::create();
        this->addChild(_dotsLayer);
        _panelLayer = PanelLayer::create();
        this->addChild(_panelLayer);
        _touchLayer = TouchLayer::create();
        this->addChild(_touchLayer);
        _menuMainLayer = MenuLayer::create(t_Menu_Main);
        _menuGameEndLayer = MenuLayer::create(t_Menu_EndGame);
        CC_SAFE_RETAIN(_menuMainLayer);
        CC_SAFE_RETAIN(_menuGameEndLayer);
        
        return true;
    }
    return false;
}

void GameScene::addDotsBegan(CCPoint point)
{
    _dotsLayer->addDotsBegan(point);
}

void GameScene::addDotsMoved(CCPoint point)
{
    _dotsLayer->addDotsMoved(point);
}

void GameScene::addDotsEnded(CCPoint point)
{
    _dotsLayer->addDotsEnded(point);
}

void GameScene::updateScore(int score)
{
    _panelLayer->updateScore(score);
}

void GameScene::playSound()
{
   CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound"));

}

void GameScene::pause()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Pause);
    _touchLayer->setTouchEnabled(false);
    _panelLayer->setTouchEnabled(false);
    this->addChild(_menuMainLayer, 128);
}

void GameScene::end()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Pause);
    _touchLayer->setTouchEnabled(false);
    _panelLayer->setTouchEnabled(false);
    this->addChild(_menuGameEndLayer, 128);
}

void GameScene::resume()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Resume);
    this->removeChild(_menuMainLayer, false);
    _touchLayer->setTouchEnabled(true);
    _panelLayer->setTouchEnabled(true);
}

void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}

void GameScene::sound()
{
    _soundOn = !_soundOn;
}

bool GameScene::getSoundStatus()
{
    return _soundOn;
}

void GameScene::music()
{
    _musicOn = !_musicOn;
    if (!_musicOn) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
    }
}

void GameScene::reset()
{
    CCScene *pScene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene);
}