//
//  ColoringClippingNode.cpp
//  DrDino
//
//  Created by 李晓飞 on 2023/2/3.
//

#include "ColoringClippingNode.h"
#include "ColorSprite.h"

ColoringClippingNode* ColoringClippingNode::create(Node *pStencil)
{
    ColoringClippingNode *pRet = new ColoringClippingNode();
    if (pRet && pRet->init(pStencil))
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = nullptr;
    }
    
    return pRet;
}

ColoringClippingNode::ColoringClippingNode(){
    
}

ColoringClippingNode::~ColoringClippingNode()
{
    
}

void ColoringClippingNode::initClippingNode()
{
        Size sprSize = this->getContentSize();
    ////    ColorSprite* colorSpr = (ColorSprite*)this->getStencil();
    ////    if (colorSpr != NULL) {
    ////
    //        testRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
    //        CC_SAFE_RETAIN(testRender);
    //        testRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
    //        this->addChild(testRender);
    //
    //        testBrush = CCSprite::create("DinoColor/paint_brush/paint_brush_1.png");
    //        CC_SAFE_RETAIN(testBrush);
    //        testBrush->setColor(ccRED);
    //        testBrush->setOpacity(20);
    //        testBrush->setScale(0.5);
    ////        this->addChild(testBrush);
    ////    }
    
    
}

void ColoringClippingNode::toolsBrushing(Vec2 _brushPos, Vec2 _lastPos)
{
    ColorSprite* colorSpr = (ColorSprite*)this->getChildByTag(20);
    if (colorSpr != NULL) {
        colorSpr->toolsBrushing(_brushPos,_lastPos);
//        CCPoint touchPoint = this->convertToNodeSpace(_testPos);
//        
//        testRender->begin();
////        colorSpr->testBrushing(_testPos);
////        colorSpr->visit();
//        testBrush->setPosition(ccp(touchPoint.x, touchPoint.y));
//        testBrush->visit();
//        testRender->end();
    }
}

bool ColoringClippingNode::isTouched(cocos2d::Touch *pTouch)
{
    bool isTouched = false;
    Vec2 touchPointInView = pTouch->getLocationInView();
    Vec2 glPoint = Director::getInstance()->convertToGL(touchPointInView);
    isTouched = this->CheckAlpha(glPoint);
    return isTouched;
}

bool ColoringClippingNode::CheckAlpha(Vec2 point)
{
    bool isTouched = false;
//    Vec2 posInParent = ((Sprite*)this->getParent())->convertToNodeSpace(point);
    ColorSprite* stencilSpr = (ColorSprite*)this->getStencil();
    if (this->getBoundingBox().containsPoint(point) && stencilSpr) {
        //this->setOpacity(100);
        int8_t data[4];
        Vec2 touchPoint = this->convertToNodeSpace(point);
        Vec2 location = Vec2((touchPoint.x), (touchPoint.y) );
        RenderTexture* renderTexture = RenderTexture::create(1,1,backend::PixelFormat::RGBA8888);
        renderTexture->beginWithClear(0,0,0,0);//只保存渲染一个像素的数据
        Vec2 oldPos = stencilSpr->getPosition();
        Vec2 oldAnchor = stencilSpr->getAnchorPoint();
        stencilSpr->setAnchorPoint(Vec2(0,0));
        stencilSpr->setPosition(Vec2(-location.x, -location.y));
        stencilSpr->visit();
        stencilSpr->setAnchorPoint(oldAnchor);
        stencilSpr->setPosition(oldPos);
        glReadPixels(0,0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        renderTexture->end();
        renderTexture->release();
        if(data[3])
        {
           
            isTouched = true;
            
        }
    }
        return isTouched ;
}



