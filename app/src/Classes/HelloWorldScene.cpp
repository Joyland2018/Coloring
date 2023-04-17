//#include <platform/android/jni/JniHelper.h>
//#include <CocosDenshion/ios/SimpleAudioEngine_objc.h>
#include "HelloWorldScene.h"
//#include "HospitalScene.h"
//#include "SecondScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "LogoScene.h"
#include "GameManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#endif
using namespace CocosDenshion;
using namespace cocos2d::extension;

USING_NS_CC;

enum {
    kBackLayerTag = 499,
    kLockBackTag = 599,
    kLockMenuTag = 699,
    kDownloadLayerTag = 750,
    kMoreGameTag = 999,
    kFlagTag = 399,
    ksTitle = 299,
};

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::keyBackClicked() {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)         //判断当前是否为Andriod平台
        JniMethodInfo minfo;                                //定义
        bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                     "com/jptang/dino/DinoHospital",   //类的路径
                                                     "rtnActivity",                    //方法名
                                                     "()Ljava/lang/Object;");          //括号里的是参数，后面的是返回
        jobject jobj;
        if (isHave){
            jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            CCLog("jobj--");
        }
        isHave = JniHelper::getMethodInfo(minfo,
                                          "com/jptang/dino/Drdino",                     //类的路径
                                          "exitGame1",                                 //方法名
                                          "()V");                                      //括号里的是参数，后面的是返回值
        if (isHave) {
            CCLog("isHave--");
            minfo.env->CallVoidMethod(jobj, minfo.methodID);
            CCLog("isHave");
        }
        CCLog("jni-java函数执行完毕");
#endif
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!CCLayer::init()){
        return false;
    }
    winsize = CCDirector::sharedDirector()->getVisibleSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    this->setKeypadEnabled(true);
    //背景
    CCSprite* bg = CCSprite::create("DinoColor/background/game_bg.png");
    bg->setPosition(ccp(winsize.width/2+poszero.x,winsize.height/2));
    this->addChild(bg);

    if (GameManager::sharedManager()->isIphoneX()){
        bg->setScale(1.3);
    }

    //play button
    CCSprite* tmp = CCSprite::create("DinoColor/background/beginButton.png");
    CCSize size = tmp->getContentSize();
    CCRect insetRect = CCRectMake(0,0,size.width-4, size.height-4);
    CCScale9Sprite* sprite = CCScale9Sprite::create("DinoColor/background/beginButton.png", insetRect);
    CCControlButton* playbut = CCControlButton::create(sprite);
    playbut->setPosition(ccp(winsize.width-130+poszero.x, 100));
    playbut->setPreferredSize(CCSize(137,139));
    this->addChild(playbut);
    playbut->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.4, 1.1),CCDelayTime::create(0.1),CCScaleTo::create(0.4, .9),NULL)));
    playbut->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::menuCloseCallback), CCControlEventTouchUpInside);

    //标题
    CCSprite* titleSprite;
    ccLanguageType la = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (la){
        case kLanguageFrench:
            titleSprite = CCSprite::create("DinoColor/background/gameName_fr.png");
            break;
        case kLanguageGerman:
            titleSprite = CCSprite::create("DinoColor/background/gameName_de.png");
            break;
        case kLanguageSpanish:
            titleSprite = CCSprite::create("DinoColor/background/gameName_es.png");
            break;
        default:
            titleSprite = CCSprite::create("DinoColor/background/gameName_en.png");
            break;
    }
    titleSprite->setPosition(ccp(winsize.width/2+poszero.x, winsize.height/3*2+30));
    this->addChild(titleSprite);

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("dinohospital/mp3/Begin_sound.mp3", true);
    CCUserDefault::sharedUserDefault()->setBoolForKey("blackGround", true);
    return true;
}





void HelloWorld::clearLock(){
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    blacklayer->removeFromParentAndCleanup(true);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//       CCTransitionCrossFade *trans = CCTransitionCrossFade::create(0.5, HospitalScene::scene());   //场景切换效果
//       CCDirector::sharedDirector()->replaceScene(trans);                                           //场景切换
}

void HelloWorld::onEnter() {
    CCLayer::onEnter();
}

void HelloWorld::onExit() {
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCLayer::onExit();
}
