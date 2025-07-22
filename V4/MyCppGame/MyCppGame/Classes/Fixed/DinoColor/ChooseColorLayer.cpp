//
//  ChooseColorLayer.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/19.
//

#include "ChooseColorLayer.hpp"
#include "../GameManager.h"
#include "cocos-ext.h"
#include "ColorManager.hpp"
#include "../BuyPage.h"
#include "ColorCanvasView.h"

using namespace cocos2d::extension ;

enum{
    kBuyLayerTag = 0,
    kLockTag = 2,
    kColorBgTag = 33,
    kPenColorTag = 111,
};

bool ChooseColorLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    buyState= false;
    Vec2 winCenter = GameManager::sharedManager()->getCenter();
    v_size = Director::getInstance()->getVisibleSize();
    poszero = Director::getInstance()->getVisibleOrigin();
    clickPen = false;
    selectPenColorIndex = 0;
    ColorManager::shared()->colorNums = 0;
//    penMoveDisY = 0;
    

    for (int i=0; i<24; i++) {
        clickPenIndexArr[i] = 0;
//        crayonTextureIndex[i]=0;
        paintColorArr[i] = 0;
        colorPenPos[i] = 0;
    }

    
    float fix_w = 0 ;
       if (GameManager::sharedManager()->isIphoneX()) {
           fix_w = 70;
       }
    
