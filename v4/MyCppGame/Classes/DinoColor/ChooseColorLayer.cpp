//
//  ChooseColorLayer.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/19.
//

#include "ChooseColorLayer.hpp"
#include "GameManager.h"
#include "extensions/cocos-ext.h"
#include "ColorManager.hpp"
#include "audio/include/AudioEngine.h"
#include "BuyPage.h"
#include "ColorCanvasView.h"

//using namespace CocosDenshion;
using namespace cocos2d::extension ;
//
//#define Tag  100
//
//#define Mark  1000
//
//const unsigned int    kNormalTag = 0x1;
//const unsigned int    kSelectedTag = 0x2;
//const unsigned int    kDisableTag = 0x3;

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
    v_size = Director::getInstance()->getWinSize();
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
    return true;
}

void ChooseColorLayer::onEnter()
{
    Layer::onEnter();
    
    // 创建触摸监听器
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(ChooseColorLayer::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(ChooseColorLayer::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(ChooseColorLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

void ChooseColorLayer::onExit()
{
    if (_touchListener) {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener = nullptr;
    }
    Layer::onExit();
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
        
        selectPenIndex = ColorManager::shared()->curLargebrushIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchLargebrush == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorLargebrushPos[i] =colorMaxDis-i*colorDisY;
                
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorLargebrushPos[i];
        }
        
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        int penColorArr[20] = {23,32,18,5,8,12,2,37,4,3,1,6,7,28,25,10,13,31,24,14};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 45;
        scaleColor  = 0.8;
//        maxDis = (colorDisY*37-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
//        colorMaxDis = colorBg->getContentSize().height/1.07+440;
//        colorMinDis = -440;
        firstPenIndex = 20;
        
        selectPenIndex = ColorManager::shared()->curCrayonIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchCrayon == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorCrayonPos[i] =colorMaxDis-i*colorDisY;
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorCrayonPos[i];
        }
        
//        ColorManager::shared()->m_pColor = Color3B(255,255,50);
    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
        int penColorArr[24] = {23,2,12,32,8,18,5,3,1,37,4,6,13,28,7,10,25,31,24,14};
        for (int i=0; i<24; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 24;
        colorDisY = 40;
        scaleColor  = 0.8;
//        maxDis = 350;
//        colorMaxDis = colorBg->getContentSize().height/1.07+390;
//        colorMinDis = -350;
        firstPenIndex = 22;
        selectPenIndex = ColorManager::shared()->curPencilIndex;
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPencil == false) {
            for (int i = 0; i < 24; i++) {
                ColorManager::shared()->colorPencilPos[i] =colorMaxDis-i*colorDisY;
            }
        }
        for (int i = 0; i < 24; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPencilPos[i];
        }
            
//        ColorManager::shared()->m_pColor = Color3B(0,0,0);
    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        int penColorArr[20] = {7,2,18,32,8,12,5,4,37,1,6,3,25,28,23,10,13,31,14,24};
        for (int i=0; i<20; i++) {
            paintColorArr[i] = penColorArr[i];
        }
        totlePenCount = 20;
        colorDisY = 65;
        scaleColor  = 0.6;
        colorDisX = 10;
//        maxDis = 900;
//        colorMaxDis = colorBg->getContentSize().height/1.07+770;
//        colorMinDis = -900;
        firstPenIndex = 20;
        
        selectPenIndex = ColorManager::shared()->curPaintbucketIndex;
        
        colorMaxDis = (colorDisY*20-colorBg->getContentSize().height/1.07)/2+colorBg->getContentSize().height/1.07;
        
        if (ColorManager::shared()->firstTouchPaintbucket == false) {
            for (int i = 0; i < 20; i++) {
                ColorManager::shared()->colorPaintbucketPos[i] =colorMaxDis-i*colorDisY;
            }
        }
        for (int i = 0; i < 20; i++) {
            colorPenPos[i] = ColorManager::shared()->colorPaintbucketPos[i];
        }
        
//        ColorManager::shared()->m_pColor = Color3B(248,37,15);
    }
    



    if (selectPenIndex>11 && selectPenIndex<16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
        ColorManager::shared()->firstColorValue(selectPenIndex);
    }else if(selectPenIndex>15 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)){
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  paintColorArr[selectPenIndex-4];
        ColorManager::shared()->changeCurColor();
        selectPenColorIndex = paintColorArr[selectPenIndex-4];
    }else{
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  paintColorArr[selectPenIndex];
        ColorManager::shared()->changeCurColor();
        selectPenColorIndex = paintColorArr[selectPenIndex];
    }
    
    
//    selectPenColorIndex = paintColorArr[selectPenIndex];

    

    
    colorMinDis = colorMaxDis-(totlePenCount-1)*colorDisY;
//    int crayonIndex[37] = {9,8,10,21,24,12,31,36,1,3,4,5,6,7,2,20,17,26,42,13,16,15,14,19,21,23,22,25,27,28,29,30,32,33,34,35,18};

//    CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
    clickPenIndexArr[selectPenIndex] = 1;
    
    for (int i = 0; i < totlePenCount; i++) {
//        crayonTextureIndex[i] = crayonIndex[i];
        if (i==selectPenIndex) {
            origiPenX = 25;
        }else{
            origiPenX = 0;
        }
        std::string name = StringUtils::format("DinoColor/toolsUI/%s_tools_cover.png",ColorManager::shared()->curPenName);
        Sprite* penColor = Sprite::create(name);
        penColor->setPosition(Vec2(colorBg->getContentSize().width/3-origiPenX,colorPenPos[i]+400));
        penColor->setTag(kPenColorTag+i);
        penColor->setScale(scaleColor);
        colorBg->addChild(penColor);
        
//        Sprite* tmp2 = Sprite::create(name);
//        Size size2 = tmp2->getContentSize();
//        Rect insetRect2 = Rect(0,0,size2.width, size2.height);
//        ui::Scale9Sprite* sprite2 = ui::Scale9Sprite::create(name, insetRect2) ;
//        ControlButton *button = ControlButton::create(sprite2) ;
//        button->setPreferredSize(size2) ;
//        button->setTag(Tag+i);
//        button->setPosition(Vec2(v_size.width -130-poszero.x-colorDisX,v_size.height/1.07+maxDis-i*colorDisY)) ;
//        button->setScale(scaleColor);
////           button->setPosition(Vec2(0, 0)) ;
//        this->addChild(button, 3) ;
        
        Sprite* brushIconShadow = NULL;
//        if (strcmp(ColorManager::shared()->curPenName, "crayon")==0 ) {
//            Texture2D* texture = ColorManager::shared()->maskedWithSpriteTexture(Sprite::create(StringUtils::format("DinoColor/crayon_texture/crayon_texture_%d.png",crayonTextureIndex[i])), Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName)), Vec2(0.5, 0.5));
//            brushIconShadow = Sprite::createWithTexture(texture);
//        }else{
        
        if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>11 && i<16) {
            brushIconShadow = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_colorshadow%d.png",ColorManager::shared()->curPenName,i));
        }else{
            
                brushIconShadow = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",ColorManager::shared()->curPenName));
            Color3B brushColor;
            if((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15){
                brushColor = ColorManager::shared()->getCurColor(paintColorArr[i-4]);
            }else{
                brushColor = ColorManager::shared()->getCurColor(paintColorArr[i]);
            }
                
                brushIconShadow->setColor(brushColor);
        }

//        }
        
        brushIconShadow->setPosition(Vec2(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
//        brushIconShadow->setTag(Tag+i);
        penColor->addChild(brushIconShadow,-1);
        
//        Sprite* mark = Sprite::create("DinoColor/brush-select.png");
//        mark->setTag(Mark);
//        mark->setPosition(Vec2(size2.width/2, size2.height/2 ));
//        button->addChild(mark);
//        if (ColorManager::shared()->SelectBrushTag == Tag+i) {
//            mark->setVisible(true);
//        }else{
//           mark->setVisible(false);
//        }
        penColor->runAction(MoveBy::create(0.3, Vec2(0, -400)));
        
        if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased") && (i<(7) || i>(11))) {
            this->addLock(penColor, i);
            std::string name = StringUtils::format("DinoColor/toolsUI/%s_iap_shadow.png",ColorManager::shared()->curPenName);
            Sprite* penIapShadow = Sprite::create(name);
            penIapShadow->setPosition(Vec2(penColor->getContentSize().width/2, penColor->getContentSize().height/2));
            penColor->addChild(penIapShadow);
        }
//        ColorManager::shared()->colorPenPos[i]  = penColor->getPosition().y-400;
//        button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), ControlEventTouchUpInside) ;
    }
//    for (int i=0; i<37; i++) {
//        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[i]);
//    }
//       for (int i = 0; i < 37; i++) {
           
//           std::string name = StringUtils::format("DinoColor/color/color_%d.png",(i+1));
//           Sprite* tmp2 = Sprite::create(name);
//           Size size2 = tmp2->getContentSize();
//           Rect insetRect2 = Rect(0,0,size2.width, size2.height);
//           ui::Scale9Sprite* sprite2 = ui::Scale9Sprite::create(name, insetRect2) ;
//           ControlButton *button = ControlButton::create(sprite2) ;
//           button->setPreferredSize(size2) ;
//           button->setTag(Tag+i);
//           button->setPosition(Vec2(v_size.width -160-poszero.x,v_size.height/1.07+800-i*100+200)) ;
//           this->addChild(button, 3) ;
////           Sprite* mark = Sprite::create("DinoColor/color-selected.png");
////           mark->setTag(Mark);
////           mark->setPosition(Vec2(size2.width/2, size2.height/2));
////           button->addChild(mark);
////           if (ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] == Tag+i) {
////               mark->setVisible(true);
////           }else{
////              mark->setVisible(false);
////           }
////
//           button->runAction(MoveBy::create(0.5, Vec2(0, -200)));
//           button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), ControlEventTouchUpInside) ;
//       }
}



void ChooseColorLayer::addLock(Ref *_parent,int _index) {

    const char* lockName = "lock";
    
    Sprite* parentSpr = (Sprite*)_parent;
    
    
    
    Sprite* locked = Sprite::create(StringUtils::format("iap/%s.png",lockName));   //那么设置一个锁的精灵
    if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        locked->setScale(0.7) ;
        locked->setPosition(Vec2(parentSpr->getContentSize().width/2.5, parentSpr->getContentSize().height/1.7));
    }else  if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        locked->setScale(0.8) ;
        locked->setPosition(Vec2(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.7));
    }else{
        locked->setScale(scaleColor-0.3) ;
        locked->setPosition(Vec2(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.9));
    }
    
