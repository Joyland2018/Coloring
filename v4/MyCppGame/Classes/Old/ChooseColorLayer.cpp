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
#include "BuyLayer.h"

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
    kColorBgTag = 3,
    kFingerTag=4,
    kGuideFingerTag = 5,
    kPenColorTag = 111,
    kColorSelectorTag = 112,
    
};

bool ChooseColorLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    isDragging = false;
    newbieGuideScrollSpeed = 0;  // 初始化滚动速度
    
    
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    clickPen = false;
    selectPenColorIndex = 0;
    ColorManager::shared()->colorNums = 0;
    

    for (int i=0; i<44; i++) {
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
//    touchColorBg = NULL;
    endY = 0;
    beginY = 0;
    

    
    this->setColorBlock();
    if (GameManager::sharedManager()->firstPlayColorGame) {
        GameManager::sharedManager()->firstPlayColorGame=false;
        this->runAction(CCSequence::create(CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::startNewbieGuide)),
                                           CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::showFirstGuide)),NULL));
    }
    this->setTouchEnabled(true);
    return true;
}

ChooseColorLayer::ChooseColorLayer(){}
ChooseColorLayer::~ChooseColorLayer(){}

void ChooseColorLayer::onEnter(){
    CCLayer::onEnter();
}

void ChooseColorLayer::onExit(){
    CCLayer::onExit();
}

void ChooseColorLayer::setColorBlock(){
    // 移除旧的 colorBg 和其子节点，避免内存泄漏
    totlePenCount=44;
    CCSprite* oldColorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    if (oldColorBg) {
        // 移除所有 penColor
        for (int i = 0; i < totlePenCount; i++) {
            CCNode* penColor = oldColorBg->getChildByTag(kPenColorTag + i);
            if (penColor) {
                penColor->removeFromParentAndCleanup(true);
                penColor=NULL;
            }
        }
        // 移除 colorSelector
        CCNode* colorSelector = oldColorBg->getChildByTag(kColorSelectorTag);
        if (colorSelector) {
            colorSelector->removeFromParentAndCleanup(true);
            colorSelector=NULL;
        }
        oldColorBg->removeFromParentAndCleanup(true);
        oldColorBg=NULL;
    }

    CCSprite* colorBg = CCSprite::create("DinoColor/color_bg.png");
    colorBg->setPosition(ccp(v_size.width -80 -poszero.x,v_size.height/2));
//    toolsBg->setScaleX(0.7);
    colorBg->setTag(kColorBgTag);
    this->addChild(colorBg,2) ;
    
    CCSprite* colorSelector = CCSprite::create("DinoColor/colorSelector.png");
    colorSelector->setPosition(ccp(colorBg->getContentSize().width*0.05,colorBg->getContentSize().height*0.5));
//    toolsBg->setScaleX(0.7);
    colorSelector->setTag(kColorSelectorTag);
    colorBg->addChild(colorSelector,3) ;
    float midColorPosY = 0.0;
    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
        totlePenCount = 44;
        colorDisY = 92;                 //笔间距
        scaleColor  = 0.8;
        firstPenIndex = 22;
//        freeIndexMin = 7;
//        freeIndexMax = 11;
        midColorPosY = -1080;
        selectPenIndex = ColorManager::shared()->curPaintIndex;
        
        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPaint == false) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorPaintPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }else{
            midColorPosY = 0;
        }
        for (int i = 0; i < totlePenCount; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPaintPos[i];
        }
        
    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        totlePenCount = 40;
        colorDisY = 92;
        scaleColor  = 0.65;
        colorDisX = 10;
        firstPenIndex = 20;
        freeIndexMin = 29;
        freeIndexMax = 31;
        selectPenIndex = ColorManager::shared()->curLargebrushIndex;
        midColorPosY = 940;
        
        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchLargebrush == false) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorLargebrushPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }else{
            midColorPosY = 0;
        }
        for (int i = 0; i < totlePenCount; i++) {
            colorPenPos[i] = ColorManager::shared()->colorLargebrushPos[i];
        }
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        totlePenCount = 40;
        colorDisY = 92;
        scaleColor  = 0.8;
//        maxDis = (colorDisY*37-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        colorMaxDis = colorBg->getContentSize().height/1.07+440;
//        colorMinDis = -440;
        firstPenIndex = 20;
//        freeIndexMin = 20;
//        freeIndexMax = 24;
        selectPenIndex = ColorManager::shared()->curCrayonIndex;
        midColorPosY = -260;
        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        
        if (ColorManager::shared()->firstTouchCrayon == false) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorCrayonPos[i] =colorMaxDis-i*colorDisY;
            }
        }else{
            midColorPosY = 0;
        }
        for (int i = 0; i < totlePenCount; i++) {
            colorPenPos[i] = ColorManager::shared()->colorCrayonPos[i];
        }
    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
        totlePenCount = 44;
        colorDisY = 92;                 //笔间距
//        scaleColor  = 0.8;
        firstPenIndex = 22;
        freeIndexMin = 4;
        freeIndexMax = 6;
        selectPenIndex = ColorManager::shared()->curPencilIndex;
        midColorPosY = -1540;
        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        if (ColorManager::shared()->firstTouchPencil == false) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorPencilPos[i] =colorMaxDis-i*colorDisY;
            }
        }else{
            midColorPosY = 0;
        }
        for (int i = 0; i < totlePenCount; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPencilPos[i];
        }

    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        totlePenCount = 40;
        colorDisY = 92;
//        scaleColor  = 0.6;
        colorDisX = 10;
//        maxDis = 900;
//        colorMaxDis = colorBg->getContentSize().height/1.07+770;
//        colorMinDis = -900;
        firstPenIndex = 20;
        freeIndexMin = 21;
        freeIndexMax = 23;
        selectPenIndex = ColorManager::shared()->curPaintbucketIndex;
        midColorPosY = 195;
        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPaintbucket == false) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorPaintbucketPos[i] =colorMaxDis-i*colorDisY;
            }
        }else{
            midColorPosY = 0;
        }
        for (int i = 0; i < totlePenCount; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPaintbucketPos[i];
        }
    }
    

    int origiPenX=0;            //初始笔的位置
    
//    selectPenIndex = ColorManager::shared()->curPaintIndex;
    
