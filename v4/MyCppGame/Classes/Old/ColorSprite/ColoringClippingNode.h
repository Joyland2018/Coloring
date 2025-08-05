//
//  ColoringClippingNode.h
//  DrDino
//
//  Created by 李晓飞 on 2023/2/3.
//

#ifndef ColoringClippingNode_h
#define ColoringClippingNode_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ColoringClippingNode : public CCClippingNode {
private:
    
    ColoringClippingNode();
    virtual ~ColoringClippingNode();
    
public:
    static ColoringClippingNode* create(CCNode *pStencil);
    
//    CCSprite* testBrush;
//    CCRenderTexture* testRender;
    
    void initClippingNode();
    void toolsBrushing(CCPoint _brushPos, CCPoint _lastPos);
    bool isTouched(cocos2d::CCTouch *pTouch);
    bool CheckAlpha(CCPoint point);
    
    void cancelLastBrushInNode();
    void saveLastBrushInNode();
    void removeFirstBrushInNode();
    void removeAllBrushArrInNode();
};

#endif /* ColoringClippingNode_h */
