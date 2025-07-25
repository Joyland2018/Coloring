//
//  ColorCanvasView.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//


#include "ColorCanvasView.h"
#include "SelectAnimalScene.h"
#include "GameManager.h"
#include "ChooseColorLayer.hpp"
//#include "DeviceManager.h"
#include "SelectBrushLayer.hpp"
#include "ColorManager.hpp"
#include "SelectColorAniScene.hpp"
#include "BuyPage.h"
#include "AudioEngine.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "2d/CCTransition.h"
#include "base/CCNS.h"

#define DrawSprite_Tag 10000

#define ToolsIcon_Tag 31
#define ToolsIconShadow_Tag 32

enum{
    kBuyLayerTag = 0,
    kPenMenuTag = 1,
    kPenPartTag = 5,
    kButtonSelectTag = 6,
    kPenButtonTag =  100,
    kRaserTag = 2,
};


Scene* ColorCanvasView::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    ColorCanvasView* layer = ColorCanvasView::create();
    // add layer as a child to scene
    scene->addChild(layer);
    ColorManager::shared()->m_pCanvasLayer = layer ;
    // return the scene
    return scene;
}

bool ColorCanvasView::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    buyState= false;
    touchedButton = false;
    selectRaser = false;
    clickEraser = false;

    showParColor = false;
    
    // 设置触摸事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ColorCanvasView::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ColorCanvasView::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ColorCanvasView::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(ColorCanvasView::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    Vec2 winCenter = GameManager::sharedManager()->getCenter();
    v_size = Director::getInstance()->getWinSize();
    poszero = Director::getInstance()->getVisibleOrigin();
//    Sprite* bg = Sprite::create("DinoColor/coloring-bg.png");
//    bg->setPosition(winCenter);
//    this->addChild(bg);
//
//   if (GameManager::sharedManager()->isIphoneX()){
//       bg->setScale(1.3);
//   }
    
    
    m_DrawArray.clear();
    m_ClipDrawArray.clear();
//    whiteCanvas = Sprite::create("DinoColor/canvas.png");
//    whiteCanvas->setPosition();
//    whiteCanvas->setColor(Color3B::GRAY);
//    this->addChild(whiteCanvas);
    Sprite* stencilCanvas = Sprite::create("DinoColor/canvas.png");
    stencilCanvas->setAnchorPoint(Vec2(0.0, 0.0));
    stencilCanvas->setPosition(Vec2::ZERO);
    whiteCanvas= ColorSprite::CreateColor("DinoColor/canvas.png", Vec2(stencilCanvas->getContentSize().width/2, stencilCanvas->getContentSize().height/2), this, m_DrawArray.size());
//    whiteCanvas = ColorNode::createColorNode(Size(stencilCanvas->getContentSize().width, stencilCanvas->getContentSize().height));
//    whiteCanvas->setAnchorPoint(Vec2(0.0, 0.0));
//    whiteCanvas->setPosition(Vec2::ZERO);
    whiteCanvas->curSprName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(ColorManager::shared()->colorAniIndex)+"canvas";
    whiteCanvas->showLastSceneImage();
    whiteCanvas->initBrushNode();
    whiteCanvas->setTag(20);
    ColoringClippingNode *clip = ColoringClippingNode::create(stencilCanvas);
    clip->setContentSize(Size(stencilCanvas->getContentSize().width, stencilCanvas->getContentSize().height));
    clip->initClippingNode();
    clip->setAlphaThreshold(0.0f);
    clip->setAnchorPoint(Vec2(0.5, 0.5));
    clip->setPosition(Vec2(stencilCanvas->getContentSize().width/2, stencilCanvas->getContentSize().height/2));
    this->addChild(clip);
    m_ClipDrawArray.pushBack(clip);
//    DrawNode* drawer = DrawNode::create();
//    clip->addChild(drawer);
//    whiteCanvas->m_Drawer = drawer;
    clip->addChild(whiteCanvas);
    m_DrawArray.pushBack(stencilCanvas);
    
//    this->addChild(testBrush);
    
    GradonFile = StringUtils::format("dragon-%d",ColorManager::shared()->m_AnimalTag);
    
    ColorManager::shared()->SelectBrushTag = 100;
//    ColorManager::shared()->m_pColor = Color3B(98,170,50);
    this->MakeToolBar();
    this->MakeContent();
    this->showColorBoard();
    
//    ColorManager::shared()->m_pColor = Color3B(98,170,50);
//    AudioEngine::play2d("mp3/sink/sinkBg.mp3", true);
    return true ;
}

void ColorCanvasView::onEnter()
{
    Layer::onEnter();
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(kChangeBrushCallback, [this](EventCustom* event){
        this->changeBrushCallback();
    });
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(kChangeColorCallback, [this](EventCustom* event){
        this->changeColorCallback();
    });
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(kShowPenColorIapCallback, [this](EventCustom* event){
        this->selectAdsOrIAP();
    });
}

void ColorCanvasView::onExit()
{
    Layer::onExit();
    
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(kChangeBrushCallback);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(kChangeColorCallback);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(kShowPenColorIapCallback);
}


