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
#include "ui/CocosGUI.h"
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
    ui::Widget* menuItem;
    Sprite* bg;
    
    int colorMaxDis;
    int colorMinDis;
    int colorDisX;
    int colorDisY;
    float scaleColor;
    
    void SetMenuItem(ui::Widget* item);
    
    virtual void registerWithTouchDispatcher();                 //注册触摸事件
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    
    void addLock(cocos2d::Ref* _parent,int _index);
    
    float beginY;
    float endY;
    int selectPenIndex;
    int selectPenColorIndex;
    int firstPenIndex;  
    int clickPenIndexArr[40];
    int paintColorArr[37];
    int totlePenCount;
    float colorPenPos[40] ;

    bool clickPen;
    Sprite* touchColorBg;
    
};

#endif /* ChooseColorLayer_hpp */
