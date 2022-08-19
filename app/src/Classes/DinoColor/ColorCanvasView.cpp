//
//  ColorCanvasView.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//


#include "ColorCanvasView.h"
#include "SelectAnimalScene.h"
#include "GameManager.h"
#include "ChooseColorLayer.h"
//#include "DeviceManager.h"
#include "SelectBrushLayer.h"

#define DrawSprite_Tag 10000


CCScene* ColorCanvasView::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
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
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite* bg = CCSprite::create("DinoColor/coloring-bg.png");
    bg->setPosition(winCenter);
    this->addChild(bg);
    
   if (GameManager::sharedManager()->isIphoneX()){
       bg->setScale(1.3);
   }
    
    m_DrawArray = CCArray::create() ;
    m_DrawArray->retain();
    m_ClipDrawArray = CCArray::create() ;
    m_ClipDrawArray->retain();
//    whiteCanvas = CCSprite::create("DinoColor/canvas.png");
//    whiteCanvas->setPosition();
//    whiteCanvas->setColor(ccGRAY);
//    this->addChild(whiteCanvas);
    
    whiteCanvas= ColorSprite::CreateColor("DinoColor/canvas.png", ccp(winCenter.x-50, winCenter.y), this, m_DrawArray->count());
    CCClippingNode *clip = CCClippingNode::create(whiteCanvas);
    clip->setAlphaThreshold(0.0f);
    this->addChild(clip);
    m_ClipDrawArray->addObject(clip);
    CCDrawNode* drawer = CCDrawNode::create();
    clip->addChild(drawer);
    whiteCanvas->m_Drawer = drawer;
    m_DrawArray->addObject(whiteCanvas);
    
    GradonFile = CCString::createWithFormat("dragon-%d",ColorManager::shared()->m_AnimalTag);
    
    ColorManager::shared()->SelectBrushTag = 101;
    ColorManager::shared()->m_pColor = ccc3(255,7,7);
    this->MakeToolBar();
    this->MakeContent();

    ColorManager::shared()->m_pColor = ccc3(255,7,7);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background/sinkBg.mp3", true);

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")) {
//        GameManager::sharedManager()->showBanner(true);
        scheduleUpdate();
    }

    return true ;
}

void ColorCanvasView::update(float date) {
    if(GameManager::sharedManager()->isNeedShowInterstitial()){
        unscheduleUpdate();
        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
            GameManager::sharedManager()->showInterstitial();
            watchedAds = true;
        }
    }
}


void ColorCanvasView::backClick()
{
    GameManager::sharedManager()->minIndex = 1;
    ColorManager::shared()->firstPlayColor=false;
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCDirector::sharedDirector()->replaceScene(SelectAnimalScene::scene());
    if ( !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->num == 3){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->num = 0;
        }else{
            GameManager::sharedManager()->num++;
        }
    }
}


void ColorCanvasView::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
    if (ColorManager::shared()->m_DrawType == Draw_Point) {
//        m_pBrush->setColor(ColorManager::shared()->m_pColor);
//        m_pBrush->setOpacity(125);
    }else if(ColorManager::shared()->m_DrawType == Draw_Eraser){
//        m_pBrush->setColor(ccWHITE);
//        m_pBrush->setOpacity(125);
    }
    if (watchedAds){
        scheduleUpdate();
        watchedAds = false;
    }
    
    for (int i = 0; i< m_DrawArray->count(); i++) {
        ColorSprite* sp = (ColorSprite*)this->getChildByTag(m_DrawArray->count()-(i+1));
        if (sp->isTouched((CCTouch *)pTouches->anyObject())) {

            m_DrawingSp = sp ;
            if (ColorManager::shared()->m_DrawType == Draw_Plating) {
              sp->PlatingSprite(ColorManager::shared()->m_pColor,m_pCanvas);
            }
            break;
        }
    }
    
}
 
