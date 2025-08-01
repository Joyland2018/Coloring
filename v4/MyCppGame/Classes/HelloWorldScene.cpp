//#include <platform/android/jni/JniHelper.h>
//#include <CocosDenshion/ios/SimpleAudioEngine_objc.h>
#include "HelloWorldScene.h"
//#include "HospitalScene.h"
//#include "SecondScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "LogoScene.h"
#include "GameManager.h"
#include "base/CCEventListenerKeyboard.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#endif

USING_NS_CC;
using namespace ui;

enum {
    kBackLayerTag = 499,
    kLockBackTag = 599,
    kLockMenuTag = 699,
    kDownloadLayerTag = 750,
    kMoreGameTag = 999,
    kFlagTag = 399,
    ksTitle = 299,
};

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    // 留空 - 按键按下事件处理
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)         //判断当前是否为Andriod平台
        JniMethodInfo minfo;                                //定义
        bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                     "com/jptang/dino/DinoHospital",   //类的路径
                                                     "rtnActivity",                    //方法名
                                                     "()Ljava/lang/Object;");          //括号里的是参数，后面的是返回
        jobject jobj;
        if (isHave){
            jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            CCLOG("jobj--");
        }
        isHave = JniHelper::getMethodInfo(minfo,
                                          "com/jptang/dino/Drdino",                     //类的路径
                                          "exitGame1",                                 //方法名
                                          "()V");                                      //括号里的是参数，后面的是返回值
        if (isHave) {
            CCLOG("isHave--");
            minfo.env->CallVoidMethod(jobj, minfo.methodID);
            CCLOG("isHave");
        }
        CCLOG("jni-java函数执行完毕");
#endif
    }
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init()){
        return false;
    }
    winsize = Director::getInstance()->getVisibleSize();
    poszero = Director::getInstance()->getVisibleOrigin();
    
    // Setup keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    //背景
    Sprite* bg = Sprite::create("DinoColor/background/game_bg.png");
    bg->setPosition(Vec2(winsize.width/2+poszero.x,winsize.height/2));
    this->addChild(bg);

    if (GameManager::sharedManager()->isIphoneX()){
        bg->setScale(1.3);
    }

    //play button
    auto playbut = ui::Button::create("DinoColor/background/beginButton.png");
    playbut->setPosition(Vec2(winsize.width-130+poszero.x, 100));
    playbut->setScale9Enabled(true);
    playbut->setContentSize(Size(137,139));
    this->addChild(playbut);
    
    // Animation for button
    auto scaleUp = ScaleTo::create(0.4f, 1.1f);
    auto delay = DelayTime::create(0.1f);
    auto scaleDown = ScaleTo::create(0.4f, 0.9f);
    auto sequence = Sequence::create(scaleUp, delay, scaleDown, nullptr);
    auto repeat = RepeatForever::create(sequence);
    playbut->runAction(repeat);
    
    playbut->addClickEventListener([this](Ref* sender){
        this->menuCloseCallback(sender);
    });

    //标题
    Sprite* titleSprite;
    LanguageType la = Application::getInstance()->getCurrentLanguage();
    switch (la){
        case LanguageType::FRENCH:
            titleSprite = Sprite::create("DinoColor/background/gameName_fr.png");
            break;
        case LanguageType::GERMAN:
            titleSprite = Sprite::create("DinoColor/background/gameName_de.png");
            break;
        case LanguageType::SPANISH:
            titleSprite = Sprite::create("DinoColor/background/gameName_es.png");
            break;
        default:
            titleSprite = Sprite::create("DinoColor/background/gameName_en.png");
            break;
    }
    titleSprite->setPosition(Vec2(winsize.width/2+poszero.x, winsize.height/3*2+30));
    this->addChild(titleSprite);

    AudioEngine::play2d("dinohospital/mp3/Begin_sound.mp3", true);
    UserDefault::getInstance()->setBoolForKey("blackGround", true);
    return true;
}

void HelloWorld::clearLock(){
    Layer *blacklayer = (Layer*)this->getChildByTag(kBackLayerTag);
    blacklayer->removeFromParentAndCleanup(true);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
//       auto trans = TransitionCrossFade::create(0.5, HospitalScene::scene());   //场景切换效果
//       Director::getInstance()->replaceScene(trans);                                           //场景切换
}

void HelloWorld::onEnter() {
    Layer::onEnter();
}

void HelloWorld::onExit() {
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Layer::onExit();
}
