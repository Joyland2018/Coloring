//
//  ColorNode.h
//  DrDino
//
//  Created by 李晓飞 on 2023/2/10.
//

#ifndef ColorNode_h
#define ColorNode_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ColorNode : public Node {
    
    
public:
    static ColorNode* createColorNode(Size _nodeSize);
    
    Sprite* testSimpleBrush;
    RenderTexture* testSimpleRender;
    Sprite* testBrush;
    ClippingNode* clippingNode;
    
    void changeTestBrush();
    void changeTestColor();
    
    void initBrushNode();
    
    void testBrushing(Vec2 _testPos);
};

#endif /* ColorNode_h */
