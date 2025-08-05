//
//  SelectColorTheme.cpp
//  DrDino
//
//  Created by LiXiaofei on 2/13/23.
//

#include "SelectColorTheme.hpp"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "DeviceManager.h"
#include "DinoTownScene.h"
#include "SelectColorAniScene.hpp"
#include "ColorManager.hpp"
#include "BookLayer.h"

using namespace CocosDenshion;

enum{
    kBackTag = 1,
    kscrollView1Tag =2,
    kscrollView2Tag =3,
    kColorThemeTag = 20,
    kCouponBookTag=996,
    kBookLayerTag = 997,
    kBackLayerTag=998,
    kBookBtnTag = 999,
    kCuoponBtbLayerTag=1000,
};

CCScene* SelectColorTheme::scene(){
    CCScene* scene = CCScene::create();
    SelectColorTheme* layer  = SelectColorTheme::create();
    scene->addChild(layer);
    return scene;
}


bool SelectColorTheme::init(){
    if (!CCLayer::init()) {
        return false;
    }
    bookBtnClick=false;
    backClick = false;
    clickTheme = false;
    showCurTheme = false;
    touchMoveTheme = false;
    GameManager::sharedManager()->clickedBookBtn=false;
    endX = 0;
    beginX = 0;
    scaleThemeIndex=0;
    curThemeIndex = 0;
    curMoveThemeX = 0;
    
    minDis = 0;
    maxDis = 0;
    
    resetThemePosX = 320;
    
    curResetTheme = 0;
    
    curTouchMoveX = 0;
    curThemeTotalCount=18;
    
    winCenter = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    CCSprite* bg = CCSprite::create("DinoColor/roles-bg.png");
    bg->setPosition(winCenter);
    this->addChild(bg);
    
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
    }
    if (DeviceManager::sharedManager()->getIsPad()) {
        resetThemePosX = 250;
    }
    
    //返回按钮
    CCSprite* back=CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBackTag);
    this->addChild(back,1);
    
    this->scheduleOnce(schedule_selector(SelectColorTheme::showTheme), 0.3);
    
//    CCSprite* bookBtn=CCSprite::create("book/colorBookBtn.png");
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("gameBackgroundMp3", true) ;
    
    const char* coinRegion = DeviceManager::sharedManager()->getCurrentDinoRegion();

    bool si = GameManager::sharedManager()->canShowColorBookLayer;
    CCSprite* bookBtn = NULL;
    bool canShowMainSceneBookBtn = GameManager::sharedManager()->checkIsCanShowMainBtn(0);
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll")==false && CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")==false){
        bookBtn = CCSprite::create("book/colorBookBtn.png");
        bookBtn->setTag(kBookBtnTag);
    }else if(CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll")==true || CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")==true){
        if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet50Coupon")==true) {
            bookBtn = CCSprite::create("book/coloringbook5.png");
            bookBtn->setTag(kCouponBookTag);
        }else if(CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet20Coupon")==true){
            bookBtn = CCSprite::create("book/coloringbook7.png");
            bookBtn->setTag(kCouponBookTag);
        }
        canShowMainSceneBookBtn = GameManager::sharedManager()->checkIsCanShowMainBtn(1);
    }
    if(bookBtn!=NULL){
        bookBtn->setPosition(ccp(rightTop.x-bookBtn->getContentSize().width*0.6,leftTop.y-50));
    //    if (GameManager::sharedManager()->checkIsCanShowBookBtn()==false) {
        bookBtn->setVisible(false);
    //    }
        
        if (strcmp(coinRegion, "US") == 0){
            if(canShowMainSceneBookBtn==true){
                bookBtn->setVisible(true);
            }
        }
        
//        this->addChild(bookBtn,100);
    }

//
    