void ColorCanvasView::selectAdsOrIAP() {
        Layer* buyLayer = (Layer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
            buyLayer = (Layer*)BuyPage::nodeWithID(2);
            buyLayer->setTag(kBuyLayerTag);
            this->addChild(buyLayer, 99);

            Size _winSize = GameManager::sharedManager()->getViewVisibleSize();
            Vec2 center = GameManager::sharedManager()->getCenter();

            LayerColor *blacklayer = LayerColor::create(Color4B(0, 0, 0, 180), _winSize.width, _winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(Vec2(center.x,center.y));
            buyLayer->addChild(blacklayer, -1);
        }
}

void ColorCanvasView::backClick()
{
    buyState=ColorManager::shared()->buyState;
    if(!buyState){
        for (int i = 0; i< m_ClipDrawArray.size(); i++) {
            ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray.at(m_ClipDrawArray.size()-(i+1));
            if (sp != NULL) {
                ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);

                if (colorSpr != NULL) {

//                ColorManager::shared()->saveInfoToFile(colorSpr->infoArr,colorSpr->curSprName);

                    ColorManager::shared()->saveTextureToFile(colorSpr->curSprName, colorSpr);
                }
            }

        }

        this->resetColorValue();

        if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased")){
            if (GameManager::sharedManager()->num == 5){
                GameManager::sharedManager()->showInterstitial();
                GameManager::sharedManager()->num = 0;
            }else{
                GameManager::sharedManager()->num++;
            }
        }

        AudioEngine::play2d("mp3/touchItem.mp3");
        ColorManager::shared()->curPenName = "pencil";
        ColorManager::shared()->firstPlayColor=false;
        AudioEngine::stopAll();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, SelectColorAniScene::scene(), Color3B::BLACK));

    }
}

void ColorCanvasView::penParticleAction(Vec2 parPos){
    int parIndex = arc4random()%4+1;
    ParticleSystemQuad* penPar = ParticleSystemQuad::create(StringUtils::format("DinoColor/particle/penParticle%d.plist",parIndex));
    penPar->setPosition(parPos);
    penPar->setTag(kPenPartTag);
    penPar->setAutoRemoveOnFinish(true);
    this->addChild(penPar);
}

bool ColorCanvasView::onTouchBegan(Touch *touch, Event *event)
{
    buyState=ColorManager::shared()->buyState;
    Vec2 location = Director::getInstance()->convertToGL(touch->getLocationInView());
    Vec2 start = touch->getLocation();
    if (ColorManager::shared()->m_DrawType == Draw_Point) {
//        m_pBrush->setColor(ColorManager::shared()->m_pColor);
//        m_pBrush->setOpacity(125);
    }else if(ColorManager::shared()->m_DrawType == Draw_Eraser){
//        m_pBrush->setColor(Color3B::WHITE);
//        m_pBrush->setOpacity(125);
    }
    
    if( ColorManager::shared()->scrollPenBoard==false && showParColor==false&&!buyState){
        showParColor = true;
        this->penParticleAction(location);
    }
    
//    for (int i = 0; i< m_DrawArray.size(); i++) {
//        ColorSprite* sp = (ColorSprite*)this->getChildByTag(m_DrawArray.size()-(i+1));
//        if (sp->isTouched(touch)) {
//            m_DrawingSp = sp ;
//            if (ColorManager::shared()->m_DrawType == Draw_Plating) {
////              sp->PlatingSprite(ColorManager::shared()->m_pColor,m_pCanvas);
//            }
//            break;
//        }
//    }
//    Vec2 posInCloseMenu = closeMenu->convertToNodeSpace(start);
//    if (Delete != NULL && Delete->getBoundingBox().containsPoint(posInCloseMenu)) {
//        Delete->setEnabled(true);
//    }else {
        for (int i = 0; i< m_ClipDrawArray.size(); i++) {
            ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray.at(m_ClipDrawArray.size()-(i+1));
            if (sp != NULL&&!buyState) {
                ColorSprite* colorSpr = (ColorSprite*)sp->getStencil();
    //            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
    //            Vec2 posInNode = sp->convertToNodeSpace(start);
    //            if (colorSpr->isTouched(touch)) {
                if (sp->isTouched(touch)) {
    //                colorSpr->setColor(ColorManager::shared()->m_pColor);
    //                sp->testBrushing(start);
                    
                    
                    if (ColorManager::shared()->SelectBrushTag == Brush_Paintbucket && ColorManager::shared()->m_DrawType != Draw_Eraser && ColorManager::shared()->scrollPenBoard==false) {
                        ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
                        if (colorSpr != NULL) {
                            colorSpr->clearColorSpr();
                            colorSpr->setColor(ColorManager::shared()->m_pColor);
                        }
                    }else {
                        m_ClippingNode = sp;
                    }
                    break;
                }
            }

        }
//        this->hideToolsBoard();
//    }
    
    return true;
}
 
