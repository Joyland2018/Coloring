//
//  SelectAnimalScene.hpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/30.
//

#ifndef SelectAnimalScene_h
#define SelectAnimalScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;

//class SelectAnimalScene : public Layer {
class SelectAnimalScene : public cocos2d::Layer, public cocos2d::extension::ScrollViewDelegate{
    cocos2d::extension::ScrollView *scrollView;
private:
    void addLock(cocos2d::Ref* _parent,int _index);
    void selectAdsOrIAP(int _pageIndex);
    
public:
    Size s;
    Vec2 poszero;
//    int xDis=0;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView *view);
    
    virtual bool init();
    static cocos2d::Scene* scene();
    void backClick();
    
    void initAnimals();
    void selectAni(Ref *sender) ;
    void bubbleShake(cocos2d::Ref *sender);
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    Vec2 pos;
    int beginPosY=0;
    int endPosY=0;
    
    int moveDisY=0;
//    int posIndex=0;
//    int aniIndex =0;
    void update(float date);
    
    void resetContainerPos();
//    void moveAniPos(Ref *pSender);
    void resetAniPos();
    
    void clickMp3();
    
    bool touchEnd=true;
    void resetTouch();
//    PointArray* aniPosArr;
    
//    void resetButtonPos();
    Layer *containerLayer;
    CREATE_FUNC(SelectAnimalScene);
};

#endif /* SelectAnimalScene_hpp */
