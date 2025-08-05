//
//  ColorSprite.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#include "ColorSprite.h"
#include "ColorManager.hpp"
#include "GameManager.h"

#define LAST_TEXTURE 131

enum{
    
};

ColorSprite* ColorSprite::CreateColor(const char* spName, CCPoint pos, CCNode *parent, int ptag)
{
    ColorSprite* sprite = new ColorSprite();
    
    if (sprite && sprite->initWithFile(spName)) {
        sprite->autorelease();
        sprite->setPosition(pos);
        sprite->setTag(ptag);
        sprite->curSprFileName = spName;
        sprite->curSprName = "";
        sprite->brushRender = NULL;
        sprite->m_EraserDrawer = NULL;
        sprite->clippingBrushSpr = NULL;
        sprite->testBrushNode = NULL;
        sprite->lastTextureArr = CCArray::create();
        CC_SAFE_RETAIN(sprite->lastTextureArr);
        
//        sprite->testRender = CCRenderTexture::create(sprite->getContentSize().width, sprite->getContentSize().height, kCCTexture2DPixelFormat_RGBA8888);
//        CC_SAFE_RETAIN(sprite->testRender);
//        sprite->testRender->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
//        sprite->addChild(sprite->testRender);
//
//        sprite->testBrush = CCSprite::create("DinoColor/paint_brush/paint_brush_1.png");
//        CC_SAFE_RETAIN(sprite->testBrush);
//        sprite->testBrush->setColor(ccRED);
//        sprite->testBrush->setOpacity(20);
//        sprite->testBrush->setScale(0.5);
//
//        parent->addChild(sprite);
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    sprite = NULL;
    return NULL ;
}

//void ColorSprite::PlatingSprite(ccColor3B color, CCRenderTexture *canvas)
//{
//    this->setColor(ccRED);
//    this->setOpacity(255);
//    canvas->begin();
//    this->visit();
//    canvas->end();
//    this->setOpacity(0);
//}
//
//bool ColorSprite::isTouched(cocos2d::CCTouch *pTouch)
//{
//    bool isTouched = false;
//    CCPoint touchPointInView = pTouch->getLocationInView();
//    CCPoint glPoint = CCDirector::sharedDirector()->convertToGL(touchPointInView);
//    isTouched = this->CheckAlpha(glPoint);
//    return isTouched;
//}
//
//bool ColorSprite::CheckAlpha(CCPoint point)
//{
//    bool isTouched = false;
//    CCPoint posInParent = ((CCSprite*)this->getParent())->convertToNodeSpace(point);
//    if (this->boundingBox().containsPoint(posInParent)) {
//        //this->setOpacity(100);
//        int8_t data[4];
//        CCPoint touchPoint = this->convertToNodeSpace(point);
//        CCPoint location = CCPoint((touchPoint.x), (touchPoint.y) );
//        CCRenderTexture* renderTexture = CCRenderTexture::create(1,1,kCCTexture2DPixelFormat_RGBA8888);
//        renderTexture->beginWithClear(0,0,0,0);//只保存渲染一个像素的数据
//        CCPoint oldPos = this->getPosition();
//        CCPoint oldAnchor = this->getAnchorPoint();
//        this->setAnchorPoint(CCPoint(0,0));
//        this->setPosition(ccp(-location.x, -location.y));
//        this->visit();
//        this->setAnchorPoint(oldAnchor);
//        this->setPosition(oldPos);
//        glReadPixels(0,0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        renderTexture->end();
//        renderTexture->release();
//        if(data[3])
//        {
//           
//            isTouched = true;
//            
//        }
//    }
//        return isTouched ;
//}

ColorSprite::ColorSprite()
{
    
}

ColorSprite::~ColorSprite()
{
    if (m_EraserDrawer != NULL) {
        CC_SAFE_RELEASE(m_EraserDrawer);
        m_EraserDrawer = NULL;
    }
    if (clippingBrushSpr != NULL) {
        CC_SAFE_RELEASE(clippingBrushSpr);
        clippingBrushSpr = NULL;
    }
    if (pencilNode != NULL) {
//        CC_SAFE_RELEASE(pencilNode);
        pencilNode = NULL;
    }
    if (brushNode != NULL) {
//        CC_SAFE_RELEASE(brushNode);
        brushNode = NULL;
    }
    
    if (lastTextureArr != NULL) {
        CC_SAFE_RELEASE(lastTextureArr);
        lastTextureArr = NULL;
    }
}

void ColorSprite::initBrushNode()
{
    CCSize sprSize = this->getContentSize();
//    ColorSprite* colorSpr = (ColorSprite*)this->getStencil();
//    if (colorSpr != NULL) {
//
//    clippingNode = NULL;
    

    if (ColorManager::shared()->m_DrawType == Draw_Eraser && m_EraserDrawer == NULL) {
        m_EraserDrawer = CCDrawNode::create();
        m_EraserDrawer->drawDot(CCPointZero, 30, ccc4f(1.0, 1.0, 1.0, 1.0));
        CC_SAFE_RETAIN(m_EraserDrawer);
    }
    
    pencilNode = NULL;
    pencilNode = CCDrawNode::create();
    this->addChild(pencilNode);
    lastDotPos = CCPointZero;
//    pencilNode = CCDrawNode::create();
//    pencilNode->drawDot(CCPointZero, 5, ccc4f(1.0, 1.0, 1.0, 1.0));
////    this->addChild(pencilNode);
//    CC_SAFE_RETAIN(pencilNode);
//    this->addChild(testBrush);
//    }
    
    paintNode = NULL;
    paintNode = CCDrawNode::create();
    this->addChild(paintNode);
//    CC_SAFE_RETAIN(paintNode);
    
    brushNode = NULL;
    brushNode = CCDrawNode::create();
//    CC_SAFE_RETAIN(brushNode);
//    this->addChild(paintNode);
    
    CCNode* twoNode = CCNode::create();
    this->addChild(twoNode);
    
    CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
    firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
    twoNode->addChild(firstRender);
    
    brushRender = firstRender;
    
    if (clippingBrushSpr == NULL) {
        
        clippingBrushSpr = CCSprite::create("DinoColor/brushs/normal_brush.png");
        int curColorIndex = ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100];
        ColorManager::shared()->getCurColor(curColorIndex);
        
        clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
        CC_SAFE_RETAIN(clippingBrushSpr);
    }
//    m_Drawer->drawDot(start, line_w, color);
    
}

