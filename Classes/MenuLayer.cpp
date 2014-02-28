//
//  MenuLayer.cpp
//  Dots
//
//  Created by Wei Fang on 2/17/14.
//
//

#include "MenuLayer.h"
#include "GameScene.h"

USING_NS_CC;

MenuLayer* MenuLayer::create(MenuType type)
{
    MenuLayer* menu = new MenuLayer();
    menu->init(type);
    menu->autorelease();
    return menu;
}

bool MenuLayer::init(MenuType type)
{
    if(CCLayer::init()){
        _backgroundLayer = BackgroundLayer::create();
        _backgroundLayer->setOpacity(200);
        this->addChild(_backgroundLayer);
        this->createMenu(type);
        return true;
    }
    return false;
}

void MenuLayer::createMenu(MenuType type)
{
    int fontSize = 28;
    CCString* fontName = CCString::create("Thonburi");
    
    CCLabelTTF* label = CCLabelTTF::create("Continue Game", fontName->getCString(), fontSize);
    label->setColor(ccc3(75, 0, 130));
    CCMenuItemLabel* resume = CCMenuItemLabel::create(label, this, menu_selector(MenuLayer::resume));
    label = CCLabelTTF::create("Sound On", fontName->getCString(), fontSize);
    label->setColor(ccc3(75, 0, 130));
    CCMenuItemLabel* soundOn = CCMenuItemLabel::create(label);
    label = CCLabelTTF::create("Sound Off", fontName->getCString(), fontSize);
    label->setColor(ccc3(75, 0, 130));
    CCMenuItemLabel* soundOff = CCMenuItemLabel::create(label);
    _sound = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::sound), soundOn, soundOff, NULL);
    
    label = CCLabelTTF::create("Music On", fontName->getCString(), fontSize);
    label->setColor(ccc3(75, 0, 130));
    CCMenuItemLabel* musicOn = CCMenuItemLabel::create(label);
    label = CCLabelTTF::create("Music Off", fontName->getCString(), fontSize);
    label->setColor(ccc3(75, 0, 130));
    CCMenuItemLabel* musicOff = CCMenuItemLabel::create(label);
    _music = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::music), musicOn, musicOff, NULL);
    
    label = CCLabelTTF::create("New Game", fontName->getCString(), fontSize);
    label->setColor(ccc3(75, 0, 130));
    CCMenuItemLabel* reset = CCMenuItemLabel::create(label, this, menu_selector(MenuLayer::reset));
    
    CCMenu* menu;
    if (type == t_Menu_Main) {
        menu = CCMenu::create(resume, _sound, _music, reset, NULL);
    } else if (type == t_Menu_EndGame) {
        menu = CCMenu::create(_sound, _music, reset, NULL);
    }
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu);
}

void MenuLayer::resume()
{
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->resume();
}

void MenuLayer::sound()
{
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->sound();
}
void MenuLayer::music()
{
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->music();
}
void MenuLayer::reset()
{
    GameScene* gameScene = (GameScene*)this->getParent();
    gameScene->reset();
}

void MenuLayer::setSoundAndMusicVolume(float soundVolume, float musicVolume)
{
    bool soundFlag = soundVolume>0;
    bool musicFlag = musicVolume>0;
    _sound->setSelectedIndex(soundFlag);
    _music->setSelectedIndex(musicFlag);
}