//    bg = Sprite::create("DinoColor/swatch_color.png");
//    bg->setPosition(Vec2(v_size.width/4*2.2-poszero.x+fix_w,v_size.height/2+10));
//
//    this->addChild(bg);
    touchColorBg = NULL;
    endY = 0;
    beginY = 0;
    

    
    this->setButton();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(ChooseColorLayer::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(ChooseColorLayer::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(ChooseColorLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void ChooseColorLayer::setButton()
{
    float fix_w = 0 ;
       if (GameManager::sharedManager()->isIphoneX()) {
           fix_w = 130;
       }
   
    
    float w_fix = 0 ;
//    if (GameManager::sharedManager()->isIphoneX()) {
//        w_fix = 50 ;
//    }
    
    Sprite* colorBg = Sprite::create("DinoColor/color_bg.png");
    colorBg->setPosition(Vec2(v_size.width -80 - w_fix-poszero.x,v_size.height/2));
//    toolsBg->setScaleX(0.7);
    colorBg->setTag(kColorBgTag);
    this->addChild(colorBg,2) ;
    
//    CCLOG("---%f---",colorBg->getContentSize().height/1.07);
    
    colorDisY=0;            //笔间距
    colorDisX=0;            //横坐标偏移
    totlePenCount =0;              //笔触数量
    firstPenIndex=0;            //初始笔
    int origiPenX=0;            //初始笔的位置
    colorMaxDis=0;
    colorMinDis = 0;
    scaleColor=0;
    
    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
        int penColorArr[24] = {23,32,18,2,8,12,5,1,3,4,6,37,25,28,7,10,13,31,24,14};
        for (int i=0; i<24; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        
        totlePenCount = 24;
        colorDisY = 40;                 //笔间距
        scaleColor  = 0.8;
        firstPenIndex = 22;
        
        selectPenIndex = ColorManager::shared()->curPaintIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPaint == false) {
            for (int i = 0; i < 24; i++) {
                ColorManager::shared()->colorPaintPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 24; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPaintPos[i];
        }
            
//        ColorManager::shared()->m_pColor = Color3B(98,170,50);
    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        int penColorArr[20] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 60;
        scaleColor  = 0.65;
        colorDisX = 10;
        firstPenIndex = 20;
//        ColorManager::shared()->m_pColor = Color3B(2,68,246);
        
        selectPenIndex = ColorManager::shared()->curLargeBrushIndex;
        
        
        colorMaxDis = (colorDisY*19-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchLargeBrush == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorLargeBrushPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorLargeBrushPos[i];
        }
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        int penColorArr[20] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 60;
        scaleColor  = 0.65;
        colorDisX = 10;
        firstPenIndex = 20;
//        ColorManager::shared()->m_pColor = Color3B(255,255,50);
        
        selectPenIndex = ColorManager::shared()->curCrayonIndex;
        
        
        colorMaxDis = (colorDisY*19-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchCrayon == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorCrayonPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorCrayonPos[i];
        }
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon_fine")==0){
        int penColorArr[20] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 60;
        scaleColor  = 0.65;
        colorDisX = 10;
        firstPenIndex = 20;
//        ColorManager::shared()->m_pColor = Color3B(0,0,0);
        
        selectPenIndex = ColorManager::shared()->curCrayonFineIndex;
        
        
        colorMaxDis = (colorDisY*19-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchCrayonFine == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorCrayonFinePos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorCrayonFinePos[i];
        }
    }else if (strcmp(ColorManager::shared()->curPenName, "marker")==0){
        int penColorArr[20] = {13,32,24,14,5,12,8,4,1,6,3,37,25,28,7,10,23,31,18,2};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 60;
        scaleColor  = 0.65;
        colorDisX = 10;
        firstPenIndex = 20;
//        ColorManager::shared()->m_pColor = Color3B(248,37,15);
        
        selectPenIndex = ColorManager::shared()->curMarkerIndex;
        
        
        colorMaxDis = (colorDisY*19-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchMarker == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorMarkerPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorMarkerPos[i];
        }
    }
    
    colorMinDis = colorMaxDis-(totlePenCount-1)*colorDisY;
    
    selectPenColorIndex = ColorManager::shared()->curCrayonIndex;
    
//    CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
    
    //设置选择颜色的ui
    for (int i=0; i<totlePenCount; i++)
    {
        
        std::string name = StringUtils::format("DinoColor/toolsUI/%s_tools_cover.png",ColorManager::shared()->curPenName) ;
        Sprite* penColor = Sprite::create(name);
        penColor->setTag(kPenColorTag+i);
        penColor->setPosition(Vec2(colorBg->getContentSize().width/2+colorDisX, colorPenPos[i]));
        penColor->setScale(scaleColor);
        colorBg->addChild(penColor, 3);
        
//        Sprite* tmp2 = Sprite::create(name);
//        Size size2 = tmp2->getContentSize();
//        Rect insetRect2 = Rect(0,0,size2.width, size2.height);
//        ui::Scale9Sprite* sprite2 = ui::Scale9Sprite::create(name, insetRect2) ;
//        ui::Button *button = ui::Button::create() ;
        
        // penColor->setAnchorPoint(ccp(0.5,0.5)) ;
        
        //设置颜色
        Sprite* brushIconShadow = NULL;
        if (strcmp(ColorManager::shared()->curPenName, "crayon")==0) {
//            Texture2D* texture = ColorManager::shared()->maskedWithSpriteTexture(Sprite::create(StringUtils::format("DinoColor/crayon_texture/crayon_texture_%d.png",crayonTextureIndex[i])), Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName)), Vec2(0.5, 0.5));
//            brushIconShadow = Sprite::createWithTexture(texture);
            
            
            
            brushIconShadow = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_colorshadow%d.png",ColorManager::shared()->curPenName,i));
        }else{
            
            brushIconShadow = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName));
        }
        Color3B brushColor;
        brushColor = ColorManager::shared()->returnPenColor(paintColorArr[i]);
        brushIconShadow->setColor(brushColor);
        brushIconShadow->setPosition(Vec2(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
        
        penColor->addChild(brushIconShadow,1);
        if (selectPenIndex == i) {
            penColor->setScale(scaleColor+0.2);
        }
        
        //        CCMenuItemSprite* menuItem = CCMenuItemSprite::create(button, NULL, this, menu_selector(ChooseColorLayer::colorClick));
        //        menuItem->setTag(kColorPenTag+i);
        //        menu = CCMenu::create(menuItem, NULL);
        //        menu->setPosition(CCPointZero);
        //        penColor->addChild(menu);
        
        //        Sprite* mark = Sprite::create("DinoColor/brush-select.png");
        //        mark->setTag(Mark);
        //        mark->setVisible(false);
        //        button->addChild(mark);
        
        penColor->runAction(MoveBy::create(0.3, Vec2(0, -400)));
        
        if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased") && (i<(7) || i>(11))) {
            
            std::string name = StringUtils::format("DinoColor/toolsUI/%s_iap_shadow.png",ColorManager::shared()->curPenName) ;
            Sprite* penIapShadow = Sprite::create(name);
            penIapShadow->setPosition(Vec2(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
            penColor->addChild(penIapShadow,2);
        }
        
        
        //        button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), ui::Widget::TouchEventType::ENDED) ;
        
        
//        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[i]);
        
        
        
//           std::string name = StringUtils::format("DinoColor/color/color_%d.png",(i+1)) ;
//           Sprite* tmp2 = Sprite::create(name);
//           Size size2 = tmp2->getContentSize();
//           Rect insetRect2 = Rect(0,0,size2.width, size2.height);
//           ui::Scale9Sprite* sprite2 = ui::Scale9Sprite::create(name, insetRect2) ;
//           ui::Button *button = ui::Button::create() ;
//
//           button->setAnchorPoint(Vec2(0.5,0.5)) ;
//           button->setPosition(Vec2(colorBg->getContentSize().width/2, colorPenPos[i]));
//           button->setTag(kPenColorTag+i);
//           button->setScale(scaleColor);
////           Sprite* mark = Sprite::create("DinoColor/color-selected.png");
////           mark->setTag(Mark);
////           mark->setVisible(false);
////           button->addChild(mark);
//           
//           colorBg->addChild(button, 1);
//           
//           
//           
//           button->runAction(MoveBy::create(0.5, Vec2(0, -200)));
//           button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), ui::Widget::TouchEventType::ENDED) ;
        
    }
}

void ChooseColorLayer::addLock(Ref *_parent,int _index) {
    
    const char* lockName = "lock";
    
    Sprite* parentSpr = (Sprite*)_parent;
    
    Sprite* locked = Sprite::create(StringUtils::format("iap/%s.png",lockName)) ;   //那么设置一个锁的精灵
    locked->setPosition(Vec2(parentSpr->getContentSize().width/2,parentSpr->getContentSize().height/2));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked);
    
    locked->runAction(Sequence::create(ScaleTo::create(0.3, 1.0),
                                       CallFunc::create([=]{
        ColorManager::shared()->buyState = true;
        BuyPage* buyLayer = BuyPage::nodeWithID(0);
        buyLayer->setTag(kBuyLayerTag);
        this->getParent()->addChild(buyLayer,200);
    }),NULL));
    
    CCLOG("点击了购买%d",_index);
    
}

void ChooseColorLayer::colorClick(Ref *obj)
{
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);
    if (colorBg) {
        Sprite* penButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+selectPenIndex);
        
        if (penButton) {
            penButton->runAction(Spawn::create(Sequence::create(ScaleTo::create(0.1, scaleColor+0.2),
                                                                ScaleTo::create(0.1, scaleColor),
                                                                NULL),
                                               EaseIn::create(MoveBy::create(0.3, Vec2(-25, 0)), 0.3),
                                               NULL));
        }
        
        for (int i = 0; i < totlePenCount; i++) {
            Sprite* otherPenButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
            if (otherPenButton && i != selectPenIndex) {
                otherPenButton->runAction(ScaleTo::create(0.2, scaleColor));
            }
        }
    }
    
//    int tag = ((Node*)obj)->getTag();
//    for (int i=0; i<totlePenCount; i++) {
//        Node* node =this->getChildByTag(Tag+i);
//    }
//    ((Node*)obj)->getChildByTag(Mark)->setVisible(true);
//
//    Sprite* pait = ( Sprite*)color->getSelectedImage()->getChildByTag(1);
//
//    pait = ( Sprite*)color->getNormalImage()->getChildByTag(1);
    
    
//    NotificationCenter::getInstance()->postNotification("colorcanvas.changecolor");
    
    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
        ColorManager::shared()->curPaintIndex = selectPenIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        ColorManager::shared()->curLargeBrushIndex = selectPenIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        ColorManager::shared()->curCrayonIndex = selectPenIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon_fine")==0){
        ColorManager::shared()->curCrayonFineIndex = selectPenIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "marker")==0){
        ColorManager::shared()->curMarkerIndex = selectPenIndex;
    }
    
    if (ColorManager::shared()->ccv) {
        ColorManager::shared()->ccv->changeColor(paintColorArr[selectPenIndex]);
//        NotificationCenter::getInstance()->postNotification("colorcanvas.changecolor");
    }
    
}