//    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") || CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")) {
//        CCSprite* couponBtn = NULL;
//        if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet50Coupon")==true) {
//            couponBtn = CCSprite::create("book/coloringbook5.png");
//        }else if(CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet20Coupon")==true){
//            couponBtn = CCSprite::create("book/coloringbook7.png");
//        }
//        //        CCSprite* couponBtn = CCSprite::create("book/couponBtn.png");
//        GameManager::sharedManager()->btnIndex=1;
//        bool canShowMainSceneBookBtn = GameManager::sharedManager()->checkIsCanShowMainBtn(GameManager::sharedManager()->btnIndex);
//    //    CCSprite* bookBtn = CCSprite::create("book/bookBtn.png");
//        if (couponBtn!=NULL) {
//            couponBtn->setPosition(ccp(leftTop.x+couponBtn->getContentSize().width*1.6, leftTop.y-50));
//            couponBtn->setTag(kCouponBookTag);
//            couponBtn->setVisible(false);
//            if (canShowMainSceneBookBtn==true && strcmp(coinRegion, "US") == 0) {
//                couponBtn->setVisible(true);
//            }
//            this->addChild(couponBtn,100);
//        }
//
//    }


    
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/sink/sinkBg.mp3", true);
    this->setTouchEnabled(true);
    return true;
}

void SelectColorTheme::showTheme(){
    int xIndex=0;

    themeX=0;
    if (GameManager::sharedManager()->isIphoneX()) {
//        xIndex = 120;
        themeX= 530;
    }else if(DeviceManager::sharedManager()->getIsPad()){
        themeX= 470;
    }else{
        themeX= 520;
    }
    minDis = winCenter.x-3*themeX;
    maxDis = winCenter.x+9*themeX;
    if (ColorManager::shared()->selectedColorTheme == false) {
        for (int i=0; i<curThemeTotalCount; i++) {
//            if (i<4) {
//                ColorManager::shared()->colorThemePos[i] =580+i*470;
//            }else{
                ColorManager::shared()->colorThemePos[i] =minDis+i*themeX;
//            }
           
        }
    }
//    for (int i=0; i<6; i++) {
////            ColorManager::shared()->colorThemePos[i] =-830+i*470;
//        CCLOG("---位置%f---",ColorManager::shared()->colorThemePos[i]);
//    }
    int themeVal = 99;
    int curVal = ColorManager::shared()->curColorTheme;
    for (int i=0; i<curThemeTotalCount; i++) {
        CCSprite* colorTheme = CCSprite::create(CCString::createWithFormat("DinoColor/colorUI/colorBg_%d.png",ColorManager::shared()->themeIndexArr[i]+1)->getCString());
            colorTheme->setPosition(ccp( ColorManager::shared()->colorThemePos[i], winCenter.y));
            themeVal = ColorManager::shared()->themeIndexArr[i];
            if (themeVal == curVal) {
                colorTheme->setScale(0.9);
            }else{
                colorTheme->setScale(0.45);
            }
            colorTheme->setTag(kColorThemeTag+i);
            this->addChild(colorTheme);
        if (themeVal>=11) {
            CCSprite* newTag = CCSprite::create("newmainscene/buildTags/new.png");
            newTag->setPosition(ccp(colorTheme->getContentSize().width*0.9, colorTheme->getContentSize().height*0.95));
            newTag->setScale(0.5);
            colorTheme->addChild(newTag,2);
        }
    }
    
}


SelectColorTheme::SelectColorTheme(){}

SelectColorTheme::~SelectColorTheme(){}

void SelectColorTheme::onEnter(){
    CCLayer::onEnter();
}

void SelectColorTheme::onExit(){
    CCLayer::onExit();
    this->unschedule(schedule_selector(SelectColorTheme::checkIsCanShowLayer));
}

void SelectColorTheme::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, DinoTownScene::scene(), ccBLACK));
}

void SelectColorTheme::goNext(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectColorAniScene::scene(), ccBLACK));
}

void SelectColorTheme::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool SelectColorTheme::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCSprite* back = (CCSprite*)this->getChildByTag(kBackTag);
    touchMoveDis = 0;
    startX = location.x;
    CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
    CCSprite* bookBtn = (CCSprite*)this->getChildByTag(kBookBtnTag);
    CCSprite* couponBtn = (CCSprite*)this->getChildByTag(kCouponBookTag);
    if (BookLayer==NULL) {
        if (back!= NULL && back->boundingBox().containsPoint(location) && backClick==false) {
            backClick = true;
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorTheme::clickBack))));
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        }else if (bookBtn!=NULL && bookBtn->boundingBox().containsPoint(location) && bookBtn->isVisible()==true && showCurTheme==false && GameManager::sharedManager()->clickedBookBtn==false){
            GameManager::sharedManager()->clickedBookBtn=true;
            bookBtnClick=true;
            showCurTheme=true;
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            bookBtn->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorTheme::openBookPage))));
//        }else{
//            bookBtnClick=false;
        }else if (couponBtn!=NULL && couponBtn->boundingBox().containsPoint(location) && couponBtn->isVisible()==true && GameManager::sharedManager()->clickedBookBtn==false){
            GameManager::sharedManager()->clickedBookBtn=true;
            showCurTheme=true;
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            if ((CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") || CCUserDefault::sharedUserDefault()->getBoolForKey("purchased"))) {
                
                couponBtn->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorTheme::openCuoponBookPage))));
            }
        }
    }
    

    
    
    return true;
}

