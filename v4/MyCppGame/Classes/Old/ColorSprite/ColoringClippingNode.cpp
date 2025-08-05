//
//  ColoringClippingNode.cpp
//  DrDino
//
//  Created by 李晓飞 on 2023/2/3.
//

#include "ColoringClippingNode.h"
#include "ColorSprite.h"

ColoringClippingNode* ColoringClippingNode::create(CCNode *pStencil)
{
    ColoringClippingNode *pRet = new ColoringClippingNode();
    if (pRet && pRet->init(pStencil))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
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
        CCSize sprSize = this->getContentSize();
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

void ColoringClippingNode::toolsBrushing(CCPoint _brushPos, CCPoint _lastPos)
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

void ColoringClippingNode::saveLastBrushInNode(){
    ColorSprite* colorSpr = (ColorSprite*)this->getChildByTag(20);
    if (colorSpr != NULL) {
        colorSpr->saveLastBrushInSpr();
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

void ColoringClippingNode::cancelLastBrushInNode(){
    ColorSprite* colorSpr = (ColorSprite*)this->getChildByTag(20);
    if (colorSpr != NULL) {
        colorSpr->cancelLastBrushInSpr();
        colorSpr->changeBrush();
    }
}

void ColoringClippingNode::removeFirstBrushInNode(){
    ColorSprite* colorSpr = (ColorSprite*)this->getChildByTag(20);
    if (colorSpr != NULL) {
        colorSpr->removeFirstBrushInSpr();
    }
}

void ColoringClippingNode::removeAllBrushArrInNode(){
    ColorSprite* colorSpr = (ColorSprite*)this->getChildByTag(20);
    if (colorSpr != NULL) {
        colorSpr->removeAllBrushArrInSpr();
    }
}

bool ColoringClippingNode::isTouched(cocos2d::CCTouch *pTouch)
{
    bool isTouched = false;
    CCPoint touchPointInView = pTouch->getLocationInView();
    CCPoint glPoint = CCDirector::sharedDirector()->convertToGL(touchPointInView);
    isTouched = this->CheckAlpha(glPoint);
    return isTouched;
}

bool ColoringClippingNode::CheckAlpha(CCPoint point)
{
    bool isTouched = false;
//    CCPoint posInParent = ((CCSprite*)this->getParent())->convertToNodeSpace(point);
    ColorSprite* stencilSpr = (ColorSprite*)this->getStencil();
    if (this->boundingBox().containsPoint(point) && stencilSpr) {
        //this->setOpacity(100);
        int8_t data[4];
        CCPoint touchPoint = this->convertToNodeSpace(point);
        CCPoint location = CCPoint((touchPoint.x), (touchPoint.y) );
        CCRenderTexture* renderTexture = CCRenderTexture::create(1,1,kCCTexture2DPixelFormat_RGBA8888);
        renderTexture->beginWithClear(0,0,0,0);//只保存渲染一个像素的数据
        CCPoint oldPos = stencilSpr->getPosition();
        CCPoint oldAnchor = stencilSpr->getAnchorPoint();
        stencilSpr->setAnchorPoint(CCPoint(0,0));
        stencilSpr->setPosition(ccp(-location.x, -location.y));
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



