//
//  ChooseColorLayer.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/19.
//

#include "ChooseColorLayer.hpp"
#include "GameManager.h"
#include "cocos-ext.h"
#include "ColorManager.hpp"
#include "SimpleAudioEngine.h"
#include "BuyPage.h"
#include "ColorCanvasView.h"

using namespace CocosDenshion;
using namespace cocos2d::extension ;
//
//#define Tag  100
//
//#define Mark  1000
//
//const unsigned int    kNormalTag = 0x1;
//const unsigned int    kSelectedTag = 0x2;
//const unsigned int    kDisableTag = 0x3;

enum{
    kBuyLayerTag = 0,
    kLockTag = 2,
    kColorBgTag = 33,
    kPenColorTag = 111,
};

bool ChooseColorLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    buyState= false;
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    clickPen = false;
    selectPenColorIndex = 0;
    ColorManager::shared()->colorNums = 0;
//    penMoveDisY = 0;
    

    for (int i=0; i<24; i++) {
        clickPenIndexArr[i] = 0;
//        crayonTextureIndex[i]=0;
        paintColorArr[i] = 0;
        colorPenPos[i] = 0;
    }

    
    float fix_w = 0 ;
       if (GameManager::sharedManager()->isIphoneX()) {
           fix_w = 70;
       }
    
//    bg = CCSprite::create("DinoColor/swatch_color.png");
//    bg->setPosition(ccp(v_size.width/4*2.2-poszero.x+fix_w,v_size.height/2+10));
//
//    this->addChild(bg);
    touchColorBg = NULL;
    endY = 0;
    beginY = 0;
    

    
    this->setButton();
    this->setTouchEnabled(true);
    return true;
}

void ChooseColorLayer::setButton()
{
    float fix_w = 0 ;
       if (GameManager::sharedManager()->isIphoneX()) {
           fix_w = 130;
       }
   
    
    float w_fix = 0 ;
//    if (GameManager::sharedManager()->isIphoneX()) {
//        w_fix = 50 ;
//    }
    
    CCSprite* colorBg = CCSprite::create("DinoColor/color_bg.png");
    colorBg->setPosition(ccp(v_size.width -80 - w_fix-poszero.x,v_size.height/2));
//    toolsBg->setScaleX(0.7);
    colorBg->setTag(kColorBgTag);
    this->addChild(colorBg,2) ;
    
//    CCLOG("---%f---",colorBg->getContentSize().height/1.07);
    
    colorDisY=0;            //笔间距
    colorDisX=0;            //横坐标偏移
    totlePenCount =0;              //笔触数量
    firstPenIndex=0;            //初始笔
    int origiPenX=0;            //初始笔的位置
    colorMaxDis=0;
    colorMinDis = 0;
    scaleColor=0;
    

    



    
    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
        int penColorArr[24] = {23,32,18,2,8,12,5,1,3,4,6,37,25,28,7,10,13,31,24,14};
        for (int i=0; i<24; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        
        totlePenCount = 24;
        colorDisY = 40;                 //笔间距
        scaleColor  = 0.8;
        firstPenIndex = 22;
        
        selectPenIndex = ColorManager::shared()->curPaintIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPaint == false) {
            for (int i = 0; i < 24; i++) {
                ColorManager::shared()->colorPaintPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 24; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPaintPos[i];
        }
            
//        ColorManager::shared()->m_pColor = ccc3(98,170,50);
    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        int penColorArr[20] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 60;
        scaleColor  = 0.65;
        colorDisX = 10;
        firstPenIndex = 20;
//        ColorManager::shared()->m_pColor = ccc3(2,68,246);
        
        selectPenIndex = ColorManager::shared()->curLargebrushIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchLargebrush == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorLargebrushPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorLargebrushPos[i];
        }
        
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        int penColorArr[20] = {23,32,18,5,8,12,2,37,4,3,1,6,7,28,25,10,13,31,24,14};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 45;
        scaleColor  = 0.8;
//        maxDis = (colorDisY*37-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        colorMaxDis = colorBg->getContentSize().height/1.07+440;
//        colorMinDis = -440;
        firstPenIndex = 20;
        
        selectPenIndex = ColorManager::shared()->curCrayonIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchCrayon == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorCrayonPos[i] =colorMaxDis-i*colorDisY;
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorCrayonPos[i];
        }
        
