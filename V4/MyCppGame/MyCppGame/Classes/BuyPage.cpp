//
//  BuyPage.cpp
//  JoyPreschool
//
//  Created by LiXiaofei on 2018/2/7.
//

#include "BuyPage.h"
#include "DinoColor/ColorManager.hpp"

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
    if (!Layer::init()) {
        return false;
    }

    pageIndex = tag;

    isTouchBuy = false;
    isTouchTerms = false;

    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 center = GameManager::sharedManager()->getCenter();
    Vec2 rightBottom = GameManager::sharedManager()->getRightBottomPos();

//    NotificationCenter::getInstance()->removeObserver(this, kRemoveSelf);

    Sprite* background = Sprite::create("iap/iapPage1_Bg.png");
    background->setPosition(center);
    background->setTag(kBgTag);
    this->addChild(background);

    Sprite* cancel = Sprite::create("iap/iapPageClose.png");
    //    String* target = String::createWithFormat("%s",FileUtils::getInstance()->getResourceDirectory());
    //    if (target->isEqual(String::create("hd/"))) {
    //    }else if (target->isEqual(String::create("ip/"))) {
    //        cancel->setPosition(Vec2(winSize.width*3/4+5, winSize.height*20/21));
    //    }
    MenuItemSprite* cancelBt = MenuItemSprite::create(cancel, cancel, CC_CALLBACK_1(BuyPage::cancelBuy, this));
    Menu* menu = Menu::create(cancelBt,NULL);
    menu->setPosition(Vec2(background->getPosition().x+background->getContentSize().width/2-10,background->getPosition().y+background->getContentSize().height/2-10));
    menu->setScale(1.5);
    menu->setTag(kCancelTag);
    background->addChild(menu,20);

    this->loadIAPStore(tag);
    dogIndex = tag;

    this->setLocalZOrder(-130);
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(BuyPage::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(BuyPage::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(BuyPage::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

//    GameManager::sharedManager()->clickAdLockCount++;

    return true;
}

void BuyPage::setInitPageIndex(int _index){
//    _curPageIndex = _index;
}

void BuyPage::setPageIndex(int _pageIndex){
//    UserDefault::getInstance()->setIntegerForKey("_curPageIndex", _pageIndex);
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

void BuyPage::loadIAPStore(int tag){

    Sprite* background = (Sprite*)this->getChildByTag(kBgTag);

    if (background != NULL) {
//        const char* fileName = String::createWithFormat("iap/iapPage%d_Btn.png",1)->getCString();
//        MenuItemImage* iapBtn = MenuItemImage::create(fileName,fileName,CC_CALLBACK_1(BuyPage::buyClick, this));
////        MenuItemImage* watchAdsBtn = MenuItemImage::create("iap/iapPageWatch.png","iap/iapPageWatch.png",CC_CALLBACK_1(BuyPage::watchAdsClick, this));
//
//        iapBtn->setPosition(Vec2(background->getContentSize().width/2,background->getContentSize().height/4));
////        watchAdsBtn->setPosition(Vec2(447,91));
//        Menu* btnMenu = Menu::create(iapBtn,NULL);
//        btnMenu->setPosition(Vec2(0,-20));
//        background->addChild(btnMenu);

        const char* btnPathStr = "iap/iapPageBuy_1.png";
        auto item1= MenuItemImage::create(btnPathStr, btnPathStr, CC_CALLBACK_1(BuyPage::buyClick, this));
        auto menu = Menu::create(item1, NULL);

        menu->setPosition(Vec2(background->getContentSize().width / 2, 91));
        background->addChild(menu);

        Sprite* unlock = Sprite::create("iap/iapPage_NoAdsTitle.png");
        unlock->setPosition(Vec2(background->getContentSize().width/2,background->getContentSize().height/2));
        background->addChild(unlock);

        Sprite* logo = Sprite::create("iap/iapPageLogo.png");
        logo->setPosition(Vec2(background->getContentSize().width/2,background->getContentSize().height/1.3));
        background->addChild(logo);

    }
}

void BuyPage::initPrompt(cocos2d::Ref *_parent){
    Sprite* background = (Sprite*)this->getChildByTag(kBgTag);
    Menu* buyMenu = (Menu*)_parent;
    if (background != NULL) {
        Sprite* tipHand = Sprite::createWithSpriteFrameName("handclick_1.png");
        tipHand->setPosition(Vec2(buyMenu->getPosition().x, buyMenu->getPosition().y-80));
        tipHand->setScale(0.5);
        background->addChild(tipHand);

        MoveBy* handMove = MoveBy::create(0.8, Vec2(0, 30));
        MoveBy* reMove = (MoveBy*)handMove->reverse();

        Sequence* handSeq = Sequence::create(handMove,reMove,NULL);

        RepeatForever* repeat = RepeatForever::create(handSeq);

        tipHand->runAction(repeat);
    }
}

void BuyPage::buyClick(cocos2d::Ref *pSender){
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    ColorManager::shared()->buyState=false;
    GameManager::sharedManager()->goToBuyIAP(0);
}

void BuyPage::watchAdsClick(Ref *pSender) {
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

void BuyPage::cancelBuy(Ref* pSender){
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

void BuyPage::termsLinkClick(cocos2d::Ref *pSender){
    Layer *blacklayer = (Layer*)this->getChildByTag(kBackLayerTag);

}

void BuyPage::selectProductID(int tag,bool isRestore){

}

void BuyPage::onTouchesBegan(const std::vector<Touch*>& touches, Event* event){
    Touch* pTouch = touches[0];

    Vec2 location = Director::getInstance()->convertToGL(pTouch->getLocationInView());
    Layer *blacklayer = (Layer*)this->getChildByTag(kBackLayerTag);
    CCLOG("=================touched=================");
    if (blacklayer == NULL) {

    }
}

void BuyPage::onTouchesMoved(const std::vector<Touch*>& touches, Event* event){

}

void BuyPage::onTouchesEnded(const std::vector<Touch*>& touches, Event* event){

}

BuyPage::BuyPage(){

}

BuyPage::~BuyPage(){
//    NotificationCenter::getInstance()->removeObserver(this, kRemoveSelf);
//    NotificationCenter::getInstance()->removeObserver(this, kGetAll);
//    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