//    colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//    
//    if (ColorManager::shared()->firstTouchPaint == false) {
//        for (int i = 0; i < totlePenCount; i++) {
//            ColorManager::shared()->colorPaintPos[i] =colorMaxDis-i*colorDisY;
//            CCLOG("---第%d支笔当前的位置%f---",i,ColorManager::shared()->colorPaintPos[i]);
//        }
//    }
//    for (int i = 0; i < totlePenCount; i++) {
//        colorPenPos[i] = ColorManager::shared()->colorPaintPos[i];
//    }
//    
    colorMinDis = colorMaxDis-(totlePenCount-1)*colorDisY;
    
    
    if (selectPenIndex>12 && selectPenIndex<17 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
        ColorManager::shared()->firstColorValue(selectPenIndex-1);
    }else if(selectPenIndex>16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)){
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  selectPenIndex-4;
        ColorManager::shared()->changeCurColor();
        selectPenColorIndex = selectPenIndex-4;
    }else{
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  selectPenIndex;
        ColorManager::shared()->changeCurColor();
        selectPenColorIndex = selectPenIndex;
    }
//    clickPenIndexArr[ColorManager::shared()->SelectBrushTag-100] = selectPenIndex;
    for (int i = 0; i < totlePenCount; i++) {
        CCSprite* penColor = CCSprite::create("DinoColor/colorBlock.png");
        penColor->setPosition(ccp(colorBg->getContentSize().width*0.24,colorPenPos[i]));
        penColor->setTag(kPenColorTag+i);
        penColor->setScale(0.8);
        colorBg->addChild(penColor);
        
        CCSprite* colorBlockShadow = NULL;
        if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>11 && i<16) {
            colorBlockShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_colorBlockShadow%d.png",ColorManager::shared()->curPenName,i)->getCString());
            colorBlockShadow->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
    //        brushIconShadow->setTag(Tag+i);
            penColor->addChild(colorBlockShadow);
        }else{
            ccColor3B brushColor;
            if((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15){
                brushColor = ColorManager::shared()->getCurColor(i-3);
            }else{
                brushColor = ColorManager::shared()->getCurColor(i+1);
            }
            
            penColor->setColor(brushColor);
        }

        
        penColor->runAction(CCMoveBy::create(0.3, ccp(0, midColorPosY)));
        
//        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") && (i<(freeIndexMin) || i>(freeIndexMax)) && (strcmp(ColorManager::shared()->curPenName, "crayon")!=0 && strcmp(ColorManager::shared()->curPenName, "paint")!=0)) {
//            if(i==freeIndexMin-1 || i==freeIndexMax+1){
//                this->addLock(penColor, i);
//                CCSprite* penIapShadow1 = CCSprite::create("DinoColor/iapLock_shadow1.png");
//                penIapShadow1->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
//                penColor->addChild(penIapShadow1);
//                if(i==freeIndexMax+1){
//                    penIapShadow1->setFlipY(true);
//                }
//            }else{
//                CCSprite* penIapShadow = CCSprite::create("DinoColor/iapLock_shadow2.png");
//                penIapShadow->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
//                penIapShadow->setTag(kLockTag);
//                penColor->addChild(penIapShadow);
//            }
//        }
         
    }
}

void ChooseColorLayer::resetColorBlockPos(bool isReset){
    
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    if (colorBg!=NULL) {
        float arrowY = colorBg->getContentSize().height * 0.5f;
        float minDis = 99999;
        int nearestIndex = -1;

        // 找到距离箭头最近的颜色块
        for (int i = 0; i < totlePenCount; i++) {
            CCSprite* pen = (CCSprite*)colorBg->getChildByTag(kPenColorTag + i);
            if (pen) {
                float penPosY = pen->getPosition().y;
                float dis = fabs(penPosY - arrowY);
                if (dis < minDis) {
                    minDis = dis;
                    nearestIndex = pen->getTag() - kPenColorTag;
    //                CCLOG("---当颜色块值%d---",i);
                }
            }

        }
       
//        CCSprite* penColor = (CCSprite*)colorBg->getChildByTag(kPenColorTag + nearestIndex);
//        if (penColor) {
//            CCSprite* adLock = (CCSprite*)penColor->getChildByTag(kLockTag);
//            if (adLock) {
//                this->moveToColorIndex(selectPenIndex, isReset);
//            }else{
                // 吸附到最近的免费色块
                selectPenIndex = nearestIndex+1;
                this->moveToColorIndex(selectPenIndex, isReset);
//            }
//        }
        
//        // 判断是否免费
//        bool isLocked = !CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") &&
//                        !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") &&
//                        (nearestIndex < freeIndexMin || nearestIndex > freeIndexMax);
//
//        if (isLocked) {
//            // 回弹到上次选中的免费色块
//            this->moveToColorIndex(selectPenIndex, isReset);
//        } else {
//            // 吸附到最近的免费色块
//            selectPenIndex = nearestIndex+1;
//            this->moveToColorIndex(selectPenIndex, isReset);
//        }
        
    }


}

void ChooseColorLayer::moveToColorIndex(int colorIndex, bool isReset){
    if(strcmp(ColorManager::shared()->curPenName, "eraser")!=0){
    int curColorIndex = colorIndex-1;
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    float arrowY = colorBg->getContentSize().height * 0.5f;
//    int preSelectPenIndex = clickPenIndexArr[ColorManager::shared()->SelectBrushTag-100];
//    CCLOG("---当前颜色值%d---",preSelectPenIndex);
//    float preTargetY = ((CCSprite*)colorBg->getChildByTag(kPenColorTag + preSelectPenIndex))->getPositionY();
//    float preSelectTargetY = ((CCSprite*)colorBg->getChildByTag(kPenColorTag + preSelectPenIndex))->getPositionY();
    float targetY = ((CCSprite*)colorBg->getChildByTag(kPenColorTag + curColorIndex))->getPositionY();
    float dy = arrowY - targetY;
    clickPenIndexArr[10] = dy;
//    CCLOG("---当前移动值%d---",clickPenIndexArr[10]);
    for (int i = 0; i < totlePenCount; i++) {
        CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag + i);
        if (penButton) {
            penButton->runAction(CCMoveBy::create(0.2f, ccp(0, dy)));
        }
    }
    
//    clickPenIndexArr[ColorManager::shared()->SelectBrushTag-100] =curColorIndex;
//    clickPenIndexArr[10] = dy;
   
    ColorManager::shared()->curSelectColorIndex = curColorIndex;
    
    //避开多色
    if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && selectPenIndex>15) {
        selectPenColorIndex = selectPenIndex-4;
    }else{
        selectPenColorIndex = selectPenIndex;
    }
