//
//  SelectNewColorThemeScene.cpp
//  DrDino
//
//  Created by mac on 2025/7/8.
//

#include "SelectNewColorThemeScene.hpp"
#include "GameManager.h"
#include "DeviceManager.h"
#include "DinoTownScene.h"
#include "ColorManager.hpp"
#include "BookLayer.h"
#include "SelectColorAniScene.hpp"

enum{
    kBackTag = 1,
    kColorThemeTag = 10,
    kGuideFingerTag = 131,
    kCouponBookTag=996,
    kBookLayerTag = 997,
    kBackLayerTag=998,
    kBookBtnTag = 999,
    kCuoponBtbLayerTag=1000,
};

CCScene* SelectNewColorThemeScene::scene(){
    CCScene* scene = CCScene::create();
    SelectNewColorThemeScene* layer = SelectNewColorThemeScene::create();
    scene->addChild(layer);
    return scene;
}

bool SelectNewColorThemeScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    GameManager::sharedManager()->clickedBookBtn=false;
    bookBtnClick=false;
    backClick = false;
    clickColorTheme = false;
    showCurColorTheme = false;
    touchMoveColorTheme = false;
    endX = 0;
    beginX = 0;
    scaleThemeIndex=0;
    curColorTheme = 0;
    curMoveThemeX = 0;
    finishX = 0.0;
    startX = 0.0;
    
    minDis = 0;
    maxDis = 0;
    
    resetThemePosX = 320;
    
    curResetTheme = 0;
    
    curTouchMoveX = 0;
    
    colorThemeTotalCount = ColorManager::shared()->curThemeTotalCount;
    
    winCenter = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    
    CCSprite* bg = CCSprite::create("DinoColor/roles-bg.png");
    bg->setPosition(winCenter);
    this->addChild(bg);
    
    if (GameManager::sharedManager()->isIphoneX()) {
//        bg->setScale(1.3);
    }
    if (DeviceManager::sharedManager()->getIsPad()) {
        resetThemePosX = 250;
    }
    CCSize curWinSize = GameManager::sharedManager()->getViewVisibleSize();
    
    //返回按钮
    CCSprite* back=CCSprite::create("background/back.png");
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBackTag);
    if (curWinSize.width < 900) {
        back->setScale(0.8);
    }else if (curWinSize.width < 930) {
        
    }else if (curWinSize.width < 1136) {
        back->setScale(0.8);
    }
    this->addChild(back,1);
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("gameBackgroundMp3", true) ;
    
    const char* coinRegion = DeviceManager::sharedManager()->getCurrentDinoRegion();

    bool si = GameManager::sharedManager()->canShowColorBookLayer;
//    CCSprite* bookBtn= CCSprite::create("book/busyBookBtn.png");
    CCSprite* bookBtn = NULL;
    bool canShowMainSceneBookBtn = GameManager::sharedManager()->checkIsCanShowMainBtn(0);
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll")==false && CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")==false){
        bookBtn = CCSprite::create("book/busyBookBtn.png");
        bookBtn->setTag(kBookBtnTag);
    }else if(CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll")==true || CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")==true){
        if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet50Coupon")==true) {
            bookBtn = CCSprite::create("book/busybook5.png");
            bookBtn->setTag(kCouponBookTag);
        }else if(CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet20Coupon")==true){
            bookBtn = CCSprite::create("book/busybook7.png");
            bookBtn->setTag(kCouponBookTag);
        }
        canShowMainSceneBookBtn = GameManager::sharedManager()->checkIsCanShowMainBtn(1);
    }
//    CCSprite* bookBtn = CCSprite::create("book/busyBookBtn.png");
    if (bookBtn!=NULL) {
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

    
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/sink/sinkBg.mp3", true);
    
    

//    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") || CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")) {
//        CCSprite* couponBtn =NULL;
//        if (CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet50Coupon")==true) {
//            couponBtn = CCSprite::create("book/busybook5.png");
//        }else if(CCUserDefault::sharedUserDefault()->getBoolForKey("IsGet20Coupon")==true){
//            couponBtn = CCSprite::create("book/busybook7.png");
//        }
////        CCSprite* couponBtn = CCSprite::create("book/couponBtn.png");
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


    
    
    this->setTouchEnabled(true);
    
    
    
    return true;
}

