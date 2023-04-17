//
//  SelectColorTheme.hpp
//  DrDino
//
//  Created by LiXiaofei on 2/13/23.
//

#ifndef SelectColorTheme_hpp
#define SelectColorTheme_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;

class SelectColorTheme : public CCLayer {
public:
//    CCScrollView *scrollView1;
//    CCScrollView *scrollView2;
//    CCLayer *containerLayer1;
//    CCLayer *containerLayer2;
    
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
    SelectColorTheme();
    ~SelectColorTheme();
    
//    virtual void scrollViewDidScroll(CCScrollView* view);
//    virtual void scrollViewDidZoom(CCScrollView* view);
    
    virtual void registerWithTouchDispatcher();                 //注册单点触摸点击事件
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
    
    void clickBack();
    void showTheme();
    void goNext();
    void resetThemePos();
    void canTouchTheme();
    
    
    bool backClick;
    bool clickTheme;
    bool showCurTheme;
    bool haveResetPos;
    
    CCPoint winCenter;
    
    int beginX;
    int endX;
    int touchMoveDis;
    int scaleThemeIndex;
    int startX;
    int finishX;
    
    int curThemeIndex;
    bool touchMoveTheme;
    
    int resetThemePosX;
    int themeX;
    float minDis;
    float maxDis;
    
    int curTouchMoveX;
    int curMoveThemeX;
    int curResetTheme;
    
    CREATE_FUNC(SelectColorTheme);
    
};

#endif /* SelectColorTheme_hpp */