void ColorSprite::showLastSceneImage(){
    CCImage* lastSceneImage = ColorManager::shared()->loadImageFromBinaryFile(this->curSprName);
    
    if (lastSceneImage != NULL) {
        
        CCTexture2D* lastSceneTexture = new CCTexture2D();
        if (lastSceneTexture && lastSceneTexture->initWithImage(lastSceneImage)) {
            
            CCSprite* lastSceneSpr = CCSprite::createWithTexture(lastSceneTexture);
            lastSceneSpr->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
            lastSceneSpr->setTag(LAST_TEXTURE);
            this->addChild(lastSceneSpr);
            
            CC_SAFE_RELEASE(lastSceneTexture);
        }
        
        CC_SAFE_RELEASE(lastSceneImage);
    }
}

void ColorSprite::toolsBrushing(CCPoint _brushPos, CCPoint _lastPos)
{
    CCPoint touchPoint = this->convertToNodeSpace(_brushPos);
    CCPoint lastTouchPoint = this->convertToNodeSpace(_lastPos);
    clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
    if (ColorManager::shared()->m_DrawType == Draw_Eraser) {
        brushRender->begin();
        m_EraserDrawer->setPosition(ccp(touchPoint.x, touchPoint.y));
        m_EraserDrawer->visit();
        brushRender->end();
    } else {
        
    //        colorSpr->testBrushing(_testPos);
    //        colorSpr->visit();
        
        switch (ColorManager::shared()->SelectBrushTag) {
            case Brush_Pencil:
            {
//                brushRender->begin();
                if (!touchPoint.equals(lastTouchPoint)) {
                    pencilNode->drawSegment(lastTouchPoint, touchPoint, 6, ccc4FFromccc3B(ColorManager::shared()->m_pColor));
                }
                pencilNode->drawDot(touchPoint, 6, ccc4FFromccc3B(ColorManager::shared()->m_pColor));
//                pencilNode->visit();
//                brushRender->end();
//                lastDotPos = touchPoint;
            }
                break;
            case Brush_Paint:
            {
                
//                brushRender->begin();
//                paintNode->setBlendFunc((ccBlendFunc){GL_ONE,GL_DST_ALPHA});
                if (!touchPoint.equals(lastTouchPoint)) {
                    paintNode->drawSegment(lastTouchPoint, touchPoint, 20, ccc4FFromccc3B(ColorManager::shared()->m_pColor));
                }
                paintNode->drawDot(touchPoint, 20, ccc4FFromccc3B(ColorManager::shared()->m_pColor));
//                paintNode->visit();
//                clippingBrushSpr->setPosition(ccp(touchPoint.x, touchPoint.y));
//                clippingBrushSpr->visit();
//                brushRender->end();
//                brushRender->getSprite()->getTexture()->setAntiAliasTexParameters();
            }
                break;
            case Brush_Largebrush:
            {
                CCPoint curSprPoint = clippingBrushSpr->getPosition();
                float distance = ccpDistance(touchPoint, curSprPoint);
                if (distance > 13.0) {
                    
                    brushRender->begin();
                    clippingBrushSpr->setPosition(ccp(touchPoint.x, touchPoint.y));
                    clippingBrushSpr->visit();
                    CCLog("testSimpleBrush ======> %d",ColorManager::shared()->SelectBrushTag);
                    brushRender->end();
                }
            }
                break;
            case Brush_Crayon:
            {
//                brushRender->begin();
//                if (!touchPoint.equals(lastTouchPoint)) {
////                    brushNode->drawSegment(lastTouchPoint, touchPoint, 20, ccc4f(1.0, 1.0, 1.0, 1.0));
//                    brushNode->drawSegment(lastTouchPoint, touchPoint, 20,  ccc4FFromccc3B(ColorManager::shared()->m_pColor));
//                }
////                brushNode->drawDot(touchPoint, 20, ccc4f(1.0, 1.0, 1.0, 1.0));
//                brushNode->drawDot(touchPoint, 20,  ccc4FFromccc3B(ColorManager::shared()->m_pColor));
////                brushNode->setPosition(ccp(touchPoint.x, touchPoint.y));
//                brushNode->visit();
//                brushRender->end();
                
                CCPoint curSprPoint = clippingBrushSpr->getPosition();
                float distance = ccpDistance(touchPoint, curSprPoint);
                if (distance > 13.0) {
                    
                    brushRender->begin();
                    clippingBrushSpr->setPosition(ccp(touchPoint.x, touchPoint.y));
                    clippingBrushSpr->visit();
                    CCLog("testSimpleBrush ======> %d",ColorManager::shared()->SelectBrushTag);
                    brushRender->end();
                }
            }
                break;
            case Brush_Texture:
            {
//                if (testBrushNode != NULL) {
//                    CCNode* newNode = testBrushNode->getStencil();
//                    if (newNode != NULL) {
//                        CCSprite* brush = CCSprite::create("makeup/makeupbrush.png");
//                        brush->setPosition(ccp(touchPoint.x, touchPoint.y));
//                        newNode->addChild(brush);
//                    }
//                }
            }
                break;
        }
    }
}

