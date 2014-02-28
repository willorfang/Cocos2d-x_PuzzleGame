//
//  Item.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "Item.h"
#include "StaticData.h"

USING_NS_CC;

Item* Item::create(ItemType type)
{
    Item* item = new Item();
    item->init(type);
    item->autorelease();
    return item;
}

bool Item::init(ItemType type)
{
    _type = type;
    
    CCArray* itemNames = STATIC_DATA_ARRAY("item");
    const char * itemName = ((CCString *)itemNames->objectAtIndex(type))->getCString();
    CCTexture2D* cache = CCTextureCache::sharedTextureCache()->addImage(itemName);
    _itemSprite = CCSprite::createWithTexture(cache);
    
    CCSize size = STATIC_DATA_SIZE("itemSize");
    float scaleX = size.width/_itemSprite->getContentSize().width;
    float scaleY = size.height/_itemSprite->getContentSize().height;
    _itemSprite->setScaleX(scaleX);
    _itemSprite->setScaleY(scaleY);
    
    return true;
}


CCRect Item::getArea()
{
    return _itemSprite->boundingBox();
}

void Item::disappear()
{
    CCScaleTo* actionScale = CCScaleTo::create(0.3f, 0.01);
    CCFadeOut* actionFadeOut = CCFadeOut::create(0.2f);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Item::disappear_CallFunc));
    CCSequence* seq = CCSequence::create(actionScale, actionFadeOut, callFunc, NULL);
    _itemSprite->runAction(seq);
}

void Item::disappear_CallFunc()
{
    _itemSprite->getParent()->removeChild(_itemSprite);
}

void Item::moveTo_CallFunc()
{
    
}

void Item::moveTo(CCPoint destination) {
    CCMoveTo* move = CCMoveTo::create(0.5f, destination);
    CCEaseBounceOut* bounce = CCEaseBounceOut::create(move);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Item::moveTo_CallFunc));
    CCSequence* seq = CCSequence::create(bounce, callFunc, NULL);
    _itemSprite->runAction(seq);
}
