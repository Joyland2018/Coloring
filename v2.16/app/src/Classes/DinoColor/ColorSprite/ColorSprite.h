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
    ccColor3B pointColor;
    CCPoint pointPos;
    std::string parentSprName;
    int brushTag;
    int colorTag;
};

class ColorSprite : public cocos2d::CCSprite {
    
    
public:

    static ColorSprite* CreateColor(const char* spName,CCPoint pos ,CCNode* parent,int ptag);
//    bool isTouched(cocos2d::CCTouch *pTouch);
//    void PlatingSprite(ccColor3B color, CCRenderTexture* canvas);
//    bool CheckAlpha(CCPoint point);
    
    std::string curSprName;
    CCDrawNode* m_EraserDrawer ;
    
    CCDrawNode* pencilNode;
    CCDrawNode* paintNode;
    CCDrawNode* brushNode;
    CCRenderTexture* brushRender;
    CCSprite* clippingBrushSpr;
//    CCRenderTexture* testRender;
//    CCSprite* texture;
//    CCClippingNode* clippingNode;
//    CCNode* twoNode;
    
    std::vector<DrawingPointInfo> infoArr;
    
    CCArray* drawPoints;
    
    void changeBrush();
    void changeColor();
    
    void clearColorSpr();
    
    void initBrushNode();
    
    void toolsBrushing(CCPoint _brushPos, CCPoint _lastPos);
    
    void showLastSceneImage();
    
private:
    
    ColorSprite();
    virtual ~ColorSprite();
    
    CCPoint lastDotPos;
    
};

#endif /* ColorSprite_hpp */
