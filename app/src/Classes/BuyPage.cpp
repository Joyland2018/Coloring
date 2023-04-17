//
//  BuyPage.cpp
//  JoyPreschool
//
//  Created by LiXiaofei on 2018/2/7.
//

#include <ColorManager.hpp>
#include "BuyPage.h"

enum{
    kBgTag = 60,
    kCancelTag = 61,
    kIAPBuyTag = 1000,
    kIAPRestoreTag = 2000,
    kTermsTag = 2100,
    kAllDogTag = 70,
    kSetTag = 71,
    kClothesTag = 72,
    kToyTag = 73,
#ifdef NEW_VERSION

    kEverythingTag = 74,
#else

    kAccessaryTag = 74,
    kEverythingTag = 75,
#endif
    kScrollLayerTag = 76,
    kScrollViewTag = 77,
    kBackgroundTag = 78,
    kDogStoreTag = 79,
    kBigStoreTag = 80,
    kParentLockTag = 299,
    kParentMenuTag = 399,
    kBackLayerTag = 499,
    kLockBackTag = 599,
    kLockMenuTag = 699,
};

BuyPage* BuyPage::nodeWithID(int tag){
    BuyPage* layer = new BuyPage();
    if (layer->initWithID(tag)) {
        layer->autorelease();

        return layer;
    }else {
        return NULL;
    }
}

bool BuyPage::initWithID(int tag){
    if (!CCLayer::init()) {
        return false;
    }

    pageIndex = tag;

    isTouchBuy = false;
    isTouchTerms = false;

    CCSize winSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint rightBottom = GameManager::sharedManager()->getRightBottomPos();

//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kRemoveSelf);

    CCSprite* background = CCSprite::create("iap/iapPage1_Bg.png");
    background->setPosition(center);
    background->setTag(kBgTag);
    this->addChild(background);

    CCSprite* cancel = CCSprite::create("iap/iapPageClose.png");
    //    CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
    //    if (target->isEqual(CCString::create("hd/"))) {
    //    }else if (target->isEqual(CCString::create("ip/"))) {
    //        cancel->setPosition(ccp(winSize.width*3/4+5, winSize.height*20/21));
    //    }
    CCMenuItemSprite* cancelBt = CCMenuItemSprite::create(cancel, cancel, this, menu_selector(BuyPage::cancelBuy));
    CCMenu* menu = CCMenu::create(cancelBt,NULL);
    menu->setPosition(ccp(background->getPosition().x+background->getContentSize().width/2-10,background->getPosition().y+background->getContentSize().height/2-10));
    menu->setScale(1.5);
    menu->setTag(kCancelTag);
    background->addChild(menu,20);

    this->loadIAPStore(tag);
    dogIndex = tag;

    this->setTouchPriority(-130);
    this->setTouchEnabled(true);

//    GameManager::sharedManager()->clickAdLockCount++;

    return true;
}

void BuyPage::setInitPageIndex(int _index){
//    _curPageIndex = _index;
}

void BuyPage::setPageIndex(int _pageIndex){
//    CCUserDefault::sharedUserDefault()->setIntegerForKey("_curPageIndex", _pageIndex);
//    CCLOG("<=================PAGEINDEX = %d=====================>",_curPageIndex);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo minfo;
//    //bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/landudu/eyechart/EyeChartForGod","rtnActivity","()Lcom/landudu/eyechart/EyeChartForGod;");
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/jpt/joyland/JoyPreschool","rtnActivity","()Lcom/jpt/joyland/JoyPreschool;");
//
//    if(!isHave)
//    {
//        CCLOG("jni:不能获取单例");
//    }
//    else
//    {
//        CCLOG("jni:可以获取单例");
//        //        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  //获取单例对象
//        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  //获取单例对象
//
//        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"com/jpt/joyland/JoyPreschool","setBuyIndex", "(I)V");
//        if (!isHaveNoStaticMethod)
//        {
//            CCLOG("jni:alertDiaShowt方法不存在");
//        }
//
//        else
//        {
//            CCLOG("jni:alertDiaShow方法存在");
//            //            minfo.env->CallVoidMethod(minfo.classID, minfo.methodID, productIndex);
//            minfo.env->CallVoidMethod(jobj, minfo.methodID,_pageIndex);
////            if (minfo.env->ExceptionOccurred()) {
////                minfo.env->ExceptionDescribe();
////                minfo.env->ExceptionClear();
////                return;
////            }
////            minfo.env->DeleteLocalRef(minfo.classID);
//        }
//    }
//    CCLOG("jni-java函数执行完毕");
//#endif
}