void ColorCanvasView::onTouchMoved(Touch *touch, Event *event)
{
    Layer* buyLayer = (Layer*)this->getChildByTag(kBuyLayerTag);
    Vec2 location = Director::getInstance()->convertToGL(touch->getLocationInView());
    CCLOG("---%d---",ColorManager::shared()->scrollPenBoard);
    if( ColorManager::shared()->scrollPenBoard==false&&!buyLayer){
        if (ColorManager::shared()->m_DrawType == Draw_Plating||m_ClippingNode ==  NULL) {
            return;
        }
        
        
        ParticleSystemQuad* penPar = (ParticleSystemQuad*)this->getChildByTag(kPenPartTag);
        if (penPar != NULL) {
            penPar->setPosition(location);
        }
        Vec2 start = touch->getLocation();
        Vec2 end = touch->getPreviousLocation();
        Rect rect =whiteCanvas->getBoundingBox();
        if(ColorManager::shared()->colorNums == 2 || ColorManager::shared()->colorNums == 3){
            ColorManager::shared()->doubleColorChange();
        }
        
        if(selectRaser==true){
            rect.origin.x +=15 ;
            rect.origin.y +=20 ;
            rect.size.width -= 35 ;
            rect.size.height -= 40 ;
        }else{
            if(GameManager::sharedManager()->isAndroidPad()){
                rect.origin.x =0 ;
                rect.origin.y +=20 ;
                rect.size.width -= 575 ;
                rect.size.height -= 40 ;
            }else if(GameManager::sharedManager()->isIphoneX()){
                rect.origin.x -=10 ;
                rect.origin.y +=20 ;
                rect.size.width -= 220 ;
                rect.size.height -= 40 ;
            }else{
                rect.origin.x -=10 ;
                rect.origin.y +=20 ;
                rect.size.width -= 450 ;
                rect.size.height -= 40 ;
            }
        }
        

        


    //    if (rect.containsPoint(start)&&
    //        rect.containsPoint(end)&&m_DrawingSp != NULL)
    //    {
    //        DrawNode* drawer = m_DrawingSp->m_Drawer;
    //        Color4F color ;
    //        int line_w = 15 ;
    //
    //        m_DrawingSp->testBrushing(start);
    //
    //        if(ColorManager::shared()->m_DrawType == Draw_Eraser){
    //            color = Color4F(Color3B::WHITE);
    //        }else{
    //            switch (ColorManager::shared()->SelectBrushTag) {
    //                case 100:
    //                    line_w = 3;
    //                    break;
    //                case 101:
    //                line_w = 15;
    //                break;
    //                case 102:
    //                line_w = 25;
    //                break;
    //                default:
    //                    break;
    //            }
    //            color = Color4F(ColorManager::shared()->m_pColor);
    //        }
    //
    //        if (!start.equals(end)) {
    //            drawer->drawSegment(end, start, line_w, color);
    //        }
    //        drawer->drawDot(start, line_w, color);
    //
    //    }
        if (rect.containsPoint(start)&&
            rect.containsPoint(end)&&m_ClippingNode != NULL)
        {
            
            m_ClippingNode->toolsBrushing(start,end);
        }
    }
    

}

void ColorCanvasView::onTouchEnded(Touch *touch, Event *event)
{
    m_DrawingSp = NULL;
    m_ClippingNode = NULL;
    ParticleSystemQuad* penPar = (ParticleSystemQuad*)this->getChildByTag(kPenPartTag);
    if (penPar != NULL) {
        penPar->removeFromParent();
        penPar = NULL;
        showParColor=false;
    }
    
//    this->showToolsBoard();
}

void ColorCanvasView::onTouchCancelled(Touch *touch, Event *event){
    ParticleSystemQuad* penPar = (ParticleSystemQuad*)this->getChildByTag(kPenPartTag);
    if (penPar != NULL) {
        penPar->removeFromParent();
        penPar = NULL;
        showParColor=false;
    }
}

////----------------------Tool Bar----------

void ColorCanvasView::UpdateChooseColor()
{
    
}

