//
//  SelectColorAniScene.cpp
//  DrDino
//
//  Created by LiXiaofei on 2/14/23.
//

#include "SelectColorAniScene.hpp"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "DeviceManager.h"
#include "DinoTownScene.h"
#include "ColorManager.hpp"
#include "SelectNewColorThemeScene.hpp"
#include "ColorCanvasView.h"
#include "BuyLayer.h"
#include "BookLayer.h"


using namespace CocosDenshion;

enum{
    kBuyLayerTag = 0,
    kBackTag = 1,
    kLockTag = 2,
    kColorBoardTag = 20,
    kColorAniTag = 30,
    kBookLayerTag = 997,
    kBackLayerTag=998,
    kBookBtnTag = 999,
};

CCScene* SelectColorAniScene::scene(){
    CCScene* scene = CCScene::create();
    SelectColorAniScene* layer  = SelectColorAniScene::create();
    scene->addChild(layer);
    return scene;
}


bool SelectColorAniScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    backClick = false;
    clickTheme = false;
    
    selectAniIndex =0;
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("blackGround", true) ;//给blcakGround键赋值
    
    winCenter = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    CCPoint rightTop = GameManager::sharedManager()->getRightTopPos();
    
    CCSprite* bg = CCSprite::create("DinoColor/colorUI/colorAniBg.png");
    bg->setPosition(winCenter);
    this->addChild(bg);
    
    iphoneXOffsetX = 0.0f;
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
        iphoneXOffsetX = 120.0f;
    }
    
    //返回按钮
    CCSprite* back=CCSprite::create("background/back.png");
    back->setTag(kBackTag);
    if (DeviceManager::sharedManager()->getIsPad()) {
        back->setScale(0.7);
        back->setPosition(ccp(leftTop.x+30,leftTop.y-30));
    }else{
        back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    }
    this->addChild(back,1);
//    CCSprite* bookBtn=NULL;
//    if (ColorManager::shared()->colorBookIndex==0) {
//        bookBtn = CCSprite::create("book/colorBookBtn.png");
//        ColorManager::shared()->colorBookIndex=1;
//    }else{
//        bookBtn = CCSprite::create("book/universalBookBtn.png");
//        ColorManager::shared()->colorBookIndex=0;
//    }
////    CCSprite* bookBtn = CCSprite::create("book/colorBookBtn.png");
////    CCSprite* bookBtn = CCSprite::create("book/universalBookBtn.png");
//    bookBtn->setTag(kBookBtnTag);
////    if (GameManager::sharedManager()->checkIsCanShowBookBtn()==false) {
//    bookBtn->setVisible(false);
////    }
//    if (DeviceManager::sharedManager()->getIsPad()) {
//        bookBtn->setScale(0.7);
//        bookBtn->setPosition(ccp(rightTop.x-bookBtn->getContentSize().width*0.4,leftTop.y-30));
//    }else{
//        bookBtn->setPosition(ccp(rightTop.x-bookBtn->getContentSize().width*0.6,leftTop.y-50));
//    }
//    this->addChild(bookBtn,100);
    const char* coinRegion = DeviceManager::sharedManager()->getCurrentDinoRegion();


//    if (GameManager::sharedManager()->checkIsInterestInBook() && strcmp(coinRegion, "US") == 0 && GameManager::sharedManager()->canShowColorBookLayer){
////    if (GameManager::sharedManager()->checkIsDayForShowBookLayer()){
//        GameManager::sharedManager()->curBookGameIndex=0;
//        this->schedule(schedule_selector(SelectColorAniScene::checkIsCanShowLayer),1);
////    }
//    }
    
//    bool canShowColorBtn = CCUserDefault::sharedUserDefault()->getBoolForKey("canShowColorBtn");
//    bool canShowColorBtn = GameManager::sharedManager()->checkIsSecondDayForBookBtn();
//    if (strcmp(coinRegion, "US") == 0 && canShowColorBtn==true){
//        this->checkIsShowBookBtn();
////        this->schedule(schedule_selector(SelectColorAniScene::checkIsShowBookBtn),1);
//    }
    
    CCLOG("---位置%d---",ColorManager::shared()->curColorTheme);
    
    this->scheduleOnce(schedule_selector(SelectColorAniScene::showAllTheme), 0.3);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/sink/sinkBg.mp3", true);
    
    this->setTouchEnabled(true);
    return true;
}