//    ColorManager::shared()->curPaintIndex = selectPenColorIndex;
    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
        ColorManager::shared()->curPaintPenColorIndex = selectPenColorIndex;
        ColorManager::shared()->curPaintIndex = selectPenIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        ColorManager::shared()->curLargebrushIndex = selectPenColorIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        ColorManager::shared()->curCrayonIndex = selectPenColorIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
        ColorManager::shared()->curPencilPenColorIndex = selectPenColorIndex;
        ColorManager::shared()->curPencilIndex = selectPenIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        ColorManager::shared()->curPaintbucketIndex = selectPenColorIndex;
    }
    if (curColorIndex>11 && curColorIndex<16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
        ColorManager::shared()->firstColorValue(curColorIndex);
    }else{
        ColorManager::shared()->colorNums = 0;
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  selectPenColorIndex;
        ColorManager::shared()->changeCurColor();
    }
    ColorManager::shared()->m_DrawType = Draw_Point ;
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.changebrushcolor");
        

   
    this->runAction(CCSequence::create(CCDelayTime::create(0.3),
                                       CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::canClickPen)),
                                       NULL));
    }
}


void ChooseColorLayer::setButton()
{
//    float fix_w = 0 ;
//       if (GameManager::sharedManager()->isIphoneX()) {
//           fix_w = 130;
//       }
//   
//    
//    float w_fix = 0 ;
////    if (GameManager::sharedManager()->isIphoneX()) {
////        w_fix = 50 ;
////    }
//    
//    CCSprite* colorBg = CCSprite::create("DinoColor/color_bg.png");
//    colorBg->setPosition(ccp(v_size.width -80 - w_fix-poszero.x,v_size.height/2));
////    toolsBg->setScaleX(0.7);
//    colorBg->setTag(kColorBgTag);
//    this->addChild(colorBg,2) ;
//    
////    CCLOG("---%f---",colorBg->getContentSize().height/1.07);
//    
//    colorDisY=0;            //笔间距
//    colorDisX=0;            //横坐标偏移
//    totlePenCount =0;              //笔触数量
//    firstPenIndex=0;            //初始笔
//    int origiPenX=0;            //初始笔的位置
//    colorMaxDis=0;
//    colorMinDis = 0;
//    scaleColor=0;
//    
////    int freeIndexMin = 0;
////    int freeIndexMax = totlePenCount;
//    float midColorPosY = 0.0;
//
//    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
////        int penColorArr[24] = {23,32,18,2,8,12,5,1,3,4,6,37,25,28,7,10,13,31,24,14};
//        int penColorArr[44] = {23,32,18,2,8,12,5,1,3,4,6,37,25,28,7,10,13,31,24,14};
//        totlePenCount = 44;
//        for (int i=0; i<totlePenCount; i++) {
////            paintColorArr[i] = penColorArr[i];
//            paintColorArr[i] = i+1;
//        }
//        
//        colorDisY = 40;                 //笔间距
//        scaleColor  = 0.8;
//        firstPenIndex = 22;
////        freeIndexMin = 16;
////        freeIndexMax = 20;
//        
//        midColorPosY = -500;
//        
//        selectPenIndex = ColorManager::shared()->curPaintIndex;
//        
//        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        
//        if (ColorManager::shared()->firstTouchPaint == false) {
//            for (int i = 0; i < totlePenCount; i++) {
//                ColorManager::shared()->colorPaintPos[i] =colorMaxDis-i*colorDisY;
//                
//            }
//        }else{
//            midColorPosY = 0;
//        }
//        for (int i = 0; i < totlePenCount; i++) {
//            colorPenPos[i] = ColorManager::shared()->colorPaintPos[i];
//        }
//            
////        ColorManager::shared()->m_pColor = ccc3(98,170,50);
//    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
////        int penColorArr[20] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
//        int penColorArr[40] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
//        totlePenCount = 40;
//        for (int i=0; i<totlePenCount; i++) {
////            paintColorArr[i] = penColorArr[i];
//            paintColorArr[i] = i+1;
//        }
//        colorDisY = 60;
//        scaleColor  = 0.65;
//        colorDisX = 10;
//        firstPenIndex = 20;
////        freeIndexMin = 28;
////        freeIndexMax = 32;
//        
//        midColorPosY = 250;
////        ColorManager::shared()->m_pColor = ccc3(2,68,246);
//        
//        selectPenIndex = ColorManager::shared()->curLargebrushIndex;
//        
//        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        
//        if (ColorManager::shared()->firstTouchLargebrush == false) {
//            for (int i = 0; i < totlePenCount; i++) {
//                ColorManager::shared()->colorLargebrushPos[i] =colorMaxDis-i*colorDisY;
//                
//            }
//        }else{
//            midColorPosY = 0;
//        }
//        for (int i = 0; i < totlePenCount; i++) {
//            colorPenPos[i] = ColorManager::shared()->colorLargebrushPos[i];
//        }
//        
//    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
////        int penColorArr[20] = {23,32,18,5,8,12,2,37,4,3,1,6,7,28,25,10,13,31,24,14};
//        int penColorArr[40] = {23,32,18,5,8,12,2,37,4,3,1,6,7,28,25,10,13,31,24,14};
//        totlePenCount = 40;
//        for (int i=0; i<totlePenCount; i++) {
////            paintColorArr[i] = penColorArr[i];
//            paintColorArr[i] = i+1;
//        }
//       
//        colorDisY = 45;
//        scaleColor  = 0.8;
////        maxDis = (colorDisY*37-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
////        colorMaxDis = colorBg->getContentSize().height/1.07+440;
////        colorMinDis = -440;
//        firstPenIndex = 20;
////        freeIndexMin = 20;
////        freeIndexMax = 24;
//        
//        midColorPosY = -250;
//        
//        selectPenIndex = ColorManager::shared()->curCrayonIndex;
//        
//        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        
//        if (ColorManager::shared()->firstTouchCrayon == false) {
//            for (int i = 0; i < totlePenCount; i++) {
//                ColorManager::shared()->colorCrayonPos[i] =colorMaxDis-i*colorDisY;
//            }
//        }else{
//            midColorPosY = 0;
//        }
//        for (int i = 0; i < totlePenCount; i++) {
//            colorPenPos[i] = ColorManager::shared()->colorCrayonPos[i];
//        }
//        
////        ColorManager::shared()->m_pColor = ccc3(255,255,50);
//    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
////        int penColorArr[24] = {23,2,12,32,8,18,5,3,1,37,4,6,13,28,7,10,25,31,24,14};
//        int penColorArr[44] = {23,2,12,32,8,18,5,3,1,37,4,6,13,28,7,10,25,31,24,14};
//        totlePenCount = 44;
//        for (int i=0; i<totlePenCount; i++) {
////            paintColorArr[i] = penColorArr[i];
//            paintColorArr[i] = i+1;
//        }
//        
//        colorDisY = 40;
//        scaleColor  = 0.8;
////        maxDis = 350;
////        colorMaxDis = colorBg->getContentSize().height/1.07+390;
////        colorMinDis = -350;
//        firstPenIndex = 22;
////        freeIndexMin = 7;
////        freeIndexMax = 11;
//        
//        midColorPosY = -850;
//        
//        selectPenIndex = ColorManager::shared()->curPencilIndex;
//        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        
//        if (ColorManager::shared()->firstTouchPencil == false) {
//            for (int i = 0; i < totlePenCount; i++) {
//                ColorManager::shared()->colorPencilPos[i] =colorMaxDis-i*colorDisY;
//            }
//        }else{
//            midColorPosY = 0;
//        }
//        for (int i = 0; i < totlePenCount; i++) {
//            colorPenPos[i] = ColorManager::shared()->colorPencilPos[i];
//        }
//            
////        ColorManager::shared()->m_pColor = ccc3(0,0,0);
//    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
////        int penColorArr[20] = {7,2,18,32,8,12,5,4,37,1,6,3,25,28,23,10,13,31,14,24};
//        int penColorArr[40] = {7,2,18,32,8,12,5,4,37,1,6,3,25,28,23,10,13,31,14,24};
//        totlePenCount = 40;
//        for (int i=0; i<40; i++) {
////            paintColorArr[i] = penColorArr[i];
//            paintColorArr[i] = i+1;
//        }
//       
//        colorDisY = 65;
//        scaleColor  = 0.6;
//        colorDisX = 10;
////        maxDis = 900;
////        colorMaxDis = colorBg->getContentSize().height/1.07+770;
////        colorMinDis = -900;
//        firstPenIndex = 20;
////        freeIndexMin = 2;
////        freeIndexMax = 6;
//        
//        midColorPosY = -1400;
//        
//        selectPenIndex = ColorManager::shared()->curPaintbucketIndex;
//        
//        colorMaxDis = (colorDisY*totlePenCount-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        
//        if (ColorManager::shared()->firstTouchPaintbucket == false) {
//            for (int i = 0; i < totlePenCount; i++) {
//                ColorManager::shared()->colorPaintbucketPos[i] =colorMaxDis-i*colorDisY;
//            }
//        }else{
//            midColorPosY = 0;
//        }
//        for (int i = 0; i < totlePenCount; i++) {
//            colorPenPos[i] = ColorManager::shared()->colorPaintbucketPos[i];
//        }
//        
////        ColorManager::shared()->m_pColor = ccc3(248,37,15);
//    }
//    
//
//
//
//    if (selectPenIndex>11 && selectPenIndex<16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
//        ColorManager::shared()->firstColorValue(selectPenIndex);
//    }else if(selectPenIndex>15 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)){
//        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  paintColorArr[selectPenIndex-4];
//        ColorManager::shared()->changeCurColor();
//        selectPenColorIndex = paintColorArr[selectPenIndex-4];
//    }else{
//        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  paintColorArr[selectPenIndex];
//        ColorManager::shared()->changeCurColor();
//        selectPenColorIndex = paintColorArr[selectPenIndex];
//    }
//    
//    
////    selectPenColorIndex = paintColorArr[selectPenIndex];
//
//    
//
//    
//    colorMinDis = colorMaxDis-(totlePenCount-1)*colorDisY;
////    int crayonIndex[37] = {9,8,10,21,24,12,31,36,1,3,4,5,6,7,2,20,17,26,42,13,16,15,14,19,21,23,22,25,27,28,29,30,32,33,34,35,18};
//
////    CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
//    clickPenIndexArr[selectPenIndex] = 1;
//    
//    for (int i = 0; i < totlePenCount; i++) {
////        crayonTextureIndex[i] = crayonIndex[i];
//        if (i==selectPenIndex) {
//            origiPenX = 25;
//        }else{
//            origiPenX = 0;
//        }
//        CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s_tools_cover.png",ColorManager::shared()->curPenName) ;
//        CCSprite* penColor = CCSprite::create(name->getCString());
//        penColor->setPosition(ccp(colorBg->getContentSize().width/3-origiPenX,colorPenPos[i]+400));
//        penColor->setTag(kPenColorTag+i);
//        penColor->setScale(scaleColor);
//        colorBg->addChild(penColor);
//        
////        CCSprite* tmp2 = CCSprite::create(name->getCString());
////        CCSize size2 = tmp2->getContentSize();
////        CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
////        CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
////        CCControlButton *button = CCControlButton::create(sprite2) ;
////        button->setPreferredSize(size2) ;
////        button->setTag(Tag+i);
////        button->setPosition(ccp(v_size.width -130-poszero.x-colorDisX,v_size.height/1.07+maxDis-i*colorDisY)) ;
////        button->setScale(scaleColor);
//////           button->setPosition(ccp(0, 0)) ;
////        this->addChild(button, 3) ;
//        
//        CCSprite* brushIconShadow = NULL;
////        if (strcmp(ColorManager::shared()->curPenName, "crayon")==0 ) {
////            CCTexture2D* texture = ColorManager::shared()->maskedWithSpriteTexture(CCSprite::create(CCString::createWithFormat("DinoColor/crayon_texture/crayon_texture_%d.png",crayonTextureIndex[i])->getCString()), CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName)->getCString()), ccp(0.5, 0.5));
////            brushIconShadow = CCSprite::createWithTexture(texture);
////        }else{
//        
//        if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>11 && i<16) {
//            brushIconShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_colorshadow%d.png",ColorManager::shared()->curPenName,i)->getCString());
//        }else{
//            
//                brushIconShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName)->getCString());
//            ccColor3B brushColor;
//            if((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15){
//                brushColor = ColorManager::shared()->getCurColor(paintColorArr[i-4]);
//            }else{
//                brushColor = ColorManager::shared()->getCurColor(paintColorArr[i]);
//            }
//                
//                brushIconShadow->setColor(brushColor);
//        }
//
////        }
//        
//        brushIconShadow->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
////        brushIconShadow->setTag(Tag+i);
//        penColor->addChild(brushIconShadow,-1);
//        
////        CCSprite* mark = CCSprite::create("DinoColor/brush-select.png");
////        mark->setTag(Mark);
////        mark->setPosition(ccp(size2.width/2, size2.height/2 ));
////        button->addChild(mark);
////        if (ColorManager::shared()->SelectBrushTag == Tag+i) {
////            mark->setVisible(true);
////        }else{
////           mark->setVisible(false);
////        }
//        penColor->runAction(CCMoveBy::create(0.3, ccp(0, midColorPosY)));
//        
//        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased") && (i<(11) || i>(16))) {
//            this->addLock(penColor, i);
//            CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s_iap_shadow.png",ColorManager::shared()->curPenName) ;
//            CCSprite* penIapShadow = CCSprite::create(name->getCString());
//            penIapShadow->setPosition(ccp(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
//            penColor->addChild(penIapShadow);
//        }
////        ColorManager::shared()->colorPenPos[i]  = penColor->getPosition().y-400;
////        button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), CCControlEventTouchUpInside) ;
//    }
////    for (int i=0; i<37; i++) {
////        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[i]);
////    }
////       for (int i = 0; i < 37; i++) {
//           
////           CCString* name = CCString::createWithFormat("DinoColor/color/color_%d.png",(i+1)) ;
////           CCSprite* tmp2 = CCSprite::create(name->getCString());
////           CCSize size2 = tmp2->getContentSize();
////           CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
////           CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
////           CCControlButton *button = CCControlButton::create(sprite2) ;
////           button->setPreferredSize(size2) ;
////           button->setTag(Tag+i);
////           button->setPosition(ccp(v_size.width -160-poszero.x,v_size.height/1.07+800-i*100+200)) ;
////           this->addChild(button, 3) ;
//////           CCSprite* mark = CCSprite::create("DinoColor/color-selected.png");
//////           mark->setTag(Mark);
//////           mark->setPosition(ccp(size2.width/2, size2.height/2));
//////           button->addChild(mark);
//////           if (ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] == Tag+i) {
//////               mark->setVisible(true);
//////           }else{
//////              mark->setVisible(false);
//////           }
//////
////           button->runAction(CCMoveBy::create(0.5, ccp(0, -200)));
////           button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), CCControlEventTouchUpInside) ;
////       }
}