void ColorSprite::changeBrush()
{
    CCSize sprSize = this->getContentSize();
    if (ColorManager::shared()->m_DrawType == Draw_Eraser) {
        if (m_EraserDrawer != NULL) {
//            m_EraserDrawer->removeFromParentAndCleanup(true);
            CC_SAFE_RELEASE(m_EraserDrawer);
            m_EraserDrawer = NULL;
        }
        
            
            m_EraserDrawer = CCDrawNode::create();
            m_EraserDrawer->drawDot(CCPointZero, 30, ccc4f(1.0, 1.0, 1.0, 1.0));
            CC_SAFE_RETAIN(m_EraserDrawer);
        if (brushRender != NULL) {
//            CC_SAFE_RELEASE(brushRender);
            brushRender = NULL;
        }
        CCNode* twoNode = CCNode::create();
        this->addChild(twoNode);
        
        CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//        CC_SAFE_RETAIN(firstRender);
        firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
        twoNode->addChild(firstRender);
        
        brushRender = firstRender;
    }else {
        switch (ColorManager::shared()->SelectBrushTag) {
            case Brush_Pencil:
            {
    //            brushRender = NULL;
                if (pencilNode != NULL) {
//                    CC_SAFE_RELEASE(pencilNode);
//                    pencilNode->removeFromParentAndCleanup(true);
                    pencilNode = NULL;
                }
                pencilNode = CCDrawNode::create();
                this->addChild(pencilNode);
                brushRender = NULL;
                CCNode* twoNode = CCNode::create();
                this->addChild(twoNode);
                
                CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//                CC_SAFE_RETAIN(firstRender);
                firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
                
                brushRender = firstRender;
            }
                break;
            case Brush_Paint:
            {
                if (paintNode != NULL) {
//                    CC_SAFE_RELEASE(paintNode);
//                    paintNode->removeFromParentAndCleanup(true);
                    paintNode = NULL;
                }
                paintNode = CCDrawNode::create();
                this->addChild(paintNode);
//                CC_SAFE_RETAIN(paintNode);
                brushRender = NULL;
                
//                CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("DinoColor/brushs/normal_brush.png");
//                clippingBrushSpr->setScale(1.0);
//                clippingBrushSpr->setTexture(texture);
//                clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
                CCNode* twoNode = CCNode::create();
                this->addChild(twoNode);
                
                CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//                CC_SAFE_RETAIN(firstRender);
                firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
                
                brushRender = firstRender;
                
            }
                break;
            case Brush_Largebrush:
            {
                if (brushRender != NULL) {
//                    CC_SAFE_RELEASE(brushRender);
                    brushRender = NULL;
                }
                
                CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("DinoColor/brushs/paint_brush.png");
                clippingBrushSpr->setTexture(texture);
                ccColor3B colorVal = ColorManager::shared()->m_pColor;
                clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
                CCNode* twoNode = CCNode::create();
                this->addChild(twoNode);
                
                CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//                CC_SAFE_RETAIN(firstRender);
                firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
                
                brushRender = firstRender;
                
            }
                break;
            case Brush_Crayon:
            {
                
    //            if (clippingNode == NULL) {
//                if (brushRender != NULL) {
//                    CC_SAFE_RELEASE(brushRender);
                    brushRender = NULL;
//                }
                
                CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("DinoColor/brushs/crayon_brush.png");
                clippingBrushSpr->setTexture(texture);
                ccColor3B colorVal = ColorManager::shared()->m_pColor;
                clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
                CCNode* twoNode = CCNode::create();
                this->addChild(twoNode);
                
                CCRenderTexture* firstRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//                CC_SAFE_RETAIN(firstRender);
                firstRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
//                brushNode = NULL;
//                brushNode = CCDrawNode::create();
////                brushNode->drawDot(CCPointZero, 20, ccc4f(1.0, 1.0, 1.0, 1.0));
//                CC_SAFE_RETAIN(brushNode);
//
//                CCPoint centerPosInWorld = GameManager::sharedManager()->getCenter();
//
//                CCPoint texturePos = this->convertToNodeSpace(centerPosInWorld);
//                CCLOG("---%d---",ColorManager::shared()->SelectColorTag[2]);
//                CCString* crayonTextNameStr = CCString::createWithFormat("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[2]);
//                CCSprite* texture = CCSprite::create(crayonTextNameStr->getCString());
//                texture->setPosition(ccp(texturePos.x, texturePos.y));
//                CCNode* newNode = CCNode::create();
//
//                CCClippingNode* clippingNode = CCClippingNode::create(newNode);
//                    clippingNode->setInverted(false);
//                    clippingNode->setAlphaThreshold(0.0f);
//
//                    clippingNode->addChild(texture);
//                    this->addChild(clippingNode);
//                //    clippingNode->setVisible(false);
//
//                        CCRenderTexture* testRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//                        CC_SAFE_RETAIN(testRender);
//                        testRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
//                        newNode->addChild(testRender);
                    
                brushRender = firstRender;
            }
                break;
            case Brush_Texture:
            {
//                CCPoint centerPosInWorld = GameManager::sharedManager()->getCenter();
//                
//                                CCPoint texturePos = this->convertToNodeSpace(centerPosInWorld);
//                int randIndex = arc4random()%10;
//                
//                const char* testFileName = "DinoColor/crayon_texture_7.png";
////                if (randIndex > 5) {
////                    testFileName = "DinoColor/crayon_texture_17.png";
////                }
//                
//                CCSprite* texture = CCSprite::create(testFileName);
//                                texture->setPosition(ccp(texturePos.x, texturePos.y));
//                                CCNode* newNode = CCNode::create();
//                
//                                CCClippingNode* clippingNode = CCClippingNode::create(newNode);
//                                    clippingNode->setInverted(false);
//                                    clippingNode->setAlphaThreshold(0.0f);
//                
//                                    clippingNode->addChild(texture);
//                                    this->addChild(clippingNode);
//                
//                testBrushNode = clippingNode;
            }
                break;
        }
    }
//    CCRenderTexture* render = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
////    clippingNode->setVisible(false);
//    render->begin();
//    testRender->visit();
//    testSimpleRender->visit();
//    render->end();
//    render->cleanup();
//    this->setTexture(render->getSprite()->getTexture());
//    clippingNode->setVisible(true);
    
}