void SelectColorAniScene::addLock(CCObject *_parent,int _index) {

    const char* lockName = "lock";
    
    CCSprite* parentSpr = (CCSprite*)_parent;
    
    CCSprite* locked = CCSprite::create(CCString::createWithFormat("iap/%s.png",lockName)->getCString()) ;   //那么设置一个锁的精灵
    locked->setScale(0.6) ;
    locked->setPosition(ccp(parentSpr->getContentSize().width-25, parentSpr->getContentSize().height/4));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked,9) ;
}

void SelectColorAniScene::selectAdsOrIAP(int _pageIndex) {
        CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
            buyLayer = (CCLayer*)BuyLayer::nodeWithID(_pageIndex);
            buyLayer->setTag(kBuyLayerTag);
            this->addChild(buyLayer, 100);

            CCSize _winSize = GameManager::sharedManager()->getViewVisibleSize();
            CCPoint center = GameManager::sharedManager()->getCenter();

            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), _winSize.width, _winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(ccp(center.x,center.y));
            buyLayer->addChild(blacklayer, -1);
        }
}

void SelectColorAniScene::showAllTheme(){
    
    CCSize curWinSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint lastscenePos = GameManager::sharedManager()->getLeftBottomPos();
    
    int x_x = 0;
    
    if (DeviceManager::sharedManager()->getIsPad()) {
        x_x = 400;
    }else if(GameManager::sharedManager()->isIphoneX()){
        x_x = 430;
    }else{
        x_x = 540;
    }
    
    for (int i=0; i<12; i++) {
        
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",1,1,2,1,2)->getCString());
        CCLOG("---位置%d---",ColorManager::shared()->curColorTheme);
        CCSprite* board = CCSprite::create("DinoColor/colorUI/colorBoard.png");
        board->setPosition(ccp(270+(i%4)*200+iphoneXOffsetX, 520-(i/4)*200));
        board->setTag(kColorBoardTag+i);
        this->addChild(board);
        
        CCSprite* colorTheme = CCSprite::create(CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/coloringType_line.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1)->getCString());
        colorTheme->setPosition(ccp(board->getContentSize().width/2, board->getContentSize().height/2));
        colorTheme->setScale(0.2);
        colorTheme->setTag(kColorAniTag+i);
        board->addChild(colorTheme,2);
        
        std::string canvasFileName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(i+1)+"canvas";
        CCImage* canvasImage = ColorManager::shared()->loadImageFromBinaryFile(canvasFileName);
        
        if (canvasImage != NULL) {
            
            CCTexture2D* canvasTexture = new CCTexture2D();
            if (canvasTexture && canvasTexture->initWithImage(canvasImage)) {
                
                
                CCSprite* stencilSpr = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("DinoColor/canvas.png"), CCRect(0, 0, 739, 640));
                stencilSpr->setAnchorPoint(ccp(0.0, 0.0));
                stencilSpr->setPosition(CCPointZero);
                
                CCSprite* canvasSpr = CCSprite::createWithTexture(canvasTexture);
                canvasSpr->setPosition(ccp(lastscenePos.x+x_x, canvasSpr->getContentSize().height/2));
                if (GameManager::sharedManager()->isIphoneX()) {
                    canvasSpr->setScaleX(0.6);
                }
                CCClippingNode* clip = CCClippingNode::create(stencilSpr);
                clip->addChild(canvasSpr);
                
                clip->setContentSize(CCSizeMake(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
                clip->setAnchorPoint(ccp(0.5, 0.5));
                clip->setPosition(ccp(colorTheme->getPosition().x, colorTheme->getPosition().y));
                clip->setAlphaThreshold(0.0f);
                clip->setScale(0.2);
                board->addChild(clip);
                
                CC_SAFE_RELEASE(canvasTexture);
            }
            CC_SAFE_RELEASE(canvasImage);
        }
        
        CCString* name = CCString::create( CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1,ColorManager::shared()->curColorTheme+1,i+1)->getCString());
        CCDictionary* pointArray = CCDictionary::createWithContentsOfFile(name->getCString()) ;
        if (pointArray!= NULL) {
            for (int j = 0; j < pointArray->count(); j++) {
                CCString* key = (CCString*)pointArray->allKeys()->objectAtIndex(j);
                std::string strFileName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(i+1)+key->m_sString;
                CCImage* renderImage = ColorManager::shared()->loadImageFromBinaryFile(strFileName);
                
                if (renderImage != NULL) {
                    
                    CCTexture2D* lastSceneTexture = new CCTexture2D();
                    if (lastSceneTexture && lastSceneTexture->initWithImage(renderImage)) {
                        
                        CCString* pngName = CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/%s.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1,key->getCString());
                        CCSprite* stencilSpr = CCSprite::create(pngName->getCString());
                        stencilSpr->setAnchorPoint(ccp(0.0, 0.0));
                        stencilSpr->setPosition(CCPointZero);
                        
                        CCSprite* lastSceneSpr = CCSprite::createWithTexture(lastSceneTexture);
                        lastSceneSpr->setPosition(ccp(stencilSpr->getContentSize().width/2, stencilSpr->getContentSize().height/2+2));
                        
                        CCClippingNode* clip = CCClippingNode::create(stencilSpr);
                        clip->addChild(lastSceneSpr);
                        
                        clip->setContentSize(CCSizeMake(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
                        clip->setAnchorPoint(ccp(0.5, 0.5));
                        clip->setPosition(ccp(colorTheme->getContentSize().width/2, colorTheme->getContentSize().height/2));
                        clip->setAlphaThreshold(0.0f);
    //                    clip->setScale(0.2);
                        colorTheme->addChild(clip,-1);
                        
                        CC_SAFE_RELEASE(lastSceneTexture);
                    }
                    CC_SAFE_RELEASE(renderImage);
                    
                }
                
            }
        }
        
//        std::string picFileName = "ColoringType_"+std::to_string(ColorManager::shared()->colorThemeIndex)+"_"+std::to_string(i+1)+"_Preview";
//        CCImage* renderImage = ColorManager::shared()->loadImageFromBinaryFile(picFileName);
//        
//        if (renderImage != NULL) {
//            
//            CCTexture2D* sceneTexture = new CCTexture2D();
//            sceneTexture->initWithImage(renderImage);
//            
//            CCSprite* colorSceneSpr = CCSprite::createWithTexture(sceneTexture);
//            colorSceneSpr->setPosition(ccp(board->getContentSize().width/2, board->getContentSize().height/2));
//            colorSceneSpr->setScale(0.2);
//            board->addChild(colorSceneSpr);
//        }
        
        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")) {
            if (ColorManager::shared()->curColorTheme == 12 || ColorManager::shared()->curColorTheme == 6
                || ColorManager::shared()->curColorTheme == 9 || ColorManager::shared()->curColorTheme == 7 || ColorManager::shared()->curColorTheme == 1) {
                if (i>0) {
                    this->addLock(board, i);
                }else if(i==0){
                    CCSprite* freeTag = CCSprite::create("dinohospital/free.png");
                    freeTag->setPosition(ccp(board->getContentSize().width-25, board->getContentSize().height));
                    freeTag->setScale(0.8);
                    board->addChild(freeTag,2);
                }
                
            }else{
                this->addLock(board, i);
            }
//            if (ColorManager::shared()->curColorTheme == 3 || ColorManager::shared()->curColorTheme == 8) {
//                if (i>1) {
//                    this->addLock(board, i);
//                }else if(i<=1){
//                    CCSprite* freeTag = CCSprite::create("dinohospital/free.png");
//                    freeTag->setPosition(ccp(board->getContentSize().width-25, board->getContentSize().height));
//                    freeTag->setScale(0.8);
//                    board->addChild(freeTag,2);
//                }
//                
//            }else if(ColorManager::shared()->curColorTheme != 3){
//                if(i==0){
//                        CCSprite* freeTag = CCSprite::create("dinohospital/free.png");
//                        freeTag->setPosition(ccp(board->getContentSize().width-25, board->getContentSize().height));
//                        freeTag->setScale(0.8);
//                        board->addChild(freeTag,2);
//                }else{
//                    this->addLock(board, i);
//                }
//                
//            }
            
        }
        
    }
    
}




