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
#include "cocos-ext.h"

using namespace cocos2d;

//class SelectAnimalScene : public CCLayer {
class SelectAnimalScene : public cocos2d::CCLayer, public extension::CCScrollViewDelegate{
    extension::CCScrollView *scrollView;
private:
    void addLock(cocos2d::CCObject* _parent,int _index);
    void selectAdsOrIAP(int _pageIndex);
    
public:
    CCSize s;
    CCPoint poszero;
//    int xDis=0;
    virtual void scrollViewDidScroll(extension::CCScrollView *view);
    virtual void scrollViewDidZoom(extension::CCScrollView *view);
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void backClick();
    
    void initAnimals();
    void selectAni(CCObject *sender) ;
    void bubbleShake(cocos2d::CCObject *sender);
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    CCPoint pos;
    int beginPosY=0;
    int endPosY=0;
    
    int moveDisY=0;
//    int posIndex=0;
//    int aniIndex =0;
    void update(float date);
    
    void resetContainerPos();
//    void moveAniPos(CCObject *pSender);
    void resetAniPos();
    
    void clickMp3();
    
    bool touchEnd=true;
    void resetTouch();
//    CCPointArray* aniPosArr;
    
//    void resetButtonPos();
    CCLayer *containerLayer;
    CREATE_FUNC(SelectAnimalScene);
};

#endif /* SelectAnimalScene_hpp */
