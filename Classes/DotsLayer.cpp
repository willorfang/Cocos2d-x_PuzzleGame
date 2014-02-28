//
//  DotsLayer.cpp
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#include "DotsLayer.h"
#include "StaticData.h"
#include "GameScene.h"
#include <iostream>
#include <map>

#define PADDING_SIZE 0
USING_NS_CC;

bool DotsLayer::init()
{
    if(CCLayer::init())
    {
        _selectedItems = CCArray::create();
        _itemArray = CCArray::create();
        CC_SAFE_RETAIN(_selectedItems);
        CC_SAFE_RETAIN(_itemArray);
        
        _selectEnded = true;
        //
        loadItems();
        return true;
    }
    return false;
}

void DotsLayer::loadItems()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float itemSizeXWithPadding = this->getWidthUnit();
    float itemSizeYWithPadding = this->getHeightUnit();
    
    int itemCountX = winSize.width/itemSizeXWithPadding - 1;
    int itemCountY = winSize.height*0.9/itemSizeYWithPadding - 1;
    float startX = (((int)winSize.width)%((int)itemSizeXWithPadding))/2 + itemSizeXWithPadding;
    float startY = (((int)(winSize.height*0.9))%((int)itemSizeYWithPadding))/2 + itemSizeYWithPadding;
    
    for (int i=0; i<itemCountX; i++) {
        for (int j=0; j<itemCountY; j++) {
            ItemType type = getRandomItemType();
            Item* item = Item::create(type);
            item->getItemSprite()->setPosition(ccp(startX+i*itemSizeXWithPadding, startY+j*itemSizeYWithPadding));
            _itemArray->addObject(item);
            this->addChild(item->getItemSprite());
        }
    }
}

ItemType DotsLayer::getRandomItemType()
{
    srandom(time(NULL));
    return (ItemType) (CCRANDOM_0_1()*t_Item_Count);
}

Item* DotsLayer::getItemByPosition(CCPoint point)
{
    for (int i=0; i<_itemArray->count(); i++) {
        Item* item = (Item*) _itemArray->objectAtIndex(i);
        if (item->getArea().containsPoint(point)) {
            return item;
        }
    }
    return NULL;
}

float DotsLayer::getWidthUnit()
{
    CCSize itemSize = STATIC_DATA_SIZE("itemSize");
    return itemSize.width + PADDING_SIZE;
}

float DotsLayer::getHeightUnit()
{
    CCSize itemSize = STATIC_DATA_SIZE("itemSize");
    return itemSize.height + PADDING_SIZE;
}

bool DotsLayer::neighbourbood(Item* a, Item* b)
{
    CCPoint posA = a->getItemSprite()->getPosition();
    CCPoint posB = b->getItemSprite()->getPosition();
    
    float itemSizeXWithPadding = this->getWidthUnit();
    float itemSizeYWithPadding = this->getHeightUnit();
    
    return (posA.x==posB.x && (posA.y==posB.y-itemSizeYWithPadding || posA.y==posB.y+itemSizeYWithPadding))
        || (posA.y==posB.y && (posA.x==posB.x-itemSizeXWithPadding || posA.x==posB.x+itemSizeXWithPadding));
}

bool DotsLayer::existInSelectedItems(Item* item)
{
    return _selectedItems->containsObject(item);
}

bool DotsLayer::addDotsBegan(CCPoint point)
{
    _selectEnded = false;
    _selectedItems->removeAllObjects();

    this->addDotsMoved(point);
    return true;
}

void DotsLayer::addDotsMoved(cocos2d::CCPoint point)
{
    if (_selectEnded) {
        return;
    }
    
    Item* currentItem = this->getItemByPosition(point);
    Item* lastItem = (Item*)_selectedItems->lastObject();
    if (currentItem != NULL) {
        if (_selectedItems->count() == 0) {
            _selectedItems->addObject(currentItem);
        } else if (currentItem != lastItem) {
            if (currentItem->getType() == lastItem->getType() && this->neighbourbood(lastItem, currentItem)) {
                if (!existInSelectedItems(currentItem))
                {
                    _selectedItems->addObject(currentItem);
                }
            } else {
                _selectEnded = true;
            }
        }
    }
}

void DotsLayer::addDotsEnded(cocos2d::CCPoint point)
{
    this->addDotsMoved(point);
    _selectEnded = true;
    
    this->dotsDisappearAndDropDown();
}

void DotsLayer::dotsDisappearAndDropDown()
{
    if (_selectedItems->count() >= 2) {
        
        // calculate dropdown distance: map (key, value)
        // key: position x where there are some items disappeared
        // value:
        //   y: position y
        //   count: how many disappeared
        typedef struct {
            float y;
            int count;
        } Info;
        std::map<float, Info> dropDownMap;
        
        CCObject* itemDisappear;
        CCARRAY_FOREACH(_selectedItems, itemDisappear)
        {
            // calculate map
            CCPoint pos = ((Item*)itemDisappear)->getItemSprite()->getPosition();
            float x = pos.x;
            if (dropDownMap.find(x) == dropDownMap.end()) {
                Info info;
                info.y = pos.y;
                info.count = 1;
                dropDownMap[x] = info;
            } else {
                dropDownMap[x].count += 1;
            }
            
            // deleted items disappeared
            ((Item*)itemDisappear)->disappear();
            _itemArray->removeObject(itemDisappear);
        }
        
        // play sound
        GameScene * gameScene = (GameScene*) this->getParent();
        if (gameScene->getSoundStatus()) {
            gameScene->playSound();
        }
        
        //update score
        gameScene->updateScore(_selectedItems->count());
        
        // dropdown
        CCObject* item;
        CCARRAY_FOREACH(_itemArray, item)
        {
            CCPoint pos = ((Item*)item)->getItemSprite()->getPosition();
            float x = pos.x;
            if (dropDownMap.find(x) != dropDownMap.end()
                && dropDownMap[x].y < pos.y) {
                float yTo = pos.y - dropDownMap[x].count * this->getHeightUnit();
                ((Item*)item)->moveTo(ccp(x, yTo));
            }
        }
    }
}

DotsLayer::~DotsLayer()
{
    CC_SAFE_RELEASE_NULL(_selectedItems);
    CC_SAFE_RELEASE_NULL(_itemArray);
}