//    locked->setPosition(Vec2(parentSpr->getContentSize().width/2, parentSpr->getContentSize().height/1.7));
    locked->setTag(kLockTag);
    parentSpr->addChild(locked,10) ;
}




void ChooseColorLayer::colorClick(Ref *obj)
{
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);

    Sprite* penButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+selectPenIndex);
    if(penButton!=NULL){
//        penButton->setScale(scaleColor);
        penButton->runAction(Spawn::create(Sequence::create(ScaleTo::create(0.1, scaleColor+0.2),
                                                                ScaleTo::create(0.1, scaleColor),
                                                                                   NULL),
                                             EaseIn::create(MoveBy::create(0.3, Vec2(-25, 0)), 0.3),
                                             NULL));
    }
    
    for (int i=0; i<totlePenCount; i++) {
        Sprite* otherPenButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
        if (i!=selectPenIndex && otherPenButton!=NULL) {
            otherPenButton->setPositionX(colorBg->getContentSize().width/3);
            otherPenButton->runAction(ScaleTo::create(0.2, scaleColor));
            clickPenIndexArr[i] = 0;
        }
    }
    
//    int tag = ((Node*)obj)->getTag();
//    for (int i = 0; i < 15; i++) {
//        Node* node =this->getChildByTag(Tag+i);
//        node->getChildByTag(Mark)->setVisible(false);
//    }
//    ((Node*)obj)->getChildByTag(Mark)->setVisible(true);
    
