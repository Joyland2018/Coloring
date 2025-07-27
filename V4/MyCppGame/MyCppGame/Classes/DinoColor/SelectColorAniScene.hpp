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

USING_NS_CC;

class SelectColorAniScene : public Layer{
public:
    static Scene* scene();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
    SelectColorAniScene();
    ~SelectColorAniScene();
    
    // Touch event handling for Cocos2d-x 4.0
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    void clickBack();
    void showAllTheme(float dt);
    void goNext();
    void aniAction();
    void aniJumpMp3();
    void addLock(Node* _parent, int _index);
    void selectAdsOrIAP(int _pageIndex);
    
    bool backClick;
    bool clickTheme;
    
    Vec2 winCenter;
    
    float iphoneXOffsetX;
    
    int selectAniIndex;
    CREATE_FUNC(SelectColorAniScene);
    
private:
    EventListenerTouchOneByOne* touchListener;
};
#endif /* SelectColorAniScene_hpp */