void ChooseColorLayer::addLock(CCObject *_parent,int _index) {

    
    const char* lockName = "colorLock";
    CCSprite* parentSpr = (CCSprite*)_parent;
    CCSprite* locked = CCSprite::create(CCString::createWithFormat("DinoColor/%s.png",lockName)->getCString()) ;
//    if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
//        locked->setScale(0.7) ;
//        locked->setPosition(ccp(parentSpr->getContentSize().width/2.5, parentSpr->getContentSize().height/1.7));
//    }else  if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
//        locked->setScale(0.8) ;
//        locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.7));
//    }else{
//        locked->setScale(scaleColor-0.3) ;
//        locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.9));
//    }
    locked->setScale(0.45) ;
    locked->setPosition(ccp(parentSpr->getContentSize().width*0.45, parentSpr->getContentSize().height/1.9));
//    locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.7));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked,10) ;
}




void ChooseColorLayer::colorClick(CCObject *obj)
{
    
//    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
//
//    // 清除上一个选中的点击标记
//    for (int i=0; i<totlePenCount; i++) {
//        if (i != selectPenIndex) {
//            clickPenIndexArr[i] = 0;
//        }
//    }
//    clickPenIndexArr[selectPenIndex] = 1;
//
//    // 应用颜色逻辑（只对某些笔刷特殊处理）
//    if (selectPenIndex > 11 && selectPenIndex < 16 &&
//        (strcmp(ColorManager::shared()->curPenName, "pencil") == 0 || strcmp(ColorManager::shared()->curPenName, "paint") == 0)) {
//        
//        ColorManager::shared()->firstColorValue(selectPenIndex);
//    } else {
//        ColorManager::shared()->colorNums = 0;
//        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag - 100] = selectPenColorIndex;
//        ColorManager::shared()->changeCurColor();
//    }
//
//    ColorManager::shared()->m_DrawType = Draw_Point;
    
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    
    CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+selectPenIndex);
    if(penButton!=NULL){
//        penButton->setScale(scaleColor);
//        penButton->runAction(CCSpawn::create(CCSequence::create(CCScaleTo::create(0.1, scaleColor+0.2),
//                                                                CCScaleTo::create(0.1, scaleColor),
//                                                                                   NULL),
//                                             CCEaseIn::create(CCMoveBy::create(0.3, ccp(-15, 0)), 0.3),
//                                             NULL));
    }
    
    for (int i=0; i<totlePenCount; i++) {
        CCSprite* otherPenButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
        if (i!=selectPenIndex && otherPenButton!=NULL) {
//            otherPenButton->setPositionX(colorBg->getContentSize().width/3);
//            otherPenButton->runAction(CCScaleTo::create(0.2, scaleColor));
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

bool ChooseColorLayer::checkIsTouchingLayer(CCPoint _checkPos){
    CCPoint checkPosInLayer = this->convertToNodeSpace(_checkPos);
    
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    if (colorBg!=NULL && colorBg->boundingBox().containsPoint(checkPosInLayer)) {
        return true;
    }
    return false;
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
    
//    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);


    if (colorBg!=NULL && colorBg->boundingBox().containsPoint(location) && ColorManager::shared()->touchedPenButton==false) {
//        touchColorBg = colorBg;
        if(strcmp(ColorManager::shared()->curPenName, "eraser")!=0){
            ColorManager::shared()->scrollPenBoard = true;
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
//    CCPoint touchPos = colorBg->convertToNodeSpace(location);
//    CCPoint preLocation = touchPos->getPreviousLocationInView();
//    CCPoint touchPrePos = colorBg->convertToNodeSpace(preLocation);
    beginY = preLocation.y;
    endY = location.y;
    touchMoveDis = endY-beginY;
    finishY= startY-endY;

    if (colorBg!=NULL && colorBg->boundingBox().containsPoint(location) && abs(touchMoveDis)>=1 && ColorManager::shared()->touchedPenButton==false && ColorManager::shared()->isNewbieGuideActive==false) {
        for (int i=0; i<totlePenCount; i++) {

            CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
            if (penButton!=NULL) {
                clickPen=true;
                isDragging = true;
                ColorManager::shared()->isMovingColorBlock=true;
//                CCLOG("---没有移动前的位置%f---",ColorManager::shared()->colorPenPos[36]);
//                CCLOG("---%f---",penButton->getPositionY());
                penButton->setPositionY(penButton->getPositionY()+touchMoveDis);
                float penPosY = penButton->getPositionY();
//                ColorManager::shared()->colorPaintPos[i] = penPosY;
//                int penPosY = penButton->getPositionY();
//                ColorManager::shared()->colorPaintPos[i] = penPosY;
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
//        if(abs(startY-endY)>100){
////            resetColorPos();
//            this->runAction(CCSequence::create(CCDelayTime::create(0.1),
//                                               CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::resetColorPos)),
//                                               NULL));
//        }
//        this->resetColorPos();
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
    
    if(!colorBg) return;
    

//    if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && selectPenIndex>15) {
//        selectPenColorIndex = selectPenIndex-3;
//    }else{
//        selectPenColorIndex = selectPenIndex;
//    }
//    ColorManager::shared()->curPaintIndex = selectPenColorIndex;
    
    
    if (!isDragging && ColorManager::shared()->isNewbieGuideActive==false) {
        // 转换成 colorBg 的坐标系
        CCPoint localPoint = colorBg->convertToNodeSpace(location);
        for (int i = 0; i < totlePenCount; i++) {
            CCSprite* pen = (CCSprite*)colorBg->getChildByTag(kPenColorTag + i);
            if (pen && pen->boundingBox().containsPoint(localPoint) && !clickPen && ColorManager::shared()->touchedPenButton==false) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
//                CCSprite* adLock = (CCSprite*)pen->getChildByTag(kLockTag);
//                if (adLock) {
//                    this->moveToColorIndex(selectPenIndex, true); // 回弹
//                    CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.showpeniap");
//                }else{
                    clickPen = true;
                    // 合法点击
                    selectPenIndex = i+1;
                    this->moveToColorIndex(selectPenIndex, true);

                    // 调用点击逻辑
//                    this->colorClick(NULL);
//                }

            }
        }
        

    }
    

    
    
    if (isDragging) {
        resetColorBlockPos(true);
        isDragging = false;
        ColorManager::shared()->isMovingColorBlock=false;
    }
    this->removeFinger();
    ColorManager::shared()->scrollPenBoard = false;
//    if (colorBg!=NULL && colorBg->boundingBox().containsPoint(location) && ColorManager::shared()->touchedPenButton==false) {
////        touchColorBg = colorBg;
//        if(strcmp(ColorManager::shared()->curPenName, "eraser")!=0){
//            ColorManager::shared()->scrollPenBoard = true;
//        }
//        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
//            ColorManager::shared()->firstTouchPaint = true;
//        }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
//            ColorManager::shared()->firstTouchLargebrush = true;
//        }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
//            ColorManager::shared()->firstTouchCrayon = true;
//        }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
//            ColorManager::shared()->firstTouchPencil = true;
//        }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
//            ColorManager::shared()->firstTouchPaintbucket = true;
//        }
//        
//    }
//    this->runAction(CCSequence::create(CCDelayTime::create(0.5),
//                                       CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::resetColorPos)),
//                                       NULL));
//    this->resetColorPos();
    

//    this->resetColorPos();
//    isMovedPen = false;
    
//    if(touchMoveDis==0){
//        for (int i=0; i<totlePenCount; i++) {
//            CCSprite* penColor = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
//            CCSprite* adLock = (CCSprite*)penColor->getChildByTag(kLockTag);
//            CCPoint penPos = colorBg->convertToNodeSpace(location);
//            if (penColor!=NULL && penColor->boundingBox().containsPoint(penPos) && !clickPen && clickPenIndexArr[i] == 0) {
//                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
////                ColorManager::shared()->firstTouchPencil = true;
//                if (adLock!=NULL) {
//    //                CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
//    //                adLock->runAction(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()));
//                     CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.showpeniap");
//                }else{
//                    clickPenIndexArr[i] = 1;
//                    clickPen = true;
//                    if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15) {
//                        selectPenColorIndex = paintColorArr[i-4];
//                    }else{
//                        selectPenColorIndex = paintColorArr[i];
//                    }
//                    selectPenIndex = i;
//                    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
//                        if(i>15){
//                            ColorManager::shared()->curPaintIndex = i-4;
//                        }else{
//                            ColorManager::shared()->curPaintIndex = i;
//                        }
//                        
//                    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
//                        ColorManager::shared()->curLargebrushIndex = i;
//                    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
//                        ColorManager::shared()->curCrayonIndex = i;
//                    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
////                        if(i>15){
////                            ColorManager::shared()->curPencilIndex = i-4;
////                        }else{
//                            ColorManager::shared()->curPencilIndex = i;
////                        }
//                    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
//                        ColorManager::shared()->curPaintbucketIndex = i;
//                    }
//                    penColor->runAction(CCSequence::create(CCCallFuncN::create(this, callfuncN_selector(ChooseColorLayer::colorClick)),
//                                                           CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::canClickPen)),
//                                                           NULL));
//                }
//            }
//        }
//    }
//    if (clickPen==true) {

//    }
    
//    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    
}

void ChooseColorLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
    if (isDragging) {
        resetColorBlockPos(true);
        isDragging = false;
        ColorManager::shared()->isMovingColorBlock=false;
    }
    ColorManager::shared()->scrollPenBoard = false;
    this->removeFinger();
}

void ChooseColorLayer::canClickPen(){
    clickPen =false;
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    for (int i=0; i<totlePenCount; i++) {
        CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
////        CCLOG("---最后一支笔当前的位置%f---",penButton->getPositionY());
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
//    this->resetColorPos();
    this->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                       CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::resetColorPos)),
                                       NULL));
}


void ChooseColorLayer::resetColorPos(){
//    int touchMoved=finishY-startY;
//    CCLOG("---当前点击移动距离%d---",clickPenIndexArr[10]);
//    CCLOG("---拖动距离%d---",touchMoveDis);
//    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
//    if(colorBg){
//        if (touchMoveDis>0 || (clickPenIndexArr[10]>0 && !isDragging)) {
//            for (int i=0; i<totlePenCount; i++) {
//        //        CCLOG("---各个笔的位置%f---",ColorManager::shared()->colorPenPos[i]);
//                CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
//                float penPos = penButton->getPositionY();
//                CCLOG("---第%d支笔当前的位置%f---",i,ColorManager::shared()->colorPaintPos[i]);
//        //        CCLOG("---第一支笔当前的位置%d---",penPos);
//    //            CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPaintPos[0]);
//    //            CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPaintPos[totlePenCount-1]);
//                if (penPos>=colorMaxDis) {
//        //            penButton->setPositionY(colorMinDis-colorDisY+touchMoveDis);
//    //                if(i!=0){
//    //                    penButton->setPositionY(colorPenPos[i-1]-colorDisY);
//    //                }else{
//    //                    penButton->setPositionY(colorPenPos[totlePenCount-1]-colorDisY);
//    //                }
//    //                if(i!=0){
//    //                    penButton->setPositionY(ColorManager::shared()->colorPaintPos[i-1]-colorDisY);
//    //                }else{
//    //                    penButton->setPositionY(ColorManager::shared()->colorPaintPos[totlePenCount-1]-colorDisY);
//    //                }
//    //                ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
//                    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
//                        if(i!=0){
//                            penButton->setPositionY(ColorManager::shared()->colorPaintPos[i-1]-colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorPaintPos[totlePenCount-1]-colorDisY);
//                        }
//                        ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
//                        if(i!=0){
//                            penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[i-1]-colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[totlePenCount-1]-colorDisY);
//                        }
//                        ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
//                        if(i!=0){
//                            penButton->setPositionY( ColorManager::shared()->colorCrayonPos[i-1]-colorDisY);
//                        }else{
//                            penButton->setPositionY( ColorManager::shared()->colorCrayonPos[totlePenCount-1]-colorDisY);
//                        }
//                        ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
//                        if(i!=0){
//                            penButton->setPositionY(ColorManager::shared()->colorPencilPos[i-1]-colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorPencilPos[totlePenCount-1]-colorDisY);
//                        }
//                        ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
//                        if(i!=0){
//                            penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[i-1]-colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[totlePenCount-1]-colorDisY);
//                        }
//                        ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
//                    }
//                    
//                    
//                    
//    //                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//    //            }else if(penPos<=colorMinDis){
//    //    //            penButton->setPositionY(colorMaxDis+colorDisY+touchMoveDis);
//    //                if(i!=36){
//    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
//    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
//    //                    penButton->setPositionY(ColorManager::shared()->colorPenPos[i+1]+colorDisY);
//    //                }else{
//    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
//    //                    penButton->setPositionY(ColorManager::shared()->colorPenPos[0]+colorDisY);
//    //                }
//    //                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//    //                CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
//                }
//        //        CCLOG("---第一支笔调整后的位置%f---", penButton->getPosition().y);
//        //        CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[36]);
//                
//            }
//        }else if(touchMoveDis<0 || (clickPenIndexArr[10]<0  && !isDragging)){
//            for (int i=totlePenCount-1; i>=0; i--) {
//        //        CCLOG("---各个笔的位置%f---",ColorManager::shared()->colorPenPos[i]);
//                CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
//                float penPos = penButton->getPositionY();
//                CCLOG("---第%d支笔当前的位置%f---",i,ColorManager::shared()->colorPaintPos[i]);
//                if(penPos<=colorMinDis){
//                    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
//                        if(i!=totlePenCount-1){
//                            penButton->setPositionY( ColorManager::shared()->colorPaintPos[i+1]+colorDisY);
//                        }else{
//                            penButton->setPositionY( ColorManager::shared()->colorPaintPos[0]+colorDisY);
//                        }
//                        ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
//                        if(i!=totlePenCount-1){
//                            penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[i+1]+colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[0]+colorDisY);
//                        }
//                        ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
//                        CCLOG("---第%d支笔---",i);
//                        CCLOG("---总共%d支笔---",totlePenCount);
//                        if(i!=totlePenCount-1){
//                            penButton->setPositionY(ColorManager::shared()->colorCrayonPos[i+1]+colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorCrayonPos[0]+colorDisY);
//                        }
//                        ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
//                        CCLOG("---当前铅笔%d---",i);
//                        if(i!=totlePenCount-1){
//                            penButton->setPositionY(ColorManager::shared()->colorPencilPos[i+1]+colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorPencilPos[0]+colorDisY);
//                        }
//                        ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
//                    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
//                        if(i!=totlePenCount-1){
//                            penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[i+1]+colorDisY);
//                        }else{
//                            penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[0]+colorDisY);
//                        }
//                        ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
//                    }
//                }
//                
//            }
//        }
//    }
    CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
    if(colorBg){
        // 获取当前笔类型对应的位置数组
        float* posArr = nullptr;
        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
            posArr = ColorManager::shared()->colorPaintPos;
        }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
            posArr = ColorManager::shared()->colorLargebrushPos;
        }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
            posArr = ColorManager::shared()->colorCrayonPos;
        }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
            posArr = ColorManager::shared()->colorPencilPos;
        }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
            posArr = ColorManager::shared()->colorPaintbucketPos;
        }

        if (!posArr) return; // 防止空指针

        // 循环处理所有精灵的循环滚动
        for (int i=0; i<totlePenCount; i++) {
            CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag+i);
            if (penButton) {
                // 使用 float 获取当前位置，避免精度丢失
                float currentPenPosY = penButton->getPositionY();
                // 计算整个滚动列表的总高度，用于循环
                float totalScrollHeight = totlePenCount * colorDisY;
                // 如果精灵向上超出上限 (已经滚动到顶部并需要从底部出现)
                if (currentPenPosY >= colorMaxDis) {
                    penButton->setPositionY(currentPenPosY - totalScrollHeight);
                    posArr[i] = penButton->getPositionY(); // 更新保存的位置
                }
                // 如果精灵向下超出下限 (已经滚动到底部并需要从顶部出现)
                else if (currentPenPosY <= colorMinDis) {
                    penButton->setPositionY(currentPenPosY + totalScrollHeight);
                    posArr[i] = penButton->getPositionY(); // 更新保存的位置
                }
                else {
                    posArr[i] = currentPenPosY;
                }
            }
        }
    }

}