void SelectColorTheme::ccTouchMoved(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint preLocation = touch->getPreviousLocationInView();
    preLocation = CCDirector::sharedDirector()->convertToGL(preLocation);
    beginX = preLocation.x;
    endX = location.x;
    touchMoveDis = endX-beginX;
    finishX = startX-endX;
//    if (finishX==0) {
//        touchMoveTheme = false;
//    }
//    if(abs(startX-endX)>150){
//        resetThemePos();
//    }
//    CCLOG("---%d---",endX-beginX);
//    resetThemePos();
    if (showCurTheme == false) {
        for (int i=0; i<curThemeTotalCount; i++) {
            CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
            if (colorThemes!=NULL && touchMoveTheme==false) {
                int themePos = colorThemes->getPosition().x;
                float themeScale = colorThemes->getScale();
                colorThemes->setPositionX(themePos+ touchMoveDis);
                ColorManager::shared()->colorThemePos[i] = colorThemes->getPositionX();
    //            CCLOG("---位置坐标%f---",colorThemes->getPosition().x);
    //            CCLOG("---移动位置差%f---",colorThemes->getPosition().x-580);
    //            CCLOG("---当前主题%d---",ColorManager::shared()->curColorTheme);
                if (abs(colorThemes->getPosition().x-winCenter.x)<100 && themeScale<0.8 ) {
                    colorThemes->runAction(CCScaleTo::create(0.3, 0.9));
                    curThemeIndex = i;
                }
                if(abs(colorThemes->getPosition().x-winCenter.x)>100 && themeScale>0.65){
                    colorThemes->runAction(CCScaleTo::create(0.3, 0.45));
                }
    //            if(themeScale>0.65){
    //                scaleThemeIndex++;
    //            }else{
    //                scaleThemeIndex--;
    //            }
            }
    }
    
    
//        CCLOG("---实际的位置%f---",colorThemes->getPositionX());
//        CCLOG("---调整前的位置%f---",ColorManager::shared()->colorThemePos[i]);
    }
            
    
}