void ColorSprite::changeColor()
{
    CCSize sprSize = this->getContentSize();
    switch (ColorManager::shared()->SelectBrushTag) {
        case Brush_Pencil:
        {
            if (pencilNode != NULL) {
                pencilNode->drawDot(CCPointZero, 5, ccc4FFromccc3B(ColorManager::shared()->m_pColor));
            }
        }
            break;
        case Brush_Paint:
        {
            if (paintNode != NULL) {
                paintNode->drawDot(CCPointZero, 20, ccc4FFromccc3B(ColorManager::shared()->m_pColor));
            }
        }
            break;
        case Brush_Largebrush:
        {
            if (clippingBrushSpr != NULL) {
                ccColor3B newColor = ColorManager::shared()->m_pColor;
                
                clippingBrushSpr->setColor(newColor);
            }
        }
            break;
        case Brush_Crayon:
        {
            if (clippingBrushSpr != NULL) {
                ccColor3B newColor = ColorManager::shared()->m_pColor;
                
                clippingBrushSpr->setColor(newColor);
            }
//            if (clippingNode != NULL) {
//            brushRender = NULL;
//            brushNode = NULL;
//            brushNode = CCDrawNode::create();
////            brushNode->drawDot(CCPointZero, 20, ccc4f(1.0, 1.0, 1.0, 1.0));
//            CC_SAFE_RETAIN(brushNode);
//            CCNode* newNode = CCNode::create();
//            CCPoint centerPosInWorld = GameManager::sharedManager()->getCenter();
//
//            CCPoint texturePos = this->convertToNodeSpace(centerPosInWorld);
//            CCString* crayonTextNameStr = CCString::createWithFormat("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[2]);
//
//            CCSprite* texture = CCSprite::create(crayonTextNameStr->getCString());
//            texture->setPosition(ccp(texturePos.x, texturePos.y));
//
//            CCClippingNode* clippingNode = CCClippingNode::create(newNode);
//            clippingNode->setInverted(false);
//            clippingNode->setAlphaThreshold(0.0f);
//
//            clippingNode->addChild(texture);
//            this->addChild(clippingNode);
//
//            CCRenderTexture* testRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
//            CC_SAFE_RETAIN(testRender);
//            testRender->setPosition(ccp(sprSize.width/2, sprSize.height/2));
//            newNode->addChild(testRender);
//
//            brushRender = testRender;
//            }
        }
            break;
        case Brush_Texture:
        {
//            testBrushNode = NULL;
//            CCPoint centerPosInWorld = GameManager::sharedManager()->getCenter();
//            
//                            CCPoint texturePos = this->convertToNodeSpace(centerPosInWorld);
//            CCSprite* texture = CCSprite::create("DinoColor/crayon_texture_17.png");
//                            texture->setPosition(ccp(texturePos.x, texturePos.y));
//                            CCNode* newNode = CCNode::create();
//            
//                            CCClippingNode* clippingNode = CCClippingNode::create(newNode);
//                                clippingNode->setInverted(false);
//                                clippingNode->setAlphaThreshold(0.0f);
//            
//                                clippingNode->addChild(texture);
//                                this->addChild(clippingNode);
//            
//            testBrushNode = clippingNode;
        }
            break;
    }
}

