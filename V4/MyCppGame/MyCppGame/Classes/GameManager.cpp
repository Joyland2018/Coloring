//
//  GameManager.cpp
//  GameGarden
//
//  Created by LiXiaofei on 2017/2/4.
//
//

#include <platform/android/jni/JniHelper.h>
//#include "DinoHospital/JigsawPuzzle/JigsawPuzzleManager.h"
#include "GameManager.h"
//#include "SecondScene.h"
//#include "SelectScene.h"
//#include "SearchScene.h"
//#include "SongScene.h"
//#include "PlayScene.h"
//#include "SimpleAudioEngine.h"
//#include "ShapePuzzle/ShapePuzzleManager.h"
//#include "FirstWord/SpellWordsInf.h"
//#include "SpellWordsScene.h"
//#include "ShapePuzzleScene.h"
//#include "Match/GameInf.h"
//#include "ShapePuzzle/ShapePuzzleManager.h"
//#include "AnimalCircus/AnimalManager.h"
//#include "JoyLandGerman/LandScene.h"
//#include "MatchScene.h"
//#include "JigsawPuzzleManager.h"
//#include "ShiningScene.h"
//#include "AnimalManager.h"
//#include "CoinManager.h"
//#include "GameData.h"
//#include "WorldGameData.h"

//extern SPELL_INF spellInf;
//extern GAME_INF gameInf;

static GameManager* gm = NULL ;
GAMEMANAGER_INF gameManagerInf = {0};

GameManager* GameManager::sharedManager()
{
    if (!gm) {
        gm = new GameManager() ;
        gm->isiphoneX = false ;
        gm->isFullAndroidPad = false;
        gm->lastTime = 0;
        gm->lastMin = 0;
        gm->selectColorPen = 0;
        gm->iapDisplayCount = 0;
    }


    return gm ;
}

bool GameManager::isIphoneX(){
    return isiphoneX;
}

bool GameManager::isAndroidPad() {
    return isFullAndroidPad;
}

bool GameManager::getOpenGameTag(){
    return gameManagerInf.openGameTag;
}

Vec2 GameManager::getViewInitPos(){
    return Vec2(Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleOrigin().y);
}

