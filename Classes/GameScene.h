//
//  GameScene.h
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#ifndef Dots_GameScene_h
#define Dots_GameScene_h

#include "cocos2d.h"
#include "DotsLayer.h"
#include "PanelLayer.h"
#include "BackgroundLayer.h"
#include "TouchLayer.h"
#include "MenuLayer.h"

typedef enum{
    k_Operate_Pause = 0,
    k_Operate_Resume
}OperateFlag;

class GameScene : public cocos2d::CCScene
{
public:
    CREATE_FUNC(GameScene);
    bool init();
    
    void addDotsBegan(cocos2d::CCPoint point);
    void addDotsMoved(cocos2d::CCPoint point);
    void addDotsEnded(cocos2d::CCPoint point);
    
    void updateScore(int score);
    
    void onEnterTransitionDidFinish();
    
    void pause();
    void end();
    void resume();
    void sound();
    void music();
    void reset();
    
    void playSound();
    bool getSoundStatus();
    ~GameScene();
    
private:
    DotsLayer* _dotsLayer;
    PanelLayer* _panelLayer;
    BackgroundLayer* _backgroundLayer;
    TouchLayer* _touchLayer;
    MenuLayer* _menuMainLayer;
    MenuLayer* _menuGameEndLayer;
    
    float _soundVolume;
    float _musicVolume;
    bool _soundOn;
    bool _musicOn;
    
    void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
};


#endif
