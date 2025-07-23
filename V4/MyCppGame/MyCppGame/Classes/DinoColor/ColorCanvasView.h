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
#include "ColorManager.hpp"
#include "ColorSprite/ColorSprite.h"
#include "ColorSprite/ColoringClippingNode.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension ;

#define kChangeBrushCallback "colorcanvas.changebrush"
#define kChangeColorCallback "colorcanvas.changecolor"
#define kShowPenColorIapCallback "colorcanvas.showpeniap"

class ColorCanvasView : public cocos2d:: CCLayer {
    
    
public:
    CCSize v_size ;
    CCPoint poszero;
    CCArray* m_DrawArray ;
    CCArray* m_ClipDrawArray ;
    
    CCRenderTexture *m_pCanvas;
    CCSprite *m_pBrush;
    ColorSprite* m_DrawingSp;
    ColoringClippingNode* m_ClippingNode;
    
    std::string ButtonNames[6];
    float selectPosY;
    bool touchedButton;

    bool  buyState;
    CREATE_FUNC(ColorCanvasView);
    virtual bool init();
    static cocos2d::CCScene* scene();
    virtual void onEnter();
    virtual void onExit();
    
    //virtual void onExit();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    void UpdateChooseColor() ;
    void backClick();
    void camera();
    
    void changeBrushCallback();
    void changeColorCallback();
    void clickPenButton(CCObject *sender);
    void showColorBoard();
    
    void canTouchButton();
    void selectAdsOrIAP();
    
    void penParticleAction(CCPoint parPos);
    
    void resetColorValue();

    float w_fix;
//    int curSelectBrush[5];
    bool selectRaser;
    
    CCPoint curParPos;
    bool clickEraser;
    
    bool showParColor;
private:
    CCString* DinoColor ;
    CCString* GradonFile ;
    void MakeToolBar() ;
    void MakeContent();
    
    void ClearCanvas(CCObject* pSender) ;
    
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
    CCMenuItemSprite* Delete;
    
    CCControlButton* back ;
    CCControlButton* camerabtu ;
    CCSprite* toolsBg;
    CCMenu* closeMenu ;
    
    CCPoint toolsBgInitPos;
    CCPoint brushBtnPos;
    CCPoint colorBtnPos;
    CCPoint eraserBtnPos;
    CCPoint toolsMenuPos;
    
    void removeNouesImage();
    void ImageVisible();
    
    void showToolsBoard();
    void hideToolsBoard();
    
   
    
};

#endif /* ColorCanvasView_hpp */