void BuyPage::registerWithTouchDispatcher()
{
    // priority比-128小就可以了
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, -150);
}

void BuyPage::loadIAPStore(int tag){

    CCSprite* background = (CCSprite*)this->getChildByTag(kBgTag);

    if (background != NULL) {
//        const char* fileName = CCString::createWithFormat("iap/iapPage%d_Btn.png",1)->getCString();
//        CCMenuItemImage* iapBtn = CCMenuItemImage::create(fileName,fileName,this,menu_selector(BuyPage::buyClick));
////        CCMenuItemImage* watchAdsBtn = CCMenuItemImage::create("iap/iapPageWatch.png","iap/iapPageWatch.png",this,menu_selector(BuyPage::watchAdsClick));
//
//        iapBtn->setPosition(ccp(background->getContentSize().width/2,background->getContentSize().height/4));
////        watchAdsBtn->setPosition(ccp(447,91));
//        CCMenu* btnMenu = CCMenu::create(iapBtn,NULL);
//        btnMenu->setPosition(ccp(0,-20));
//        background->addChild(btnMenu);

        const char* btnPathStr = "iap/iapPageBuy_1.png";
        auto item1= CCMenuItemImage::create(btnPathStr, btnPathStr, this,menu_selector(BuyPage::buyClick));
        auto menu = CCMenu::create(item1, NULL);

        menu->setPosition(ccp(background->getContentSize().width / 2, 91));
        background->addChild(menu);

        CCSprite* unlock = CCSprite::create("iap/iapPage_NoAdsTitle.png");
        unlock->setPosition(ccp(background->getContentSize().width/2,background->getContentSize().height/2));
        background->addChild(unlock);

        CCSprite* logo = CCSprite::create("iap/iapPageLogo.png");
        logo->setPosition(ccp(background->getContentSize().width/2,background->getContentSize().height/1.3));
        background->addChild(logo);

    }
}

void BuyPage::initPrompt(cocos2d::CCObject *_parent){
    CCSprite* background = (CCSprite*)this->getChildByTag(kBgTag);
    CCMenu* buyMenu = (CCMenu*)_parent;
    if (background != NULL) {
        CCSprite* tipHand = CCSprite::createWithSpriteFrameName("handclick_1.png");
        tipHand->setPosition(ccp(buyMenu->getPosition().x, buyMenu->getPosition().y-80));
        tipHand->setScale(0.5);
        background->addChild(tipHand);

        CCMoveBy* handMove = CCMoveBy::create(0.8, ccp(0, 30));
        CCMoveBy* reMove = (CCMoveBy*)handMove->reverse();

        CCSequence* handSeq = CCSequence::create(handMove,reMove,NULL);

        CCRepeatForever* repeat = CCRepeatForever::create(handSeq);

        tipHand->runAction(repeat);
    }
}

void BuyPage::buyClick(cocos2d::CCObject *pSender){
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    ColorManager::shared()->buyState=false;
    GameManager::sharedManager()->goToBuyIAP(0);
}

void BuyPage::watchAdsClick(CCObject *pSender) {
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    GameManager::sharedManager()->showReward();
}

void BuyPage::setAllVersion(){

    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);

    //        [[BuyControl sharedManager] removeNotifi];

//    GameManager::sharedManager()->setLastTime();
}

void BuyPage::cancelBuy(CCObject* pSender){
    CCLOG("cancel!!");
    //    if ([BuyControl sharedManager].isGaming == false) {
    //        SelectScene* curParent = (SelectScene*)this->getParent();
    //        curParent->resetTouchScroll();
    //    }
    ColorManager::shared()->buyState=false;

    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);

//        [[BuyControl sharedManager] removeNotifi];

//        GameManager::sharedManager()->setLastTime();
//    }
}

void BuyPage::termsLinkClick(cocos2d::CCObject *pSender){
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);

}

void BuyPage::selectProductID(int tag,bool isRestore){

}

void BuyPage::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();

    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    CCLOG("=================touched=================");
    if (blacklayer == NULL) {

    }
}

void BuyPage::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){

}

void BuyPage::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){

}

BuyPage::BuyPage(){

}

BuyPage::~BuyPage(){
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kRemoveSelf);
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kGetAll);
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}
