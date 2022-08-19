//
//  ColorSprite.hpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#ifndef ColorSprite_hpp
#define ColorSprite_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;

class ColorSprite : public cocos2d::CCSprite {
    
    
public:

    static ColorSprite* CreateColor(const char* spName,CCPoint pos ,CCNode* parent,int ptag);
    bool isTouched(cocos2d::CCTouch *pTouch);
    void PlatingSprite(ccColor3B color, CCRenderTexture* canvas);
    bool CheckAlpha(CCPoint point);
    CCDrawNode* m_Drawer ;
    
private:
};

#endif /* ColorSprite_hpp */