void SelectColorTheme::ccTouchEnded(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    CCPoint point = touch->getLocation();
    CCPoint lastPoint = touch->getPreviousLocation();
    CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
    CCLayer* cuoponBookLayer = (CCLayer*)this->getChildByTag(kCuoponBtbLayerTag);
//    for (int i=0; i<6; i++) {
//        CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
//        ColorManager::shared()->colorThemePos[i] = colorThemes->getPositionX();
//    }

//    if (showCurTheme == false && clickTheme==false) {
        this->resetThemePos();
//    }
    if (bookBtnClick==false && BookLayer==NULL && cuoponBookLayer==NULL) {
        float moveIndex=0;
            for (int i=0; i<curThemeTotalCount; i++) {
                CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
                int themePos = colorThemes->getPosition().x;
    //            CCLOG("---最后实际的位置%f---",colorThemes->getPositionX());
    //            CCLOG("---位置差%f---",themePos-winCenter.x);
                if (abs(themePos-winCenter.x)<resetThemePosX && showCurTheme==false && touchMoveTheme==false && finishX !=0) {
    //                if (touchMoveDis!=0 && finishX !=0) {
    //                    resetThemePos();
    //                }
    //                if(colorThemes->getScale()<0.65){
//                    bookBtnClick=true;
                    curTouchMoveX = 0;
                    if(clickTheme==false){
                        ColorManager::shared()->curColorTheme=ColorManager::shared()->themeIndexArr[i];
                    }
                    ColorManager::shared()->selectedColorTheme=true;
                    showCurTheme = true;
                    colorThemes->runAction(CCScaleTo::create(0.3, 0.9));
                    curThemeIndex = i;
    //                }
                    moveIndex=themePos-winCenter.x;
    //                moveIndex= ColorManager::shared()->colorThemePos[curThemeIndex]-winCenter.x;
                    curMoveThemeX = moveIndex;
                    this->fixOldThemePos(moveIndex);
    //                CCLOG("---距离差%f---",moveIndex);
//                    for (int n=0; n<curThemeTotalCount; n++) {
//                        CCSprite* oldcolorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+n);
//        //                    if (ColorManager::shared()->curColorTheme==i) {
//        //                        oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.6));
//        ////                        scaleThemeIndex--;
//        //                    }
//                        if(n!=curThemeIndex){
//                            oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
//                        }
//                        
//                        oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(oldcolorThemes->getPositionX()-moveIndex, winCenter.y)),
//                                                                     CCDelayTime::create(0.3),
//                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),NULL));
//        //                    CCLOG("---移动位置差%d---",moveIndex);
//                        ColorManager::shared()->colorThemePos[n] = ColorManager::shared()->colorThemePos[n]-moveIndex;
//        //                    oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(ColorManager::shared()->colorThemePos[i]-moveIndex, winCenter.y)),
//        //                                                                 CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
//        //                                                                 CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),
//        //                                                                 NULL));
//    //
//                    }
                }
                if (colorThemes!=NULL && colorThemes->boundingBox().containsPoint(location) && clickTheme==false && touchMoveDis==0  && touchMoveTheme==false) {
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                    if ( ColorManager::shared()->curColorTheme==ColorManager::shared()->themeIndexArr[i]) {
        //                ColorManager::shared()->curColorTheme=i;
                        clickTheme=true;
                        ColorManager::shared()->selectedColorTheme=true;
                        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
                        
                        colorThemes->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorTheme::goNext))));
                    }else{
                        touchMoveTheme = true;
                        clickTheme=false;
                        showCurTheme = true;
    //                    CCLOG("---当前主题%d---",ColorManager::shared()->curColorTheme);
    //                    CCLOG("---选择的主题%d---",i);
    //                    if (scaleThemeIndex==0) {
                        colorThemes->runAction(CCScaleTo::create(0.3, 0.9));
    //                        scaleThemeIndex++;
    //                    }
                        curThemeIndex = i;
                        moveIndex = themePos-winCenter.x;
    //                    CCLOG("---位置%d---",ColorManager::shared()->curColorTheme);
    //                    if (ColorManager::shared()->colorThemePos[i] < ColorManager::shared()->colorThemePos[ ColorManager::shared()->curColorTheme]) {
    //                        moveIndex = themeX;
    //                    }else if (ColorManager::shared()->colorThemePos[i] > ColorManager::shared()->colorThemePos[ ColorManager::shared()->curColorTheme]){
    //                        moveIndex = -themeX;
    //                    }
                        curTouchMoveX = -moveIndex;
    //                    moveIndex = ColorManager::shared()->colorThemePos[curThemeIndex]-winCenter.x;
                        this->fixOldThemePos(moveIndex);
//                        for (int j=0; j<curThemeTotalCount; j++) {
//                            CCSprite* oldcolorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+j);
//    //                        if (ColorManager::shared()->curColorTheme==i) {
//    //                            oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
//    ////                            scaleThemeIndex--;
//    //                        }
//                            if(j!=curThemeIndex){
//                                oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
//                            }
//                            moveIndex=themePos-winCenter.x;
//        //                    CCLOG("---移动位置差%d---",moveIndex);
//    //                        CCLOG("---最后的位置%f---",ColorManager::shared()->colorThemePos[j]);
//                            oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(oldcolorThemes->getPositionX()-moveIndex, winCenter.y)),
//    //                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetTouchThemePos)),
//    //                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
//                                                                         CCDelayTime::create(0.3),
//                                                                         CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),
//                                                                         NULL));
//    //                        CCLOG("---最后调整后第0个的位置%f---",ColorManager::shared()->colorThemePos[0]);
//                            ColorManager::shared()->colorThemePos[j] = ColorManager::shared()->colorThemePos[j]-moveIndex;
//    //                        CCLOG("---最后未调整的位置%f---",ColorManager::shared()->colorThemePos[j]);
//    //                        oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(ColorManager::shared()->colorThemePos[j]+moveIndex, winCenter.y)),
//    //                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
//    //                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),
//    //                                                                     NULL));
//    //                        resetThemePos();
//    //                        CCLOG("---位置%f---",ColorManager::shared()->colorThemePos[i]);
//    //
//                        }
    //                    resetThemePos();
                        ColorManager::shared()->curColorTheme= ColorManager::shared()->themeIndexArr[i];
                        
                    }
                    
    //                for (int i=0; i<6; i++) {
    //                        ColorManager::shared()->colorThemePos[i] =-830+i*470;
                        
    //                }

    //                ColorManager::shared()->colorThemeIndex = i+1;
                }
            }
    }

    

