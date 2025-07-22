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
#include "ColorSprite/ColorSprite.h"

using namespace cocos2d;

class ChooseColorLayer : public CCLayer {
    
    
public:
    CCSize v_size ;
    CCPoint poszero;
    CREATE_FUNC(ChooseColorLayer);
    virtual bool init();
    bool buyState;
    void setButton();
    void colorClick(CCObject* obj);
    CCMenuItemSprite* color;
    CCSprite* bg;
    
    int colorMaxDis;
    int colorMinDis;
    int colorDisX;
    int colorDisY;
    float scaleColor;
    
    void SetMenuItem(CCMenuItemSprite* item);
    
    virtual void registerWithTouchDispatcher();                 //注册单点触摸点击事件
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
    
    void resetColorPos();
    void cacheCayonTexture(CCObject* _parent);
    void canClickPen();
    
    void addLock(cocos2d::CCObject* _parent,int _index);
    
    int beginY;
    int endY;
    int startY;
    int finishY;
    int touchMoveDis;
    int selectPenIndex;
    int selectPenColorIndex;
    int penMoveDisY;
    int firstPenIndex;  
    int clickPenIndexArr[40];
    int crayonTextureIndex[37];
    int paintColorArr[37];
    int totlePenCount;
    int colorPenPos[40] ;

    bool clickPen;
    CCSprite* touchColorBg;
    
};

#endif /* ChooseColorLayer_hpp */
