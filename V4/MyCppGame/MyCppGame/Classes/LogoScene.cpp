//
//  LogoScene.cpp
//  GameGarden
//
//  Created by LiXiaofei on 2017/2/23.
//
//

#include "LogoScene.h"
#include "GameManager.h"
#include "HelloWorldScene.h"

//#include "ShiningScene.h"
//#include "IceShopScene.h"
//#include "LandScene.h"
//#include "AniCircusScene.h"
//#include "ChooseScene.h"
//#include "HospitalScene.h"
//#include "NEK_MazeLayer.h"
//#include "CoinScene.h"
//#include "MapScene.h"
//#include "CatSelectScene.h"
//#include "LetterCover.h"
//#include "WorldScene.h"
//#include "ClockDrogLayer.h"
//#include "SelectAnimalScene.h"
//#include "SelectSalonAnim.hpp"
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
//#include "CodingStageScene.h"
#include "DinoColor/SelectColorTheme.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif

using namespace std;

Scene* LogoScene::scene(){
    
    Scene* scene = Scene::create();
    
    LogoScene* layer = LogoScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool LogoScene::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = GameManager::sharedManager()->getCenter();
    
    isSetBackground = false;
    
//    Director::getInstance()->purgeCachedData();
    
    clickCount = 0;
    
    Sprite* background = Sprite::create("joyland/logo_bg.jpg");
    background->setPosition(center);
    background->setScale(MAX(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height));
    this->addChild(background,1);
    
//    Sprite* cloud = Sprite::create("bg/clouds.png");
//    cloud->setPosition(Vec2(visibleSize.width/2, visibleSize.height*4/5));
//    cloud->setScale(MAX(visibleSize.width/cloud->getContentSize().width, visibleSize.height/cloud->getContentSize().height));
//    this->addChild(cloud,5);

    Sprite* title = Sprite::create("joyland/Logo_title.png");
    title->setPosition(Vec2(center.x, center.y+visibleSize.height/8));
    this->addChild(title,6);
    
//    auto particleSystem = ParticleFireworks::create();
//    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
//    particleSystem->setPosition(center);
//    this->addChild(particleSystem, 10);
    
    
    Sprite* logo = Sprite::create("joyland/companyLogo.png");
    logo->setPosition(Vec2(center.x, center.y-visibleSize.height/4));
    logo->setScale(0.6);
    this->addChild(logo,7);
    
    
    this->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(LogoScene::gotoGameScene, this)),NULL));
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(LogoScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool LogoScene::onTouchBegan(Touch* touch, Event* event) {
    if (!isSetBackground) {
        this->gotoGameScene();
        isSetBackground = true;
    }
    return true;
}

void LogoScene::gotoGameScene() {
//    CCUserDefault::sharedUserDefault()->setBoolForKey("gotoGameFromLogo",true);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene(), Color3B::BLACK));
    
}

LogoScene::LogoScene(){
    
}

LogoScene::~LogoScene(){
    
}

void LogoScene::onEnter(){
    Layer::onEnter();
}

void LogoScene::onExit(){
    Layer::onExit();
}