//        ColorManager::shared()->m_pColor = ccc3(255,255,50);
    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
        int penColorArr[24] = {23,2,12,32,8,18,5,3,1,37,4,6,13,28,7,10,25,31,24,14};
        for (int i=0; i<24; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 24;
        colorDisY = 40;
        scaleColor  = 0.8;
//        maxDis = 350;
//        colorMaxDis = colorBg->getContentSize().height/1.07+390;
//        colorMinDis = -350;
        firstPenIndex = 22;
        selectPenIndex = ColorManager::shared()->curPencilIndex;
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPencil == false) {
            for (int i = 0; i < 24; i++) {
                ColorManager::shared()->colorPencilPos[i] =colorMaxDis-i*colorDisY;
            }
        }
        for (int i = 0; i < 24; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPencilPos[i];
        }
            
//        ColorManager::shared()->m_pColor = ccc3(0,0,0);
    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        int penColorArr[20] = {7,2,18,32,8,12,5,4,37,1,6,3,25,28,23,10,13,31,14,24};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 65;
        scaleColor  = 0.6;
        colorDisX = 10;
//        maxDis = 900;
//        colorMaxDis = colorBg->getContentSize().height/1.07+770;
//        colorMinDis = -900;
        firstPenIndex = 20;
        
        selectPenIndex = ColorManager::shared()->curPaintbucketIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPaintbucket == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorPaintbucketPos[i] =colorMaxDis-i*colorDisY;
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPaintbucketPos[i];
        }
        
//        ColorManager::shared()->m_pColor = ccc3(248,37,15);
    }
    



    if (selectPenIndex>11 && selectPenIndex<16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
        ColorManager::shared()->firstColorValue(selectPenIndex);
    }else if(selectPenIndex>15 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)){
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  paintColorArr[selectPenIndex-4];
        ColorManager::shared()->changeCurColor();
        selectPenColorIndex = paintColorArr[selectPenIndex-4];
    }else{
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  paintColorArr[selectPenIndex];
        ColorManager::shared()->changeCurColor();
        selectPenColorIndex = paintColorArr[selectPenIndex];
    }
    
    
//    selectPenColorIndex = paintColorArr[selectPenIndex];

    

    
    colorMinDis = colorMaxDis-(totlePenCount-1)*colorDisY;
//    int crayonIndex[37] = {9,8,10,21,24,12,31,36,1,3,4,5,6,7,2,20,17,26,42,13,16,15,14,19,21,23,22,25,27,28,29,30,32,33,34,35,18};

//    CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
    clickPenIndexArr[selectPenIndex] = 1;
    
    for (int i = 0; i < totlePenCount; i++) {
//        crayonTextureIndex[i] = crayonIndex[i];
        if (i==selectPenIndex) {
            origiPenX = 25;
        }else{
            origiPenX = 0;
        }
        CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s_tools_cover.png",ColorManager::shared()->curPenName) ;
        CCSprite* penColor = CCSprite::create(name->getCString());
        penColor->setPosition(ccp(colorBg->getContentSize().width/3-origiPenX,colorPenPos[i]+400));
        penColor->setTag(kPenColorTag+i);
        penColor->setScale(scaleColor);
        colorBg->addChild(penColor);
        
//        CCSprite* tmp2 = CCSprite::create(name->getCString());
//        CCSize size2 = tmp2->getContentSize();
//        CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
//        CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
//        CCControlButton *button = CCControlButton::create(sprite2) ;
//        button->setPreferredSize(size2) ;
//        button->setTag(Tag+i);
//        button->setPosition(ccp(v_size.width -130-poszero.x-colorDisX,v_size.height/1.07+maxDis-i*colorDisY)) ;
//        button->setScale(scaleColor);
////           button->setPosition(ccp(0, 0)) ;
//        this->addChild(button, 3) ;
        
        CCSprite* brushIconShadow = NULL;
//        if (strcmp(ColorManager::shared()->curPenName, "crayon")==0 ) {
//            CCTexture2D* texture = ColorManager::shared()->maskedWithSpriteTexture(CCSprite::create(CCString::createWithFormat("DinoColor/crayon_texture/crayon_texture_%d.png",crayonTextureIndex[i])->getCString()), CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName)->getCString()), ccp(0.5, 0.5));
//            brushIconShadow = CCSprite::createWithTexture(texture);
//        }else{
        
        if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>11 && i<16) {
            brushIconShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_colorshadow%d.png",ColorManager::shared()->curPenName,i)->getCString());
        }else{
            
                brushIconShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName)->getCString());
            ccColor3B brushColor;
            if((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15){
                brushColor = ColorManager::shared()->getCurColor(paintColorArr[i-4]);
            }else{
                brushColor = ColorManager::shared()->getCurColor(paintColorArr[i]);
            }
                
                brushIconShadow->setColor(brushColor);
        }