// 新增的 update 方法，用于新手引导的自动循环运动
void ChooseColorLayer::update(float dt) {
    if (ColorManager::shared()->isNewbieGuideActive) {
        CCSprite* colorBg = (CCSprite*)this->getChildByTag(kColorBgTag);
        if (!colorBg) return;

        // 根据新手引导滚动速度进行移动
        float moveAmount = newbieGuideScrollSpeed * dt;
        
        float totalScrollHeight = totlePenCount * colorDisY;

        for (int i = 0; i < totlePenCount; i++) {
            CCSprite* penButton = (CCSprite*)colorBg->getChildByTag(kPenColorTag + i);
            if (penButton) {
                // 应用移动量，直接更新精灵位置
                float currentPenPosY = penButton->getPositionY() + moveAmount;
                
                // 处理循环滚动逻辑：当色块超出可见范围时，将其“传送”到另一端
                // colorMaxDis 和 colorMinDis 是 ChooseColorLayer 的成员变量，表示色块可见范围的边界
                if (currentPenPosY >= colorMaxDis) {
                    penButton->setPositionY(currentPenPosY - totalScrollHeight);
                }
                else if (currentPenPosY <= colorMinDis) {
                    penButton->setPositionY(currentPenPosY + totalScrollHeight);
                }
                else {
                    penButton->setPositionY(currentPenPosY); // 在范围内则保持新位置
                }
                
            }
        }
    }
}

