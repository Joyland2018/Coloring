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
#include "SelectColorTheme.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif

using namespace std;

CCScene* LogoScene::scene(){
    
    CCScene* scene = CCScene::create();
    
    LogoScene* layer = LogoScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool LogoScene::init(){
    
    if (!CCLayer::init())
    {
        return false;
    }
    // CCFileUtils::sharedFileUtils()->setOBBPath();

    std::string pathToSave = CCFileUtils::sharedFileUtils()->getWritablePath();
    // pathToSave += "tmpDir";
    DIR *pDir = NULL;
    pDir = opendir(pathToSave.c_str());
    if (!pDir) {
        mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }

    //添加下载后的资源路径
            vector<string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
            vector<string>::iterator iter = searchPaths.begin();
            searchPaths.insert(iter, pathToSave);
            CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    CCPoint center = GameManager::sharedManager()->getCenter();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#ifdef AVOCADO
    CCSprite* logo = CCSprite::create("universal/logo.png");
#else
    CCSprite* logo = CCSprite::create("universal/logo_old.png");
#endif
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCSprite* logo = CCSprite::create("background/logo_old.png");
#endif
    logo->setPosition(ccp(center.x-1.3, center.y-1.3));
    this->addChild(logo);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    this->scheduleOnce(schedule_selector(LogoScene::runGame), 5.95);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    this->scheduleOnce(schedule_selector(LogoScene::runGame), 1.95);
#endif
    
    return true;
    
}

void LogoScene::runGame(){
    

    if (GameManager::sharedManager()->lastTime == 0) {
        GameManager::sharedManager()->setLastTime();
    }
    
//    DeviceManager::sharedManager()->setAnimalTrack();
//CCTransitionFade *action = CCTransitionFade::create(0.5, ShiningScene::sceneWithId(0), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, CodingStageScene::sceneWithId(0), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, LandScene::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, ChooseScene::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, NEK_MazeLayer::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, CoinScene::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, MapScene::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, CatSelectScene::sceneWithID(0), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, LetterCover::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, WorldScene::scene(), ccWHITE);
//    CCTransitionFade *action = CCTransitionFade::create(0.5, ClockDrogLayer::scene(), ccWHITE);
    CCTransitionFade *action = CCTransitionFade::create(0.5, SelectColorTheme::scene(), ccWHITE);

    CCDirector::sharedDirector()->replaceScene(action);
}

LogoScene::LogoScene(){
    
}

LogoScene::~LogoScene(){
    
}

void LogoScene::onEnter(){
    CCLayer::onEnter();
}

void LogoScene::onExit(){
    CCLayer::onExit();
}