void ColorCanvasView::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (ColorManager::shared()->m_DrawType == Draw_Plating||m_DrawingSp ==  NULL) {
        return;
    }
     
   CCTouch *touch = (CCTouch *)pTouches->anyObject();
   CCPoint start = touch->getLocation();
    CCPoint end = touch->getPreviousLocation();
    CCRect rect =whiteCanvas->boundingBox();
    rect.origin.x +=15 ;
    rect.origin.y +=20 ;
    rect.size.width -= 30 ;
    rect.size.height -= 40 ;

    if (rect.containsPoint(start)&&
        rect.containsPoint(end)&&m_DrawingSp != NULL)
    {
        CCDrawNode* drawer = m_DrawingSp->m_Drawer;
        ccColor4F color ;
        int line_w = 15 ;
        
        if(ColorManager::shared()->m_DrawType == Draw_Eraser){
            color = ccc4FFromccc3B(ccWHITE);
        }else{
            switch (ColorManager::shared()->SelectBrushTag) {
                case 100:
                    line_w = 3;
                    break;
                case 101:
                line_w = 15;
                break;
                case 102:
                line_w = 25;
                break;
                default:
                    break;
            }
            color = ccc4FFromccc3B(ColorManager::shared()->m_pColor);
        }
        if (!start.equals(end)) {
            drawer->drawSegment(end, start, line_w, color);
        }
        drawer->drawDot(start, line_w, color);
    }
  
}

void ColorCanvasView::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    m_DrawingSp = NULL;
}

////----------------------Tool Bar----------

void ColorCanvasView::UpdateChooseColor()
{
    
}

void ColorCanvasView::MakeContent()
{
    CCString* name = CCString::createWithFormat( "DinoColor/dragon-%d/dragon-%d.plist" ,ColorManager::shared()->m_AnimalTag ,ColorManager::shared()->m_AnimalTag );
     CCDictionary* pointArray = CCDictionary::createWithContentsOfFile(name->getCString()) ;
    if (pointArray!= NULL) {
        
        for (int i = 0; i < pointArray->count(); i++) {
            CCString* key = (CCString*)pointArray->allKeys()->objectAtIndex(i);
            CCString* pngName = CCString::createWithFormat("DinoColor/dragon-%d/%s.png",ColorManager::shared()->m_AnimalTag,key->getCString());
            CCString* value = (CCString*)pointArray->objectForKey(key->getCString());
            CCPoint pos =CCPointFromString(value->getCString());
            pos.x += v_size.width/2 ;
            pos.y += v_size.height/2 ;
            std::string na =key->getCString();
            if (na.find("line")!= std::string::npos) {
                CCSprite* sprite = CCSprite::create(pngName->getCString());
                sprite->setPosition(pos);
                this->addChild(sprite,1);
                m_ClipDrawArray->addObject(sprite);
            }else{
                ColorSprite* sp = ColorSprite::CreateColor(pngName->getCString(), pos, this, m_DrawArray->count());
                CCClippingNode *clip = CCClippingNode::create(sp);
                clip->setAlphaThreshold(0.0f);
                this->addChild(clip);
                CCDrawNode* drawer = CCDrawNode::create();
                clip->addChild(drawer);
                sp->m_Drawer = drawer;
                m_DrawArray->addObject(sp);
                m_ClipDrawArray->addObject(clip);
            }
            
        }
        
    }
}

