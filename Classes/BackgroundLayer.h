//
//  BackgroundLayer.h
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#ifndef Dots_BackgroundLayer_h
#define Dots_BackgroundLayer_h

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer{
public:
    CREATE_FUNC(BackgroundLayer);
    bool init();
    void setOpacity(GLubyte opa);
private:
    cocos2d::CCSprite* _background;
};


#endif
