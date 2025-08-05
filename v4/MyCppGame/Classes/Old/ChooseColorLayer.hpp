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
#include "ColorSprite.h"

using namespace cocos2d;

class ChooseColorLayer : public CCLayer {
    
    
public:
    CCSize v_size ;
    CCPoint poszero;
    CREATE_FUNC(ChooseColorLayer);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    ChooseColorLayer();
    ~ChooseColorLayer();
    
    void setButton();
    void colorClick(CCObject* obj);
    CCMenuItemSprite* color;
    CCSprite* bg;
    
    int colorMaxDis;
    int colorMinDis;
    int colorDisX;
    float colorDisY;
    float scaleColor;
    
    void SetMenuItem(CCMenuItemSprite* item);
    
    virtual void registerWithTouchDispatcher();                 //注册单点触摸点击事件
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    void resetColorPos();
    void cacheCayonTexture(CCObject* _parent);
    void canClickPen();
    
    void addLock(cocos2d::CCObject* _parent,int _index);
    
    bool checkIsTouchingLayer(CCPoint _checkPos);
    
    void setColorBlock();
    void resetColorBlockPos(bool isReset);
    void moveToColorIndex(int colorIndex,bool isReset);
    
    bool isDragging;
    int beginY;
    int endY;
    int startY;
    int finishY;
    int touchMoveDis;
    int selectPenIndex;
    int selectPenColorIndex;
    int firstPenIndex;  
    int clickPenIndexArr[50];
    int crayonTextureIndex[37];
    int paintColorArr[50];
    int totlePenCount;
    int colorPenPos[50] ;

    
    bool clickPen;
    
    
    int freeIndexMin ;
    int freeIndexMax ;
    
    float newbieGuideScrollSpeed;  // 初始化滚动速度
    void startNewbieGuide();
    void finishNewbieGuide();
    void update(float dt);
    void showFirstGuide();
    void resetGuideFingerPos();
    void removeFirstGuide();
    
    void showFinger();
    void showFingerAction();
    void removeFinger();
    
//    CCSprite* touchColorBg;
    
};

#endif /* ChooseColorLayer_hpp */