//        }
        
        brushIconShadow->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
//        brushIconShadow->setTag(Tag+i);
        penColor->addChild(brushIconShadow,-1);
        
//        CCSprite* mark = CCSprite::create("DinoColor/brush-select.png");
//        mark->setTag(Mark);
//        mark->setPosition(ccp(size2.width/2, size2.height/2 ));
//        button->addChild(mark);
//        if (ColorManager::shared()->SelectBrushTag == Tag+i) {
//            mark->setVisible(true);
//        }else{
//           mark->setVisible(false);
//        }
        penColor->runAction(CCMoveBy::create(0.3, ccp(0, -400)));
        
        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") && (i<(7) || i>(11))) {
            this->addLock(penColor, i);
            CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s_iap_shadow.png",ColorManager::shared()->curPenName) ;
            CCSprite* penIapShadow = CCSprite::create(name->getCString());
            penIapShadow->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
            penColor->addChild(penIapShadow);
        }
//        ColorManager::shared()->colorPenPos[i]  = penColor->getPosition().y-400;
//        button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), CCControlEventTouchUpInside) ;
    }
//    for (int i=0; i<37; i++) {
//        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[i]);
//    }
//       for (int i = 0; i < 37; i++) {
           
//           CCString* name = CCString::createWithFormat("DinoColor/color/color_%d.png",(i+1)) ;
//           CCSprite* tmp2 = CCSprite::create(name->getCString());
//           CCSize size2 = tmp2->getContentSize();
//           CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
//           CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
//           CCControlButton *button = CCControlButton::create(sprite2) ;
//           button->setPreferredSize(size2) ;
//           button->setTag(Tag+i);
//           button->setPosition(ccp(v_size.width -160-poszero.x,v_size.height/1.07+800-i*100+200)) ;
//           this->addChild(button, 3) ;
////           CCSprite* mark = CCSprite::create("DinoColor/color-selected.png");
////           mark->setTag(Mark);
////           mark->setPosition(ccp(size2.width/2, size2.height/2));
////           button->addChild(mark);
////           if (ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] == Tag+i) {
////               mark->setVisible(true);
////           }else{
////              mark->setVisible(false);
////           }
////
//           button->runAction(CCMoveBy::create(0.5, ccp(0, -200)));
//           button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), CCControlEventTouchUpInside) ;
//       }
}



void ChooseColorLayer::addLock(CCObject *_parent,int _index) {

    const char* lockName = "lock";
    
    CCSprite* parentSpr = (CCSprite*)_parent;
    
    
    
    CCSprite* locked = CCSprite::create(CCString::createWithFormat("iap/%s.png",lockName)->getCString()) ;   //那么设置一个锁的精灵
    if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        locked->setScale(0.7) ;
        locked->setPosition(ccp(parentSpr->getContentSize().width/2.5, parentSpr->getContentSize().height/1.7));
    }else  if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        locked->setScale(0.8) ;
        locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.7));
    }else{
        locked->setScale(scaleColor-0.3) ;
        locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.9));
    }
    
//    locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.7));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked,10) ;
}




void ChooseColorLayer::colorClick(CCObject *obj)
{
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);

    CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+selectPenIndex);
    if(penButton!=NULL){
//        penButton->setScale(scaleColor);
        penButton->runAction(CCSpawn::create(CCSequence::create(CCScaleTo::create(0.1, scaleColor+0.2),
                                                                CCScaleTo::create(0.1, scaleColor),
                                                                                   NULL),
                                             CCEaseIn::create(CCMoveBy::create(0.3, ccp(-25, 0)), 0.3),
                                             NULL));
    }
    
    for (int i=0; i<totlePenCount; i++) {
        CCSprite* otherPenButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
        if (i!=selectPenIndex && otherPenButton!=NULL) {
            otherPenButton->setPositionX(colorBg->getContentSize().width/3);
            otherPenButton->runAction(CCScaleTo::create(0.2, scaleColor));
            clickPenIndexArr[i] = 0;
        }
    }
    
//    int tag = ((CCNode*)obj)->getTag();
//    for (int i = 0; i < 15; i++) {
//        CCNode* node =this->getChildByTag(Tag+i);
//        node->getChildByTag(Mark)->setVisible(false);
//    }
//    ((CCNode*)obj)->getChildByTag(Mark)->setVisible(true);
    