//    Sprite* pait = ( Sprite*)color->getSelectedImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
//    pait = ( Sprite*)color->getNormalImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
//    color->unselected();
//    NotificationCenter::getInstance()->postNotification("colorcanvas.changecolor");
//    this->removeFromParent();
    if (selectPenIndex>11 && selectPenIndex<16 && (strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0)) {
        ColorManager::shared()->firstColorValue(selectPenIndex);
    }else{
        ColorManager::shared()->colorNums = 0;
        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  selectPenColorIndex;
        ColorManager::shared()->changeCurColor();
    }




    ColorManager::shared()->m_DrawType = Draw_Point ;
//    if (strcmp(ColorManager::shared()->curPenName, "crayon")==0) {
//        ColorManager::shared()->SelectColorTag[ColorManager::shared()->SelectBrushTag-100] =  crayonTextureIndex[selectPenIndex];
//        NotificationCenter::getInstance()->postNotification("colorcanvas.changecolor");

//    }

}

void ChooseColorLayer::SetMenuItem(MenuItemSprite *item)
{
    color = item;
}


bool ChooseColorLayer::onTouchBegan(Touch *touch, Event *event){
    Vec2 location = touch->getLocationInView();

    location = Director::getInstance()->convertToGL(location);
    Vec2 preLocation = touch->getPreviousLocationInView();
    startY = location.y;
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);
    buyState=ColorManager::shared()->buyState;
    if (colorBg!=NULL && colorBg->getBoundingBox().containsPoint(location)&&!buyState) {
        touchColorBg = colorBg;
        if(strcmp(ColorManager::shared()->curPenName, "eraser")!=0){
            ColorManager::shared()->scrollPenBoard = true;
        }
        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
            ColorManager::shared()->firstTouchPaint = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
            ColorManager::shared()->firstTouchLargebrush = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
            ColorManager::shared()->firstTouchCrayon = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
            ColorManager::shared()->firstTouchPencil = true;
        }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
            ColorManager::shared()->firstTouchPaintbucket = true;
        }
        
    }
    

    
    touchMoveDis = 0;
    
    return true;
}

