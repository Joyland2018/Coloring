//
//  SelectAnimalScene.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/30.
//

#include "SelectAnimalScene.h"
#include "cocos-ext.h"
#include "GameManager.h"
#include "ColorManager.h"
#include "ColorCanvasView.h"
//#include "HospitalScene.h"
#include "BuyPage.h"
//#include "PizzaManager.h"

#ifdef NEWDINO
#include "ShiningScene.h"
#endif
//#if defined (NEWMAIN)
//#include "DinoTownScene.h"
//#endif

using namespace cocos2d::extension ;

enum{
    kBuyLayerTag = 899,
    kLockTag = 799,
    kBackTag = 99,
    kBackLayerTag = 499,
    kLockBackTag = 599,
    kLockMenuTag = 699,
};

CCScene* SelectAnimalScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SelectAnimalScene* layer = SelectAnimalScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    //ColorManager::shared()->m_pCanvasLayer = layer ;
    // return the scene
    return scene;
}

bool SelectAnimalScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
     s = CCDirector::sharedDirector()->getVisibleSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite* bg = CCSprite::create("DinoColor/roles-bg.png");
    bg->setPosition(winCenter);
    this->addChild(bg);
    
    if (GameManager::sharedManager()->isIphoneX()) {
        bg->setScale(1.3);
    }
   
    
//    CCMenuItemImage* closeBtn = CCMenuItemImage::create("universal/back.png", "universal/back.png", this, menu_selector(SelectAnimalScene::backClick));
//           //closeBtn->setScale(1.2);
//       CCMenu* closeMenu = CCMenu::create();
//       closeMenu->setPosition(ccp(poszero.x+50,s.height-50));
//       closeMenu->addChild(closeBtn);
//    this->addChild(closeMenu,999) ;
    this->initAnimals();
    this->setTouchEnabled(true);
//    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")) {
//        GameManager::sharedManager()->showBanner(true);
//    }
    return true ;
}

void SelectAnimalScene::addLock(CCObject *_parent,int _index) {

    const char* lockName = "lock";
    
    CCSprite* parentSpr = (CCSprite*)_parent;
    
    CCSprite* locked = CCSprite::create(CCString::createWithFormat("background/%s.png",lockName)->getCString()) ;   //那么设置一个锁的精灵
//    locked->setScale(1.0) ;
    locked->setPosition(ccp(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/2-locked->getContentSize().height/3));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked) ;
}

void SelectAnimalScene::initAnimals()
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background/sinkBg.mp3", true);
    //滑动屏幕
//    containerLayer=CCLayer::create();
//    scrollView = extension::CCScrollView::create();
//    scrollView->setPosition(CCPointZero);
//    scrollView->setViewSize(CCSizeMake(1136, 640));             //设置可视区域的大小
//    containerLayer->setContentSize(CCSizeMake(1136, 3000));      //设置真实区域的大小
////    containerLayer->setPosition(ccp(0, -3000));                  //初始位置
//    scrollView->setContainer(containerLayer);
////    CCLog("---%d---",ColorManager::shared()->yDis);
//    scrollView->setContentOffset(ccp(0,ColorManager::shared()->yDis));
//    scrollView->setTouchEnabled(true);
//    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
//    scrollView->setDelegate(this);                                 //开启代理
//    scrollView->setBounceable(true);
//    this->addChild(scrollView);
//    containerLayer->setTouchEnabled(true);
    