//    this->resetThemePos();
//    this->runAction(CCSequence::create(CCDelayTime::create(0.3),
//                                       CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
//                                       NULL));
//    for (int i=0; i<6; i++) {
////            ColorManager::shared()->colorThemePos[i] =-830+i*470;
//        CCLOG("---再次调整后的位置%f---",ColorManager::shared()->colorThemePos[i]);
//    }
}

void SelectColorTheme::fixOldThemePos(int themeMove){
    for (int n=0; n<curThemeTotalCount; n++) {
        CCSprite* oldcolorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+n);
        if(n!=curThemeIndex){
            oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
        }
        
        oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(oldcolorThemes->getPositionX()-themeMove, winCenter.y)),
                                                     CCDelayTime::create(0.3),
                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),NULL));
//                    CCLOG("---移动位置差%d---",moveIndex);
        ColorManager::shared()->colorThemePos[n] = ColorManager::shared()->colorThemePos[n]-themeMove;
//
    }
}

void SelectColorTheme::canTouchTheme(){
    touchMoveTheme = false;
    showCurTheme = false;
    
}





void SelectColorTheme::resetThemePos(){
//    int movedIndex=0;
    
//    if (touchMoveDis<0 || curTouchMoveX<0) {
//        for (int i=0; i<curThemeTotalCount; i++) {
//            CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
//            if (colorThemes!=NULL) {
//                float themePos = colorThemes->getPosition().x;
//                if (themePos+touchMoveDis<minDis) { //左滑
////                    movedIndex =-minDis-themePos;
//    //                CCLOG("---%d---",movedIndex);
//    //                CCLOG("---%d---",touchMoveDis);
////                    CCLOG("---调整后最后一位的位置%f---",ColorManager::shared()->colorThemePos[5]);
//                    if(i!=0){
//                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[i-1]+themeX);
//                    }else{
//                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[curThemeTotalCount-1]+themeX);
//                    }
//                    ColorManager::shared()->colorThemePos[i] = colorThemes->getPosition().x;
//                    
////                    curResetTheme = i;
////                    CCLOG("---第5的调整位置%f---",ColorManager::shared()->colorThemePos[5]);
////                    CCLOG("---第0的调整位置%f---",ColorManager::shared()->colorThemePos[0]);
////                }else if(themePos+touchMoveDis>1520){       //右滑
////    //                CCLOG("---%d---",movedIndex);
////    //                CCLOG("---%d---",touchMoveDis);
////                    movedIndex =themePos-1520;
////                    if(i!=5){
////                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[i+1]+touchMoveDis-470);
////                    }else{
////                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[0]+touchMoveDis-470);
////                    }
////                    ColorManager::shared()->colorThemePos[i] = colorThemes->getPosition().x;
////                }else{
////                    if(curMoveThemeX!=0){
////                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]-curMoveThemeX;
////                    }else if(curTouchMoveX!=0){
////                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]+curTouchMoveX;
////                    }
//                    
//                }
//                
//            }
//        }
//    }else if(touchMoveDis>0 || curTouchMoveX>0){
//        for (int i=curThemeTotalCount-1; i>=0; i--) {
//            CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
//            if (colorThemes!=NULL) {
//                float themePos = colorThemes->getPosition().x;
//                if(themePos+touchMoveDis>maxDis){       //右滑
//    //                CCLOG("---%d---",movedIndex);
//    //                CCLOG("---%d---",touchMoveDis);
////                    movedIndex =themePos-maxDis;
//                    if(i!=curThemeTotalCount-1){
//                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[i+1]-themeX);
//                    }else{
//                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[0]-themeX);
//                    }
//                    ColorManager::shared()->colorThemePos[i] = colorThemes->getPosition().x;
////                    curResetTheme = i;
////                }else{
////                    if(curMoveThemeX!=0){
////                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]-curMoveThemeX;
////                    }else if(curTouchMoveX!=0){
////                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]+curTouchMoveX;
////                    }
//                    
//                }
//            }
//        }
//    }

    float totalLoopWidth = curThemeTotalCount * themeX;

    // 循环遍历所有主题精灵
    for (int i = 0; i < curThemeTotalCount; i++) {
        CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag + i);
        if (colorThemes != NULL) {
            float currentX = colorThemes->getPositionX();
            // 使用 while 循环处理快速滑动时一次性超出多个循环宽度的情况
            while (currentX < minDis) {
                currentX += totalLoopWidth;
            }
            // 使用 while 循环处理快速滑动时一次性超出多个循环宽度的情况
            while (currentX > maxDis) {
                currentX -= totalLoopWidth;
            }
            
            // 只有当精灵的位置发生变化时才更新，避免不必要的设置
            if (colorThemes->getPositionX() != currentX) {
                colorThemes->setPositionX(currentX);
                // 同时更新 ColorManager 中保存的主题位置，以保持数据同步
                ColorManager::shared()->colorThemePos[i] = currentX;
            }
        }
    }
    
}