SelectColorAniScene::SelectColorAniScene(){}

SelectColorAniScene::~SelectColorAniScene(){}

void SelectColorAniScene::onEnter(){
    CCLayer::onEnter();
}

void SelectColorAniScene::onExit(){
    CCLayer::onExit();
}

void SelectColorAniScene::clickBack(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectNewColorThemeScene::scene(), ccBLACK));
}

void SelectColorAniScene::goNext(){
    CCUserDefault::sharedUserDefault()->setBoolForKey("blackGround", false) ;//给blcakGround键赋值
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ColorCanvasView::scene(), ccBLACK));
}

void SelectColorAniScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool SelectColorAniScene::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCSprite* back = (CCSprite*)this->getChildByTag(kBackTag);
    
    CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
//    CCSprite* bookBtn = (CCSprite*)this->getChildByTag(kBookBtnTag);

    if(BookLayer==NULL){
        if (back!= NULL && back->boundingBox().containsPoint(location) && backClick==false) {
            backClick = true;
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::clickBack))));
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//        }else if (bookBtn!=NULL && bookBtn->boundingBox().containsPoint(location) && bookBtn->isVisible()==true && clickTheme==false){
//            clickTheme=true;
//            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
//            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
//            bookBtn->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::openBookPage))));
        }else{
            for (int i=0; i<12; i++) {
                CCSprite* board = (CCSprite*)this->getChildByTag(kColorBoardTag+i);
        //        CCSprite* colorAni = (CCSprite*)board->getChildByTag(kColorAniTag+i);
                CCSprite* adLock = (CCSprite*)board->getChildByTag(kLockTag);
        //        CCPoint themePos =board->convertToNodeSpace(location);
                if (board!=NULL && board->boundingBox().containsPoint(location) && clickTheme==false) {
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                    if (adLock!=NULL) {
        //                CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //                adLock->runAction(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()));
                        this->selectAdsOrIAP(2);
                    }else{
                        selectAniIndex = i;
                        clickTheme=true;
                        ColorManager::shared()->colorAniIndex = i+1;
                        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.3);
                        
                        board->runAction(CCSequence::create(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()),
                                                                          CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::aniAction)),
                                                                          CCDelayTime::create(1.1),
                                                                          CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::goNext)),NULL));
                    }

        //            colorThemes->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::goNext))));
                }
            }
        }
    }
    

    

    
    
    
    
    return true;
}

