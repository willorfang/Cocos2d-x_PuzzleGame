//
//  Item.h
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#ifndef __Dots__Item__
#define __Dots__Item__
#include "cocos2d.h"

typedef enum {
    t_Item_1 = 0,
    t_Item_2,
    t_Item_3,
    t_Item_4,
    t_Item_5,
    t_Item_6,
    t_Item_Count
} ItemType;

class Item : public cocos2d::CCObject
{
public:
    static Item* create(ItemType type = t_Item_1);
    bool init(ItemType type = t_Item_1);
    
    CC_SYNTHESIZE(cocos2d::CCSprite*, _itemSprite, ItemSprite);
    CC_SYNTHESIZE(ItemType, _type, Type);
    
    cocos2d::CCRect getArea();
    void moveTo(cocos2d::CCPoint destination);
    void disappear();
    
private:
    void disappear_CallFunc();
    void moveTo_CallFunc();
};


#endif /* defined(__Dots__Item__) */
