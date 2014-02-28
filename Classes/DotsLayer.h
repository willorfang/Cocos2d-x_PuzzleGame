//
//  DotsLayer.h
//  Dots
//
//  Created by Wei Fang on 2/13/14.
//
//

#ifndef Dots_DotsLayer_h
#define Dots_DotsLayer_h
#include "cocos2d.h"
#include "Item.h"

class DotsLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(DotsLayer);
    bool init();
    ~DotsLayer();
    
    bool addDotsBegan(cocos2d::CCPoint point);
    void addDotsMoved(cocos2d::CCPoint point);
    void addDotsEnded(cocos2d::CCPoint point);
    
private:
    void loadItems();
    ItemType getRandomItemType();
    Item* getItemByPosition(cocos2d::CCPoint point);
    void dotsDisappearAndDropDown();
    bool neighbourbood(Item* a, Item* b);
    bool existInSelectedItems(Item* item);
    float getHeightUnit();
    float getWidthUnit();
    
    cocos2d::CCArray* _itemArray;
    cocos2d::CCArray* _selectedItems;
    bool _selectEnded;
};

#endif