void ColorSprite::fillColorInSpr(const ccColor3B& _colorVal){
    
    CCSize sprSize = this->getContentSize();
    if (this->curSprFileName != "") {
        CCSprite* curFillingSpr = CCSprite::create(this->curSprFileName.c_str());
        if (curFillingSpr != NULL) {
            curFillingSpr->setColor(_colorVal);
            curFillingSpr->setPosition(ccp(sprSize.width/2, sprSize.height/2));
            this->addChild(curFillingSpr);
        }
    }
}

void ColorSprite::saveLastBrushInSpr(){
    CCSize sprSize = this->getContentSize();
    CCRenderTexture* saveBrushRender = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
    if (lastTextureArr != NULL) {
        saveBrushRender->begin();
//        this->setFlipY(true);
        this->visit();
        saveBrushRender->end();
//        this->setFlipY(false);
        
        lastTextureArr->addObject(saveBrushRender);
    }
    
}

void ColorSprite::removeFirstBrushInSpr(){
    if (lastTextureArr != NULL) {
        if (lastTextureArr->count() > 1) {
            
            lastTextureArr->removeObjectAtIndex(0);
        }
    }
}

void ColorSprite::removeAllBrushArrInSpr(){
    if (lastTextureArr != NULL) {
        if (lastTextureArr->count() > 1) {
            
            lastTextureArr->removeAllObjects();
        }
    }
}