//    aniPosArr = CCPointArray::create(35);
    
    if (ColorManager::shared()->firstPlayColor) {
        for (int i=0; i<35; i++) {
            for (int j=0; j<2; j++) {
                if (j==0) {
                    if (i<32) {
                        ColorManager::shared()->aniPosArr[i][0]=260+200*(i%4);
                    }else if(i>=32){
                        ColorManager::shared()->aniPosArr[i][0]=360+200*(i%4);
                    }else if(i>35){
                        ColorManager::shared()->aniPosArr[i][0]=260+200*(i%4);
                    }
                }else if(j==1){
                    ColorManager::shared()->aniPosArr[i][1]=420 -280*(i/4);
                }

            }
        }
    }
    
    
    
    float fix_w = 0 ;
    if (GameManager::sharedManager()->isIphoneX()) {
        fix_w = 100;
    }else if(GameManager::sharedManager()->isAndroidPad()){
        fix_w = -50;
    }
    for (int i = 0; i <35; i++) {
          
        CCString* name = CCString::createWithFormat("DinoColor/dinoballon/dragon-%d.png",(i+1)) ;
        CCSprite* tmp2 = CCSprite::create(name->getCString());
//        CCSize size2 = tmp2->getContentSize();
//        CCRect insetRect2 = CCRectMake(2,2,size2.width-4, size2.height-4);
//        CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
//        CCControlButton *button = CCControlButton::create(sprite2) ;
//        button->setPreferredSize(size2) ;
//        button->setTag(i+1);
        
//        CCLog("containHeight ====> %d",ColorManager::shared()->aniPosArr[i][1]);
//        button->setPosition(ccp(aniPosArr[i][0], aniPosArr[i][1]));
        tmp2->setTag(i+1);
        if (i<32) {
            tmp2->setPosition(ccp(260+200*(i%4)+fix_w, ColorManager::shared()->aniPosArr[i][1])) ;
        }else if(i>=32) {
            tmp2->setPosition(ccp(360+200*(i%4)+fix_w, ColorManager::shared()->aniPosArr[i][1])) ;
        }

        this->addChild(tmp2, 3) ;
        
//        containerLayer->runAction(CCMoveTo::create(600.0, ccp(0, 640)));
//        containerLayer->runAction(CCSequence::create(CCMoveTo::create(600.0, ccp(0, 640)),
//                                                     CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)),
//                                                     NULL));
        
        if (i !=0 && i!=8 && i!=27 && i!=5 && i!=15 && i!=16 && i!=23 && i!=31 && i!=32 && (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased"))) {
            this->addLock(tmp2, i);
        }
        
        if ((i ==0 || i==8 || i==27 || i==5 || i==15 || i==16 || i== 23 || i== 31 || i==32) && (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased"))) {
            CCSprite* freeTag = CCSprite::create("background/free.png");
            freeTag->setPosition(ccp(tmp2->getContentSize().width-50,tmp2->getContentSize().height-20));
//            freeTag->setScale(1.5);
            tmp2->addChild(freeTag,9);
        }
        
//        button->addTargetWithActionForControlEvents(this, cccontrol_selector(SelectAnimalScene::selectAni), CCControlEventTouchUpInside) ;//button 优先级高于ccmove
       
//        bubbleShake(button);
    }
//    if (touchEnd) {
        scheduleUpdate();
//    }
    
}


void SelectAnimalScene::update(float date){
//    if(moveDisY==0){
    for (int i=1; i<36; i++) {
        CCSprite* aniButton = (CCSprite*)this->getChildByTag(i);
//        if (touchEnd) {
        aniButton->setPositionY(aniButton->getPosition().y+1);
        CCLog("containHeight ====> %f",aniButton->getPosition().y);
        if (aniButton->getPosition().y>700) {
            
                aniButton->setPositionY(-1820);
            
            
//            int index = 700-aniButton->getPosition().y;
//            if(moveDisY<=index){
//                aniButton->setPositionY(-1820);
//            }else if(moveDisY>index){
//                int index1 = moveDisY-index;
//                aniButton->setPositionY(-1820+index1);
//            }
        }
        ColorManager::shared()->aniPosArr[i-1][1]=aniButton->getPosition().y;
//        }
    }
//    }
}


void SelectAnimalScene::resetAniPos(){
    for (int i=1; i<36; i++) {
        CCSprite* aniButton = (CCSprite*)this->getChildByTag(i);
        CCLog("containHeight ====> %d",ColorManager::shared()->aniPosArr[i-1][1]);
        CCLog("containHeight ====> %f",aniButton->getPosition().y);
        if (aniButton->getPosition().y>700) {                              //向上滑动
//            aniButton->setPositionY(-1820+(moveDisY-(700-ColorManager::shared()->aniPosArr[i-1][1])));
            int index = aniButton->getPosition().y-700;
//            if(moveDisY==index){
//                aniButton->setPositionY(-1820);
//            }else
//            if(moveDisY>=index){
                int index1 = moveDisY+index;
                aniButton->setPositionY(-1820+index1);
//            }
        }else if(aniButton->getPosition().y<-1820){                         //向下滑动
            int index = -1820-aniButton->getPosition().y;
            int index1 = moveDisY-index;
//            aniButton->setPositionY(700+(moveDisY+(-1820+ColorManager::shared()->aniPosArr[i-1][1])));
            aniButton->setPositionY(700+index1);
        }else if(aniButton->getPosition().y>=-1820 && aniButton->getPosition().y<=700){
            aniButton->setPositionY(aniButton->getPosition().y+moveDisY);
        }
        
        
        ColorManager::shared()->aniPosArr[i-1][1]=aniButton->getPosition().y;
    }
}


//void SelectAnimalScene::moveAniPos(CCObject *pSender){
//
////    posIndex = i/4;
//    CCSprite* button = (CCSprite*)pSender;
//    int aniIndex1 = button->getTag()-1;
//
////    if (aniIndex1<32) {
////        button->setPosition(ccp(260+200*(aniIndex1%4), 420 -280*(aniIndex1/4))) ;
////    }else if(aniIndex1>=32) {
////        button->setPosition(ccp(360+200*(aniIndex1%4), 420 -280*(aniIndex1/4))) ;
////    }
////    posIndex = aniIndex1/4;
//    aniIndex = aniIndex1;
//    CCSequence* sequence=CCSequence::create(
//                                            CCMoveTo::create(5.0+(aniIndex/4)*2.8,ccp(260+200*(aniIndex1%4),700)),
//                                            CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)),
////                                            CCMoveTo::create(45,ccp(260+200*(aniIndex1%4),700)),
////                                            CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)),
//                                                             NULL);
////    CCSequence* sequences = CCSequence::create(CCMoveTo::create((700-button->getPosition().y)/56,ccp(260+200*(aniIndex1%4),700)),
////                                               CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)),
////                                               CCRepeatForever::create(sequence),
////                                               NULL);
////    button->runAction(CCSequence::create(CCMoveTo::create(5.0+(aniIndex/4)*2.8, ccp(button->getPosition().x, button->getPosition().y+((aniIndex/4)+1)*280)),
////                                         CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)),
////                                         NULL));
//    button->runAction(CCRepeatForever::create(sequence));
////    button->runAction(sequence);
//    CCLog("---%f---",button->getPosition().y);
////    if (button->getPosition().y == 700) {
////        button->setPosition(ccp(260+200*(aniIndex%4), 140));
////    }
//}

//void SelectAnimalScene::resetAniPos(CCObject *pSender){
//    CCSprite* button = (CCSprite*)pSender;
//    int aniIndex1 = button->getTag()-1;
//    aniIndex = 39;
//    button->setPositionY(ColorManager::shared()->aniPosArr[39][1]);
////    if (button->getPosition().y >= 700) {
////        button->setPosition(ccp(260+200*(aniIndex1%4), button->getPosition().y-abs(aniIndex1-10)*280));
////        aniIndex = abs(aniIndex1-10);
////    }
//    CCLog("---%f---",button->getPosition().y);
//}


void SelectAnimalScene::resetContainerPos(){
    int pos = -2360;
    containerLayer->setPosition(ccp(0, -2360));
}

//void SelectAnimalScene::resetAniPos(CCObject *pSender){
//    CCLayer *container = (CCLayer*)pSender;
//    if (container) {
////        container->setPosition(ccp(0, 3200));
//        CCLOG("---%f---",containerLayer->getPosition().y);
////        ColorManager::shared()->yDis=-2360;
////        containerLayer->runAction(CCMoveTo::create(0.01, ccp(0,-2360)));
////        ColorManager::shared()->yDis=-2360;
////        CCRepeatForever* repeat = CCRepeatForever::create(CCSequence::create(CCMoveTo::create(-(containerLayer->getPosition().y*0.01),ccp(0,180)),
////                                                                             CCMoveTo::create(0.000000001, ccp(0, -2900)),
////                                                                             CCMoveTo::create(-(containerLayer->getPosition().y*0.01),ccp(0,180)),
////                                                                             CCCallFuncN::create(this,callfuncN_selector(SelectAnimalScene::resetAniPos)),
////                                                                             NULL));
//        CCSequence* sequence = CCSequence::create(
//                                                  CCMoveTo::create(25,ccp(0,680)),
//                                                  CCMoveTo::create(0.000000001, ccp(0, -2360)),
//                                                  CCCallFunc::create(this, callfunc_selector(SelectAnimalScene::resetContainerPos)),
//                                                  CCMoveTo::create(25,ccp(0,680)),
//                                                  CCMoveTo::create(0.000000001, ccp(0, -2360)),
////                                                  CCCallFuncN::create(this,callfuncN_selector(SelectAnimalScene::resetAniPos)),
//                                                  NULL);
////        container->runAction(CCSequence::create(
//////                                                repeat,
//////                                                CCMoveTo::create(-(containerLayer->getPosition().y*0.01), ccp(0, 180)),
////                                                CCMoveTo::create(0.000000001, ccp(0, -2900)),
//////                                                CCDelayTime::create(0.5),
////                                                CCMoveTo::create(-(containerLayer->getPosition().y*0.01), ccp(0, 180)),
////                                                CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)),
////                                                NULL));
//        container->runAction(CCRepeatForever::create(sequence));
//    }
//}

void SelectAnimalScene::scrollViewDidScroll(extension::CCScrollView *view){
    CCLog("---%f---",containerLayer->getPosition().y);
    ColorManager::shared()->yDis = containerLayer->getPosition().y;
   
    return;
}

void SelectAnimalScene::scrollViewDidZoom(extension::CCScrollView *view){
    return;
}

void SelectAnimalScene::selectAdsOrIAP(int _pageIndex) {
//    if (GameManager::sharedManager()->clickAdLockCount < 2){
        CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
//            if (GameManager::sharedManager()->clickAdLockCount == 0){
//
//                buyLayer = (CCLayer*)BuyPage::nodeWithID(0);
//            } else{

            buyLayer = (CCLayer*)BuyPage::nodeWithID(_pageIndex);
//            }
            buyLayer->setTag(kBuyLayerTag);
            this->addChild(buyLayer, 100);

            CCSize _winSize = GameManager::sharedManager()->getViewVisibleSize();
            CCPoint center = GameManager::sharedManager()->getCenter();

            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), _winSize.width, _winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(ccp(center.x,center.y));
            buyLayer->addChild(blacklayer, -1);
        }
