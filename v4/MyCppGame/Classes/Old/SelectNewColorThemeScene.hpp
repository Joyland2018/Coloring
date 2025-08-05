//
//  SelectNewColorThemeScene.hpp
//  DrDino
//
//  Created by mac on 2025/7/8.
//

#ifndef SelectNewColorThemeScene_hpp
#define SelectNewColorThemeScene_hpp

#include <stdio.h>#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace extension;
using namespace CocosDenshion;

class SelectNewColorThemeScene : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
    SelectNewColorThemeScene();
    ~SelectNewColorThemeScene();
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    
    void clickBack();
    void showNewColorTheme();
    void goNext();
    void canTouchColorTheme();
    
    void showColorThemeAni();
    void showFirstGuide();
    void removeFirstGuide();
    
    bool backClick;
    bool clickColorTheme;
    bool showCurColorTheme;
    bool haveResetColor;
    bool bookBtnClick;
    
    CCPoint winCenter;
    
    float beginX;
    float endX;
    float touchMoveDis;
    int scaleThemeIndex;
    int curColorTheme;
    
    bool touchMoveColorTheme;
    int resetThemePosX;
    int themeX;
    float minDis;
    float maxDis;
    float finishX;
    float startX;
    
    int curTouchMoveX;
    int curMoveThemeX;
    int curResetTheme;
    
    int colorThemeTotalCount;
    
    CREATE_FUNC(SelectNewColorThemeScene);
    
};

#endif /* SelectNewColorThemeScene_hpp */
