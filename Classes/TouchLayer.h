//
//  TouchLayer.h
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#ifndef __Dots__TouchLayer__
#define __Dots__TouchLayer__

#include "cocos2d.h"
class GameScene;

class TouchLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(TouchLayer);
    bool init();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void setTouchEnabled(bool flag);
protected:
    GameScene* getGameScene();
    cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch *touch);
    
};

#endif /* defined(__Dots__TouchLayer__) */
