//
//  SelectColorTheme.cpp
//  DrDino
//
//  Created by LiXiaofei on 2/13/23.
//

#include "SelectColorTheme.hpp"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
//#include "DeviceManager.h"

#include "SelectColorAniScene.hpp"
#include "ColorManager.hpp"

using namespace CocosDenshion;

enum{
    kBackTag = 1,
    kscrollView1Tag =2,
    kscrollView2Tag =3,
    kColorThemeTag = 20,
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
    
    backClick = false;
    clickTheme = false;
    showCurTheme = false;
    touchMoveTheme = false;
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

    winCenter = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();

    CCSprite* bg = CCSprite::create("DinoColor/roles-bg.jpg");
    bg->setPosition(winCenter);
    this->addChild(bg);

    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
    }
    if (GameManager::sharedManager()->isAndroidPad()) {
        resetThemePosX = 250;
    }

    //返回按钮
//    CCSprite* back=CCSprite::create("background/back.png");
//    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
//    back->setTag(kBackTag);
//    this->addChild(back,1);

    this->scheduleOnce(schedule_selector(SelectColorTheme::showTheme), 0.3);

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/sink/sinkBg.mp3", true);
    this->setTouchEnabled(true);
    return true;
}

void SelectColorTheme::showTheme(){
    int xIndex=0;

    themeX=0;
    if (GameManager::sharedManager()->isIphoneX()) {
//        xIndex = 120;1
        themeX= 530;
    }else if(GameManager::sharedManager()->isAndroidPad()){
        themeX= 470;
    }else{
        themeX= 520;
    }
    minDis = winCenter.x-3*themeX;
    maxDis = winCenter.x+2*themeX;
    if (ColorManager::shared()->selectedColorTheme == false) {
        for (int i=0; i<6; i++) {
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
    
    for (int i=0; i<6; i++) {
        CCSprite* colorTheme = CCSprite::create(CCString::createWithFormat("DinoColor/colorUI/colorBg_%d.png",i+1)->getCString());
            colorTheme->setPosition(ccp( ColorManager::shared()->colorThemePos[i], winCenter.y));
            if (i==ColorManager::shared()->curColorTheme) {
                colorTheme->setScale(0.9);
            }else{
                colorTheme->setScale(0.45);
            }
            colorTheme->setTag(kColorThemeTag+i);
            this->addChild(colorTheme);

    }
    
}


SelectColorTheme::SelectColorTheme(){}

SelectColorTheme::~SelectColorTheme(){}

void SelectColorTheme::onEnter(){
    CCLayer::onEnter();
}

void SelectColorTheme::onExit(){
    CCLayer::onExit();
}

void SelectColorTheme::clickBack(){
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->num == 5){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->num = 0;
        }else{
            GameManager::sharedManager()->num++;
        }
    }
  //  CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, DinoTownScene::scene(), ccBLACK));
}

void SelectColorTheme::goNext(){
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        GameManager::sharedManager()->showInterstitial();
    }
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
    showCurTheme=false;
    startX = location.x;
    
    if (back!= NULL && back->boundingBox().containsPoint(location) && backClick==false) {
        backClick = true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorTheme::clickBack))));
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
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
        for (int i=0; i<6; i++) {
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
    
//    for (int i=0; i<6; i++) {
//        CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
//        ColorManager::shared()->colorThemePos[i] = colorThemes->getPositionX();
//    }

//    if (showCurTheme == false && clickTheme==false) {
        this->resetThemePos();
//    }

    float moveIndex=0;
        for (int i=0; i<6; i++) {
            CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
            int themePos = colorThemes->getPosition().x;
//            CCLOG("---最后实际的位置%f---",colorThemes->getPositionX());
//            CCLOG("---位置差%f---",themePos-winCenter.x);
            if (abs(themePos-winCenter.x)<resetThemePosX && showCurTheme==false && touchMoveTheme==false && finishX !=0) {
//                if (touchMoveDis!=0 && finishX !=0) {
//                    resetThemePos();
//                }
//                if(colorThemes->getScale()<0.65){
                curTouchMoveX = 0;
                if(clickTheme==false){
                    ColorManager::shared()->curColorTheme=i;
                }
                ColorManager::shared()->selectedColorTheme=true;
                showCurTheme = true;
                colorThemes->runAction(CCScaleTo::create(0.3, 0.9));
                curThemeIndex = i;
//                }
                moveIndex=themePos-winCenter.x;
//                moveIndex= ColorManager::shared()->colorThemePos[curThemeIndex]-winCenter.x;
                curMoveThemeX = moveIndex;
//                CCLOG("---距离差%f---",moveIndex);
                for (int i=0; i<6; i++) {
                    CCSprite* oldcolorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
//                    if (ColorManager::shared()->curColorTheme==i) {
//                        oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.6));
////                        scaleThemeIndex--;
//                    }
                    if(i!=curThemeIndex){
                        oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
                    }
                    
                    oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(oldcolorThemes->getPositionX()-moveIndex, winCenter.y)),
                                                                 CCDelayTime::create(0.3),
                                                                 CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),NULL));
//                    CCLOG("---移动位置差%d---",moveIndex);
                    ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]-moveIndex;