void ChooseColorLayer::onTouchMoved(Touch *touch, Event *event){
    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    Vec2 preLocation = touch->getPreviousLocationInView();
    preLocation = Director::getInstance()->convertToGL(preLocation);
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);
    buyState=ColorManager::shared()->buyState;
    buyState=ColorManager::shared()->buyState;
//    Vec2 touchPos = colorBg->convertToNodeSpace(location);
//    Vec2 preLocation = touchPos->getPreviousLocationInView();
//    Vec2 touchPrePos = colorBg->convertToNodeSpace(preLocation);
    beginY = preLocation.y;
    endY = location.y;
    touchMoveDis = endY-beginY;
    finishY= startY-endY;
    if(abs(startY-endY)>100){
        resetColorPos();
    }
    if (touchColorBg!=NULL && touchColorBg->getBoundingBox().containsPoint(location) && touchMoveDis!=0&&!buyState) {
        for (int i=0; i<totlePenCount; i++) {

            Sprite* penButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
            if (penButton!=NULL) {
//                CCLOG("---没有移动前的位置%f---",ColorManager::shared()->colorPenPos[36]);
//                CCLOG("---%f---",penButton->getPositionY());
                penButton->setPositionY(penButton->getPositionY()+touchMoveDis);
                int penPosY = penButton->getPositionY();
                if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
                    ColorManager::shared()->colorPaintPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                    ColorManager::shared()->colorLargebrushPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                    ColorManager::shared()->colorCrayonPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
                    ColorManager::shared()->colorPencilPos[i] = penPosY;
                }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                    ColorManager::shared()->colorPaintbucketPos[i] = penPosY;
                }
//                ColorManager::shared()->colorPenPos[i] = penPosY;
//                CCLOG("---各个笔移动后的位置%f---",ColorManager::shared()->colorPenPos[i]);
            }
        }
    }
