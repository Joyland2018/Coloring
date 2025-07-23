//
//  ColorSprite.hpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#ifndef ColorSprite_hpp
#define ColorSprite_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;

struct DrawingPointInfo {
    Color3B pointColor;
    Vec2 pointPos;
    std::string parentSprName;
    int brushTag;
    int colorTag;
};

class ColorSprite : public cocos2d::Sprite {
    
    
public:

    static ColorSprite* CreateColor(const char* spName, Vec2 pos, Node* parent, int ptag);
//    bool isTouched(cocos2d::Touch *pTouch);
//    void PlatingSprite(Color3B color, RenderTexture* canvas);
//    bool CheckAlpha(Vec2 point);
    
    std::string curSprName;
    DrawNode* m_EraserDrawer ;
    
    DrawNode* pencilNode;
    DrawNode* paintNode;
    DrawNode* brushNode;
    RenderTexture* brushRender;
    Sprite* clippingBrushSpr;
//    RenderTexture* testRender;
//    Sprite* texture;
//    ClippingNode* clippingNode;
//    Node* twoNode;
    
    std::vector<DrawingPointInfo> infoArr;
    
    Vector<Node*> drawPoints;
    
    void changeBrush();
    void changeColor();
    
    void clearColorSpr();
    
    void initBrushNode();
    
    void toolsBrushing(Vec2 _brushPos, Vec2 _lastPos);
    
    void showLastSceneImage();
    
private:
    
    ColorSprite();
    virtual ~ColorSprite();
    
    Vec2 lastDotPos;
    
};

#endif /* ColorSprite_hpp */