void ColorCanvasView::MakeContent()
{
//    std::string name = StringUtils::format( "DinoColor/dragon-%d/dragon-%d.plist" ,ColorManager::shared()->m_AnimalTag ,ColorManager::shared()->m_AnimalTag );
    std::string name = StringUtils::format("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,ColorManager::shared()->colorAniIndex,ColorManager::shared()->curColorTheme+1,ColorManager::shared()->colorAniIndex);
    ValueMap pointArray = FileUtils::getInstance()->getValueMapFromFile(name);
    if (!pointArray.empty()) {
        for (auto& pair : pointArray) {
            std::string key = pair.first;
//            std::string pngName = StringUtils::format("DinoColor/dragon-%d/%s.png",ColorManager::shared()->m_AnimalTag,key.c_str());
            std::string pngName = StringUtils::format("DinoColor/ColoringType_%d/ColoringType_%d_%d/%s.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,ColorManager::shared()->colorAniIndex,key.c_str());
            std::string value = pair.second.asString();
            Vec2 pos = PointFromString(value);
            pos.x += v_size.width/2 ;
            pos.y += v_size.height/2 ;
            if (key.find("line")!= std::string::npos) {
                Sprite* sprite = Sprite::create(pngName);
                sprite->setPosition(pos);
                this->addChild(sprite,1);
//                m_ClipDrawArray.pushBack(sprite);
            }else{
                ColorSprite* stencilSpr = ColorSprite::CreateColor(pngName, Vec2::ZERO, this, m_DrawArray.size());
                stencilSpr->setAnchorPoint(Vec2(0.0, 0.0));
                stencilSpr->setPosition(Vec2::ZERO);
                ColorSprite* sp = ColorSprite::CreateColor(pngName, Vec2(stencilSpr->getContentSize().width/2, stencilSpr->getContentSize().height/2), this, m_DrawArray.size());
//                ColorNode* sp = ColorNode::createColorNode(Size(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
//                sp->setAnchorPoint(Vec2(0.0, 0.0));
//                sp->setPosition(Vec2::ZERO);
                sp->curSprName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(ColorManager::shared()->colorAniIndex)+key;
                
                sp->showLastSceneImage();
                sp->initBrushNode();
//                sp->setColor(Color3B::BLUE);
//                sp->setColor(Color3B::BLUE);
//                ClippingNode *clip = ClippingNode::create(sp);
                ColoringClippingNode *clip = ColoringClippingNode::create(stencilSpr);
                clip->initClippingNode();
                clip->setContentSize(Size(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
                clip->setAnchorPoint(Vec2(0.5, 0.5));
                clip->setPosition(pos);
                sp->setTag(20);
                clip->setAlphaThreshold(0.0f);
                this->addChild(clip);
//                DrawNode* drawer = DrawNode::create();
//                clip->addChild(drawer);
//                sp->m_Drawer = drawer;

                clip->addChild(sp);

                m_DrawArray.pushBack(stencilSpr);
                m_ClipDrawArray.pushBack(clip);
            }
            
        }
        
    }
}

void ColorCanvasView::MakeToolBar()
{
    w_fix = 0 ;
//    if (GameManager::sharedManager()->isIphoneX()) {
//        w_fix = 50 ;
//    }

    Button* back = Button::create("universal/back.png");
    back->setPosition(Vec2(poszero.x+ 50,v_size.height-50));
    this->addChild(back, 3);
    buyState=ColorManager::shared()->buyState;
    back->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
        if(type == Widget::TouchEventType::ENDED){
            this->backClick();
        }
    });

//    Button* camerabtu = Button::create("universal/camera.png");
//    camerabtu->setPosition(Vec2(poszero.x+ camerabtu->getContentSize().width/2*3,v_size.height-50));
//    this->addChild(camerabtu, 3);
//    camerabtu->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
//        if(type == Widget::TouchEventType::ENDED){
//            this->removeNouesImage();
//        }
//    });
    
//    Sprite* colorBg = Sprite::create("DinoColor/color_bg.png");
//    colorBg->setPosition(Vec2(v_size.width -80 - w_fix-poszero.x,v_size.height/2));
////    toolsBg->setScaleX(0.7);
//    this->addChild(colorBg,2) ;
    
    
    
    toolsBg = Sprite::create("DinoColor/buttonBg.png");
    toolsBg->setPosition(Vec2(v_size.width -50 - w_fix-poszero.x,v_size.height/2));
//    toolsBg->setScaleX(0.7);
    this->addChild(toolsBg,5) ;
    
    Sprite* buttonSelect = Sprite::create("DinoColor/toolsUI/buttonSelect.png");
    buttonSelect->setPosition(Vec2(v_size.width -50 - w_fix-poszero.x,v_size.height/1.13));
    buttonSelect->setTag(kButtonSelectTag);
    this->addChild(buttonSelect,6) ;
    
    toolsBgInitPos = toolsBg->getPosition();
    
    int firstPendisX = 0;
    
    std::string names[] = {"pencil","paint","crayon","paintbucket","largebrush","eraser"} ;
    for (int i =0; i<6; i++) {
        ButtonNames[i] = names[i];
    }
    Menu* penMenu = Menu::create();
    penMenu->setPosition(Vec2(0,0));
    penMenu->setTag(kPenMenuTag);
    this->addChild(penMenu,10);
       for (int i = 0; i < 5; i++) {
           if (i==0) {
               firstPendisX = -15;
           }else{
               firstPendisX = 0;
           }
           std::string name = StringUtils::format("DinoColor/toolsUI/%s.png",ButtonNames[i].c_str());
           Sprite* penNormalButton   = Sprite::create(name);
//           penNormalButton->setPosition(Vec2(toolsBg->getContentSize().width/2, toolsBg->getContentSize().height/1.07-i*100));
//           penNormalButton->setTag(kPenButtonTag+i);
//           penNormalButton->setScale(0.7);
           
//           std::string name = StringUtils::format("DinoColor/toolsUI/%s.png",names[i].c_str());
           Sprite* penSelectButton   = Sprite::create(name);
//           penSelectButton->setScale(0.7);
           MenuItemSprite* penButton = MenuItemSprite::create(penNormalButton, penSelectButton, CC_CALLBACK_1(ColorCanvasView::clickPenButton, this));
           penButton->setPosition(Vec2(v_size.width -50 - w_fix-poszero.x+firstPendisX,v_size.height/1.13-i*100));
           penButton->setTag(kPenButtonTag+i);
           penMenu->addChild(penButton,100);

       }

    

    std::string name = StringUtils::format("DinoColor/toolsUI/%s.png",ButtonNames[5].c_str());
    Sprite* penNormalButton   = Sprite::create(name);
    Sprite* penSelectButton   = Sprite::create(name);
    MenuItemSprite* penButton = MenuItemSprite::create(penNormalButton, penSelectButton, [this](Ref* sender){
        this->ChangeRraser();
    });
    penButton->setPosition(Vec2(v_size.width -40 - w_fix-poszero.x,v_size.height/1.13-5*100));
    penButton->setTag(kPenButtonTag+5);
    penMenu->addChild(penButton,100);
    
    Menu* deleteMenu = Menu::create();
    deleteMenu->setPosition(Vec2(0,0));
    this->addChild(deleteMenu,10);
    Sprite* deleteNormalButton   = Sprite::create("DinoColor/toolsUI/normalDelete.png");
    Sprite* deleteSelectButton   = Sprite::create("DinoColor/toolsUI/selectDelete.png");
    MenuItemSprite* deleteButton = MenuItemSprite::create(deleteNormalButton, deleteSelectButton, CC_CALLBACK_1(ColorCanvasView::ClearCanvas, this));
    deleteButton->setPosition(Vec2(poszero.x+ 50,v_size.height/1.13-5*100));
    deleteButton->setTag(kPenButtonTag+6);
    deleteButton->setScale(0.6);
    deleteMenu->addChild(deleteButton,100);

    
//    Sprite* normalBtn = Sprite::create("DinoColor/toolsbg_normal.png");
//    Sprite* selectedBtn = Sprite::create("DinoColor/toolsbg_down.png");
    
//    const char* toolsTypeName = "";
//
//    switch (ColorManager::shared()->SelectBrushTag) {
//        case 100:
//        {
//            toolsTypeName = "pencil";
//        }
//            break;
//        case 101:
//        {
//            toolsTypeName = "paint";
//        }
//            break;;
//        case 102:
//        {
//            toolsTypeName = "largebrush";
//        }
//            break;
//        case 103:
//        {
//            toolsTypeName = "paintbucket";
//        }
//            break;
//        case 104:
//        {
//            toolsTypeName = "crayon";
//        }
//            break;
//        default:
//            break;
//    }
//    for (int i = 0; i < 2; i++) {
//
//        Sprite* brushIconSpr = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_cover.png",toolsTypeName));
//        if (brushIconSpr != NULL) {
//            brushIconSpr->setScale(0.45);
//            brushIconSpr->setRotation(30);
//            brushIconSpr->setTag(ToolsIcon_Tag);
//
//            Sprite* brushIconShadow = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",toolsTypeName));
//            brushIconShadow->setPosition(Vec2(brushIconSpr->getContentSize().width/2, brushIconSpr->getContentSize().height/2));
//            brushIconShadow->setColor(ColorManager::shared()->m_pColor);
//            brushIconShadow->setTag(ToolsIconShadow_Tag);
//            brushIconSpr->addChild(brushIconShadow,-1);
//
//            if (i == 0) {
//                brushIconSpr->setPosition(Vec2(normalBtn->getContentSize().width/2, normalBtn->getContentSize().height/2+10));
//                normalBtn->addChild(brushIconSpr);
//            } else {
//                brushIconSpr->setPosition(Vec2(selectedBtn->getContentSize().width/2, selectedBtn->getContentSize().height/2));
//                selectedBtn->addChild(brushIconSpr);
//            }
//
//        }
//    }
//    brush = MenuItemSprite::create(normalBtn, selectedBtn, CC_CALLBACK_1(ColorCanvasView::ClickBrush, this));
//
//    Sprite* color_normal = Sprite::create("DinoColor/color-normal.png");
//    Vec2 pos =Vec2(color_normal->getContentSize().width/2-20, color_normal->getContentSize().height/2+8);
//    Sprite* paint = Sprite::create("DinoColor/paint.png");
//    paint->setPosition(pos);
//    Sprite* paint_shadow = Sprite::create("DinoColor/paint-shadow.png");
//    paint_shadow->setPosition(pos);
//    Sprite* paint_effect = Sprite::create("DinoColor/paint-effect.png");
//    paint_effect->setPosition(pos);
//
//    color_normal->addChild(paint_shadow,0);
//    color_normal->addChild(paint,0,1);
//    paint->setColor(Color3B(255,7,7));
//    color_normal->addChild(paint_effect);
//
//    Sprite* color_down = Sprite::create("DinoColor/color-down.png");
//    Sprite* paint2 = Sprite::create("DinoColor/paint.png");
//    pos = Vec2(pos.x, pos.y-10);
//    paint2->setPosition(pos);
//    Sprite* paint_shadow2 = Sprite::create("DinoColor/paint-shadow.png");
//    paint_shadow2->setPosition(pos);
//    Sprite* paint_effect2 = Sprite::create("DinoColor/paint-effect.png");
//    paint_effect2->setPosition(pos);
//
//    color_down->addChild(paint_shadow2,0);
//    color_down->addChild(paint2,0,1);
//    paint2->setColor(Color3B(255,7,7));
//    color_down->addChild(paint_effect2);
//
//
//    color = MenuItemSprite::create(color_normal, color_down, CC_CALLBACK_1(ColorCanvasView::ClickColor, this));
//
//    eraser = MenuItemSprite::create(Sprite::create("DinoColor/eraser-normal.png"), Sprite::create("DinoColor/eraser-down.png"), [this](Ref* sender){
//        this->ChangeRraser();
//    });
//    eraser->setPosition(Vec2(v_size.width -100 - w_fix-poszero.x, v_size.height/5*1.4)) ;
//
//    Sprite* normalDelete = Sprite::create("DinoColor/Delete.png");
//    normalDelete->setColor(Color3B::BLACK);
//    Sprite* selectedDelete = Sprite::create("DinoColor/Delete.png");
//    Sprite* disableDelete = Sprite::create("DinoColor/Delete.png");
//    disableDelete->setColor(Color3B::GRAY);
//    Delete = MenuItemSprite::create(normalDelete, selectedDelete, disableDelete, CC_CALLBACK_1(ColorCanvasView::ClearCanvas, this));
//    Delete->setPosition(Vec2(v_size.width -100 - w_fix-poszero.x, v_size.height/5*0.6)) ;
//    Delete->setEnabled(false);
//
//    closeMenu = Menu::create(brush,color,eraser,Delete,NULL);
//    closeMenu->setPosition(Vec2(v_size.width -100 - w_fix-poszero.x,v_size.height/2));
//     this->addChild(closeMenu,1000) ;
//
//    toolsMenuPos = closeMenu->getPosition();
//    closeMenu->alignItemsVerticallyWithPadding(30);
//    brush->selected();
}

void ColorCanvasView::showToolsBoard()
{
    Vec2 centerPos = GameManager::sharedManager()->getCenter();
    Vec2 rightPos = GameManager::sharedManager()->getRightBottomPos();
    
    if (toolsBg != NULL) {
        toolsBg->stopAllActions();
        toolsBg->runAction(MoveTo::create(0.2, Vec2(toolsBgInitPos.x, toolsBgInitPos.y)));
    }
    
    if (closeMenu != NULL) {
        closeMenu->stopAllActions();
        closeMenu->runAction(MoveTo::create(0.2, Vec2(toolsMenuPos.x, toolsMenuPos.y)));
    }
}

void ColorCanvasView::hideToolsBoard()
{
    Vec2 rightBottomPos = GameManager::sharedManager()->getRightBottomPos();
    
    if (toolsBg != NULL) {
        toolsBg->runAction(MoveTo::create(0.2, Vec2(rightBottomPos.x+200, toolsBgInitPos.y)));
    }
    
    if (closeMenu != NULL) {
        closeMenu->runAction(MoveTo::create(0.2, Vec2(rightBottomPos.x+200, toolsMenuPos.y)));
    }
    
    Node* Selectlayer = (Node*)this->getChildByTag(9999);
    if (Selectlayer != NULL) {
           
        Selectlayer->removeFromParent();
           //brush->unselected();
    }
    
    Node* ColorLayer = (Node*)this->getChildByTag(999);
    if (ColorLayer != NULL) {
        ColorLayer->removeFromParent();
        color->unselected();
    }
}
   
void ColorCanvasView::ClearCanvas(Ref* pSender)
{
//    Node* layer = (Node*)this->getChildByTag(999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//    }
//    layer = (Node*)this->getChildByTag(9999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//    }
    buyState=ColorManager::shared()->buyState;
    if(!buyState){
        for (int i = 0; i< m_ClipDrawArray.size(); i++) {
            ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray.at(m_ClipDrawArray.size()-(i+1));
            if (sp != NULL) {
                ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
                if (colorSpr != NULL) {
                    colorSpr->clearColorSpr();
                    colorSpr->setColor(Color3B::WHITE);
                    colorSpr->changeBrush();
//                colorSpr->removeAllChildrenWithCleanup(true);
                }
            }

        }

        if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased")){
            if (GameManager::sharedManager()->selectColorPen == 10){
                GameManager::sharedManager()->showInterstitial();
                GameManager::sharedManager()->selectColorPen = 0;
            }else{
                GameManager::sharedManager()->selectColorPen++;
            }
        }
        AudioEngine::play2d("mp3/touchItem.mp3");
    }


//    MenuItemSprite* curClearItem = (MenuItemSprite*)pSender;
//    if (curClearItem != NULL) {
//        curClearItem->setEnabled(false);
//    }
    
//    for (int i = 0; i< m_DrawArray.size(); i++) {
//        ColorSprite* sp = (ColorSprite*)this->getChildByTag(i);
//        sp->m_Drawer->clear();
//    }
}
   
void ColorCanvasView::ChangePlatingMode()
{
    ColorManager::shared()->m_DrawType = Draw_Plating ;
}
   
void ColorCanvasView::ChangePointMode()
{
   ColorManager::shared()->m_DrawType = Draw_Point ;
}
   
void ColorCanvasView::ChangeRraser()
{
    buyState=ColorManager::shared()->buyState;
    ColorManager::shared()->curPenName  = ButtonNames[5].c_str();

    Sprite* buttonSelect = (Sprite*)this->getChildByTag(kButtonSelectTag);
    int raserMoveX=0;
        if (buttonSelect!=NULL&&!buyState) {
            AudioEngine::play2d("mp3/touchItem.mp3");
            touchedButton=true;
            buttonSelect->runAction(Sequence::create(MoveTo::create(0.2, Vec2(v_size.width -40 - w_fix-poszero.x,v_size.height/1.13-5*100)),
                                                       CallFunc::create(CC_CALLBACK_0(ColorCanvasView::canTouchButton, this)),
                                                       NULL));
        }

    
    Menu* penMenu = (Menu*)this->getChildByTag(kPenMenuTag);
    for (int i=0; i<5; i++) {
        MenuItemSprite* otherPenButton = (MenuItemSprite*)penMenu->getChildByTag(kPenButtonTag+i);
        if(otherPenButton!=NULL){
//            otherPenButton->runAction(MoveTo::create(0.2, Vec2(v_size.width -50 - w_fix-poszero.x, 0)));
//            otherPenButton->runAction(MoveBy::create(0.1, Vec2(v_size.width -50 - w_fix-poszero.x, 0)));
            otherPenButton->setPositionX(v_size.width -50 - w_fix-poszero.x);
        }
    }
    if (selectRaser==false&&!buyState) {
        selectRaser = true;
        raserMoveX = -5;
    }else{
        raserMoveX = 0;
    }
        
        MenuItemSprite* raserButton = (MenuItemSprite*)penMenu->getChildByTag(kPenButtonTag+5);
        if (raserButton!=NULL&&!buyState) {
            raserButton->runAction(Spawn::create(Sequence::create(ScaleTo::create(0.1, 1.2),
                                                                    ScaleTo::create(0.1, 1.0),
                                                                                       NULL),
                                                 EaseIn::create(MoveBy::create(0.3, Vec2(raserMoveX, 0)), 0.3),
                                                 NULL));
        }
    

    
//    Node* layer = (Node*)this->getChildByTag(999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//    }
//    layer = (Node*)this->getChildByTag(9999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//        brush->unselected();
//    }
    ColorManager::shared()->m_DrawType = Draw_Eraser ;
   // ColorManager::shared()->m_pColor = Color3B::WHITE ;
//    eraser->selected();
//    color->unselected();
//    brush->unselected();
    
    for (int i = 0; i< m_ClipDrawArray.size(); i++) {
        ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray.at(m_ClipDrawArray.size()-(i+1));
        if (sp != NULL) {
            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
            if (colorSpr != NULL) {
                colorSpr->changeBrush();
            }
        }

    }
    
    ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
    buyState=ColorManager::shared()->buyState;
    if (layer!=NULL && clickEraser==false&&!buyState) {
        clickEraser = true;
        layer->runAction(EaseIn::create(MoveTo::create(0.3, Vec2(layer->getPosition().x+130, layer->getPosition().y)), 0.3));
    }

    if (!UserDefault::getInstance()->getBoolForKey("UnlockAll") && !UserDefault::getInstance()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->selectColorPen == 10){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->selectColorPen = 0;
        }else{
            GameManager::sharedManager()->selectColorPen++;
        }
    }
}