Size GameManager::getViewVisibleSize(){
    return Size(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
}

Vec2 GameManager::getLeftTopPos(){
    Vec2 leftTopPos = Vec2::ZERO;
    leftTopPos = Vec2(getViewInitPos().x, getViewInitPos().y+getViewVisibleSize().height);
    return leftTopPos;
}

Vec2 GameManager::getLeftBottomPos(){
    Vec2 leftBottomPos = Vec2::ZERO;
    leftBottomPos = Vec2(getViewInitPos().x, getViewInitPos().y);
    return leftBottomPos;
}

Vec2 GameManager::getRightTopPos(){
    Vec2 rightTopPos = Vec2::ZERO;
    rightTopPos = Vec2(getViewInitPos().x+getViewVisibleSize().width, getViewInitPos().y+getViewVisibleSize().height);
    return rightTopPos;
}

Vec2 GameManager::getRightBottomPos(){
    Vec2 rightBottomPos = Vec2::ZERO;
    rightBottomPos = Vec2(getViewInitPos().x+getViewVisibleSize().width, getViewInitPos().y);
    return rightBottomPos;
}

Vec2 GameManager::getCenter(){
    Vec2 centerPos = Vec2::ZERO;
    centerPos = Vec2(getViewInitPos().x+getViewVisibleSize().width/2, getViewInitPos().y+getViewVisibleSize().height/2);
    return centerPos;
}

void GameManager::setResourceInfo(int _gameType){
    
    const char* filePath = "";
    
    const char* infoKey = "";
    
    switch (_gameType) {
        case kMatchTag:
            filePath = "universal/matchResourceInfo.plist";
            break;
        case kShapePuzzleTag:
            filePath = "universal/shapeResourceInfo.plist";
            break;
        case kSpellWordsTag:
            filePath = "universal/spellResourceInfo.plist";
            break;
        case kJigsawPuzzleTag:
            filePath = "universal/jigsawResourceInfo.plist";
            break;
        default:
            break;
    }
    
    curResourceInfo = FileUtils::getInstance()->getValueMapFromFile(filePath);
    
}


void GameManager::setResourceVersion(int _index,std::string _version){
    CCLOG("<============set resource version============> %s",_version.c_str());
    // _index = _index+1;
    switch (_index) {
        case kCatDressTag:
            UserDefault::getInstance()->setStringForKey("CatVersion",_version.c_str());
            break;
        case kMatchTag:
            UserDefault::getInstance()->setStringForKey("MatchVersion",_version.c_str());
            break;
        case kUnitedStatesTag:
            UserDefault::getInstance()->setStringForKey("UnitedVersion",_version.c_str());
            break;
        case kCircusTag:
            UserDefault::getInstance()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kMathTag:
            UserDefault::getInstance()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kShapePuzzleTag:
            UserDefault::getInstance()->setStringForKey("ShapeVersion",_version.c_str());
            break;
        case kWorldTag:
            UserDefault::getInstance()->setStringForKey("WorldVersion",_version.c_str());
            break;
        case kNumbersTag:
            UserDefault::getInstance()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kWordFamilyTag:
            UserDefault::getInstance()->setStringForKey("WordFamilyVersion",_version.c_str());
            break;
        case kAnimalTag:
            UserDefault::getInstance()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kSpellWordsTag:
            UserDefault::getInstance()->setStringForKey("SpellVersion",_version.c_str());
            break;
        default:
            break;
    }
}

std::string GameManager::getResourceVersion(int _index){
    std::string _version = "";

    CCLOG("<===========get resource version=============> %d",_index);
    _index = _index - 1;
    switch (_index) {
        case kCatDressTag:
            _version = UserDefault::getInstance()->getStringForKey("CatVersion");
            break;
        case kMatchTag:
            _version = UserDefault::getInstance()->getStringForKey("MatchVersion");
            break;
        case kUnitedStatesTag:
            _version = UserDefault::getInstance()->getStringForKey("UnitedVersion");
            break;
        case kCircusTag:
            _version = UserDefault::getInstance()->getStringForKey("CircusVersion");
            break;
        case kMathTag:
            _version = UserDefault::getInstance()->getStringForKey("CircusVersion");
            break;
        case kShapePuzzleTag:
            _version = UserDefault::getInstance()->getStringForKey("ShapeVersion");
            break;
        case kWorldTag:
            _version = UserDefault::getInstance()->getStringForKey("WorldVersion");
            break;
        case kNumbersTag:
            _version = UserDefault::getInstance()->getStringForKey("CircusVersion");
            break;
        case kWordFamilyTag:
            _version = UserDefault::getInstance()->getStringForKey("WordFamilyVersion");
            break;
        case kAnimalTag:
            _version = UserDefault::getInstance()->getStringForKey("CircusVersion");
            break;
        case kSpellWordsTag:
            _version = UserDefault::getInstance()->getStringForKey("SpellVersion");
            break;
        default:
            break;
    }

    return _version;
}

void GameManager::initGameSystem(){
//    SpellWordsInf::initSpellInf();
//
//    ShapePuzzleManager::shareGameManger()->initLocalLanguage();
//    ShapePuzzleManager::shareGameManger()->setGameDefult();
//
//    GameInf::initGameInf();
//
////    JigsawPuzzleManager::shareGameManger()->initDefault();
//
//    AnimalManager::shareGameManger()->initGameInfo() ;
////
//    AnimalManager::shareGameManger()->setGameArray() ;
//    
//    CoinManager::shareGameManger()->setGameDefault();
//    
//    GameData::shareGameData();
//    
//    WorldGameData::shareGameData();
    
//    UserDefault::getInstance()->setBoolForKey("UnlockAll",true);
    
    UserDefault::getInstance()->setIntegerForKey("ClockIndex", 1);
    
    int clock = UserDefault::getInstance()->getIntegerForKey("ClockIndex");
    if (clock == 0) {
        clock = 1;
        UserDefault::getInstance()->setIntegerForKey("ClockIndex", clock);
    }
    
    if (!UserDefault::getInstance()->getIntegerForKey("GameLevel")) {
        UserDefault::getInstance()->setIntegerForKey("GameLevel", 2);
    }
}

void GameManager::setCurrentGameInfo(int _gameType){
    const char* filePath = "";
    
    const char* infoKey = "";
    
    switch (_gameType) {
        case kMatchTag:
            filePath = "spellwords/mainscenes/scenesIcon/matchInfo.plist";
            infoKey = "match";
            break;
        case kShapePuzzleTag:
            filePath = "spellwords/mainscenes/scenesIcon/shapePuzzleInfo.plist";
            infoKey = "shapepuzzle";
            break;
        case kSpellWordsTag:
            filePath = "spellwords/mainscenes/scenesIcon/spellWordsInfo.plist";
            infoKey = "spellwords";
            break;
        case kJigsawPuzzleTag:
            filePath = "jigsawpuzzle/jigsawPuzzleInfo.plist";
            infoKey = "jigsawpuzzle";
            break;
        default:
            break;
    }
    
    curGameInfo = FileUtils::getInstance()->getValueMapFromFile(filePath);
    
    ValueMap curScenesInfo = FileUtils::getInstance()->getValueMapFromFile("spellwords/mainscenes/scenesIcon/scenesInfo.plist");
        
    sceneKeys = curScenesInfo.at(infoKey).asValueVector();
    
    ValueMap curScenesKeyInfo = FileUtils::getInstance()->getValueMapFromFile("spellwords/mainscenes/scenesInfo.plist");
    
    sceneIndexKeys = curScenesKeyInfo.at(infoKey).asValueVector();
    
    for (int i = 0; i < sceneKeys.size(); i++) {
        CCLOG("=====index = %d,key = %s=====",i,sceneKeys[i].asString().c_str());
    }
    
    ValueMap curHippoInfo = FileUtils::getInstance()->getValueMapFromFile("spellwords/mainscenes/hippoAnim/hippoInfo.plist");
    
    hippoInfo = curHippoInfo.at(infoKey).asValueVector();
}

Sprite* GameManager::getIconSprite(int _iconId){
    
    const char* iconFile = sceneKeys[_iconId].asString().c_str();
    
    std::string filePath = StringUtils::format("spellwords/mainscenes/scenesIcon/%s.png",iconFile);
    
    CCLOG("------index = %d,imageName = %s------",_iconId,iconFile);
    
    Sprite* trainIcon = Sprite::create(filePath);
    
    if (trainIcon != NULL) {
        return trainIcon;
    } else {
        return NULL;
    }
    
}

void GameManager::playIconRead(int _soundId){
    const char* iconFile = sceneIndexKeys[_soundId].asString().c_str();
    
    std::string filePath = StringUtils::format("spellwords/mainscenes/scenesIcon/sound/%s.mp3",iconFile);
    
    CCLOG("------index = %d,imageName = %s------",_soundId,iconFile);

//    AudioEngine::play2d(filePath);
}

time_t GameManager::getCurTime(){
    struct timeval now;
    gettimeofday(&now, NULL);

    time_t timep = now.tv_sec;

//    struct tm *tm;
//    time_t timep = now.tv_sec;
//    tm = localtime(&timep);
//    int min=tm->tm_min;
    
    return timep;
    
}

//bool GameManager::isNeedShowIAP(){
//
//    if (iapDisplayCount < 2) {
//
//        int curMin = this->getCurTime();
//
//        int duration = curMin - lastTime;
//
//        if (iapDisplayCount == 0 && duration >= 5) {
//            lastTime = curMin;
//            iapDisplayCount++;
//            return true;
//        }else if (iapDisplayCount == 1 && duration >= 15){
//            lastTime = curMin;
//            iapDisplayCount++;
//            return true;
//        }
//    }
//
//    return false;
//}

bool GameManager::isNeedShowIAP(){

//    if (iapDisplayCount < 1) {

    time_t curMin = this->getCurTime();

    time_t duration = curMin - lastTime;
    struct tm *tm;
    tm = localtime(&duration);
//    duration = abs(curMin - 60) - abs(lastTime - 60);

//    if (duration >= 5 && !GameManager::sharedManager()->isShowenReview) {
//        DeviceManager::sharedManager()->gotoReview();
//    }

    if (iapDisplayCount == 0 && tm->tm_min >= 7) {
        lastTime = curMin;
        iapDisplayCount++;
        return true;
//        }else if (iapDisplayCount == 1 && duration >= 15){
//            lastTime = curMin;
//            iapDisplayCount++;
//            return true;
    }
//    }

    return false;
}

void GameManager::testSchedule(){
    
    bool isShow = this->isNeedShowIAP();
    
    if (isShow) {
        CCLOG("----------true----------");
    } else {
        CCLOG("----------false----------");
    }
}

void GameManager::setLastTime(){
    lastTime = this->getCurTime();
    lastMin = this->getCurTime();
}

bool GameManager::isNeedShowInterstitial() {
    time_t curMin = this->getCurTime();

    time_t duration = curMin - lastMin;
    struct tm *tm;
    tm = localtime(&duration);

    if (tm->tm_min >= minIndex) {
        lastMin = curMin;
        minIndex++;
        return true;
    }
    return false;
}

std::string GameManager::getCurrentTime(){
    struct timeval now;
    gettimeofday(&now, NULL);
    
    struct tm *tm;
    time_t timep = now.tv_sec+7*24*60*60;
    tm = localtime(&timep);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon;
    int day = tm->tm_mday;
    
    const char* curMonth = "";
    //Jan. Feb. Mar. Apr. May. Jun. Jul. Aug. Sep. Oct. Nov. Dec.
    switch (month) {
        case 0:
            curMonth = "Jan.";
            break;
        case 1:
            curMonth = "Feb.";
            break;
        case 2:
            curMonth = "Mar.";
            break;
        case 3:
            curMonth = "Apr.";
            break;
        case 4:
            curMonth = "May";
            break;
        case 5:
            curMonth = "Jun.";
            break;
        case 6:
            curMonth = "Jul.";
            break;
        case 7:
            curMonth = "Aug.";
            break;
        case 8:
            curMonth = "Sep.";
            break;
        case 9:
            curMonth = "Oct.";
            break;
        case 10:
            curMonth = "Nov.";
            break;
        case 11:
            curMonth = "Dec.";
            break;
        default:
            break;
    }
    
//    std::string curTime = StringUtils::format("%d-%d-%d",year,month+1,day);
    std::string curTime = StringUtils::format("%d.%d.%d",day,month+1,year);
    return curTime;
}

void GameManager::setGameSystem(int _gameType,int _sceneId){
    switch (_gameType) {
        case kSpellWordsTag:
        {
            setSpellWordsInfo(_sceneId);
        }
            break;
        case kMatchTag:
        {
            setMatchInfo(_sceneId);
        }
            break;
        case kCircusTag:
        {
            setCircusInfo(_sceneId);
        }
            break;
        case kAnimalTag:
        {
            setMathInfo(_sceneId);
        }
            break;
        case kShapePuzzleTag:
        {
            setShapePuzzleInfo(_sceneId);
        }
            break;
       #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case kJigsawPuzzleTag:
        {
            setJigsawPuzzleInfo(_sceneId);
        }
            break;
#endif
        
        default:
            break;
    }
}

void GameManager::setMathInfo(int _sceneId){
    
}

void GameManager::setCircusInfo(int _sceneId){
    
}

void GameManager::setShapePuzzleInfo(int _sceneId){
    
//    std::string infoKey = sceneIndexKeys[_sceneId].asString();
//
//    ValueMap info = curGameInfo.at(infoKey).asValueMap();
//
//    int sceneIndex = info.at("currentSceneIndex").asInt();
//    int itemIndex = info.at("currentItemIndex").asInt();
//
//    ShapePuzzleManager::shareGameManger()->setSceneIndex(sceneIndex);
//    ShapePuzzleManager::shareGameManger()->setItemIndex(itemIndex);
    
}

void GameManager::setMatchInfo(int _sceneId){
//
//    std::string infoKey = sceneIndexKeys[_sceneId].asString();
//
//    ValueMap info = curGameInfo.at(infoKey).asValueMap();
//
//    gameInf.currentIndex = info.at("currentIndex").asInt();
//
}

void GameManager::setSpellWordsInfo(int _sceneId){
//    spellInf.currentLevel = 1;
//    spellInf.currentLanguage = 1;
//
//    std::string infoKey = sceneIndexKeys[_sceneId].asString();
//
//    ValueMap info = curGameInfo.at(infoKey).asValueMap();
//
//    int curSceneIndex = info.at("currentSceneIndex").asInt();
//    int curNum = info.at("currentNum").asInt();
//
//    if (spellInf.chooseSceneIndex != curSceneIndex || spellInf.currentNum != curNum) {
//        spellInf.currentWord = 0;
//    }
//    spellInf.chooseSceneIndex = curSceneIndex;
//    spellInf.currentNum = curNum;
    
}

//void GameManager::setJigsawPuzzleInfo(int _sceneId){
    
//    std::string infoKey = sceneIndexKeys[_sceneId].asString();
    
//    JigsawPuzzleManager::shareGameManger()->currentAnimKey = infoKey;

//    ValueMap info = curGameInfo.at(infoKey).asValueMap();

//    JigsawPuzzleManager::shareGameManger()->picImageName = info.at("imageName").asString();
//}


void GameManager::setJigsawPuzzleInfo(int _sceneId){

//
//    const char* infoKey = "";
//
//    switch (_sceneId){
//        case 0:
//        {
//            infoKey = "Begin";
//        }
//            break;
//        case 1:
//        {
//            infoKey = "YK";
//        }
//            break;
//        case 2:
//        {
//            infoKey = "NEK";
//        }
//            break;
//        case 3:
//        {
//            infoKey = "GK";
//        }
//            break;
//        case 4:
//        {
//            infoKey = "BF";
//        }
//            break;
//        case 5:
//        {
//            infoKey = "JZ";
//        }
//            break;
//        case 6:
//        {
//            infoKey = "YK2";
//        }
//            break;
//        case 7:
//        {
//            infoKey = "NK";
//        }
//            break;
//        case 8:
//        {
//            infoKey = "TJ";
//        }
//            break;
//        case 10:
//        {
//            infoKey = "Shower";
//        }
//            break;
//        case 11:
//        {
//            infoKey = "Clip";
//        }
//            break;
//        case 9:
//        {
//            infoKey = "Sink";
//        }
//            break;
//        case 12:
//        {
//            infoKey = "Clothes";
//        }
//            break;
//        case 13:
//        {
//            infoKey = "Toilet";
//        }
//            break;
//        case 14:
//        {
//            infoKey = "Dress";
//        }
//            break;
//        default:
//            break;
//    }
//
////    JigsawPuzzleManager::shareGameManger()->currentAnimKey = infoKey;
//
//    std::string info = curGameInfo.at(infoKey).asString();
//
//    JigsawPuzzleManager::shareGameManger()->picImageName = info;
//    JigsawPuzzleManager::shareGameManger()->currentImageIndex = _sceneId;
//

}

void GameManager::replaceToGameScenes(){
    
}

//banner
void GameManager::showBanner() {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo minfo;
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");
//
//    if (!isHave){
//        CCLOG("jni:不能获取单例");
//    } else{
//        CCLOG("jni:可以获取单例");
//
//        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//
//        bool isHaveNoStaticMethodInfo = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","onShowOrHideBanner","()V");
//        if (!isHaveNoStaticMethodInfo){
//            CCLOG("jni:alertDiaShowt方法不存在");
//        } else{
//            CCLOG("jni:alertDiaShow方法存在");
//            minfo.env->CallVoidMethod(jobj,minfo.methodID);
//        }
//    }
//#endif
}

void GameManager::noBanner() {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo minfo;
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");
//
//    if (!isHave){
//        CCLOG("jni:不能获取单例");
//    } else{
//        CCLOG("jni:可以获取单例");
//        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);         //获取单例对象
//        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","noBannerAds","()V");
//        if (!isHaveNoStaticMethod){
//            CCLOG("jni:alertDiaShowt方法不存在");
//        } else{
//            CCLOG("jni:alertDiaShow方法存在");
//            minfo.env->CallVoidMethod(jobj,minfo.methodID);
//        }
//    }
//    CCLOG("jni-java函数执行完毕");
//#endif
}


//插页广告
void GameManager::showInterstitial() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");

    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");

        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

        bool isHaveNoStaticMethodInfo = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","onShowInterstitial","()V");
        if (!isHaveNoStaticMethodInfo){
            CCLOG("jni:alertDiaShowt方法不存在");
        } else{
            CCLOG("jni:alertDiaShow方法存在");
            minfo.env->CallVoidMethod(jobj,minfo.methodID);
        }
    }
