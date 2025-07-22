//
//  GameManager.h
//  GameGarden
//
//  Created by LiXiaofei on 2017/2/4.
//
//

#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;

typedef struct GAMEMANAGER_INF
{
    bool openGameTag;
}GAMEMANAGER_INF;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
typedef enum BigGameType {
   kCodingTag = 7,
    kTimeTag = 8,
    kMathTag = 15,
    kNumbersTag = 12,
    kCircusTag = 0,
    kShapePuzzleTag = 4,
    kJigsawPuzzleTag = 14,
    kMatchTag = 2,
    kSpellWordsTag = 6,
    kAnimalTag = 5,
    kHospitalTag = 1,
    kCoinTag = 9,
    kUnitedStatesTag = 13,
    kCatDressTag = 3,
    kWordFamilyTag = 11,
    kWorldTag = 10,

} gameType;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
typedef enum GameType {
    kTimeTag = 6,
    kMathTag = 8,
    kNumbersTag = 12,
    kCircusTag = 9,
    kShapePuzzleTag = 11,
    kJigsawPuzzleTag = 7,
    kMatchTag = 0,
    kSpellWordsTag = 15,
    kAnimalTag = 14,
    kHospitalTag = 1,
    kCoinTag = 5,
    kUnitedStatesTag = 4,
    kCatDressTag = 2,
    kWordFamilyTag = 13,
    kWorldTag = 10,
    kCodingGameTag = 3,
} gameType;
#endif

class GameManager {
    
public:
    
    ValueVector sceneKeys;
    ValueVector sceneIndexKeys;
    ValueVector hippoInfo;
    ValueMap curGameInfo;
    ValueMap curResourceInfo;

    int GameIndex;

    int num;
    int lastTime = 0;
    int iapDisplayCount = 0;
    
    int clickIAPSceneIndex;


    static GameManager* sharedManager();
    
    static Vec2 getLeftTopPos();
    static Vec2 getLeftBottomPos();
    static Vec2 getRightTopPos();
    static Vec2 getRightBottomPos();
    static Vec2 getCenter();
    static Vec2 getViewInitPos();
    static Size getViewVisibleSize();
    
    static void initGameSystem();//初始化游戏配置
    
    void setGameSystem(int _gameType,int _sceneId);//根据_gameType调用不同玩法的设置函数
    
    static void replaceToGameScenes();
    void setCurrentGameInfo(int _gameType);
    
    Sprite* getIconSprite(int _iconId);
    void playIconRead(int _soundId);

    time_t getCurTime();

    void requestInitAds();
    void showBanner();
    void noBanner();
    void showInterstitial();
    void showReward();
    void trackMixpanel(const char* _trackStr);
    void timeEventMixpanel(const char* _timeEventStr);
    void showIap(int _buyIndex);
    void changeToGameScene();
    void otherGame();
//    void showAdAndGetReward();
    void goToBuyIAP(int _buyIndex);

    ValueVector getFreeIndexArr(int _dayValue);
    int curDayOfWeekValue;
    bool isCanShowIAP1;
    static bool getOpenGameTag();


    std::string getCurrentTime();
    
    void setLastTime();
    void setReviewLastTime();  //reivew
    
    bool isNeedShowIAP();


    int  FlyGameIndex = 0 ;
    int dinoFlyPlayCount;
    bool isiphoneX = false ;
    bool isIphoneX() ;
    bool isAndroidPad();
    bool isFullAndroidPad = false;
    int clickSceneIndex;
    int clickChangeDinoIndex;
    // void setResourceInfo(int _gameType);
    void setResourceVersion(int _index,std::string _version);
    std::string getResourceVersion(int _index);
    void goToShowReview();
    void testSchedule();
    void isNeedshowReview();
    bool isShowenReview;
    time_t reviewlastTime;
    
    void setResourceInfo(int _gameType);
    void setJigsawPuzzleInfo(int _sceneId);//设置jigsawpuzzle的配置信息
    bool ShowGuide = true;

    bool isNeedShowInterstitial();
    time_t lastMin;

    int minIndex;
    int selectColorPen;

private:
    void setMathInfo(int _sceneId);//设置match的配置信息
    void setShapePuzzleInfo(int _sceneId);//设置shapepuzzle的配置信息
    
    void setSpellWordsInfo(int _sceneId);//设置spellwords的配置信息
    void setMatchInfo(int _sceneId);//设置match的配置信息
    void setCircusInfo(int _sceneId);//设置circus的配置信息
    
};

#endif /* GameManager_h */