// 新增的新手引导开始方法
void ChooseColorLayer::startNewbieGuide() {
    if (ColorManager::shared()->isNewbieGuideActive) return;

    ColorManager::shared()->isNewbieGuideActive = true;
    this->setTouchEnabled(false);
    
    // 设置滚动速度
    newbieGuideScrollSpeed = -1300.0f; // 每秒位移

    // 计算一个完整的周期所需的距离和时间
    float totalScrollHeight = totlePenCount * colorDisY;
    // 持续时间 = 总距离 / 速度的绝对值
    float guideDuration = totalScrollHeight / fabsf(newbieGuideScrollSpeed);
    
    this->scheduleUpdate();

    this->runAction(CCSequence::create(
                                       CCDelayTime::create(guideDuration),
                                       CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::finishNewbieGuide)),
                                       NULL));
}

// 新增的新手引导结束方法
void ChooseColorLayer::finishNewbieGuide() {
    this->unscheduleUpdate();
    ColorManager::shared()->isNewbieGuideActive = false;
    this->setTouchEnabled(true);
    this->removeFirstGuide();
    this->scheduleOnce(schedule_selector(ChooseColorLayer::showFinger), 0.5);
}

void ChooseColorLayer::showFirstGuide()
{
    CCPoint center = GameManager::sharedManager()->getCenter();
        CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
        if (guideFinger == NULL) {
            guideFinger = CCSprite::create("unitedstates/ui/touch0.png");
            guideFinger->setPosition(ccp(v_size.width -150 -poszero.x, center.y+150));
            guideFinger->setTag(kGuideFingerTag);
            guideFinger->setScale(0.3);
            guideFinger->setOpacity(0);
            this->addChild(guideFinger, 1002);
        }
        
        if (guideFinger != NULL) {
            guideFinger->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(0.3, 255),CCMoveTo::create(1.0, ccp(v_size.width -150 -poszero.x, center.y-150)),CCFadeTo::create(0.5, 0),CCCallFunc::create(this, callfunc_selector(ChooseColorLayer::resetGuideFingerPos)),NULL)));
        }
}