//    } else{
//
//        GameManager::sharedManager()->showAdAndGetReward();
//    }
}

void SelectAnimalScene::selectAni(CCObject * sender)
{
    CCNode* button = (CCNode*)sender;
    
    CCSprite* adLock = (CCSprite*)button->getChildByTag(kLockTag);
    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
    if (buyLayer == NULL) {
//        if (ColorManager::shared()->yDis==0) {
            if (adLock != NULL) {
                this->selectAdsOrIAP(2);
            } else {
                if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
                    GameManager::sharedManager()->showInterstitial();
                }
                int tag = button->getTag() ;
                ColorManager::shared()->m_AnimalTag = tag ;
                CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, ColorCanvasView::scene()));
            }
//        }
    }
    
    
}

void SelectAnimalScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    moveDisY=0;
    touchEnd=false;
    unscheduleUpdate();
}


void SelectAnimalScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCPoint preLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getPreviousLocationInView());//即时获取上次的触摸点
    beginPosY = preLocation.y;
    endPosY = location.y;
    moveDisY = endPosY-beginPosY;
    resetAniPos();
    if (!touchEnd) {
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(SelectAnimalScene::resetAniPos)),
                                           
                                           CCCallFunc::create(this, callfunc_selector(SelectAnimalScene::resetTouch)),
                                           NULL));
    }
    unscheduleUpdate();
}