#endif
}



//激励视频
void GameManager::showReward() {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo minfo;
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");
//    if (!isHave){
//        CCLOG("jni:不能获取单例");
//    } else{
//        CCLOG("jni:可以获取单例");
//        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
//        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","showRewardAds","()V");
//        if (!isHaveNoStaticMethod){
//            CCLOG("jni:不能获取单例");
//        } else{
//            CCLOG("jni:可以获取单例");
//            minfo.env->CallVoidMethod(jobject1,minfo.methodID);
//        }
//    }
//    CCLOG("jni-java函数执行完毕");
//#endif
}

void GameManager::changeToGameScene() {
//    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, CircusSelectScene::sceneWithID(_gameTag), Color3B::WHITE));
//    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, SearchScene::sceneWithID(gameIndex), Color3B::WHITE));
//    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, ABCcircusMatchScene::sceneWithID(gameIndex), Color3B::WHITE));
//    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, SongScene::scene(), Color3B::WHITE));
    switch (GameIndex) {
//        case 0:
////            Director::getInstance()->replaceScene(TransitionFade::create(0.5, CircusSelectScene::sceneWithID(1), Color3B::BLACK));
//            Director::getInstance()->replaceScene(TransitionFade::create(0.5, PlayScene::scene(), Color3B::BLACK));
//            break;
//        case 1:
////            Director::getInstance()->replaceScene(TransitionFade::create(0.5, CircusSelectScene::sceneWithID(2), Color3B::BLACK));
//            Director::getInstance()->replaceScene(TransitionFade::create(0.5, PlayScene::scene(), Color3B::BLACK));
//            break;
//            //        case 2:
//            //            Director::getInstance()->replaceScene(TransitionFade::create(0.5, SelectScene::sceneWithID(3), Color3B::BLACK));
//            //            break;
//        case 2:
//            Director::getInstance()->replaceScene(TransitionFade::create(0.5, SearchScene::sceneWithID(0), Color3B::BLACK));
//            break;
//            //        case 4:
//            //            Director::getInstance()->replaceScene(TransitionFade::create(0.5, SearchNumScene::scene(), Color3B::BLACK));
//            //            break;
//        case 3:
//            Director::getInstance()->replaceScene(TransitionFade::create(0.5, ABCMatchScene::sceneWithID(0), Color3B::BLACK));
//            break;
//            //        case 6:
//            //            Director::getInstance()->replaceScene(TransitionFade::create(0.5, ABCMatchScene::sceneWithID(1), Color3B::BLACK));
//            //            break;
//        case 4:
//            Director::getInstance()->replaceScene(TransitionFade::create(0.5, SongScene::scene(), Color3B::BLACK));
//            break;
//            //        case 8:
//            ////            Director::getInstance()->replaceScene(TransitionFade::create(0.5, TextScene::scene(), Color3B::BLACK));
//            //            break;
//        default:
//            break;
    }
}