void ChooseColorLayer::resetGuideFingerPos()
{
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
    if (guideFinger != NULL) {
            guideFinger->setPosition(ccp(v_size.width -150 -poszero.x, center.y+150));
    }
}

void ChooseColorLayer::removeFirstGuide()
{
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
    if (guideFinger != NULL) {
        guideFinger->stopAllActions();
        guideFinger->removeFromParentAndCleanup(true);
        guideFinger = NULL;
    }
}

void ChooseColorLayer::showFinger(){
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pick.plist");
//    if (curRoomId==0) {
//    if (creamGun!=NULL && cupcake!=NULL) {
        //手势
        CCSprite* finger = CCSprite::createWithSpriteFrameName("touch0.png");
        finger->setPosition(ccp(v_size.width -150 -poszero.x,center.y+80));
        finger->setTag(kFingerTag);
        finger->setScale(0.3);
//        finger->runAction(CCFadeIn::create(0.3));
        this->addChild(finger,990);
        this->schedule(schedule_selector(ChooseColorLayer::showFingerAction),1.0f);
//    }

//    }
}

void ChooseColorLayer::showFingerAction(){
    CCSprite* finger=(CCSprite*)this->getChildByTag(kFingerTag);
    CCArray* frame = CCArray::create();
    for (int m =0; m<2; m++) {
        CCString *name = CCString::createWithFormat("touch%d.png",m);
        frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
    }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(0.3f);
        CCAnimate *animate = CCAnimate::create(animation);
//    if(!GameManager::sharedManager()->firstPlay){
        finger->runAction(animate);
//    }
        
}

void ChooseColorLayer::removeFinger(){
    CCSprite* finger=(CCSprite*)this->getChildByTag(kFingerTag);
    if (finger!=NULL) {
        this->unschedule(schedule_selector(ChooseColorLayer::showFingerAction));
        finger->removeFromParentAndCleanup(true);
    }

}
