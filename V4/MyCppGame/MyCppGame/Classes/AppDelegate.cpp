#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
//#include "DeviceManager.h"
#include "LogoScene.h"
#include "AudioEngine.h"
#include "DinoColor/ColorManager.hpp"
//#include "platform/GLViewImpl.h"
//#include "ColorManager.h"
//#include "BarberShop/SalonManager.hpp"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* pDirector = Director::getInstance();
    GLView* pEGLView = Director::getInstance()->getOpenGLView();
    
    if(!pEGLView) {
        pEGLView = GLViewImpl::create("My Cpp Game");
        pDirector->setOpenGLView(pEGLView);
    }

//    UserDefault::getInstance()->setBoolForKey("UnlockAll", true);    //打开此代码所有游戏都可以玩
    //Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
    float with = Director::getInstance()->getOpenGLView()->getFrameSize().width ;
    float  hight = Director::getInstance()->getOpenGLView()->getFrameSize().height ;
    if ((with/hight) >=2.0) {
        GameManager::sharedManager()->isiphoneX = true;
    }else if ((with/hight) >= 1.6 && (with/hight) < 1.76) {
        GameManager::sharedManager()->isFullAndroidPad = true;
    }
    
    if ((with/hight) < 1.4) {
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
    }else{
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
    }
	
 	if (GameManager::sharedManager()->lastTime == 0) {
        GameManager::sharedManager()->setLastTime();
    }

    if (GameManager::sharedManager()->reviewlastTime == 0) {
        GameManager::sharedManager()->setReviewLastTime();
    }

//    if (UserDefault::getInstance()->getBoolForKey("ICESHOP_SCORE_Guide",true)){
//        GameManager::sharedManager()->ShowGuide = true;
//    }else{
//        GameManager::sharedManager()->ShowGuide = false;
//    }
//    cocos2d::UserDefault::getInstance()->setBoolForKey("ICESHOP_SCORE_Guide",true);
//    GameManager::sharedManager()->initGameSystem();
//    SalonManager::shared()->initSalonManager();
    ColorManager::shared()->initColorManager();
    GameManager::sharedManager()->requestInitAds();
    GameManager::sharedManager()->isShowenReview = false;
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    UserDefault::getInstance()->setBoolForKey("isBegin", true);

    // create a scene. it's an autorelease object
    Scene *pScene = LogoScene::scene();
    
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
    Director::getInstance()->stopAnimation();

    // if you use AudioEngine, it must be pause
    AudioEngine::pauseAll();		//回到后台背景音乐去掉
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use AudioEngine, it must resume here
    AudioEngine::resumeAll();
}
