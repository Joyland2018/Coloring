#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
// #include "HospitalScene.h"
#include "GameManager.h"
#include "LogoScene.h"
#include "platform/CCFileUtils.h"
//#include "IceShopScene.h"
//#include "SelectSalonAnim.hpp"

#include "SelectAnimalScene.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{
    
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

void Java_org_cocos2dx_lib_Cocos2dxActivity_openGame(JNIEnv* env, jobject thiz)
{
	if (!GameManager::getOpenGameTag())
    {
    // CCFileUtils::sharedFileUtils()->setOBBPath();
    // ccGLInvalidateStateCache();
        // CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
    CCDirector* pDirector = CCDirector::sharedDirector();
    // CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    // pDirector->setOpenGLView(pEGLView);
    
    // CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionNoBorder);
    GameManager::sharedManager()->initGameSystem();

    // CCScene *pScene = LogoScene::scene();

    // CCTransitionFade *action = CCTransitionFade::create(0.5, TestScene::scene(), ccWHITE);


}
    // CCLOG("width ============> %f,height ==============> %f",CCEGLView::sharedOpenGLView()->getVisibleSize().width,CCEGLView::sharedOpenGLView()->getVisibleSize().height);
    // AppDelegate *pAppDelegate = new AppDelegate();
    //     CCApplication::sharedApplication()->run();
}

void Java_color_games_kids_free_JoyPreschool_getIAPInfo(JNIEnv*  env, jobject thiz,jboolean _isUnlock)
{
//	CCLOG("getIAPInfo");
//	unsigned char b = _isUnlock;
//	 if (b) {
//		//  CCLOG("<=========Unlock is true========>");
//		CCUserDefault::sharedUserDefault()->setBoolForKey("UnlockAll", true);
//	 } else {
//		 CCLOG("<=========Unlock is false========>");
//		CCUserDefault::sharedUserDefault()->setBoolForKey("UnlockAll", false);
//	 }
}

void Java_color_games_kids_free_JoyPreschool_onIAPLifetimeCallback(JNIEnv* env, jobject thiz, jboolean _isUnlock){
    if (_isUnlock == true){

        CCUserDefault::sharedUserDefault()->setBoolForKey("purchased", true);
//        GameManager::sharedManager()->showBanner(false);
    } else{

        CCUserDefault::sharedUserDefault()->setBoolForKey("purchased", false);
    }
}

void Java_color_games_kids_free_JoyPreschool_onIAPChangeScene(JNIEnv* env, jobject thiz){
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ShiningScene::sceneWithId(0), ccWHITE));
//    if(!GameManager::sharedManager()->ShowGuide){
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectAnimalScene::scene(), ccWHITE));
//    }

}

void Java_color_games_kids_free_JoyPreschool_onIAPCallback(JNIEnv*  env, jobject thiz,jint select)
{
//	CCLOG("in callback");
//	CCUserDefault::sharedUserDefault()->setBoolForKey("UnlockAll", true);
//    //call your cpp code
////	CCNotificationCenter::sharedNotificationCenter()->postNotification("buylayer.remove");
//
//	CCLOG("<========select %d=======>",select);
//	switch (select) {
//	            case 0:
//	            {
//	            	CCNotificationCenter::sharedNotificationCenter()->postNotification("buypage.getall");
//	            	CCLOG("<==========post notification========>");
//	            }
////	                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, ShiningScene::sceneWithId(0), ccWHITE));
//	                break;
//	            case 1:
////	                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScreenScene::sceneWithId(kJigsawPuzzleTag), ccWHITE));
//	                break;
//
//	            case 10:
//	                // CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HospitalScene::scene(), ccWHITE));
//	                break;
//
//	            default:
//	                break;
//	  }
}

void Java_color_games_kids_free_JoyPreschool_onRewardAdsCallBack(JNIEnv* env, jobject thiz){
//	GameManager::sharedManager()->changeToGameScene();
}
}