//IAP
void GameManager::showIap(int _buyIndex) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");
    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");
        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","buyProduct","(I)V");
        if (!isHaveNoStaticMethod){
            CCLOG("jni:不能获取单例");
        } else{
            CCLOG("jni:可以获取单例");
            minfo.env->CallVoidMethod(jobject1,minfo.methodID,_buyIndex);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}

void GameManager::isNeedshowReview(){

//    if (iapDisplayCount < 1) {

    time_t curMin = this->getCurTime();

    time_t duration = curMin - reviewlastTime;
    struct tm *tm;
    tm = localtime(&duration);
//        duration = abs(curMin - 60) - abs(lastTime - 60);

    if (tm->tm_min >= 5 && !GameManager::sharedManager()->isShowenReview) {
//        DeviceManager::sharedManager()->goToReview();
        this->goToShowReview();
        GameManager::sharedManager()->isShowenReview = true;
    }

//    if (iapDisplayCount == 0 && tm->tm_min >= 7) {
//        lastTime = curMin;
//        iapDisplayCount++;
//        return true;
////        }else if (iapDisplayCount == 1 && duration >= 15){
////            lastTime = curMin;
////            iapDisplayCount++;
////
//    }
//    }

//    return false;
}

void GameManager::requestInitAds() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "color/games/kids/free/JoyPreschool",
                                                 "rtnActivity",
                                                 "()Lcolor/games/kids/free/JoyPreschool;");
    if (!isHave) {
        CCLOG("jni:不能获取单例");
    } else {
        CCLOG("jni:可以获取单例");
        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,
                                                             "color/games/kids/free/JoyPreschool",
                                                             "initAds", "()V");
        if (!isHaveNoStaticMethod) {
            CCLOG("jni:不能获取单例");
        } else {
            CCLOG("jni:可以获取单例");
            minfo.env->CallVoidMethod(jobject1, minfo.methodID);
        }
        CCLOG("jni-java函数执行完毕");
    }
