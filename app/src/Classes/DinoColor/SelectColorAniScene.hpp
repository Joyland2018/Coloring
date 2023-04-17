//
//  SelectColorAniScene.hpp
//  DrDino
//
//  Created by LiXiaofei on 2/14/23.
//

#ifndef SelectColorAniScene_hpp
#define SelectColorAniScene_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class SelectColorAniScene : public CCLayer{
public:
    static CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
    SelectColorAniScene();
    ~SelectColorAniScene();
    
    virtual void registerWithTouchDispatcher();                 //注册单点触摸点击事件
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
    
    void clickBack();
    void showAllTheme();
    void goNext();
    void aniAction();
    void aniJumpMp3();
    void addLock(cocos2d::CCObject* _parent,int _index);
    void selectAdsOrIAP(int _pageIndex);
    
    bool backClick;
    bool clickTheme;
    
    CCPoint winCenter;
    
    float iphoneXOffsetX;
    
    int selectAniIndex;
    CREATE_FUNC(SelectColorAniScene);
    
};
#endif /* SelectColorAniScene_hpp */
