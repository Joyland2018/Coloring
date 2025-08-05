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
#include "ColorSprite.h"
#include "ColoringClippingNode.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension ;

#define kChangeBrushCallback "colorcanvas.changebrush"
#define kChangeColorCallback "colorcanvas.changecolor"
#define kShowPenColorIapCallback "colorcanvas.showpeniap"
#define kChangeBrushColorCallback "colorcanvas.changebrushcolor"

class ColorCanvasView : public cocos2d:: CCLayer {
    
    
public:
    CCSize v_size ;
    CCPoint poszero;
    CCArray* m_DrawArray ;
    CCArray* m_ClipDrawArray ;
    CCArray* last_ClipNodeArray;
    
    CCRenderTexture *m_pCanvas;
    CCSprite *m_pBrush;
    ColorSprite* m_DrawingSp;
    ColoringClippingNode* m_ClippingNode;
    ColoringClippingNode* last_ClippingNode;
    
    std::string ButtonNames[6];
    float selectPosY;
//    bool touchedButton;
    
    
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
    
    void cancelLastBrush();
    void saveLastBrush(ColoringClippingNode* _saveColoringNode);
    
    void changeBrushColorCallback();
    
    //book按钮
    void openBookPage();
    void showBookPageBtn(int pageId);
    void checkIsCanShowLayer();
    
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
    
    void onClickPrintBtn(CCObject* obj);
    void onPrintCurScene(CCObject* obj);
    void callPrintImage(float dt);
    
    void hideAllButtons();
    void showAllButtons();
    
    void showFirstGuide();
    void resetGuideFingerPos();
    void removeFirstGuide();
    
    ColorSprite* whiteCanvas;
    CCMenuItemSprite* brush;
    CCMenuItemSprite* color;
    CCMenuItemSprite* eraser ;
    CCMenuItemSprite* Delete;
    
    CCControlButton* back ;
    CCMenu* camerabtu ;
    CCSprite* toolsBg;
    CCMenu* closeMenu ;
    CCMenu* deleteMenu;
    CCMenu* printMenu;
    
    CCPoint toolsBgInitPos;
    CCPoint brushBtnPos;
    CCPoint colorBtnPos;
    CCPoint eraserBtnPos;
    CCPoint toolsMenuPos;
    
    void removeNouesImage();
    void ImageVisible();
    
    void showToolsBoard();
    void hideToolsBoard();
    
    void createParentsLock();
    void parentsLockCallback(CCObject *sender);
    void clearLock();
    int gameRand;
    int locknum[3];
    int accessnum[3];
    int accessIndex;
};

#endif /* ColorCanvasView_hpp */
