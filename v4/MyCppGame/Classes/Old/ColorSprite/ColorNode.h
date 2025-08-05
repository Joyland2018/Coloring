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

class ColorNode : public CCNode {
    
    
public:
    static ColorNode* createColorNode(CCSize _nodeSize);
    
    CCSprite* testSimpleBrush;
    CCRenderTexture* testSimpleRender;
    CCSprite* testBrush;
    CCClippingNode* clippingNode;
    
    void changeTestBrush();
    void changeTestColor();
    
    void initBrushNode();
    
    void testBrushing(CCPoint _testPos);
};

#endif /* ColorNode_h */
