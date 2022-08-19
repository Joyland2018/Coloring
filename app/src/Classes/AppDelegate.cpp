#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
//#include "DeviceManager.h"
#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "ColorManager.h"
//#include "ColorManager.h"
//#include "BarberShop/SalonManager.hpp"
USING_NS_CC;
using namespace CocosDenshion;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

//    CCUserDefault::sharedUserDefault()->setBoolForKey("UnlockAll", true);    //打开此代码所有游戏都可以玩
    //CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionNoBorder);
    float with = CCEGLView::sharedOpenGLView()->getVisibleSize().width ;
    float  hight =CCEGLView::sharedOpenGLView()->getVisibleSize().height ;
    if ((with/hight) >=2.0) {
        GameManager::sharedManager()->isiphoneX = true;
    }else if ((with/hight) >= 1.6 && (with/hight) < 1.76) {
        GameManager::sharedManager()->isFullAndroidPad = true;
    }
    
    if ((with/hight) < 1.4) {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionNoBorder);
    }else{
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionFixedHeight);
    }
	
 	if (GameManager::sharedManager()->lastTime == 0) {
        GameManager::sharedManager()->setLastTime();
    }

    if (GameManager::sharedManager()->reviewlastTime == 0) {
        GameManager::sharedManager()->setReviewLastTime();
    }

//    if (CCUserDefault::sharedUserDefault()->getBoolForKey("ICESHOP_SCORE_Guide",true)){
//        GameManager::sharedManager()->ShowGuide = true;
//    }else{
//        GameManager::sharedManager()->ShowGuide = false;
//    }
//    cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("ICESHOP_SCORE_Guide",true);
//    GameManager::sharedManager()->initGameSystem();
//    SalonManager::shared()->initSalonManager();
    ColorManager::shared()->initColorManager();
    GameManager::sharedManager()->requestInitAds();
    GameManager::sharedManager()->isShowenReview = false;
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("isBegin", true);

    // create a scene. it's an autorelease object
    CCScene *pScene = LogoScene::scene();
    
//    DeviceManager::sharedManager()->shareMixpanel();

    // run
    pDirector->runWithScene(pScene);
    
//    DeviceManager::sharedManager()->getIAPInfo();

    return true;
}

void AppDelegate::beginGame() {

}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();		//回到后台背景音乐去掉
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