//    CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[36]);
}

void ChooseColorLayer::onTouchEnded(Touch *touch, Event *event){

    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    Vec2 point = touch->getLocation();
    Vec2 lastPoint = touch->getPreviousLocation();
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);
//    CCLOG("---手滑动距离%d---",touchMoveDis);
    for (int i=0; i<totlePenCount; i++) {
        Sprite* penButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
//        CCLOG("---最后一支笔当前的位置%f---",penButton->getPositionY());
        if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
            ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
            ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
            ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
            ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
        }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
            ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
        }

        
        
    }
    ColorManager::shared()->scrollPenBoard = false;
//    isMovedPen = false;
    resetColorPos();
    ColorCanvasView* c = (ColorCanvasView*)this->getChildByTag(kBuyLayerTag);
    if(touchMoveDis==0){
        for (int i=0; i<totlePenCount; i++) {
            Sprite* penColor = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
            Sprite* adLock = (Sprite*)penColor->getChildByTag(kLockTag);
            Vec2 penPos = colorBg->convertToNodeSpace(location);
            buyState=ColorManager::shared()->buyState;
            if (penColor!=NULL && penColor->getBoundingBox().containsPoint(penPos) && clickPen==false && clickPenIndexArr[i] == 0&&!buyState) {
                AudioEngine::play2d("mp3/touchItem.mp3");
//                ColorManager::shared()->firstTouchPencil = true;
                if (adLock!=NULL) {
    //                ScaleBy* scaleBy = ScaleBy::create(0.1, 1.2);
    //                adLock->runAction(Sequence::createWithTwoActions(scaleBy, scaleBy->reverse()));
                     Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("colorcanvas.showpeniap");
                     ColorManager::shared()->buyState= true;
                }else{

                    clickPenIndexArr[i] = 1;
                    clickPen = true;
                    if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15) {
                        selectPenColorIndex = paintColorArr[i-4];
                    }else{
                        selectPenColorIndex = paintColorArr[i];
                    }
                    selectPenIndex = i;
                    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
//                        if(i>15){
//                            ColorManager::shared()->curPaintIndex = i-4;
//                        }else{
                            ColorManager::shared()->curPaintIndex = i;
//                        }
                        
                    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                        ColorManager::shared()->curLargebrushIndex = i;
                    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                        ColorManager::shared()->curCrayonIndex = i;
                    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
//                        if(i>15){
//                            ColorManager::shared()->curPencilIndex = i-4;
//                        }else{
                            ColorManager::shared()->curPencilIndex = i;
//                        }
                    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                        ColorManager::shared()->curPaintbucketIndex = i;
                    }
                    penColor->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_1(ChooseColorLayer::colorClick, this)),
                                                           CallFunc::create(CC_CALLBACK_0(ChooseColorLayer::canClickPen, this)),
                                                           NULL));

                }
            }
        }
    }
//    if (clickPen==true) {

//    }
    
//    SimpleAudioEngine::getInstance()->stopAllEffects();
    
}

void ChooseColorLayer::canClickPen(){
    clickPen =false;
}


