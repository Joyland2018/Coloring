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
    
    if (!Layer::init())
    {
        return false;
    }
    // FileUtils::getInstance()->setOBBPath();

    std::string pathToSave = FileUtils::getInstance()->getWritablePath();
    // pathToSave += "tmpDir";
    DIR *pDir = NULL;
    pDir = opendir(pathToSave.c_str());
    if (!pDir) {
        mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }

    //添加下载后的资源路径
            vector<string> searchPaths = FileUtils::getInstance()->getSearchPaths();
            vector<string>::iterator iter = searchPaths.begin();
            searchPaths.insert(iter, pathToSave);
            FileUtils::getInstance()->setSearchPaths(searchPaths);
    Vec2 center = GameManager::sharedManager()->getCenter();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#ifdef AVOCADO
    Sprite* logo = Sprite::create("universal/logo.png");
#else
    Sprite* logo = Sprite::create("universal/logo_old.png");
#endif
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Sprite* logo = Sprite::create("background/logo_old.png");
#endif
    logo->setPosition(Vec2(center.x-1.3, center.y-1.3));
    this->addChild(logo);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(LogoScene::runGame), 5.95);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(LogoScene::runGame), 1.95);
#endif
    
    return true;
    
}

void LogoScene::runGame(float dt){
    

    if (GameManager::sharedManager()->lastTime == 0) {
        GameManager::sharedManager()->setLastTime();
    }
    
//    DeviceManager::sharedManager()->setAnimalTrack();
//TransitionFade *action = TransitionFade::create(0.5, ShiningScene::sceneWithId(0), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, CodingStageScene::sceneWithId(0), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, LandScene::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, ChooseScene::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, NEK_MazeLayer::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, CoinScene::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, MapScene::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, CatSelectScene::sceneWithID(0), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, LetterCover::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, WorldScene::scene(), Color3B::WHITE);
//    TransitionFade *action = TransitionFade::create(0.5, ClockDrogLayer::scene(), Color3B::WHITE);
    TransitionFade *action = TransitionFade::create(0.5, SelectColorTheme::scene(), Color3B::WHITE);

    Director::getInstance()->replaceScene(action);
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
