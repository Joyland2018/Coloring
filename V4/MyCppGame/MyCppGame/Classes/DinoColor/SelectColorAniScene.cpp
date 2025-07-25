//
//  SelectColorAniScene.cpp
//  DrDino
//
//  Created by LiXiaofei on 2/14/23.
//

#include "SelectColorAniScene.hpp"
#include "audio/include/SimpleAudioEngine.h"
#include "GameManager.h"
//#include "DeviceManager.h"

#include "ColorManager.hpp"
#include "SelectColorTheme.hpp"
#include "ColorCanvasView.h"
#include "BuyPage.h"

USING_NS_CC;
using namespace CocosDenshion;

enum{
    kBuyLayerTag = 0,
    kBackTag = 1,
    kLockTag = 2,
    kColorBoardTag = 20,
    kColorAniTag = 30,
};

Scene* SelectColorAniScene::scene(){
    Scene* scene = Scene::create();
    SelectColorAniScene* layer  = SelectColorAniScene::create();
    scene->addChild(layer);
    return scene;
}


bool SelectColorAniScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    backClick = false;
    clickTheme = false;
    
    selectAniIndex =0;
    
    winCenter = GameManager::sharedManager()->getCenter();
    Vec2 leftTop = GameManager::sharedManager()->getLeftTopPos();
    
    Sprite* bg = Sprite::create("DinoColor/colorUI/colorAniBg.png");
    bg->setPosition(winCenter);
    this->addChild(bg);
    
    iphoneXOffsetX = 0.0f;
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
        iphoneXOffsetX = 120.0f;
    }
    
    //返回按钮
    Sprite* back=Sprite::create("background/back.png");
    back->setPosition(Vec2(leftTop.x+50,leftTop.y-50));
    back->setTag(kBackTag);
    this->addChild(back,1);
    
    CCLOG("---位置%d---",ColorManager::shared()->curColorTheme);
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SelectColorAniScene::showAllTheme), 0.3);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/sink/sinkBg.mp3", true);
    
    // Setup touch listener for Cocos2d-x 4.0
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(SelectColorAniScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(SelectColorAniScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(SelectColorAniScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void SelectColorAniScene::addLock(Node *_parent,int _index) {

    const char* lockName = "lock";
    
    Sprite* parentSpr = (Sprite*)_parent;
    
    Sprite* locked = Sprite::create(StringUtils::format("iap/%s.png",lockName)) ;   //那么设置一个锁的精灵
    locked->setScale(0.6) ;
    locked->setPosition(Vec2(parentSpr->getContentSize().width-25, parentSpr->getContentSize().height/4));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked) ;
}

void SelectColorAniScene::selectAdsOrIAP(int _pageIndex) {
        Layer* buyLayer = (Layer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
            buyLayer = (Layer*)BuyPage::nodeWithID(_pageIndex);
            buyLayer->setTag(kBuyLayerTag);
            this->addChild(buyLayer, 100);

            Size _winSize = GameManager::sharedManager()->getViewVisibleSize();
            Vec2 center = GameManager::sharedManager()->getCenter();

            LayerColor *blacklayer = LayerColor::create(Color4B(0, 0, 0, 180), _winSize.width, _winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(Vec2(center.x,center.y));
            buyLayer->addChild(blacklayer, -1);
        }
}

void SelectColorAniScene::showAllTheme(){
    
    Size curWinSize = GameManager::sharedManager()->getViewVisibleSize();
    Vec2 lastscenePos = GameManager::sharedManager()->getLeftBottomPos();
    
    int x_x = 0;
    
    if (GameManager::sharedManager()->isAndroidPad()) {
        x_x = 50;
    }else if(GameManager::sharedManager()->isIphoneX()){
        x_x = 0;
    }else{
        x_x = 0;
    }
    
    for (int i=0; i<8; i++) {
        
//        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(StringUtils::format("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",1,1,2,1,2));
        CCLOG("---位置%d---",ColorManager::shared()->curColorTheme);
        Sprite* board = Sprite::create("DinoColor/colorUI/colorBoard.png");
        board->setPosition(Vec2(270+(i%4)*200+iphoneXOffsetX-x_x, 420-(i/4)*200));
        board->setTag(kColorBoardTag+i);
        this->addChild(board);
        
        Sprite* colorTheme = Sprite::create(StringUtils::format("DinoColor/ColoringType_%d/ColoringType_%d_%d/coloringType_line.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1));
        colorTheme->setPosition(Vec2(board->getContentSize().width/2, board->getContentSize().height/2));
        colorTheme->setScale(0.2);
        colorTheme->setTag(kColorAniTag+i);
        board->addChild(colorTheme,2);
        
//        std::string canvasFileName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(i+1)+"canvas";
//        Image* canvasImage = ColorManager::shared()->loadImageFromBinaryFile(canvasFileName);
//
//        if (canvasImage != NULL) {
//
//            Texture2D* canvasTexture = new Texture2D();
//            if (canvasTexture && canvasTexture->initWithImage(canvasImage)) {
//
//
//                Sprite* stencilSpr = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("DinoColor/canvas.png"), Rect(0, 0, 739, 640));
//                stencilSpr->setAnchorPoint(Vec2(0.0, 0.0));
//                stencilSpr->setPosition(Vec2::ZERO);
//
//                Sprite* canvasSpr = Sprite::createWithTexture(canvasTexture);
//                canvasSpr->setPosition(Vec2(lastscenePos.x+x_x, canvasSpr->getContentSize().height/2));
//                if (GameManager::sharedManager()->isIphoneX()) {
//                    canvasSpr->setScaleX(0.6);
//                }
//                ClippingNode* clip = ClippingNode::create(stencilSpr);
//                clip->addChild(canvasSpr);
//
//                clip->setContentSize(Size(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
//                clip->setAnchorPoint(Vec2(0.5, 0.5));
//                clip->setPosition(Vec2(colorTheme->getPosition().x, colorTheme->getPosition().y));
//                clip->setAlphaThreshold(0.0f);
//                clip->setScale(0.2);
//                board->addChild(clip);
//
//                CC_SAFE_RELEASE(canvasTexture);
//            }
//            CC_SAFE_RELEASE(canvasImage);
//        }
        
        std::string name = StringUtils::format("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1,ColorManager::shared()->curColorTheme+1,i+1);
        ValueMap pointArray = FileUtils::getInstance()->getValueMapFromFile(name) ;
        if (!pointArray.empty()) {
            for (auto& pair : pointArray) {
                std::string key = pair.first;
                std::string strFileName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(i+1)+key;
//                Image* renderImage = ColorManager::shared()->loadImageFromBinaryFile(strFileName);
                
//                if (renderImage != NULL) {
                    
//                    Texture2D* lastSceneTexture = new Texture2D();
//                    if (lastSceneTexture && lastSceneTexture->initWithImage(renderImage)) {
                        
                        std::string pngName = StringUtils::format("DinoColor/ColoringType_%d/ColoringType_%d_%d/%s.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,i+1,key.c_str());
                        Sprite* stencilSpr = Sprite::create(pngName);
                        stencilSpr->setAnchorPoint(Vec2(0.0, 0.0));
                        stencilSpr->setPosition(Vec2::ZERO);
                        
//                        Sprite* lastSceneSpr = Sprite::createWithTexture(lastSceneTexture);
//                        lastSceneSpr->setPosition(Vec2(stencilSpr->getContentSize().width/2, stencilSpr->getContentSize().height/2+2));

                        ClippingNode* clip = ClippingNode::create(stencilSpr);
//                        clip->addChild(lastSceneSpr);
                        
                        clip->setContentSize(Size(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
                        clip->setAnchorPoint(Vec2(0.5, 0.5));
                        clip->setPosition(Vec2(colorTheme->getContentSize().width/2, colorTheme->getContentSize().height/2));
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
//        Image* renderImage = ColorManager::shared()->loadImageFromBinaryFile(picFileName);
//        
//        if (renderImage != NULL) {
//            
//            Texture2D* sceneTexture = new Texture2D();
//            sceneTexture->initWithImage(renderImage);
//            
//            Sprite* colorSceneSpr = Sprite::createWithTexture(sceneTexture);
//            colorSceneSpr->setPosition(Vec2(board->getContentSize().width/2, board->getContentSize().height/2));
//            colorSceneSpr->setScale(0.2);
//            board->addChild(colorSceneSpr);
//        }
        
        if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased")) {
            if (ColorManager::shared()->curColorTheme == 3) {
                if (i>1) {
                    this->addLock(board, i);
                }else if(i<=1){
                    Sprite* freeTag = Sprite::create("background/free.png");
                    freeTag->setPosition(Vec2(board->getContentSize().width-25, board->getContentSize().height));
                    freeTag->setScale(0.8);
                    board->addChild(freeTag,2);
                }
                
            }else if(ColorManager::shared()->curColorTheme != 3){
                if(i==0){
                        Sprite* freeTag = Sprite::create("background/free.png");
                        freeTag->setPosition(Vec2(board->getContentSize().width-25, board->getContentSize().height));
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

SelectColorAniScene::~SelectColorAniScene(){
    if (touchListener) {
        _eventDispatcher->removeEventListener(touchListener);
    }
}

void SelectColorAniScene::onEnter(){
    Layer::onEnter();
}

void SelectColorAniScene::onExit(){
    Layer::onExit();
}

void SelectColorAniScene::clickBack(){
    if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->num == 5){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->num = 0;
        }else{
            GameManager::sharedManager()->num++;
        }
    }
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, SelectColorTheme::scene(), Color3B::BLACK));
}

void SelectColorAniScene::goNext(){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, ColorCanvasView::scene(), Color3B::BLACK));
}

bool SelectColorAniScene::onTouchBegan(Touch *touch, Event *event){
    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    Sprite* back = (Sprite*)this->getChildByTag(kBackTag);
    Layer* buyLayer = (Layer*)this->getChildByTag(kBuyLayerTag);
    if (back!= NULL && back->getBoundingBox().containsPoint(location) && backClick==false&&!buyLayer) {
        backClick = true;
        ScaleBy* scaleBy = ScaleBy::create(0.1, 1.2);
        SimpleAudioEngine::getInstance()->playEffect("mp3/touchItem.mp3");
        back->runAction(Sequence::createWithTwoActions(Sequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CallFunc::create(CC_CALLBACK_0(SelectColorAniScene::clickBack, this))));
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }

    for (int i=0; i<8; i++) {
        Sprite* board = (Sprite*)this->getChildByTag(kColorBoardTag+i);
//        Sprite* colorAni = (Sprite*)board->getChildByTag(kColorAniTag+i);
        Sprite* adLock = (Sprite*)board->getChildByTag(kLockTag);
//        Vec2 themePos =board->convertToNodeSpace(location);
        if (board!=NULL && board->getBoundingBox().containsPoint(location) && clickTheme==false &&!buyLayer) {
            SimpleAudioEngine::getInstance()->playEffect("mp3/touchItem.mp3");
            if (adLock!=NULL) {
//                ScaleBy* scaleBy = ScaleBy::create(0.1, 1.2);
//                adLock->runAction(Sequence::createWithTwoActions(scaleBy, scaleBy->reverse()));
                this->selectAdsOrIAP(2);
            }else{
                selectAniIndex = i;
                clickTheme=true;
                ColorManager::shared()->colorAniIndex = i+1;
                ScaleBy* scaleBy = ScaleBy::create(0.1, 1.3);
                GameManager::sharedManager()->trackMixpanel(StringUtils::format("Click ColorTheme%d themeAni%d Times",ColorManager::shared()->curColorTheme,i).c_str());
                board->runAction(Sequence::create(Sequence::createWithTwoActions(scaleBy, scaleBy->reverse()),
                                                                  CallFunc::create(CC_CALLBACK_0(SelectColorAniScene::aniAction, this)),
                                                                  DelayTime::create(1.1),
                                                                  CallFunc::create(CC_CALLBACK_0(SelectColorAniScene::goNext, this)),NULL));
            }

//            colorThemes->runAction(Sequence::createWithTwoActions(Sequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CallFunc::create(CC_CALLBACK_0(SelectColorAniScene::goNext, this))));
        }
    }
    
    
    
    
    return true;
}

void SelectColorAniScene::onTouchMoved(Touch *touch, Event *event){
    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
}

void SelectColorAniScene::onTouchEnded(Touch *touch, Event *event){
    Vec2 point = touch->getLocation();
    Vec2 lastPoint = touch->getPreviousLocation();
    

}


void SelectColorAniScene::aniAction(){
    Sprite* board = (Sprite*)this->getChildByTag(kColorBoardTag+selectAniIndex);
    if (board!=NULL) {
        Sprite* colorThemes = (Sprite*)board->getChildByTag(kColorAniTag+selectAniIndex);
        if(colorThemes!=NULL){
            SimpleAudioEngine::getInstance()->playEffect("mp3/hairSalon/takeBrush.mp3");
            Spawn* actionSpawn = Spawn::create(JumpBy::create(0.3, Vec2(0, 0), 5, 2),
                                                   CallFunc::create(CC_CALLBACK_0(SelectColorAniScene::aniJumpMp3, this)),
                                                   NULL);
            colorThemes ->runAction(Sequence::create(RotateTo::create(0.1, -25),
                                                       RotateTo::create(0.1, 0),
                                                       RotateTo::create(0.1, 25),
                                                       RotateTo::create(0.1, 0),
                                                       actionSpawn,
                                                       NULL));
        }
        
    }
}


void SelectColorAniScene::aniJumpMp3(){
    SimpleAudioEngine::getInstance()->playEffect("mp3/changing/buttonJump.mp3");
}
