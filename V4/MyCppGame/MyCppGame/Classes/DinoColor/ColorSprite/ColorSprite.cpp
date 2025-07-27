//
//  ColorSprite.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#include "ColorSprite.h"
#include "../ColorManager.hpp"
#include "GameManager.h"

#define LAST_TEXTURE 131

ColorSprite* ColorSprite::CreateColor(const char* spName, Vec2 pos, Node *parent, int ptag)
{
    ColorSprite* sprite = new ColorSprite();
    
    if (sprite && sprite->initWithFile(spName)) {
        sprite->autorelease();
        sprite->setPosition(pos);
        sprite->setTag(ptag);
        sprite->curSprName = "";
        sprite->brushRender = NULL;
        sprite->m_EraserDrawer = NULL;
        sprite->clippingBrushSpr = NULL;
//        sprite->testRender = RenderTexture::create(sprite->getContentSize().width, sprite->getContentSize().height, backend::PixelFormat::RGBA8888);
//        sprite->testRender->retain();
//        sprite->testRender->setPosition(Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
//        sprite->addChild(sprite->testRender);
//
//        sprite->testBrush = Sprite::create("DinoColor/paint_brush/paint_brush_1.png");
//        sprite->testBrush->retain();
//        sprite->testBrush->setColor(Color3B::RED);
//        sprite->testBrush->setOpacity(20);
//        sprite->testBrush->setScale(0.5);
//
//        parent->addChild(sprite);
        return sprite;
    }
    
    delete sprite;
    sprite = NULL;
    return NULL ;
}

//void ColorSprite::PlatingSprite(Color3B color, RenderTexture *canvas)
//{
//    this->setColor(Color3B::RED);
//    this->setOpacity(255);
//    canvas->begin();
//    this->visit();
//    canvas->end();
//    this->setOpacity(0);
//}
//
//bool ColorSprite::isTouched(cocos2d::Touch *pTouch)
//{
//    bool isTouched = false;
//    Vec2 touchPointInView = pTouch->getLocationInView();
//    Vec2 glPoint = Director::getInstance()->convertToGL(touchPointInView);
//    isTouched = this->CheckAlpha(glPoint);
//    return isTouched;
//}
//
//bool ColorSprite::CheckAlpha(Vec2 point)
//{
//    bool isTouched = false;
//    Vec2 posInParent = ((Sprite*)this->getParent())->convertToNodeSpace(point);
//    if (this->getBoundingBox().containsPoint(posInParent)) {
//        //this->setOpacity(100);
//        int8_t data[4];
//        Vec2 touchPoint = this->convertToNodeSpace(point);
//        Vec2 location = Vec2((touchPoint.x), (touchPoint.y) );
//        RenderTexture* renderTexture = RenderTexture::create(1,1,backend::PixelFormat::RGBA8888);
//        renderTexture->beginWithClear(0,0,0,0);//只保存渲染一个像素的数据
//        Vec2 oldPos = this->getPosition();
//        Vec2 oldAnchor = this->getAnchorPoint();
//        this->setAnchorPoint(Vec2(0,0));
//        this->setPosition(Vec2(-location.x, -location.y));
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
        m_EraserDrawer->release();
        m_EraserDrawer = NULL;
    }
    if (clippingBrushSpr != NULL) {
        clippingBrushSpr->release();
        clippingBrushSpr = NULL;
    }
    if (pencilNode != NULL) {
//        pencilNode->release();
        pencilNode = NULL;
    }
    if (brushNode != NULL) {
//        brushNode->release();
        brushNode = NULL;
    }
    
}

