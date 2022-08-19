//
//  ColorSprite.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#include "ColorSprite.h"

ColorSprite* ColorSprite::CreateColor(const char* spName, CCPoint pos, CCNode *parent, int ptag)
{
    ColorSprite* sprite = new ColorSprite();
    
    if (sprite && sprite->initWithFile(spName)) {
        sprite->autorelease();
        sprite->setPosition(pos);
        sprite->setTag(ptag);
        parent->addChild(sprite);
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    sprite = NULL;
    return NULL ;
}

void ColorSprite::PlatingSprite(ccColor3B color, CCRenderTexture *canvas)
{
    this->setColor(ccRED);
    this->setOpacity(255);
    canvas->begin();
    this->visit();
    canvas->end();
    this->setOpacity(0);
}

bool ColorSprite::isTouched(cocos2d::CCTouch *pTouch)
{
    bool isTouched = false;
    CCPoint touchPointInView = pTouch->getLocationInView();
    CCPoint glPoint = CCDirector::sharedDirector()->convertToGL(touchPointInView);
    isTouched = this->CheckAlpha(glPoint);
    return isTouched;
}

bool ColorSprite::CheckAlpha(CCPoint point)
{
    bool isTouched = false;
    if (this->boundingBox().containsPoint(point)) {
        //this->setOpacity(100);
        int8_t data[4];
        CCPoint touchPoint = this->convertToNodeSpace(point);        
        CCPoint location = CCPoint((touchPoint.x), (touchPoint.y) );
        CCRenderTexture* renderTexture = CCRenderTexture::create(1,1,kCCTexture2DPixelFormat_RGBA8888);
        renderTexture->beginWithClear(0,0,0,0);//只保存渲染一个像素的数据
        CCPoint oldPos = this->getPosition();
        CCPoint oldAnchor = this->getAnchorPoint();
        this->setAnchorPoint(CCPoint(0,0));
        this->setPosition(ccp(-location.x, -location.y));
        this->visit();
        this->setAnchorPoint(oldAnchor);
        this->setPosition(oldPos);
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