//    CCSprite* pait = ( CCSprite*)color->getSelectedImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
//    pait = ( CCSprite*)color->getNormalImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
//    color->unselected();
//    CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.changecolor");
//    this->removeFromParent();
    if (selectPenIndex>11 && selectPenIndex<16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
        ColorManager::shared()->firstColorValue(selectPenIndex);
    }else{
        ColorManager::shared()->colorNums = 0;
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  selectPenColorIndex;
        ColorManager::shared()->changeCurColor();
    }




    ColorManager::shared()->m_DrawType = Draw_Point ;
//    if (strcmp(ColorManager::shared()->curPenName, "crayon")==0) {
//        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  crayonTextureIndex[selectPenIndex];
//        CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.changecolor");

//    }

}

void ChooseColorLayer::SetMenuItem(CCMenuItemSprite *item)
{
    color = item;
}


void ChooseColorLayer::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool ChooseColorLayer::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();

    location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint preLocation = touch->getPreviousLocationInView();
    startY = location.y;
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    buyState=ColorManager::shared()->buyState;
    if (colorBg!=NULL && colorBg->boundingBox().containsPoint(location)&&!buyState) {
        touchColorBg = colorBg;
        if(strcmp(ColorManager::shared()->curPenName, "eraser")!=0){
            ColorManager::shared()->scrollPenBoard = true;
        }
        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
            ColorManager::shared()->firstTouchPaint = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
            ColorManager::shared()->firstTouchLargebrush = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
            ColorManager::shared()->firstTouchCrayon = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
            ColorManager::shared()->firstTouchPencil = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
            ColorManager::shared()->firstTouchPaintbucket = true;
        }
        
    }
    

    
    touchMoveDis = 0;
    
    return true;
}

void ChooseColorLayer::ccTouchMoved(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint preLocation = touch->getPreviousLocationInView();
    preLocation = CCDirector::sharedDirector()->convertToGL(preLocation);
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    buyState=ColorManager::shared()->buyState;
    buyState=ColorManager::shared()->buyState;
//    CCPoint touchPos = colorBg->convertToNodeSpace(location);
//    CCPoint preLocation = touchPos->getPreviousLocationInView();
//    CCPoint touchPrePos = colorBg->convertToNodeSpace(preLocation);
    beginY = preLocation.y;
    endY = location.y;
    touchMoveDis = endY-beginY;
    finishY= startY-endY;
    if(abs(startY-endY)>100){
        resetColorPos();
    }
    if (touchColorBg!=NULL && touchColorBg->boundingBox().containsPoint(location) && touchMoveDis!=0&&!buyState) {
        for (int i=0; i<totlePenCount; i++) {

            CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
            if (penButton!=NULL) {
//                CCLOG("---没有移动前的位置%f---",ColorManager::shared()->colorPenPos[36]);
//                CCLOG("---%f---",penButton->getPositionY());
                penButton->setPositionY(penButton->getPositionY()+touchMoveDis);
                int penPosY = penButton->getPositionY();
                if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
                    ColorManager::shared()->colorPaintPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                    ColorManager::shared()->colorLargebrushPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                    ColorManager::shared()->colorCrayonPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
                    ColorManager::shared()->colorPencilPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                    ColorManager::shared()->colorPaintbucketPos[i] = penPosY;
                }
//                ColorManager::shared()->colorPenPos[i] = penPosY;
//                CCLOG("---各个笔移动后的位置%f---",ColorManager::shared()->colorPenPos[i]);
            }
        }
    }
//    CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[36]);
}

void ChooseColorLayer::ccTouchEnded(CCTouch *touch, CCEvent *event){

    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint point = touch->getLocation();
    CCPoint lastPoint = touch->getPreviousLocation();
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
//    CCLOG("---手滑动距离%d---",touchMoveDis);
    for (int i=0; i<totlePenCount; i++) {
        CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
//        CCLOG("---最后一支笔当前的位置%f---",penButton->getPositionY());
        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
            ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
            ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
            ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
            ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
            ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
        }

        
        
    }
    ColorManager::shared()->scrollPenBoard = false;
