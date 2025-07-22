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

class ColoringClippingNode : public ClippingNode {
private:
    
    ColoringClippingNode();
    virtual ~ColoringClippingNode();
    
public:
    static ColoringClippingNode* create(Node *pStencil);
    
//    Sprite* testBrush;
//    RenderTexture* testRender;
    
    void initClippingNode();
    void toolsBrushing(Vec2 _brushPos, Vec2 _lastPos);
    bool isTouched(cocos2d::Touch *pTouch);
    bool CheckAlpha(Vec2 point);
};

#endif /* ColoringClippingNode_h */
