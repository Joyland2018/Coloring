//
//  SelectBrushLayer.hpp
//  DrDino
//
//  Created by chuining meng on 2020/4/30.
//

#ifndef SelectBrushLayer_hpp
#define SelectBrushLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class SelectBrush : public CCLayer {
        
public:
    CCSize v_size;
    CCPoint poszero;
    CREATE_FUNC(SelectBrush);
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    void setButton();
    void brushClick(CCObject* obj);
    CCMenuItemSprite* brushBtu;
    
    void SetMenuItem(CCMenuItemSprite* item);
};

#endif /* SelectBrushLayer_hpp */