void SelectNewColorThemeScene::showNewColorTheme(){
    
    CCSize curWinSize = GameManager::sharedManager()->getViewVisibleSize();
    
    int themeCol = 0;
    int themeRow = 0;

    int maxCols = 5;
    float padding = 10.0f;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize(); // 当前屏幕尺寸

   
    CCSprite* tmpSprite = CCSprite::create("DinoColor/colorUI/colorBg_1.png");
    CCSize itemSize = tmpSprite->getContentSize()*0.291;
    tmpSprite->removeFromParentAndCleanup(true); // 释放临时 sprite

    float gridWidth = maxCols * itemSize.width;
    float totalWidth = gridWidth + (maxCols - 1) * padding;

    // 计算起始 x/y，居中对齐
    float startX = (winSize.width - totalWidth) / 2 + itemSize.width *0.6;
    float startY = winSize.height *0.85 ;

    int totalRows = (colorThemeTotalCount + maxCols - 1) / maxCols;
    int lastRowCount = colorThemeTotalCount % maxCols;
    if (lastRowCount == 0) lastRowCount = maxCols;
    int ipadOffY_y=6;
    if (curWinSize.width < 900) {
        ipadOffY_y=1;
        startY = winSize.height *0.82 ;
    }

    for (int i = 0; i < colorThemeTotalCount; i++) {
        CCSprite* colorTheme = CCSprite::create(CCString::createWithFormat("DinoColor/colorUI/colorBg_%d.png", i + 1)->getCString());
        colorTheme->setScale(0.291);
        float currentStartX = startX;
        if (i>9) {
            maxCols=4;
        }
        if (themeRow >1 && lastRowCount < 4) {
            float lastRowWidth = lastRowCount * itemSize.width + (lastRowCount - 1) * padding;
            currentStartX = (winSize.width - lastRowWidth) / 2 + itemSize.width *0.05;
        }
        float posX = currentStartX + themeCol * (itemSize.width + padding);
        float posY = startY - themeRow * (itemSize.height + ipadOffY_y);
        colorTheme->setPosition(ccp(posX, posY));
        
        colorTheme->setTag(kColorThemeTag + i);
        this->addChild(colorTheme);

        if (themeCol >= maxCols - 1) {
            themeCol = 0;
            themeRow++;
        } else {
            themeCol++;
        }
    }
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("ColorThemeGuide", false)) {
        this->scheduleOnce(schedule_selector(SelectNewColorThemeScene::showColorThemeAni), 0.1);
    }
}

void SelectNewColorThemeScene::showColorThemeAni(){
    for (int i=0; i<colorThemeTotalCount; i++) {
        CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
        
        float delayTime = 0.2*(i+1);
        if (colorThemes!=NULL) {
            colorThemes->runAction(CCSequence::create(CCDelayTime::create(delayTime),CCScaleTo::create(0.3, 0.336),CCScaleTo::create(0.3, 0.291),NULL));
            if (i == colorThemeTotalCount - 1) {
                this->scheduleOnce(schedule_selector(SelectNewColorThemeScene::showFirstGuide), delayTime);
            }
        }
    }
}

SelectNewColorThemeScene::SelectNewColorThemeScene(){}
SelectNewColorThemeScene::~SelectNewColorThemeScene(){}


void SelectNewColorThemeScene::onEnter(){
    CCLayer::onEnter();
    
    this->showNewColorTheme();
}

void SelectNewColorThemeScene::onExit(){
    CCLayer::onExit();
}

void SelectNewColorThemeScene::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, DinoTownScene::scene(), ccBLACK));
}

void SelectNewColorThemeScene::goNext(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectColorAniScene::scene(), ccBLACK));
}

void SelectNewColorThemeScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, this);
}

bool SelectNewColorThemeScene::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCSprite* back = (CCSprite*)this->getChildByTag(kBackTag);
    if (back!=NULL && back->boundingBox().containsPoint(location) && backClick == false) {
        backClick = true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectNewColorThemeScene::clickBack))));
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }else{
        
    }
    
    return true;
}

void SelectNewColorThemeScene::ccTouchMoved(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint preLocation = touch->getPreviousLocationInView();
    preLocation = CCDirector::sharedDirector()->convertToGL(preLocation);
    
}


void SelectNewColorThemeScene::ccTouchEnded(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    for (int i=0; i<colorThemeTotalCount; i++) {
        CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag+i);
        
        if (colorThemes!=NULL && colorThemes->boundingBox().containsPoint(location) && clickColorTheme==false && touchMoveColorTheme==false) {
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            clickColorTheme=true;
            ColorManager::shared()->selectedColorTheme=true;
            ColorManager::shared()->curColorTheme=ColorManager::shared()->themeIndexArr[i];
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            colorThemes->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectNewColorThemeScene::goNext))));
            CCUserDefault::sharedUserDefault()->setBoolForKey("ColorThemeGuide", true);

            
        }
    }

    
}


void SelectNewColorThemeScene::canTouchColorTheme(){
    touchMoveColorTheme = false;
    showCurColorTheme = false;
    
}

void SelectNewColorThemeScene::showFirstGuide(){
    CCPoint centerPos = GameManager::sharedManager()->getCenter();
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
    CCSprite* colorThemes = (CCSprite*)this->getChildByTag(kColorThemeTag);
    if (guideFinger == NULL && colorThemes != NULL) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pick.plist");
            
        guideFinger = CCSprite::createWithSpriteFrameName("touch0.png");
        guideFinger->setPosition(ccp(colorThemes->getPosition().x+50, colorThemes->getPosition().y-30));
        guideFinger->setTag(kGuideFingerTag);
        guideFinger->setScale(0.5);
        guideFinger->setOpacity(0);
        this->addChild(guideFinger, 1002);
        
        CCArray* frame = CCArray::create();
        for (int m =0; m<2; m++) {
            CCString *name = CCString::createWithFormat("touch%d.png",m);
            frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(0.3f);
        animation->setLoops(3);
        
        CCAnimate* guideAnim = CCAnimate::create(animation);
        guideFinger->runAction(CCSequence::create(CCFadeTo::create(0.5, 255),guideAnim,CCFadeTo::create(0.5, 0),CCCallFunc::create(this, callfunc_selector(SelectNewColorThemeScene::removeFirstGuide)),NULL));
    }
    

}

void SelectNewColorThemeScene::removeFirstGuide()
{
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
    if (guideFinger != NULL) {
        guideFinger->stopAllActions();
        guideFinger->removeFromParentAndCleanup(true);
        guideFinger = NULL;
    }
}