void ColorSprite::initBrushNode()
{
    Size sprSize = this->getContentSize();
//    ColorSprite* colorSpr = (ColorSprite*)this->getStencil();
//    if (colorSpr != NULL) {

//    clippingNode = NULL;
    

    if (ColorManager::shared()->m_DrawType == Draw_Eraser && m_EraserDrawer == NULL) {
        m_EraserDrawer = DrawNode::create();
        m_EraserDrawer->drawDot(Vec2::ZERO, 30, Color4F(1.0, 1.0, 1.0, 1.0));
        m_EraserDrawer->retain();
    }
    
    pencilNode = NULL;
    pencilNode = DrawNode::create();
    this->addChild(pencilNode);
    lastDotPos = Vec2::ZERO;
//    pencilNode = DrawNode::create();
//    pencilNode->drawDot(Vec2::ZERO, 5, Color4F(1.0, 1.0, 1.0, 1.0));
////    this->addChild(pencilNode);
//    pencilNode->retain();
//    this->addChild(testBrush);
//    }
    
    paintNode = NULL;
    paintNode = DrawNode::create();
    this->addChild(paintNode);
//    paintNode->retain();
    
    brushNode = NULL;
    brushNode = DrawNode::create();
//    brushNode->retain();
//    this->addChild(paintNode);
    
    Node* twoNode = Node::create();
    this->addChild(twoNode);
    
    RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
    firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
    twoNode->addChild(firstRender);
    
    brushRender = firstRender;
    
    if (clippingBrushSpr == NULL) {
        
        clippingBrushSpr = Sprite::create("DinoColor/brushs/normal_brush.png");
        int curColorIndex = ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100];
        ColorManager::shared()->getCurColor(curColorIndex);
        
        clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
        clippingBrushSpr->retain();
    }
//    m_Drawer->drawDot(start, line_w, color);
    
}

void ColorSprite::showLastSceneImage(){
//    Image* lastSceneImage = ColorManager::shared()->loadImageFromBinaryFile(this->curSprName);

//    if (lastSceneImage != NULL) {

        Texture2D* lastSceneTexture = new Texture2D();
//        if (lastSceneTexture && lastSceneTexture->initWithImage(lastSceneImage)) {
            
            Sprite* lastSceneSpr = Sprite::createWithTexture(lastSceneTexture);
            lastSceneSpr->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
            lastSceneSpr->setTag(LAST_TEXTURE);
            this->addChild(lastSceneSpr);
            
            lastSceneTexture->release();
//        }

//        lastSceneImage->release();
//    }
}

void ColorSprite::toolsBrushing(Vec2 _brushPos, Vec2 _lastPos)
{
    Vec2 touchPoint = this->convertToNodeSpace(_brushPos);
    Vec2 lastTouchPoint = this->convertToNodeSpace(_lastPos);
    clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
    if (ColorManager::shared()->m_DrawType == Draw_Eraser) {
        brushRender->begin();
        m_EraserDrawer->setPosition(Vec2(touchPoint.x, touchPoint.y));
//        m_EraserDrawer->visit();
        brushRender->end();
    } else {
        
    //        colorSpr->testBrushing(_testPos);
    //        colorSpr->visit();
        
        switch (ColorManager::shared()->SelectBrushTag) {
            case Brush_Pencil:
            {
//                brushRender->begin();
                if (!touchPoint.equals(lastTouchPoint)) {
                    pencilNode->drawSegment(lastTouchPoint, touchPoint, 5, Color4F(ColorManager::shared()->m_pColor));
                }
                pencilNode->drawDot(touchPoint, 5, Color4F(ColorManager::shared()->m_pColor));
//                pencilNode->visit();
//                brushRender->end();
//                lastDotPos = touchPoint;
            }
                break;
            case Brush_Paint:
            {
                
//                brushRender->begin();
//                paintNode->setBlendFunc(BlendFunc{backend::BlendFactor::ONE, backend::BlendFactor::DST_ALPHA});
                if (!touchPoint.equals(lastTouchPoint)) {
                    paintNode->drawSegment(lastTouchPoint, touchPoint, 20, Color4F(ColorManager::shared()->m_pColor));
                }
                paintNode->drawDot(touchPoint, 20, Color4F(ColorManager::shared()->m_pColor));
//                paintNode->visit();
//                clippingBrushSpr->setPosition(Vec2(touchPoint.x, touchPoint.y));
//                clippingBrushSpr->visit();
//                brushRender->end();
//                brushRender->getSprite()->getTexture()->setAntiAliasTexParameters();
            }
                break;
            case Brush_Largebrush:
            {
                Vec2 curSprPoint = clippingBrushSpr->getPosition();
                float distance = touchPoint.distance(curSprPoint);
                if (distance > 13.0) {
                    
                    brushRender->begin();
                    clippingBrushSpr->setPosition(Vec2(touchPoint.x, touchPoint.y));
                    clippingBrushSpr->visit();
                    CCLOG("testSimpleBrush ======> %d",ColorManager::shared()->SelectBrushTag);
                    brushRender->end();
                }
            }
                break;
            case Brush_Crayon:
            {
//                brushRender->begin();
//                if (!touchPoint.equals(lastTouchPoint)) {
////                    brushNode->drawSegment(lastTouchPoint, touchPoint, 20, Color4F(1.0, 1.0, 1.0, 1.0));
//                    brushNode->drawSegment(lastTouchPoint, touchPoint, 20,  Color4F(ColorManager::shared()->m_pColor));
//                }
////                brushNode->drawDot(touchPoint, 20, Color4F(1.0, 1.0, 1.0, 1.0));
//                brushNode->drawDot(touchPoint, 20,  Color4F(ColorManager::shared()->m_pColor));
////                brushNode->setPosition(Vec2(touchPoint.x, touchPoint.y));
//                brushNode->visit();
//                brushRender->end();
                
                Vec2 curSprPoint = clippingBrushSpr->getPosition();
                float distance = touchPoint.distance(curSprPoint);
                if (distance > 13.0) {
                    
                    brushRender->begin();
                    clippingBrushSpr->setPosition(Vec2(touchPoint.x, touchPoint.y));
                    clippingBrushSpr->visit();
                    CCLOG("testSimpleBrush ======> %d",ColorManager::shared()->SelectBrushTag);
                    brushRender->end();
                }
            }
                break;
        }
    }
}