void ColorCanvasView::ClickBrush()
{
    Node* layer = (Node*)this->getChildByTag(999);
    if (layer != NULL) {
        layer->removeFromParent();
    }
    ColorManager::shared()->m_DrawType = Draw_Point ;
    eraser->unselected();
    color->unselected();

    Node* Selectlayer = (Node*)this->getChildByTag(9999);
       if (Selectlayer == NULL) {
           SelectBrush* Selectlayer = SelectBrush::create();
           Selectlayer->setTag(9999);
           Selectlayer->SetMenuItem(brush);
           this->addChild(Selectlayer,10);
       }else{
           Selectlayer->removeFromParent();
           //brush->unselected();
       }
    brush->selected();
}

void ColorCanvasView::showColorBoard(){
    Node* layer = (Node*)this->getChildByTag(999);
    if (layer == NULL) {
        ChooseColorLayer* layer = ChooseColorLayer::create();
        layer->setTag(999);
//        layer->SetMenuItem(color);
        this->addChild(layer,3);
//        color->selected();
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName.c_str());
    }else{
        layer->removeFromParent();
//        color->unselected();
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName.c_str());
    }
}

void ColorCanvasView::clickPenButton(Ref *sender){
    MenuItemSprite* penButton = (MenuItemSprite*)sender;
    buyState=ColorManager::shared()->buyState;
    int penIndex =penButton->getTag();
    clickEraser = false;
    if (touchedButton==false && penButton!=NULL&&!buyState) {
        selectRaser = false;
        
        ColorManager::shared()->m_DrawType = Draw_Point ;
        
        AudioEngine::play2d("mp3/touchItem.mp3");
        Sprite* buttonSelect = (Sprite*)this->getChildByTag(kButtonSelectTag);
        selectPosY = penButton->getPosition().y;
        if (buttonSelect!=NULL) {
                touchedButton=true;
                buttonSelect->runAction(Sequence::create(MoveTo::create(0.2, Vec2(v_size.width -50 - w_fix-poszero.x, selectPosY)),
                                                           CallFunc::create(CC_CALLBACK_0(ColorCanvasView::canTouchButton, this)),
                                                           NULL));
        }

        int scaleColor = penButton->getScale();
        penButton->runAction(Spawn::create(Sequence::create(ScaleTo::create(0.1, scaleColor+0.2),
                                                                ScaleTo::create(0.1, scaleColor),
                                                                                   NULL),
                                             EaseIn::create(MoveBy::create(0.3, Vec2(-15, 0)), 0.3),
                                             NULL));
        
        
        
        Menu* penMenu = (Menu*)this->getChildByTag(kPenMenuTag);
        for (int i=0; i<6; i++) {
            MenuItemSprite* otherPenButton = (MenuItemSprite*)penMenu->getChildByTag(kPenButtonTag+i);
            if (i!=penIndex && i<5) {
                otherPenButton->setPositionX(v_size.width -50 - w_fix-poszero.x);
//                otherPenButton->runAction(MoveBy::create(0.1, Vec2(v_size.width -50 - w_fix-poszero.x, 0)));
            }else if(i==5){
                otherPenButton->setPositionX(v_size.width -40 - w_fix-poszero.x);
            }
        }
        
        
        ColorManager::shared()->SelectBrushTag = penIndex;
        
        ColorManager::shared()->curPenName  = ButtonNames[penIndex-100].c_str() ;
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName.c_str());
        ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
        if (layer != NULL) {
            layer->removeFromParent();
        }
        layer = ChooseColorLayer::create();
        layer->setTag(999);
    //    layer->SetMenuItem(color);
        this->addChild(layer,3);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("colorcanvas.changebrush");
    }


}