void SelectAnimalScene::resetTouch(){
    touchEnd=true;
//    moveDisY=0;
}

void SelectAnimalScene::clickMp3(){
    SimpleAudioEngine::sharedEngine()->playEffect("background/buttonPop.mp3");
}

void SelectAnimalScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
//    if (moveDisY!=0) {
//        moveDisY=0;
//    }
    
    for (int i=1; i<36; i++) {
        CCSprite* aniPop = (CCSprite*)this->getChildByTag(i);
        if (aniPop && aniPop->boundingBox().containsPoint(location) && moveDisY==0) {
            aniPop->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.2),
                                                 CCDelayTime::create(0.2),
                                                 CCScaleTo::create(0.1, 1),
                                                 CCCallFunc::create(this, callfunc_selector(SelectAnimalScene::clickMp3)),
                                                 CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::selectAni)),
                                                 NULL));
        }
    }
    scheduleUpdate();
//    if (containerLayer->getPosition().y<=20) {
//        containerLayer->runAction(CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::resetAniPos)));
//    }
    
}

void SelectAnimalScene::backClick()
{
    
//#if defined (NEWMAIN)
//    CCTransitionCrossFade *trans = CCTransitionCrossFade::create(0.5, DinoTownScene::scene()) ;
//#else
//    CCTransitionCrossFade *trans = CCTransitionCrossFade::create(0.5, ShiningScene::sceneWithId(kCatDressTag+1)) ;
//#endif
//    CCDirector::sharedDirector()->replaceScene(trans) ;
}