void ColorCanvasView::MakeToolBar()
{
    float w_fix = 0 ;
    if (GameManager::sharedManager()->isIphoneX()) {
        w_fix = 50 ;
    }

    CCSprite* tmp2 = CCSprite::create("background/back.png");
    CCSize size2 = tmp2->getContentSize();
    CCRect insetRect2 = CCRectMake(2,2,size2.width, size2.height);
    CCScale9Sprite* sprite2 = CCScale9Sprite::create("background/back.png", insetRect2) ;
    back  = CCControlButton::create(sprite2) ;
    back->setPreferredSize(size2) ;
    back->setPosition(ccp(poszero.x+ 50,v_size.height-50)) ;
    this->addChild(back, 3) ;
    back->addTargetWithActionForControlEvents(this, cccontrol_selector(ColorCanvasView::backClick), CCControlEventTouchUpInside) ;
    
//    CCSprite* catmp2 = CCSprite::create("universal/camera.png");
//    CCSize casize2 = catmp2->getContentSize();
//    CCRect cainsetRect2 = CCRectMake(2,2,casize2.width, casize2.height);
//    CCScale9Sprite* casprite2 = CCScale9Sprite::create("universal/camera.png", cainsetRect2) ;
//    camerabtu= CCControlButton::create(casprite2) ;
//    camerabtu->setPreferredSize(casize2) ;
//    camerabtu->setPosition(ccp(poszero.x+ catmp2->getContentSize().width/2*3,v_size.height-50)) ;
//    this->addChild(camerabtu, 3) ;
//    camerabtu->addTargetWithActionForControlEvents(this, cccontrol_selector(ColorCanvasView::camera), CCControlEventTouchUpInside) ;
    
    toolsBg = CCSprite::create("DinoColor/board.png");
    toolsBg->setPosition(ccp(v_size.width -100 - w_fix-poszero.x,v_size.height/2));
    this->addChild(toolsBg) ;
    
//    if ( ) {
//        <#statements#>
//    }
    switch (ColorManager::shared()->SelectBrushTag) {
        case 100:
             brush = CCMenuItemSprite::create(CCSprite::create("DinoColor/pencil-normal.png"), CCSprite::create("DinoColor/pencil-down.png"), this, menu_selector(ColorCanvasView::ClickBrush));
            break;
        case 101:
             brush = CCMenuItemSprite::create(CCSprite::create("DinoColor/brush-normal.png"), CCSprite::create("DinoColor/brush-down.png"), this, menu_selector(ColorCanvasView::ClickBrush));
                       break;;
        case 102:
             brush = CCMenuItemSprite::create(CCSprite::create("DinoColor/largebrush-normal.png"), CCSprite::create("DinoColor/largebrush-down.png"), this, menu_selector(ColorCanvasView::ClickBrush));
                       break;;
        default:
            break;
    }
    
   
    
    CCSprite* color_normal = CCSprite::create("DinoColor/color-normal.png");
    CCPoint pos =ccp(color_normal->getContentSize().width/2-20, color_normal->getContentSize().height/2+8);
    CCSprite* paint = CCSprite::create("DinoColor/paint.png");
    paint->setPosition(pos);
    CCSprite* paint_shadow = CCSprite::create("DinoColor/paint-shadow.png");
    paint_shadow->setPosition(pos);
    CCSprite* paint_effect = CCSprite::create("DinoColor/paint-effect.png");
    paint_effect->setPosition(pos);
    
    color_normal->addChild(paint_shadow,0);
    color_normal->addChild(paint,0,1);
    paint->setColor(ccc3(255,7,7));
    color_normal->addChild(paint_effect);
    
    CCSprite* color_down = CCSprite::create("DinoColor/color-down.png");
    CCSprite* paint2 = CCSprite::create("DinoColor/paint.png");
    pos = ccp(pos.x, pos.y-10);
    paint2->setPosition(pos);
    CCSprite* paint_shadow2 = CCSprite::create("DinoColor/paint-shadow.png");
    paint_shadow2->setPosition(pos);
    CCSprite* paint_effect2 = CCSprite::create("DinoColor/paint-effect.png");
    paint_effect2->setPosition(pos);
    
    color_down->addChild(paint_shadow2,0);
    color_down->addChild(paint2,0,1);
    paint2->setColor(ccc3(255,7,7));
    color_down->addChild(paint_effect2);
    
    
    color = CCMenuItemSprite::create(color_normal, color_down, this, menu_selector(ColorCanvasView::ClickColor));

    eraser = CCMenuItemSprite::create(CCSprite::create("DinoColor/eraser-normal.png"), CCSprite::create("DinoColor/eraser-down.png"), this, menu_selector(ColorCanvasView::ChangeRraser));
    eraser->setPosition(ccp(v_size.width -100 - w_fix-poszero.x, v_size.height/5*1.4)) ;
   
    CCMenuItemSprite* Delete = CCMenuItemSprite::create(CCSprite::create("DinoColor/Delete.png"), CCSprite::create("DinoColor/Delete.png"), this, menu_selector(ColorCanvasView::ClearCanvas));
    Delete->setPosition(ccp(v_size.width -100 - w_fix-poszero.x, v_size.height/5*0.6)) ;
    
    
    closeMenu = CCMenu::create(brush,color,eraser,Delete,NULL);
    closeMenu->setPosition(ccp(v_size.width -100 - w_fix-poszero.x,v_size.height/2));
     this->addChild(closeMenu,1000) ;
    closeMenu->alignItemsVerticallyWithPadding(30);
    brush->selected();
}
   