//    isMovedPen = false;
    resetColorPos();
    ColorCanvasView* c = (ColorCanvasView*)this->getChildByTag(kBuyLayerTag);
    if(touchMoveDis==0){
        for (int i=0; i<totlePenCount; i++) {
            CCSprite* penColor = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
            CCSprite* adLock = (CCSprite*)penColor->getChildByTag(kLockTag);
            CCPoint penPos = colorBg->convertToNodeSpace(location);
            buyState=ColorManager::shared()->buyState;
            if (penColor!=NULL && penColor->boundingBox().containsPoint(penPos) && clickPen==false && clickPenIndexArr[i] == 0&&!buyState) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
//                ColorManager::shared()->firstTouchPencil = true;
                if (adLock!=NULL) {
    //                CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
    //                adLock->runAction(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()));
                     CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.showpeniap");
                     ColorManager::shared()->buyState= true;
                }else{

                    clickPenIndexArr[i] = 1;
                    clickPen = true;
                    if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15) {
                        selectPenColorIndex = paintColorArr[i-4];
                    }else{
                        selectPenColorIndex = paintColorArr[i];
                    }
                    selectPenIndex = i;
                    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
//                        if(i>15){
//                            ColorManager::shared()->curPaintIndex = i-4;
//                        }else{
                            ColorManager::shared()->curPaintIndex = i;
//                        }
                        
                    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                        ColorManager::shared()->curLargebrushIndex = i;
                    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                        ColorManager::shared()->curCrayonIndex = i;
                    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
//                        if(i>15){
//                            ColorManager::shared()->curPencilIndex = i-4;
//                        }else{
                            ColorManager::shared()->curPencilIndex = i;
//                        }
                    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                        ColorManager::shared()->curPaintbucketIndex = i;
                    }
                    penColor->runAction(CCSequence::create(CCCallFuncN::create(this, callfuncN_selector(ChooseColorLayer::colorClick)),
                                                           CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::canClickPen)),
                                                           NULL));

                }
            }
        }
    }
//    if (clickPen==true) {

//    }
    
//    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
}

void ChooseColorLayer::canClickPen(){
    clickPen =false;
}


void ChooseColorLayer::resetColorPos(){
//    int touchMoved=finishY-startY;
//    CCLOG("---当前画笔%d---",colorMaxDis);
//    CCLOG("---拖动距离%d---",touchMoveDis);
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    if (touchMoveDis>0) {
        for (int i=0; i<totlePenCount; i++) {
    //        CCLOG("---各个笔的位置%f---",ColorManager::shared()->colorPenPos[i]);
            CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
            int penPos = penButton->getPositionY();
    //        CCLOG("---第一支笔当前的位置%d---",penPos);
    //        CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
    //        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[36]);
            if (penPos>=colorMaxDis) {
    //            penButton->setPositionY(colorMinDis-colorDisY+touchMoveDis);
//                if(i!=0){
//                    penButton->setPositionY(colorPenPos[i-1]-colorDisY);
//                }else{
//                    penButton->setPositionY(colorPenPos[totlePenCount-1]-colorDisY);
//                }
                if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorPaintPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorPaintPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                    if(i!=0){
                        penButton->setPositionY( ColorManager::shared()->colorCrayonPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY( ColorManager::shared()->colorCrayonPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
                }
                
//                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//            }else if(penPos<=colorMinDis){
//    //            penButton->setPositionY(colorMaxDis+colorDisY+touchMoveDis);
//                if(i!=36){
//                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
//                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
//                    penButton->setPositionY(ColorManager::shared()->colorPenPos[i+1]+colorDisY);
//                }else{
//                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
//                    penButton->setPositionY(ColorManager::shared()->colorPenPos[0]+colorDisY);
//                }
//                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//                CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
            }
    //        CCLOG("---第一支笔调整后的位置%f---", penButton->getPosition().y);
    //        CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[36]);
            
        }
    }else if(touchMoveDis<0){
        for (int i=totlePenCount-1; i>=0; i--) {
    //        CCLOG("---各个笔的位置%f---",ColorManager::shared()->colorPenPos[i]);
            CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
            int penPos = penButton->getPositionY();
    //        CCLOG("---第一支笔当前的位置%d---",penPos);
    //        CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
    //        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[36]);
            if(penPos<=colorMinDis){
    //            penButton->setPositionY(colorMaxDis+colorDisY+touchMoveDis);
//                if(i!=totlePenCount-1){
////                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
////                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
//                    penButton->setPositionY(colorPenPos[i+1]+colorDisY);
//                }else{
////                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
//                    penButton->setPositionY(colorPenPos[0]+colorDisY);
//                }
                if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY( ColorManager::shared()->colorPaintPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY( ColorManager::shared()->colorPaintPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorCrayonPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorCrayonPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
                }
                
//                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//                CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
            }
    //        CCLOG("---第一支笔调整后的位置%f---", penButton->getPosition().y);
    //        CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[36]);
            
        }
    }

}