void ColorCanvasView::canTouchButton(){
    touchedButton = false;
}

void ColorCanvasView::changeBrushCallback()
{
//    Sprite* pait = ( Sprite*)color->getSelectedImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
//    pait = ( Sprite*)color->getNormalImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
    
    for (int i = 0; i< m_ClipDrawArray.size(); i++) {
        ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray.at(m_ClipDrawArray.size()-(i+1));
        if (sp != NULL) {
            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            Vec2 posInNode = sp->convertToNodeSpace(start);
//            if (colorSpr->isTouched(touch)) {
            if (colorSpr != NULL) {
                colorSpr->changeBrush();
            }
        }

    }
}

void ColorCanvasView::ClickColor()
{
//    eraser->unselected();
//    //brush->unselected();
//    Node* layer = (Node*)this->getChildByTag(999);
//    if (layer == NULL) {
//        ChooseColorLayer* layer = ChooseColorLayer::create();
//        layer->setTag(999);
//        layer->SetMenuItem(color);
//        this->addChild(layer,10);
//        color->selected();
//
//    }else{
//        layer->removeFromParent();
//        color->unselected();
//    }
//    layer = (Node*)this->getChildByTag(9999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//        //brush->unselected();
//    }
}

void ColorCanvasView::changeColorCallback()
{
    
    for (int i = 0; i< m_ClipDrawArray.size(); i++) {
        ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray.at(m_ClipDrawArray.size()-(i+1));
        if (sp != NULL) {
            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            Vec2 posInNode = sp->convertToNodeSpace(start);
//            if (colorSpr->isTouched(touch)) {
            if (colorSpr != NULL) {
                colorSpr->changeColor();
            }
        }

    }
    
//    for (int i = 0; i < 2; i++) {
//        Sprite* btnSpr = NULL;
//        if (i == 0) {
//            btnSpr = (Sprite*)brush->getNormalImage();
//        } else {
//            btnSpr = (Sprite*)brush->getSelectedImage();
//        }
//
//        if (btnSpr != NULL) {
//            Sprite* btnIconSpr = (Sprite*)btnSpr->getChildByTag(ToolsIcon_Tag);
//            Sprite* btnIconShadow = (Sprite*)btnIconSpr->getChildByTag(ToolsIconShadow_Tag);
//
//            if (btnIconShadow != NULL) {
//                btnIconShadow->setColor(ColorManager::shared()->m_pColor);
//            }
//        }
//    }
}

