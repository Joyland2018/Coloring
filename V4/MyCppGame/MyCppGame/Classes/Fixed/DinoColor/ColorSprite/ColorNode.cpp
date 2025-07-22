//
//  ColorNode.cpp
//  DrDino
//
//  Created by 李晓飞 on 2023/2/10.
//

#include "ColorNode.h"
#include "../ColorManager.hpp"

ColorNode * ColorNode::createColorNode(Size _nodeSize)
{
    ColorNode * pRet = new ColorNode();
    if (pRet && pRet->init())
    {
        pRet->setContentSize(_nodeSize);
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}

void ColorNode::initBrushNode()
{
    Size sprSize = this->getContentSize();
//    ColorSprite* colorSpr = (ColorSprite*)this->getStencil();
//    if (colorSpr != NULL) {
//
    clippingNode = NULL;

        testBrush = Sprite::create("makeup/makeupbrush.png");
        testBrush->retain();
//        testBrush->setColor(Color3B::RED);
        testBrush->setOpacity(20);
        testBrush->setScale(0.5);
//    this->addChild(testBrush);
//    }
    Node* twoNode = Node::create();
    this->addChild(twoNode);
    
    RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
    firstRender->retain();
    firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
    twoNode->addChild(firstRender);
    
    testSimpleRender = firstRender;
    
    testSimpleBrush = Sprite::create("DinoColor/paint_brush/paint_brush_1.png");
    testSimpleBrush->retain();
//    m_Drawer->drawDot(start, line_w, color);
}

void ColorNode::testBrushing(Vec2 _testPos)
{
    Vec2 touchPoint = this->convertToNodeSpace(_testPos);
    
    if (ColorManager::shared()->m_DrawType == Draw_Eraser) {
        testSimpleBrush->setColor(Color3B::WHITE);
        testSimpleRender->begin();
        testSimpleBrush->setPosition(Vec2(touchPoint.x, touchPoint.y));
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
                testSimpleBrush->setPosition(Vec2(touchPoint.x, touchPoint.y));
                testSimpleBrush->visit();
                CCLOG("testSimpleBrush ======> %d",ColorManager::shared()->SelectBrushTag);
                testSimpleRender->end();
            }
                break;
            case 102:
            {
                testSimpleRender->begin();
                testBrush->setPosition(Vec2(touchPoint.x, touchPoint.y));
                testBrush->visit();
                testSimpleRender->end();
            }
                break;
        }
    }
}

void ColorNode::changeTestBrush()
{
    Size sprSize = this->getContentSize();
//    RenderTexture* render = RenderTexture::create(sprSize.width, sprSize.height, Texture2D::PixelFormat::RGBA8888);
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
            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("makeup/makeupbrush.png");
            testSimpleBrush->setTexture(texture);
            testSimpleBrush->setColor(Color3B::BLUE);
            Node* twoNode = Node::create();
            this->addChild(twoNode);
            
            RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
            firstRender->retain();
            firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
            twoNode->addChild(firstRender);
            
            testSimpleRender = firstRender;
//            twoNode->setZOrder(12);
            CCLOG("select Brush 100======> %d",ColorManager::shared()->SelectBrushTag);
        }
            break;
        case 101:
        {
            testSimpleRender = NULL;
            clippingNode = NULL;
//            testRender->clear(0, 0, 0, 0);
//            clippingNode->setZOrder(1);
            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("DinoColor/paint_brush/paint_brush_1.png");
            testSimpleBrush->setTexture(texture);
            testSimpleBrush->setColor(ColorManager::shared()->m_pColor);
            Node* twoNode = Node::create();
            this->addChild(twoNode);
            
            RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
            firstRender->retain();
            firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
            twoNode->addChild(firstRender);
            
            testSimpleRender = firstRender;
//            twoNode->setZOrder(12);
            CCLOG("select Brush ======> %d",ColorManager::shared()->SelectBrushTag);
        }
            break;
        case 102:
        {
            
            if (clippingNode == NULL) {
                testSimpleRender = NULL;
                
                Sprite* texture = Sprite::create("DinoColor/paintingroller_texture/paintingroller_texture_1.png");
                texture->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                Node* newNode = Node::create();
                
                clippingNode = ClippingNode::create(newNode);
                clippingNode->setInverted(false);
                clippingNode->setAlphaThreshold(0.0f);
                
                clippingNode->addChild(texture);
                this->addChild(clippingNode);
            //    clippingNode->setVisible(false);
                
                    RenderTexture* testRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
                    testRender->retain();
                    testRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
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
    Size sprSize = this->getContentSize();
    switch (ColorManager::shared()->SelectBrushTag) {
        case 100:
        case 101:
        {
            Color3B newColor = ColorManager::shared()->m_pColor;
            
            testSimpleBrush->setColor(newColor);
        }
            break;
        case 102:
        {
            if (clippingNode != NULL) {
                
                if (ColorManager::shared()->SelectColorTag[2] == 102) {
                    Sprite* texture = Sprite::create("DinoColor/paintingroller_texture/paintingroller_texture_1.png");
                    texture->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                    clippingNode->addChild(texture);
                } else {
                    Sprite* texture = Sprite::create("DinoColor/crayon_texture/crayon_texture_1.png");
                    texture->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                    clippingNode->addChild(texture);
                }
            }
        }
            break;
    }
}