void ColorSprite::changeBrush()
{
    Size sprSize = this->getContentSize();
    if (ColorManager::shared()->m_DrawType == Draw_Eraser) {
        if (m_EraserDrawer != NULL) {
            m_EraserDrawer->release();
            m_EraserDrawer = NULL;
        }
        
            
            m_EraserDrawer = DrawNode::create();
            m_EraserDrawer->drawDot(Vec2::ZERO, 30, Color4F(1.0, 1.0, 1.0, 1.0));
            m_EraserDrawer->retain();
        
        brushRender = NULL;
        Node* twoNode = Node::create();
        this->addChild(twoNode);
        
        RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//        firstRender->retain();
        firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
        twoNode->addChild(firstRender);
        
        brushRender = firstRender;
    }else {
        switch (ColorManager::shared()->SelectBrushTag) {
            case Brush_Pencil:
            {
    //            brushRender = NULL;
                pencilNode = NULL;
                pencilNode = DrawNode::create();
                this->addChild(pencilNode);
                brushRender = NULL;
                Node* twoNode = Node::create();
                this->addChild(twoNode);
                
                RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//                firstRender->retain();
                firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
                
                brushRender = firstRender;
            }
                break;
            case Brush_Paint:
            {
                paintNode = NULL;
                paintNode = DrawNode::create();
                this->addChild(paintNode);
//                paintNode->retain();
                brushRender = NULL;
                
//                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("DinoColor/brushs/normal_brush.png");
//                clippingBrushSpr->setScale(1.0);
//                clippingBrushSpr->setTexture(texture);
//                clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
                Node* twoNode = Node::create();
                this->addChild(twoNode);
                
                RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//                firstRender->retain();
                firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
                
                brushRender = firstRender;
                
            }
                break;
            case Brush_Largebrush:
            {
                brushRender = NULL;
                
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("DinoColor/brushs/paint_brush.png");
                clippingBrushSpr->setTexture(texture);
                Color3B colorVal = ColorManager::shared()->m_pColor;
                clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
                Node* twoNode = Node::create();
                this->addChild(twoNode);
                
                RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//                firstRender->retain();
                firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
                
                brushRender = firstRender;
                
            }
                break;
            case Brush_Crayon:
            {
                
    //            if (clippingNode == NULL) {
                brushRender = NULL;
                
                Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("DinoColor/brushs/crayon_brush.png");
                clippingBrushSpr->setTexture(texture);
                Color3B colorVal = ColorManager::shared()->m_pColor;
                clippingBrushSpr->setColor(ColorManager::shared()->m_pColor);
                Node* twoNode = Node::create();
                this->addChild(twoNode);
                
                RenderTexture* firstRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//                firstRender->retain();
                firstRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
                twoNode->addChild(firstRender);
//                brushNode = NULL;
//                brushNode = DrawNode::create();
////                brushNode->drawDot(Vec2::ZERO, 20, Color4F(1.0, 1.0, 1.0, 1.0));
//                brushNode->retain();
//
//                Vec2 centerPosInWorld = GameManager::sharedManager()->getCenter();
//
//                Vec2 texturePos = this->convertToNodeSpace(centerPosInWorld);
//                CCLOG("---%d---",ColorManager::shared()->SelectColorTag[2]);
//                StringUtils::format* crayonTextNameStr = StringUtils::format("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[2]);
//                Sprite* texture = Sprite::create(crayonTextNameStr->getCString());
//                texture->setPosition(Vec2(texturePos.x, texturePos.y));
//                Node* newNode = Node::create();
//
//                ClippingNode* clippingNode = ClippingNode::create(newNode);
//                    clippingNode->setInverted(false);
//                    clippingNode->setAlphaThreshold(0.0f);
//
//                    clippingNode->addChild(texture);
//                    this->addChild(clippingNode);
//                //    clippingNode->setVisible(false);
//
//                        RenderTexture* testRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//                        testRender->retain();
//                        testRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
//                        newNode->addChild(testRender);
                    
                brushRender = firstRender;
            }
                break;
        }
    }
//    RenderTexture* render = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
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
    Size sprSize = this->getContentSize();
    switch (ColorManager::shared()->SelectBrushTag) {
        case Brush_Pencil:
        {
            pencilNode->drawDot(Vec2::ZERO, 5, Color4F(ColorManager::shared()->m_pColor));
        }
            break;
        case Brush_Paint:
        {
            paintNode->drawDot(Vec2::ZERO, 20, Color4F(ColorManager::shared()->m_pColor));
        }
            break;
        case Brush_Largebrush:
        {
            Color3B newColor = ColorManager::shared()->m_pColor;
            
            clippingBrushSpr->setColor(newColor);
        }
            break;
        case Brush_Crayon:
        {
            Color3B newColor = ColorManager::shared()->m_pColor;
            
            clippingBrushSpr->setColor(newColor);
//            if (clippingNode != NULL) {
//            brushRender = NULL;
//            brushNode = NULL;
//            brushNode = DrawNode::create();
////            brushNode->drawDot(Vec2::ZERO, 20, Color4F(1.0, 1.0, 1.0, 1.0));
//            brushNode->retain();
//            Node* newNode = Node::create();
//            Vec2 centerPosInWorld = GameManager::sharedManager()->getCenter();
//
//            Vec2 texturePos = this->convertToNodeSpace(centerPosInWorld);
//            StringUtils::format* crayonTextNameStr = StringUtils::format("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[2]);
//
//            Sprite* texture = Sprite::create(crayonTextNameStr->getCString());
//            texture->setPosition(Vec2(texturePos.x, texturePos.y));
//
//            ClippingNode* clippingNode = ClippingNode::create(newNode);
//            clippingNode->setInverted(false);
//            clippingNode->setAlphaThreshold(0.0f);
//
//            clippingNode->addChild(texture);
//            this->addChild(clippingNode);
//
//            RenderTexture* testRender = RenderTexture::create(sprSize.width, sprSize.height, backend::PixelFormat::RGBA8888);
//            testRender->retain();
//            testRender->setPosition(Vec2(sprSize.width/2, sprSize.height/2));
//            newNode->addChild(testRender);
//
//            brushRender = testRender;
//            }
        }
            break;
    }
}

void ColorSprite::clearColorSpr()
{
    Sprite* lastSceneSpr = (Sprite*)this->getChildByTag(LAST_TEXTURE);
    if (lastSceneSpr != NULL) {
        lastSceneSpr->removeFromParentAndCleanup(true);
    }
    brushRender = NULL;
    this->removeAllChildrenWithCleanup(true);
    
    if (m_EraserDrawer != NULL) {
        m_EraserDrawer->release();
        m_EraserDrawer = NULL;
    }
    if (clippingBrushSpr != NULL) {
        clippingBrushSpr->release();
        clippingBrushSpr = NULL;
    }
    if (pencilNode != NULL) {
//        pencilNode->release();
        pencilNode = NULL;
    }
    if (brushNode != NULL) {
//        brushNode->release();
        brushNode = NULL;
    }
    
    this->initBrushNode();
    
}