void SelectAnimalScene::bubbleShake(cocos2d::CCObject *sender)
{
    float fix_w = 0 ;
    if (GameManager::sharedManager()->isIphoneX()) {
        fix_w = 100;
    }
    CCSprite* bubble = (CCSprite*)sender;
    int posIndex = bubble->getTag()-1;
//    if (posIndex<32) {
//        pos=ccp(260+200*(posIndex%4)+fix_w, 420 -280*(posIndex/4));
//    }else if(posIndex>=32) {
//        pos=ccp(360+200*(posIndex%4)+fix_w, 420 -280*(posIndex/4)) ;
//    }
////    CCPoint pos = ccp(260+200*(posIndex%4)+fix_w, 2760 -280*(posIndex/4));
//    bubble->runAction(CCSequence::create(CCMoveTo::create(5.0, ccp(bubble->getPosition().x, bubble->getPosition().y+300+(posIndex/4)*280)),
//                                         NULL));
    int random1 = arc4random()%2 > 0? 1:-1;
    int random2 = arc4random()%2 > 0? 1:-1;
    int offset = 2;
    
    CCPoint endPoint = CCPoint(bubble->getPosition().x + random1*(arc4random()%offset+1.0), bubble->getPosition().y + random1*(arc4random()%offset+1.0));
    CCMoveTo* move = CCMoveTo::create(0.2*(arc4random()%2+1.0), endPoint);
    bubble->runAction(CCSequence::createWithTwoActions(move, CCCallFuncN::create(this, callfuncN_selector(SelectAnimalScene::bubbleShake))));
}