void ChooseColorLayer::resetColorPos(){
//    int touchMoved=finishY-startY;
//    CCLOG("---当前画笔%d---",colorMaxDis);
//    CCLOG("---拖动距离%d---",touchMoveDis);
    Sprite* colorBg = (Sprite*)this->getChildByTag(kColorBgTag);
    if (touchMoveDis>0) {
        for (int i=0; i<totlePenCount; i++) {
    //        CCLOG("---各个笔的位置%f---",ColorManager::shared()->colorPenPos[i]);
            Sprite* penButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
            int penPos = penButton->getPositionY();
    //        CCLOG("---第一支笔当前的位置%d---",penPos);
    //        CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
    //        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[36]);
            if (penPos>=colorMaxDis) {
    //            penButton->setPositionY(colorMinDis-colorDisY+touchMoveDis);
//                if(i!=0){
//                    penButton->setPositionY(colorPenPos[i-1]-colorDisY);
//                }else{
//                    penButton->setPositionY(colorPenPos[totlePenCount-1]-colorDisY);
//                }
                if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorPaintPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorPaintPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                    if(i!=0){
                        penButton->setPositionY( ColorManager::shared()->colorCrayonPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY( ColorManager::shared()->colorCrayonPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                    if(i!=0){
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[i-1]-colorDisY);
                    }else{
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[totlePenCount-1]-colorDisY);
                    }
                    ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
                }
                
//                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//            }else if(penPos<=colorMinDis){
//    //            penButton->setPositionY(colorMaxDis+colorDisY+touchMoveDis);
//                if(i!=36){
//                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
//                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
//                    penButton->setPositionY(ColorManager::shared()->colorPenPos[i+1]+colorDisY);
//                }else{
//                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
//                    penButton->setPositionY(ColorManager::shared()->colorPenPos[0]+colorDisY);
//                }
//                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//                CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
            }
    //        CCLOG("---第一支笔调整后的位置%f---", penButton->getPosition().y);
    //        CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[36]);
            
        }
    }else if(touchMoveDis<0){
        for (int i=totlePenCount-1; i>=0; i--) {
    //        CCLOG("---各个笔的位置%f---",ColorManager::shared()->colorPenPos[i]);
            Sprite* penButton = (Sprite*)colorBg->getChildByTag(kPenColorTag+i);
            int penPos = penButton->getPositionY();
    //        CCLOG("---第一支笔当前的位置%d---",penPos);
    //        CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
    //        CCLOG("---最后一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[36]);
            if(penPos<=colorMinDis){
    //            penButton->setPositionY(colorMaxDis+colorDisY+touchMoveDis);
//                if(i!=totlePenCount-1){
////                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
////                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
//                    penButton->setPositionY(colorPenPos[i+1]+colorDisY);
//                }else{
////                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
//                    penButton->setPositionY(colorPenPos[0]+colorDisY);
//                }
                if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY( ColorManager::shared()->colorPaintPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY( ColorManager::shared()->colorPaintPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorPaintPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorLargebrushPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorLargebrushPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorCrayonPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorCrayonPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorCrayonPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorPencilPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorPencilPos[i] = penButton->getPositionY();
                }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
                    if(i!=totlePenCount-1){
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
    //                    CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i+1]);
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[i+1]+colorDisY);
                    }else{
    //                    CCLOG("---第一支笔当前的位置%f---",ColorManager::shared()->colorPenPos[0]);
                        penButton->setPositionY(ColorManager::shared()->colorPaintbucketPos[0]+colorDisY);
                    }
                    ColorManager::shared()->colorPaintbucketPos[i] = penButton->getPositionY();
                }
                
//                ColorManager::shared()->colorPenPos[i] = penButton->getPosition().y;
//                CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[i]);
            }
    //        CCLOG("---第一支笔调整后的位置%f---", penButton->getPosition().y);
    //        CCLOG("---第一支笔调整后的位置%f---",ColorManager::shared()->colorPenPos[36]);
            
        }
    }

}
