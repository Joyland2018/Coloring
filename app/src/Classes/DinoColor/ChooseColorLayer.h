//
//  ChooseColorLayer.hpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/19.
//

#ifndef ChooseColorLayer_hpp
#define ChooseColorLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class ChooseColorLayer : public CCLayer {
    
    
public:
    CCSize v_size ;
    CCPoint poszero;
    CREATE_FUNC(ChooseColorLayer);
    virtual bool init();
    
    void setButton();
    void colorClick(CCObject* obj);
    CCMenuItemSprite* color;
    
    void SetMenuItem(CCMenuItemSprite* item);
};

#endif /* ChooseColorLayer_hpp */