void SelectColorTheme::openBookPage() {
//    DeviceManager::sharedManager()->showiOSVideo(1);
    this->showBookPageBtn(0);
}

void SelectColorTheme::showBookPageBtn(int pageId) {
    CCPoint center = GameManager::getCenter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);

    if (blacklayer == NULL) {
        CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
        if (BookLayer == NULL) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        buyLayer = (CCLayer*)BuyLayer::nodeWithID(_pageId);
//#else
            BookLayer = (CCLayer*)BookLayer::nodeWithID(0,0);
//        buyLayer->setInitPageIndex(0);
//#endif
            BookLayer->setTag(kBookLayerTag);
            this->addChild(BookLayer, 300);

            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(center);
            BookLayer->addChild(blacklayer,-1);
        }
    }
    showCurTheme=false;
    bookBtnClick=false;
}


void SelectColorTheme::checkIsShowBookBtn(){
    CCSprite* bookBtn = (CCSprite*)this->getChildByTag(kBookBtnTag);
    if (bookBtn != NULL && bookBtn->isVisible()==false) {
        bookBtn->setVisible(true);
//        this->unschedule(schedule_selector(SelectColorTheme::checkIsShowBookBtn));
    }
}


void SelectColorTheme::checkIsCanShowLayer(){
    CCLayer* bookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
    if (!GameManager::sharedManager()->checkIsInterestInBook()){
        this->unschedule(schedule_selector(SelectColorTheme::checkIsCanShowLayer));
    }else if (GameManager::sharedManager()->checkIsCanShowBookLayer() && bookLayer == NULL){
        this->openBookPage();
        GameManager::sharedManager()->canShowColorBookLayer=false;
        GameManager::sharedManager()->recordBookLayerInfo();
        this->unschedule(schedule_selector(SelectColorTheme::checkIsCanShowLayer));
    }
}


void SelectColorTheme::openCuoponBookPage() {
    string curBookCouponType = CCUserDefault::sharedUserDefault()->getStringForKey("bookcouponbyproduct", "");
    
//    DeviceManager::sharedManager()->showiOSVideo(1);
    if (strcmp(curBookCouponType.c_str(), "mouthoryear") == 0) {
        this->showCuoponBookPageBtn(3);
    } else if (strcmp(curBookCouponType.c_str(), "lifetime") == 0) {
        this->showCuoponBookPageBtn(4);
    }
}

void SelectColorTheme::showCuoponBookPageBtn(int pageId) {
    CCPoint center = GameManager::getCenter();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);

    if (blacklayer == NULL) {
        BookLayer* bookLayer = (BookLayer*)this->getChildByTag(kCuoponBtbLayerTag);
        if (bookLayer == NULL) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        buyLayer = (CCLayer*)BuyLayer::nodeWithID(_pageId);
//#else
            bookLayer = BookLayer::nodeWithID(pageId,0);
//            bookLayer->curBookIndex = 0;
//        buyLayer->setInitPageIndex(0);
//#endif
            bookLayer->setTag(kCuoponBtbLayerTag);
            this->addChild(bookLayer, 300);

            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(center);
            bookLayer->addChild(blacklayer,-1);
        }
    }
    showCurTheme=false;
}
