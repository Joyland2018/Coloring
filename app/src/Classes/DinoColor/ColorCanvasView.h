//
//  ColorCanvasView.hpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#ifndef ColorCanvasView_hpp
#define ColorCanvasView_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include "ColorManager.h"
#include "ColorSprite/ColorSprite.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension ;

class ColorCanvasView : public cocos2d:: CCLayer {
    
    
public:
    CCSize v_size ;
    CCPoint poszero;
    CCArray* m_DrawArray ;
    CCArray* m_ClipDrawArray ;
    
    CCRenderTexture *m_pCanvas;
    CCSprite *m_pBrush;
    ColorSprite* m_DrawingSp;
    
    CREATE_FUNC(ColorCanvasView);
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    //virtual void onExit();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void UpdateChooseColor() ;
    void backClick();
    void camera();
    void update(float date);
    bool watchedAds=false;

private:
    CCString* DinoColor ;
    CCString* GradonFile ;
    void MakeToolBar() ;
    void MakeContent();
    
    void ClearCanvas() ;
    
    void ChangePlatingMode();
    
    void ChangePointMode();
    
    void ChangeRraser();
    
    void ClickBrush();
    void ClickColor();
    void ClickEraser();
    ColorSprite* whiteCanvas;
    CCMenuItemSprite* brush;
    CCMenuItemSprite* color;
    CCMenuItemSprite* eraser ;
    
    CCControlButton* back ;
    CCControlButton* camerabtu ;
    CCSprite* toolsBg;
    CCMenu* closeMenu ;
    
};

#endif /* ColorCanvasView_hpp */