//                    oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(ColorManager::shared()->colorThemePos[i]-moveIndex, winCenter.y)),
//                                                                 CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
//                                                                 CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),
//                                                                 NULL));
//
                }
            }
            if (colorThemes!=NULL && colorThemes->boundingBox().containsPoint(location) && clickTheme==false && touchMoveDis==0  && touchMoveTheme==false) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                if ( ColorManager::shared()->curColorTheme==i) {
                    GameManager::sharedManager()->trackMixpanel(CCString::createWithFormat("Click ColorTheme%d Game Times",i)->getCString());
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
                    for (int j=0; j<6; j++) {
                        CCSprite* oldcolorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+j);
//                        if (ColorManager::shared()->curColorTheme==i) {
//                            oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
////                            scaleThemeIndex--;
//                        }
                        if(j!=curThemeIndex){
                            oldcolorThemes->runAction(CCScaleTo::create(0.3, 0.45));
                        }
                        moveIndex=themePos-winCenter.x;
    //                    CCLOG("---移动位置差%d---",moveIndex);
//                        CCLOG("---最后的位置%f---",ColorManager::shared()->colorThemePos[j]);
                        oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(oldcolorThemes->getPositionX()-moveIndex, winCenter.y)),
//                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetTouchThemePos)),
//                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
                                                                     CCDelayTime::create(0.3),
                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),
                                                                     NULL));
//                        CCLOG("---最后调整后第0个的位置%f---",ColorManager::shared()->colorThemePos[0]);
                        ColorManager::shared()->colorThemePos[j] = ColorManager::shared()->colorThemePos[j]-moveIndex;
//                        CCLOG("---最后未调整的位置%f---",ColorManager::shared()->colorThemePos[j]);
//                        oldcolorThemes->runAction(CCSequence::create(CCMoveTo::create(0.1, ccp(ColorManager::shared()->colorThemePos[j]+moveIndex, winCenter.y)),
//                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::resetThemePos)),
//                                                                     CCCallFunc::create(this, callfunc_selector(SelectColorTheme::canTouchTheme)),
//                                                                     NULL));
//                        resetThemePos();
//                        CCLOG("---位置%f---",ColorManager::shared()->colorThemePos[i]);
//
                    }
//                    resetThemePos();
                    ColorManager::shared()->curColorTheme=i;
                    
                }
                
//                for (int i=0; i<6; i++) {
//                        ColorManager::shared()->colorThemePos[i] =-830+i*470;
                    
//                }

//                ColorManager::shared()->colorThemeIndex = i+1;
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


void SelectColorTheme::canTouchTheme(){
    touchMoveTheme = false;
    showCurTheme = false;
    
}





void SelectColorTheme::resetThemePos(){
//    int movedIndex=0;
    
    if (touchMoveDis<0 || curTouchMoveX<0) {
        for (int i=0; i<6; i++) {
            CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
            if (colorThemes!=NULL) {
                float themePos = colorThemes->getPosition().x;
                if (themePos+touchMoveDis<minDis) { //左滑
//                    movedIndex =-minDis-themePos;
    //                CCLOG("---%d---",movedIndex);
    //                CCLOG("---%d---",touchMoveDis);
//                    CCLOG("---调整后最后一位的位置%f---",ColorManager::shared()->colorThemePos[5]);
                    if(i!=0){
                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[i-1]+themeX);
                    }else{
                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[5]+themeX);
                    }
                    ColorManager::shared()->colorThemePos[i] = colorThemes->getPosition().x;
                    
//                    curResetTheme = i;
//                    CCLOG("---第5的调整位置%f---",ColorManager::shared()->colorThemePos[5]);
//                    CCLOG("---第0的调整位置%f---",ColorManager::shared()->colorThemePos[0]);
//                }else if(themePos+touchMoveDis>1520){       //右滑
//    //                CCLOG("---%d---",movedIndex);
//    //                CCLOG("---%d---",touchMoveDis);
//                    movedIndex =themePos-1520;
//                    if(i!=5){
//                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[i+1]+touchMoveDis-470);
//                    }else{
//                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[0]+touchMoveDis-470);
//                    }
//                    ColorManager::shared()->colorThemePos[i] = colorThemes->getPosition().x;
//                }else{
//                    if(curMoveThemeX!=0){
//                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]-curMoveThemeX;
//                    }else if(curTouchMoveX!=0){
//                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]+curTouchMoveX;
//                    }
                    
                }
                
            }
        }
    }else if(touchMoveDis>0 || curTouchMoveX>0){
        for (int i=5; i>=0; i--) {
            CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
            if (colorThemes!=NULL) {
                float themePos = colorThemes->getPosition().x;
                if(themePos+touchMoveDis>maxDis){       //右滑
    //                CCLOG("---%d---",movedIndex);
    //                CCLOG("---%d---",touchMoveDis);
//                    movedIndex =themePos-maxDis;
                    if(i!=5){
                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[i+1]-themeX);
                    }else{
                        colorThemes->setPositionX(ColorManager::shared()->colorThemePos[0]-themeX);
                    }
                    ColorManager::shared()->colorThemePos[i] = colorThemes->getPosition().x;
//                    curResetTheme = i;
//                }else{
//                    if(curMoveThemeX!=0){
//                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]-curMoveThemeX;
//                    }else if(curTouchMoveX!=0){
//                        ColorManager::shared()->colorThemePos[i] = ColorManager::shared()->colorThemePos[i]+curTouchMoveX;
//                    }
                    
                }
            }
        }
    }

}
