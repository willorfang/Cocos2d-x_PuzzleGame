//
//  MenuLayer.h
//  Dots
//
//  Created by Wei Fang on 2/17/14.
//
//

#ifndef __Dots__MenuLayer__
#define __Dots__MenuLayer__

#include "cocos2d.h"
#include "BackgroundLayer.h"

typedef enum {
    t_Menu_Main = 0,
    t_Menu_EndGame
} MenuType;

class MenuLayer : public cocos2d::CCLayer
{
public:
    static MenuLayer* create(MenuType type = t_Menu_Main);
    bool init(MenuType type = t_Menu_Main);
    
    void setSoundAndMusicVolume(float soundVolume, float musicVolume);
    
protected:
    void resume();
    void sound();
    void music();
    void reset();
    
    
    void createMenu(MenuType type);
    
    cocos2d::CCMenuItemToggle* _sound;
    cocos2d::CCMenuItemToggle* _music;
    BackgroundLayer* _backgroundLayer;
};

#endif /* defined(__Dots__MenuLayer__) */
