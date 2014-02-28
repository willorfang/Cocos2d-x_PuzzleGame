//
//  PanelLayer.h
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#ifndef Dots_PanelLayer_h
#define Dots_PanelLayer_h
#include "cocos2d.h"

class PanelLayer : public cocos2d::CCLayer{
public:
    CREATE_FUNC(PanelLayer);
    bool init();
    void back();
    void updateScore(int score);
    void reset();
    void setTouchEnabled(bool enabled);
    
private:
    cocos2d::CCLabelTTF* _score;
    cocos2d::CCLabelTTF* _time;
    cocos2d::CCMenu* _menu;
    int _curTime;
    int _curScore;
    void scheduleStart();
    void scheduleTimeUp();
    void updateTime();
};


#endif