#endif
}

//review
void GameManager::goToShowReview() {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo minfo;
//    bool isHave = JniHelper::getStaticMethodInfo(minfo, "color/games/kids/free/JoyPreschool",
//                                                 "rtnActivity",
//                                                 "()Lcolor/games/kids/free/JoyPreschool;");
//    if (!isHave) {
//        CCLOG("jni:不能获取单例");
//    } else {
//        CCLOG("jni:可以获取单例");
//        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","ShowReview","()V");
//        if (!isHaveNoStaticMethod) {
//            CCLOG("jni:不能获取单例");
//        } else {
//            CCLOG("jni:可以获取单例");
//            minfo.env->CallVoidMethod(jobject1, minfo.methodID);
//        }
//        CCLOG("jni-java函数执行完毕");
//#endif
//    }
}

void GameManager::setReviewLastTime(){
    reviewlastTime = this->getCurTime();
}

//导量
void GameManager::otherGame() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");
    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");
        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","goToMarket","()V");
        if (!isHaveNoStaticMethod){
            CCLOG("jni:不能获取单例");
        } else{
            CCLOG("jni:可以获取单例");
            minfo.env->CallVoidMethod(jobject1,minfo.methodID);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}





//Mixpanel
void GameManager::trackMixpanel(const char *_trackStr) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    //bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/landudu/eyechart/EyeChartForGod","rtnActivity","()Lcom/landudu/eyechart/EyeChartForGod;");
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");

    if(!isHave)
    {
        CCLOG("jni:不能获取单例");
    }
    else
    {
        CCLOG("jni:可以获取单例");
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  //获取单例对象

//        bool isHaveNoStaticMethod = JniHelper::getStaticMethodInfo(minfo,"com/jpt/joyland/JoyPreschool","onBuySomething", "(I)V");
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","cppSetTrack", "(Ljava/lang/String;)V");
        if (!isHaveNoStaticMethod)
        {
            CCLOG("jni:alertDiaShowt方法不存在");
        }

        else
        {
            CCLOG("jni:alertDiaShow方法存在");
            jstring jdata = minfo.env->NewStringUTF(_trackStr);
            minfo.env->CallVoidMethod(jobj, minfo.methodID, jdata);
//            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, productIndex);
//            if (minfo.env->ExceptionOccurred()) {
//                minfo.env->ExceptionDescribe();
//                minfo.env->ExceptionClear();
//                return;
//            }
//            minfo.env->DeleteLocalRef(minfo.classID);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}

void GameManager::timeEventMixpanel(const char *_timeEventStr) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    //bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/landudu/eyechart/EyeChartForGod","rtnActivity","()Lcom/landudu/eyechart/EyeChartForGod;");
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");

    if(!isHave)
    {
        CCLOG("jni:不能获取单例");
    }
    else
    {
        CCLOG("jni:可以获取单例");
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);  //获取单例对象

//        bool isHaveNoStaticMethod = JniHelper::getStaticMethodInfo(minfo,"com/jpt/joyland/JoyPreschool","onBuySomething", "(I)V");
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","cppSetTimeEvent", "(Ljava/lang/String;)V");
        if (!isHaveNoStaticMethod)
        {
            CCLOG("jni:alertDiaShowt方法不存在");
        }

        else
        {
            CCLOG("jni:alertDiaShow方法存在");
            jstring jdata = minfo.env->NewStringUTF(_timeEventStr);
            minfo.env->CallVoidMethod(jobj, minfo.methodID, jdata);
//            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, productIndex);
//            if (minfo.env->ExceptionOccurred()) {
//                minfo.env->ExceptionDescribe();
//                minfo.env->ExceptionClear();
//                return;
//            }
//            minfo.env->DeleteLocalRef(minfo.classID);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}

//void GameManager::showAdAndGetReward() {
//    int _curSceneIndex = this->clickIAPSceneIndex;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo minfo;
//
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");
//
//    if (!isHave){
//        CCLOG("jni:不能获取单例");
//    } else{
//        CCLOG("jni:可以获取单例");
//
//        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//
//        bool isHaveNoStaticMethodInfo = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","onShowReward","(I)V");
//        if (!isHaveNoStaticMethodInfo){
//            CCLOG("jni:alertDiaShowt方法不存在");
//        } else{
//            CCLOG("jni:alertDiaShow方法存在");
//            minfo.env->CallVoidMethod(jobj,minfo.methodID,_curSceneIndex);
//        }
//    }
//#endif
//}

void GameManager::goToBuyIAP(int _buyIndex) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"color/games/kids/free/JoyPreschool","rtnActivity","()Lcolor/games/kids/free/JoyPreschool;");

    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");

        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

        bool isHaveNoStaticMethodInfo = JniHelper::getMethodInfo(minfo,"color/games/kids/free/JoyPreschool","onBuyProduct","(I)V");
        if (!isHaveNoStaticMethodInfo){
            CCLOG("jni:alertDiaShowt方法不存在");
        } else{
            CCLOG("jni:alertDiaShow方法存在");
            minfo.env->CallVoidMethod(jobj,minfo.methodID,_buyIndex);
        }
    }
#endif
}

ValueVector GameManager::getFreeIndexArr(int _dayValue) {
    ValueVector freeIndexArr;

    ValueMap freeIndexMap = FileUtils::getInstance()->getValueMapFromFile("dinohospital/dailyFreeInfo.plist");
    const char* indexKey = "";
    switch (_dayValue){
        case 1:
        {
            indexKey = "Sun";
        }
            break;
        case 2:
        {
            indexKey = "Mon";
        }
            break;
        case 3:
        {
            indexKey = "Tue";
        }
            break;
        case 4:
        {
            indexKey = "Wed";
        }
            break;
        case 5:
        {
            indexKey = "Thu";
        }
            break;
        case 6:
        {
            indexKey = "Fri";
        }
            break;
        case 7:
        {
            indexKey = "Sat";
        }
            break;
        default:
            break;
    }

    freeIndexArr = freeIndexMap.at(indexKey).asValueVector();

    return freeIndexArr;
}