void ColorCanvasView::ClearCanvas()
{
    CCNode* layer = (CCNode*)this->getChildByTag(999);
    if (layer != NULL) {
        layer->removeFromParent();
    }
    layer = (CCNode*)this->getChildByTag(9999);
    if (layer != NULL) {
        layer->removeFromParent();
    }
    for (int i = 0; i< m_DrawArray->count(); i++) {
        ColorSprite* sp = (ColorSprite*)this->getChildByTag(i);
        sp->m_Drawer->clear();
    }
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
        if (GameManager::sharedManager()->num == 3){
            GameManager::sharedManager()->showInterstitial();
            GameManager::sharedManager()->num = 0;
        }else{
            GameManager::sharedManager()->num++;
        }
    }
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
    if (watchedAds){
        scheduleUpdate();
        watchedAds = false;
    }
    
    CCNode* layer = (CCNode*)this->getChildByTag(999);
    if (layer != NULL) {
        layer->removeFromParent();
    }
    layer = (CCNode*)this->getChildByTag(9999);
    if (layer != NULL) {
        layer->removeFromParent();
        brush->unselected();
    }
    ColorManager::shared()->m_DrawType = Draw_Eraser ;
   // ColorManager::shared()->m_pColor = ccWHITE ;
    eraser->selected();
    color->unselected();
    brush->unselected();
}

void ColorCanvasView::ClickBrush()
{
    if (watchedAds){
        scheduleUpdate();
        watchedAds = false;
    }

    CCNode* layer = (CCNode*)this->getChildByTag(999);
    if (layer != NULL) {
        layer->removeFromParent();
    }
    ColorManager::shared()->m_DrawType = Draw_Point ;
    eraser->unselected();
    color->unselected();
        
    CCNode* Selectlayer = (CCNode*)this->getChildByTag(9999);
       if (Selectlayer == NULL) {
           SelectBrush* Selectlayer = SelectBrush::create();
           Selectlayer->setTag(9999);
           Selectlayer->SetMenuItem(brush);
           this->addChild(Selectlayer,10);
           brush->selected();
       }else{
           Selectlayer->removeFromParent();
           //brush->unselected();
       }
}

void ColorCanvasView::ClickColor()
{
    if (watchedAds){
        scheduleUpdate();
        watchedAds = false;
    }
    eraser->unselected();
    //brush->unselected();
    CCNode* layer = (CCNode*)this->getChildByTag(999);
    if (layer == NULL) {
        ChooseColorLayer* layer = ChooseColorLayer::create();
        layer->setTag(999);
        layer->SetMenuItem(color);
        this->addChild(layer,10);
        color->selected();
        
    }else{
        layer->removeFromParent();
        color->unselected();
    }
    layer = (CCNode*)this->getChildByTag(9999);
    if (layer != NULL) {
        layer->removeFromParent();
        //brush->unselected();
    }
}

void ColorCanvasView::ClickEraser()
{
    
}

void ColorCanvasView::camera()
{
    closeMenu->setVisible(false);
    camerabtu->setVisible(false);
    toolsBg->setVisible(false);
    SimpleAudioEngine::sharedEngine()->playEffect("background/camera.mp3");
//    CCImage* image = DeviceManager::sharedManager()->getRenderUImage(CCDirector::sharedDirector()->getRunningScene());
//    DeviceManager::sharedManager()->cameraSelf(image);
    closeMenu->setVisible(true);
    camerabtu->setVisible(true);
    toolsBg->setVisible(true);
}

