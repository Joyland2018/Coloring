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

class ChooseColorLayer : public Layer {
    
    
public:
    Size v_size ;
    Vec2 poszero;
    CREATE_FUNC(ChooseColorLayer);
    virtual bool init();
    bool buyState;
    void setButton();
    void colorClick(Ref* obj);
    MenuItemSprite* color;
    Sprite* bg;
    
    int colorMaxDis;
    int colorMinDis;
    int colorDisX;
    int colorDisY;
    float scaleColor;
    
    void SetMenuItem(MenuItemSprite* item);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    void resetColorPos();
    void cacheCayonTexture(Ref* _parent);
    void canClickPen();
    
    void addLock(cocos2d::Ref* _parent,int _index);
    
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
    Sprite* touchColorBg;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
private:
    EventListenerTouchOneByOne* _touchListener;
    
};

#endif /* ChooseColorLayer_hpp */