void SelectColorAniScene::ccTouchMoved(CCTouch *touch, CCEvent *event){
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
}

void SelectColorAniScene::ccTouchEnded(CCTouch *touch, CCEvent *event){
    CCPoint point = touch->getLocation();
    CCPoint lastPoint = touch->getPreviousLocation();
    

}


void SelectColorAniScene::aniAction(){
    CCSprite* board = (CCSprite*)this->getChildByTag(kColorBoardTag+selectAniIndex);
    if (board!=NULL) {
        CCSprite* colorThemes = (CCSprite*)board->getChildByTag(kColorAniTag+selectAniIndex);
        if(colorThemes!=NULL){
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/hairSalon/takeBrush.mp3");
            CCSpawn* actionSpawn = CCSpawn::create(CCJumpBy::create(0.3, ccp(0, 0), 5, 2),
                                                   CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::aniJumpMp3)),
                                                   NULL);
            colorThemes ->runAction(CCSequence::create(CCRotateTo::create(0.1, -25),
                                                       CCRotateTo::create(0.1, 0),
                                                       CCRotateTo::create(0.1, 25),
                                                       CCRotateTo::create(0.1, 0),
                                                       actionSpawn,
                                                       NULL));
        }
        
    }
}


void SelectColorAniScene::aniJumpMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/changing/buttonJump.mp3");
}


void SelectColorAniScene::openBookPage() {
//    DeviceManager::sharedManager()->showiOSVideo(1);
    this->showBookPageBtn(0);
}

void SelectColorAniScene::showBookPageBtn(int pageId) {
//    CCPoint center = GameManager::getCenter();
//
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
//
//    if (blacklayer == NULL) {
//        CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
//        if (BookLayer == NULL) {
////#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
////        buyLayer = (CCLayer*)BuyLayer::nodeWithID(_pageId);
////#else
//            BookLayer = (CCLayer*)BookLayer::nodeWithID(0,0);
////        buyLayer->setInitPageIndex(0);
////#endif
//            BookLayer->setTag(kBookLayerTag);
//            this->addChild(BookLayer, 300);
//
//            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
//            blacklayer->ignoreAnchorPointForPosition(false);
//            blacklayer->setPosition(center);
//            BookLayer->addChild(blacklayer,-1);
//            clickTheme=false;
//        }
//    }

}


void SelectColorAniScene::checkIsShowBookBtn(){
    CCSprite* bookBtn = (CCSprite*)this->getChildByTag(kBookBtnTag);
    if ( bookBtn != NULL && bookBtn->isVisible()==false) {
        bookBtn->setVisible(true);
//        this->unschedule(schedule_selector(SelectColorAniScene::checkIsShowBookBtn));
    }
}


void SelectColorAniScene::checkIsCanShowLayer(){
    CCLayer* bookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
    if (!GameManager::sharedManager()->checkIsInterestInBook()){
        this->unschedule(schedule_selector(SelectColorAniScene::checkIsCanShowLayer));
    }else if (GameManager::sharedManager()->checkIsCanShowBookLayer() && bookLayer == NULL){
        this->openBookPage();
        GameManager::sharedManager()->canShowColorBookLayer=false;
        GameManager::sharedManager()->recordBookLayerInfo();
        this->unschedule(schedule_selector(SelectColorAniScene::checkIsCanShowLayer));
    }
}
