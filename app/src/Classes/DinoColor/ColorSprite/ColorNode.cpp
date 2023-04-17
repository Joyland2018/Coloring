//
//  ColorNode.cpp
//  DrDino
//
//  Created by 李晓飞 on 2023/2/10.
//

#include "ColorNode.h"
#include "ColorManager.hpp"

ColorNode * ColorNode::createColorNode(CCSize _nodeSize)
{
    ColorNode * pRet = new ColorNode();
    if (pRet && pRet->init())
    {
        pRet->setContentSize(_nodeSize);
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void ColorNode::initBrushNode()
{
    CCSize sprSize = this->getContentSize();
//    ColorSprite* colorSpr = (ColorSprite*)this->getStencil();
//    if (colorSpr != NULL) {
//
    clippingNode = NULL;

        testBrush = CCSprite::create("makeup/makeupbrush.png");
        CC_SAFE_RETAIN(testBrush);
//        testBrush->setColor(ccRED);
        testBrush->setOpacity(20);
        testBrush->setScale(0.5);
//    this->addChild(testBrush);
//    }
    CCNode* twoNode = CCNode::create();
    this->addChild(twoNode);
    
    CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
    CC_SAFE_RETAIN(firstRender);
    firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
    twoNode->addChild(firstRender);
    
    testSimpleRender = firstRender;
    
    testSimpleBrush = CCSprite::create("DinoColor/paint_brush/paint_brush_1.png");
    CC_SAFE_RETAIN(testSimpleBrush);
//    m_Drawer->drawDot(start, line_w, color);
}

void ColorNode::testBrushing(CCPoint _testPos)
{
    CCPoint touchPoint = this->convertToNodeSpace(_testPos);
    
    if (ColorManager::shared()->m_DrawType == Draw_Eraser) {
        testSimpleBrush->setColor(ccWHITE);
        testSimpleRender->begin();
        testSimpleBrush->setPosition(ccp(touchPoint.x, touchPoint.y));
        testSimpleBrush->visit();
        testSimpleRender->end();
    } else {
        
    //        colorSpr->testBrushing(_testPos);
    //        colorSpr->visit();
        
        switch (ColorManager::shared()->SelectBrushTag) {
            case 100:
            case 101:
            {
                testSimpleRender->begin();
                testSimpleBrush->setPosition(ccp(touchPoint.x, touchPoint.y));
                testSimpleBrush->visit();
                CCLog("testSimpleBrush ======> %d",ColorManager::shared()->SelectBrushTag);
                testSimpleRender->end();
            }
                break;
            case 102:
            {
                testSimpleRender->begin();
                testBrush->setPosition(ccp(touchPoint.x, touchPoint.y));
                testBrush->visit();
                testSimpleRender->end();
            }
                break;
        }
    }
}

void ColorNode::changeTestBrush()
{
    CCSize sprSize = this->getContentSize();
//    CCRenderTexture* render = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
////    clippingNode->setVisible(false);
//    render->begin();
//    testRender->visit();
//    testSimpleRender->visit();
//    render->end();
//    render->cleanup();
//    this->setTexture(render->getSprite()->getTexture());
//    clippingNode->setVisible(true);
    switch (ColorManager::shared()->SelectBrushTag) {
        case 100:
        {
            testSimpleRender = NULL;
            clippingNode = NULL;
//            testRender->clear(0, 0, 0, 0);
//            clippingNode->setZOrder(1);
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("makeup/makeupbrush.png");
            testSimpleBrush->setTexture(texture);
            testSimpleBrush->setColor(ccBLUE);
            CCNode* twoNode = CCNode::create();
            this->addChild(twoNode);
            
            CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
            CC_SAFE_RETAIN(firstRender);
            firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
            twoNode->addChild(firstRender);
            
            testSimpleRender = firstRender;
//            twoNode->setZOrder(12);
            CCLog("select Brush 100======> %d",ColorManager::shared()->SelectBrushTag);
        }
            break;
        case 101:
        {
            testSimpleRender = NULL;
            clippingNode = NULL;
//            testRender->clear(0, 0, 0, 0);
//            clippingNode->setZOrder(1);
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("DinoColor/paint_brush/paint_brush_1.png");
            testSimpleBrush->setTexture(texture);
            testSimpleBrush->setColor(ColorManager::shared()->m_pColor);
            CCNode* twoNode = CCNode::create();
            this->addChild(twoNode);
            
            CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
            CC_SAFE_RETAIN(firstRender);
            firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
            twoNode->addChild(firstRender);
            
            testSimpleRender = firstRender;
//            twoNode->setZOrder(12);
            CCLog("select Brush ======> %d",ColorManager::shared()->SelectBrushTag);
        }
            break;
        case 102:
        {
            
            if (clippingNode == NULL) {
                testSimpleRender = NULL;
                
                CCSprite* texture = CCSprite::create("DinoColor/paintingroller_texture/paintingroller_texture_1.png");
                texture->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                CCNode* newNode = CCNode::create();
                
                clippingNode = CCClippingNode::create(newNode);
                clippingNode->setInverted(false);
                clippingNode->setAlphaThreshold(0.0f);
                
                clippingNode->addChild(texture);
                this->addChild(clippingNode);
            //    clippingNode->setVisible(false);
                
                    CCRenderTexture* testRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
                    CC_SAFE_RETAIN(testRender);
                    testRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                    newNode->addChild(testRender);
                
                testSimpleRender = testRender;
            }
//            testSimpleRender->clear(0, 0, 0, 0);
        }
            break;
    }
}

void ColorNode::changeTestColor()
{
    CCSize sprSize = this->getContentSize();
    switch (ColorManager::shared()->SelectBrushTag) {
        case 100:
        case 101:
        {
            ccColor3B newColor = ColorManager::shared()->m_pColor;
            
            testSimpleBrush->setColor(newColor);
        }
            break;
        case 102:
        {
            if (clippingNode != NULL) {
                
                if (ColorManager::shared()->SelectColorTag[2] == 102) {
                    CCSprite* texture = CCSprite::create("DinoColor/paintingroller_texture/paintingroller_texture_1.png");
                    texture->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                    clippingNode->addChild(texture);
                } else {
                    CCSprite* texture = CCSprite::create("DinoColor/crayon_texture/crayon_texture_1.png");
                    texture->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                    clippingNode->addChild(texture);
                }
            }
        }
            break;
    }
}



