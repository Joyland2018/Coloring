//
//  SelectColorAniScene.cpp
//  DrDino
//
//  Created by LiXiaofei on 2/14/23.
//

#include "SelectColorAniScene.hpp"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
//#include "DeviceManager.h"

#include "ColorManager.hpp"
#include "SelectColorTheme.hpp"
#include "ColorCanvasView.h"
#include "BuyPage.h"


using namespace CocosDenshion;

enum{
    kBuyLayerTag = 0,
    kBackTag = 1,
    kLockTag = 2,
    kColorBoardTag = 20,
    kColorAniTag = 30,
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
    
    winCenter = GameManager::sharedManager()->getCenter();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    
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
    back->setPosition(ccp(leftTop.x+50,leftTop.y-50));
    back->setTag(kBackTag);
    this->addChild(back,1);
    
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
    parentSpr->addChild(locked) ;
}

void SelectColorAniScene::selectAdsOrIAP(int _pageIndex) {
        CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
            buyLayer = (CCLayer*)BuyPage::nodeWithID(_pageIndex);
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
    
    if (GameManager::sharedManager()->isAndroidPad()) {
        x_x = 50;
    }else if(GameManager::sharedManager()->isIphoneX()){
        x_x = 0;
    }else{
        x_x = 0;
    }
    
    for (int i=0; i<8; i++) {
        
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",1,1,2,1,2)->getCString());
        CCLOG("---位置%d---",ColorManager::shared()->curColorTheme);
        CCSprite* board = CCSprite::create("DinoColor/colorUI/colorBoard.png");
        board->setPosition(ccp(270+(i%4)*200+iphoneXOffsetX-x_x, 420-(i/4)*200));
        board->setTag(kColorBoardTag+i);
        this->addChild(board);
        
        CCSprite* colorTheme = CCSprite::create(CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/coloringType_line.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1)->getCString());
        colorTheme->setPosition(ccp(board->getContentSize().width/2, board->getContentSize().height/2));
        colorTheme->setScale(0.2);
        colorTheme->setTag(kColorAniTag+i);
        board->addChild(colorTheme,2);
        
//        std::string canvasFileName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(i+1)+"canvas";
//        CCImage* canvasImage = ColorManager::shared()->loadImageFromBinaryFile(canvasFileName);
//
//        if (canvasImage != NULL) {
//
//            CCTexture2D* canvasTexture = new CCTexture2D();
//            if (canvasTexture && canvasTexture->initWithImage(canvasImage)) {
//
//
//                CCSprite* stencilSpr = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("DinoColor/canvas.png"), CCRect(0, 0, 739, 640));
//                stencilSpr->setAnchorPoint(ccp(0.0, 0.0));
//                stencilSpr->setPosition(CCPointZero);
//
//                CCSprite* canvasSpr = CCSprite::createWithTexture(canvasTexture);
//                canvasSpr->setPosition(ccp(lastscenePos.x+x_x, canvasSpr->getContentSize().height/2));
//                if (GameManager::sharedManager()->isIphoneX()) {
//                    canvasSpr->setScaleX(0.6);
//                }
//                CCClippingNode* clip = CCClippingNode::create(stencilSpr);
//                clip->addChild(canvasSpr);
//
//                clip->setContentSize(CCSizeMake(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
//                clip->setAnchorPoint(ccp(0.5, 0.5));
//                clip->setPosition(ccp(colorTheme->getPosition().x, colorTheme->getPosition().y));
//                clip->setAlphaThreshold(0.0f);
//                clip->setScale(0.2);
//                board->addChild(clip);
//
//                CC_SAFE_RELEASE(canvasTexture);
//            }
//            CC_SAFE_RELEASE(canvasImage);
//        }
        
        CCString* name = CCString::create( CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1,ColorManager::shared()->curColorTheme+1,i+1)->getCString());
        CCDictionary* pointArray = CCDictionary::createWithContentsOfFile(name->getCString()) ;
        if (pointArray!= NULL) {
            for (int j = 0; j < pointArray->count(); j++) {
                CCString* key = (CCString*)pointArray->allKeys()->objectAtIndex(j);
                std::string strFileName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(i+1)+key->m_sString;
//                CCImage* renderImage = ColorManager::shared()->loadImageFromBinaryFile(strFileName);
                
//                if (renderImage != NULL) {
                    
//                    CCTexture2D* lastSceneTexture = new CCTexture2D();
//                    if (lastSceneTexture && lastSceneTexture->initWithImage(renderImage)) {
                        
                        CCString* pngName = CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/%s.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1,key->getCString());
                        CCSprite* stencilSpr = CCSprite::create(pngName->getCString());
                        stencilSpr->setAnchorPoint(ccp(0.0, 0.0));
                        stencilSpr->setPosition(CCPointZero);
                        
//                        CCSprite* lastSceneSpr = CCSprite::createWithTexture(lastSceneTexture);
//                        lastSceneSpr->setPosition(ccp(stencilSpr->getContentSize().width/2, stencilSpr->getContentSize().height/2+2));

                        CCClippingNode* clip = CCClippingNode::create(stencilSpr);
//                        clip->addChild(lastSceneSpr);
                        
                        clip->setContentSize(CCSizeMake(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
                        clip->setAnchorPoint(ccp(0.5, 0.5));
                        clip->setPosition(ccp(colorTheme->getContentSize().width/2, colorTheme->getContentSize().height/2));
                        clip->setAlphaThreshold(0.0f);
    //                    clip->setScale(0.2);
                        colorTheme->addChild(clip,-1);
                        
//                        CC_SAFE_RELEASE(lastSceneTexture);
//                    }
//                    CC_SAFE_RELEASE(renderImage);
                    
//                }
                
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
            if (ColorManager::shared()->curColorTheme == 3) {
                if (i>1) {
                    this->addLock(board, i);
                }else if(i<=1){
                    CCSprite* freeTag = CCSprite::create("background/free.png");
                    freeTag->setPosition(ccp(board->getContentSize().width-25, board->getContentSize().height));
                    freeTag->setScale(0.8);
                    board->addChild(freeTag,2);
                }
                
            }else if(ColorManager::shared()->curColorTheme != 3){
                if(i==0){
                        CCSprite* freeTag = CCSprite::create("background/free.png");
                        freeTag->setPosition(ccp(board->getContentSize().width-25, board->getContentSize().height));
                        freeTag->setScale(0.8);
                        board->addChild(freeTag,2);
                }else{
                    this->addLock(board, i);
                }
                
            }
            
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
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->num == 5){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->num = 0;
        }else{
            GameManager::sharedManager()->num++;
        }
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectColorTheme::scene(), ccBLACK));
}

void SelectColorAniScene::goNext(){
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
    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
    if (back!= NULL && back->boundingBox().containsPoint(location) && backClick==false&&!buyLayer) {
        backClick = true;
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        back->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::clickBack))));
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }

    for (int i=0; i<8; i++) {
        CCSprite* board = (CCSprite*)this->getChildByTag(kColorBoardTag+i);
//        CCSprite* colorAni = (CCSprite*)board->getChildByTag(kColorAniTag+i);
        CCSprite* adLock = (CCSprite*)board->getChildByTag(kLockTag);
//        CCPoint themePos =board->convertToNodeSpace(location);
        if (board!=NULL && board->boundingBox().containsPoint(location) && clickTheme==false &&!buyLayer) {
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
                GameManager::sharedManager()->trackMixpanel(CCString::createWithFormat("Click ColorTheme%d themeAni%d Times",ColorManager::shared()->curColorTheme,i)->getCString());
                board->runAction(CCSequence::create(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()),
                                                                  CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::aniAction)),
                                                                  CCDelayTime::create(1.1),
                                                                  CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::goNext)),NULL));
            }

//            colorThemes->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(SelectColorAniScene::goNext))));
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