void ChooseColorLayer::SetMenuItem(ui::Widget *item)
{
    menuItem = item;
}

void ChooseColorLayer::registerWithTouchDispatcher()
{
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerTouchOneByOne::create(), this);
}

void ChooseColorLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event* event){
    Touch* touch = touches[0];
    Vec2 location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    Vec2 preLocation = touch->getPreviousLocationInView();
    
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);
    
    if (colorBg->getBoundingBox().containsPoint(location)) {
        for (int i=0; i<totlePenCount; i++) {
            Node* penNode = colorBg->getChildByTag(kPenColorTag+i);
            if (penNode) {
                Vec2 penPos = colorBg->convertToNodeSpace(location);
                if (penNode->getBoundingBox().containsPoint(penPos)) {
                    if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased") && (i<(7) || i>(11))) {
                        addLock(penNode, i);
                        return;
                    }
                    
                    selectPenIndex = i;
                    colorClick(penNode);
                    
                    Sprite* penButton = (Sprite*)penNode;
                    penButton->runAction(ScaleTo::create(0.1, scaleColor+0.2));
                    return;
                }
            }
        }
        
        beginY = location.y;
        touchColorBg = colorBg;
        clickPen = true;
    }
}

void ChooseColorLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event* event){
    Touch* touch = touches[0];
    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    if (clickPen && touchColorBg) {
        float moveY = location.y - beginY;
        
        for (int i = 0; i < totlePenCount; i++) {
            Node* penNode = touchColorBg->getChildByTag(kPenColorTag+i);
            if (penNode) {
                float newY = colorPenPos[i] + moveY;
                
                if (newY > colorMaxDis) {
                    newY = colorMaxDis;
                } else if (newY < colorMinDis) {
                    newY = colorMinDis;
                }
                
                penNode->setPositionY(newY);
            }
        }
    }
}

void ChooseColorLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event){
    Touch* touch = touches[0];
    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    if (clickPen && touchColorBg) {
        float moveY = location.y - beginY;
        
        for (int i = 0; i < totlePenCount; i++) {
            float newY = colorPenPos[i] + moveY;
            
            if (newY > colorMaxDis) {
                newY = colorMaxDis;
            } else if (newY < colorMinDis) {
                newY = colorMinDis;
            }
            
            colorPenPos[i] = newY;
        }
        
        // Save positions based on pen type
        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorPaintPos[i] = colorPenPos[i];
            }
        } else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorLargeBrushPos[i] = colorPenPos[i];
            }
        } else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorCrayonPos[i] = colorPenPos[i];
            }
        } else if (strcmp(ColorManager::shared()->curPenName, "crayon_fine")==0) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorCrayonFinePos[i] = colorPenPos[i];
            }
        } else if (strcmp(ColorManager::shared()->curPenName, "marker")==0) {
            for (int i = 0; i < totlePenCount; i++) {
                ColorManager::shared()->colorMarkerPos[i] = colorPenPos[i];
            }
        }
        
        clickPen = false;
        touchColorBg = NULL;
    }
}
