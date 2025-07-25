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
#include "AudioEngine.h"
#include <iostream>
#include "ColorManager.hpp"
#include "ColorSprite/ColorSprite.h"
#include "ColorSprite/ColoringClippingNode.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

#define kChangeBrushCallback "colorcanvas.changebrush"
#define kChangeColorCallback "colorcanvas.changecolor"
#define kShowPenColorIapCallback "colorcanvas.showpeniap"

class ColorCanvasView : public cocos2d::Layer {
    
    
public:
    Size v_size ;
    Vec2 poszero;
    Vector<Node*> m_DrawArray ;
    Vector<Node*> m_ClipDrawArray ;
    
    RenderTexture *m_pCanvas;
    Sprite *m_pBrush;
    ColorSprite* m_DrawingSp;
    ColoringClippingNode* m_ClippingNode;
    
    std::string ButtonNames[6];
    float selectPosY;
    bool touchedButton;

    bool  buyState;
    CREATE_FUNC(ColorCanvasView);
    virtual bool init();
    static cocos2d::Scene* scene();
    virtual void onEnter();
    virtual void onExit();
    
    //virtual void onExit();
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
    void UpdateChooseColor() ;
    void backClick();
    void camera();
    
    void changeBrushCallback();
    void changeColorCallback();
    void clickPenButton(Ref *sender);
    void showColorBoard();
    
    void canTouchButton();
    void selectAdsOrIAP();
    
    void penParticleAction(Vec2 parPos);
    
    void resetColorValue();

    float w_fix;
//    int curSelectBrush[5];
    bool selectRaser;
    
    Vec2 curParPos;
    bool clickEraser;
    
    bool showParColor;
private:
    std::string DinoColor ;
    std::string GradonFile ;
    void MakeToolBar() ;
    void MakeContent();
    
    void ClearCanvas(Ref* pSender) ;
    
    void ChangePlatingMode();
    
    void ChangePointMode();
    
    void ChangeRraser();
    
    void ClickBrush();
    void ClickColor();
    void ClickEraser();
    ColorSprite* whiteCanvas;
    MenuItemSprite* brush;
    MenuItemSprite* color;
    MenuItemSprite* eraser ;
    MenuItemSprite* Delete;
    
    Button* back ;
    Button* camerabtu ;
    Sprite* toolsBg;
    Menu* closeMenu ;
    
    Vec2 toolsBgInitPos;
    Vec2 brushBtnPos;
    Vec2 colorBtnPos;
    Vec2 eraserBtnPos;
    Vec2 toolsMenuPos;
    
    void removeNouesImage();
    void ImageVisible(float dt);
    
    void showToolsBoard();
    void hideToolsBoard();
    
   
    
};

#endif /* ColorCanvasView_hpp */