void ColorSprite::cancelLastBrushInSpr(){
    if (lastTextureArr != NULL) {
        CCRenderTexture* lastBrushRender = NULL;
        
        int curLastIndex = lastTextureArr->count();
        if (curLastIndex > 1) {
            lastTextureArr->removeObjectAtIndex(curLastIndex-1);
            
            int newLastIndex = lastTextureArr->count();
            if (newLastIndex > 0) {
                lastBrushRender = (CCRenderTexture*)lastTextureArr->objectAtIndex(newLastIndex-1);
                
                if (lastBrushRender != NULL) {
                    
                    CCImage* lastSceneImage = lastBrushRender->newCCImage();
                    
                    if (lastSceneImage != NULL) {
    //                    this->setColor(ccWHITE);
                        CCTexture2D* lastSceneTexture = new CCTexture2D();
                        if (lastSceneTexture && lastSceneTexture->initWithImage(lastSceneImage)) {
                            this->setTexture(lastSceneTexture);
                        }
                        
                    }
    //                CCTexture2D* lastTexture = lastBrushRender->getSprite()->getTexture();
                    CCSprite* lastSceneSpr = (CCSprite*)this->getChildByTag(LAST_TEXTURE);
                    if (lastSceneSpr != NULL) {
                        lastSceneSpr->removeFromParentAndCleanup(true);
                    }
                    this->removeAllChildrenWithCleanup(true);
                    if (m_EraserDrawer != NULL) {
                        CC_SAFE_RELEASE(m_EraserDrawer);
                        m_EraserDrawer = NULL;
                    }
                    if (clippingBrushSpr != NULL) {
                        CC_SAFE_RELEASE(clippingBrushSpr);
                        clippingBrushSpr = NULL;
                    }
                    if (pencilNode != NULL) {
                //        CC_SAFE_RELEASE(pencilNode);
                        pencilNode = NULL;
                    }
                    if (brushNode != NULL) {
                //        CC_SAFE_RELEASE(brushNode);
                        brushNode = NULL;
                    }
                    this->initBrushNode();
                    
                }
            }
        }
        
            
    }
}

void ColorSprite::clearColorSpr(bool _isClearLastTextureArr)
{
    CCSprite* lastSceneSpr = (CCSprite*)this->getChildByTag(LAST_TEXTURE);
    if (lastSceneSpr != NULL) {
        lastSceneSpr->removeFromParentAndCleanup(true);
    }
    brushRender = NULL;
    this->removeAllChildrenWithCleanup(true);
    
    if (lastTextureArr != NULL && _isClearLastTextureArr) {
        lastTextureArr->removeAllObjects();
    }
    
    if (m_EraserDrawer != NULL) {
        CC_SAFE_RELEASE(m_EraserDrawer);
        m_EraserDrawer = NULL;
    }
    if (clippingBrushSpr != NULL) {
        CC_SAFE_RELEASE(clippingBrushSpr);
        clippingBrushSpr = NULL;
    }
    if (pencilNode != NULL) {
//        CC_SAFE_RELEASE(pencilNode);
        pencilNode = NULL;
    }
    if (brushNode != NULL) {
//        CC_SAFE_RELEASE(brushNode);
        brushNode = NULL;
    }
    
    if (this->curSprFileName != "") {
        CCTexture2D* curSprTexture = CCTextureCache::sharedTextureCache()->addImage(this->curSprFileName.c_str());
        if (curSprTexture != NULL) {
            this->setTexture(curSprTexture);
        }
    }
    
    this->initBrushNode();
    
}





