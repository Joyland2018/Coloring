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
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace extension;

class SelectColorTheme : public Layer {
public:
//    ui::ScrollView *scrollView1;
//    ui::ScrollView *scrollView2;
//    Layer *containerLayer1;
//    Layer *containerLayer2;
    
    static Scene* scene();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
    SelectColorTheme();
    ~SelectColorTheme();
    
//    virtual void scrollViewDidScroll(ui::ScrollView* view);
//    virtual void scrollViewDidZoom(ui::ScrollView* view);
    
    // 新的触摸处理方式
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    
    void clickBack();
    void showTheme(float dt);
    void goNext();
    void resetThemePos();
    void canTouchTheme();
    
    
    bool backClick;
    bool clickTheme;
    bool showCurTheme;
    bool haveResetPos;
    
    Vec2 winCenter;
    
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