void ColorCanvasView::ClickEraser()
{
    
}

void ColorCanvasView::camera()
{
    buyState=ColorManager::shared()->buyState;
    AudioEngine::play2d("mp3/camera.mp3");
    if (whiteCanvas != NULL&&!buyState) {
//        Image* image = DeviceManager::sharedManager()->getRenderUImage(whiteCanvas);
//        DeviceManager::sharedManager()->cameraSelf(image);
////        DeviceManager::sharedManager()->printImage(image);
    }
//    Image* image = DeviceManager::sharedManager()->getRenderUImage(Director::getInstance()->getRunningScene());
//    DeviceManager::sharedManager()->cameraSelf(image);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(ColorCanvasView::ImageVisible), 0.2);
}


void ColorCanvasView::removeNouesImage(){
//    closeMenu->setVisible(false);
//    camerabtu->setVisible(false);
//    toolsBg->setVisible(false);
//    back->setVisible(false);
//    this->scheduleOnce(CC_SCHEDULE_SELECTOR(ColorCanvasView::camera), 0.2);

}

void ColorCanvasView::ImageVisible(float dt){
//    closeMenu->setVisible(true);
//    camerabtu->setVisible(true);
//    toolsBg->setVisible(true);
//    back->setVisible(true);
}


void ColorCanvasView::resetColorValue(){
    ColorManager::shared()->curPaintIndex = 9;
    ColorManager::shared()->curPencilIndex = 9;
    ColorManager::shared()->curPaintbucketIndex = 9;
    ColorManager::shared()->curCrayonIndex = 9;
    ColorManager::shared()->curLargebrushIndex = 9;
    
    ColorManager::shared()->firstTouchPaint = false;
    ColorManager::shared()->firstTouchCrayon = false;
    ColorManager::shared()->firstTouchPencil = false;
    ColorManager::shared()->firstTouchLargebrush = false;
    ColorManager::shared()->firstTouchPaintbucket = false;
    
    for (int i=0; i<30; i++) {
        ColorManager::shared()->colorPaintPos[i] = 0.0;
        ColorManager::shared()->colorPencilPos[i] = 0.0;
        ColorManager::shared()->colorPaintbucketPos[i] = 0.0;
        ColorManager::shared()->colorCrayonPos[i] = 0.0;
        ColorManager::shared()->colorLargebrushPos[i] = 0.0;
    }
}
