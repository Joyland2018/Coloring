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
    buyState= false;
    touchedButton = false;
    selectRaser = false;
    clickEraser = false;

    showParColor = false;
    
    this->setTouchEnabled(true);
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
//    CCSprite* bg = CCSprite::create("DinoColor/coloring-bg.png");
//    bg->setPosition(winCenter);
//    this->addChild(bg);
//
//   if (GameManager::sharedManager()->isIphoneX()){
//       bg->setScale(1.3);
//   }
    
    
    m_DrawArray = CCArray::create() ;
//    m_DrawArray->retain();
    CC_SAFE_RETAIN(m_DrawArray);
    m_ClipDrawArray = CCArray::create() ;
//    m_ClipDrawArray->retain();
    CC_SAFE_RETAIN(m_ClipDrawArray);
//    whiteCanvas = CCSprite::create("DinoColor/canvas.png");
//    whiteCanvas->setPosition();
//    whiteCanvas->setColor(ccGRAY);
//    this->addChild(whiteCanvas);
    CCSprite* stencilCanvas = CCSprite::create("DinoColor/canvas.png");
    stencilCanvas->setAnchorPoint(ccp(0.0, 0.0));
    stencilCanvas->setPosition(CCPointZero);
    whiteCanvas= ColorSprite::CreateColor("DinoColor/canvas.png", ccp(stencilCanvas->getContentSize().width/2, stencilCanvas->getContentSize().height/2), this, m_DrawArray->count());
//    whiteCanvas = ColorNode::createColorNode(CCSizeMake(stencilCanvas->getContentSize().width, stencilCanvas->getContentSize().height));
//    whiteCanvas->setAnchorPoint(ccp(0.0, 0.0));
//    whiteCanvas->setPosition(CCPointZero);
    whiteCanvas->curSprName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(ColorManager::shared()->colorAniIndex)+"canvas";
    whiteCanvas->showLastSceneImage();
    whiteCanvas->initBrushNode();
    whiteCanvas->setTag(20);
    ColoringClippingNode *clip = ColoringClippingNode::create(stencilCanvas);
    clip->setContentSize(CCSizeMake(stencilCanvas->getContentSize().width, stencilCanvas->getContentSize().height));
    clip->initClippingNode();
    clip->setAlphaThreshold(0.0f);
    clip->setAnchorPoint(ccp(0.5, 0.5));
    clip->setPosition(ccp(stencilCanvas->getContentSize().width/2, stencilCanvas->getContentSize().height/2));
    this->addChild(clip);
    m_ClipDrawArray->addObject(clip);
//    CCDrawNode* drawer = CCDrawNode::create();
//    clip->addChild(drawer);
//    whiteCanvas->m_Drawer = drawer;
    clip->addChild(whiteCanvas);
    m_DrawArray->addObject(stencilCanvas);
    
//    this->addChild(testBrush);
    
    GradonFile = CCString::createWithFormat("dragon-%d",ColorManager::shared()->m_AnimalTag);
    
    ColorManager::shared()->SelectBrushTag = 100;
//    ColorManager::shared()->m_pColor = ccc3(98,170,50);
    this->MakeToolBar();
    this->MakeContent();
    this->showColorBoard();
    
//    ColorManager::shared()->m_pColor = ccc3(98,170,50);
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/sink/sinkBg.mp3", true);
    return true ;
}

void ColorCanvasView::onEnter()
{
    CCLayer::onEnter();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ColorCanvasView::changeBrushCallback), kChangeBrushCallback, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ColorCanvasView::changeColorCallback), kChangeColorCallback, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ColorCanvasView::selectAdsOrIAP), kShowPenColorIapCallback, NULL);
}

void ColorCanvasView::onExit()
{
    CCLayer::onExit();
    
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kChangeBrushCallback);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kChangeColorCallback);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kShowPenColorIapCallback);
    
    CC_SAFE_RELEASE(m_DrawArray);
    CC_SAFE_RELEASE(m_ClipDrawArray);
}


void ColorCanvasView::selectAdsOrIAP() {
        CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
            buyLayer = (CCLayer*)BuyPage::nodeWithID(2);
            buyLayer->setTag(kBuyLayerTag);
            this->addChild(buyLayer, 99);

            CCSize _winSize = GameManager::sharedManager()->getViewVisibleSize();
            CCPoint center = GameManager::sharedManager()->getCenter();

            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), _winSize.width, _winSize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setPosition(ccp(center.x,center.y));
            buyLayer->addChild(blacklayer, -1);
        }
}

void ColorCanvasView::backClick()
{
    buyState=ColorManager::shared()->buyState;
    if(!buyState){
        for (int i = 0; i< m_ClipDrawArray->count(); i++) {
            ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
            if (sp != NULL) {
                ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);

                if (colorSpr != NULL) {

//                ColorManager::shared()->saveInfoToFile(colorSpr->infoArr,colorSpr->curSprName);

                    ColorManager::shared()->saveTextureToFile(colorSpr->curSprName, colorSpr);
                }
            }

        }

        this->resetColorValue();

        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
            if (GameManager::sharedManager()->num == 5){
                GameManager::sharedManager()->showInterstitial();
                GameManager::sharedManager()->num = 0;
            }else{
                GameManager::sharedManager()->num++;
            }
        }

        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        ColorManager::shared()->curPenName = "pencil";
        ColorManager::shared()->firstPlayColor=false;
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, SelectColorAniScene::scene(), ccBLACK));

    }
}

void ColorCanvasView::penParticleAction(CCPoint parPos){
    int parIndex = arc4random()%4+1;
    CCParticleSystemQuad* penPar = CCParticleSystemQuad::create(CCString::createWithFormat("DinoColor/particle/penParticle%d.plist",parIndex)->getCString());
    penPar->setPosition(parPos);
    penPar->setTag(kPenPartTag);
    penPar->setAutoRemoveOnFinish(true);
    this->addChild(penPar);
}

void ColorCanvasView::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
    buyState=ColorManager::shared()->buyState;
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCPoint start = touch->getLocation();
    if (ColorManager::shared()->m_DrawType == Draw_Point) {
//        m_pBrush->setColor(ColorManager::shared()->m_pColor);
//        m_pBrush->setOpacity(125);
    }else if(ColorManager::shared()->m_DrawType == Draw_Eraser){
//        m_pBrush->setColor(ccWHITE);
//        m_pBrush->setOpacity(125);
    }
    
    if( ColorManager::shared()->scrollPenBoard==false && showParColor==false&&!buyState){
        showParColor = true;
        this->penParticleAction(location);
    }
    
//    for (int i = 0; i< m_DrawArray->count(); i++) {
//        ColorSprite* sp = (ColorSprite*)this->getChildByTag(m_DrawArray->count()-(i+1));
//        if (sp->isTouched((CCTouch *)pTouches->anyObject())) {
//            m_DrawingSp = sp ;
//            if (ColorManager::shared()->m_DrawType == Draw_Plating) {
////              sp->PlatingSprite(ColorManager::shared()->m_pColor,m_pCanvas);
//            }
//            break;
//        }
//    }
//    CCPoint posInCloseMenu = closeMenu->convertToNodeSpace(start);
//    if (Delete != NULL && Delete->boundingBox().containsPoint(posInCloseMenu)) {
//        Delete->setEnabled(true);
//    }else {
        for (int i = 0; i< m_ClipDrawArray->count(); i++) {
            ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
            if (sp != NULL&&!buyState) {
                ColorSprite* colorSpr = (ColorSprite*)sp->getStencil();
    //            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
    //            CCPoint posInNode = sp->convertToNodeSpace(start);
    //            if (colorSpr->isTouched((CCTouch *)pTouches->anyObject())) {
                if (sp->isTouched((CCTouch *)pTouches->anyObject())) {
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
    
    
}
 
void ColorCanvasView::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCLOG("---%d---",ColorManager::shared()->scrollPenBoard);
    if( ColorManager::shared()->scrollPenBoard==false&&!buyLayer){
        if (ColorManager::shared()->m_DrawType == Draw_Plating||m_ClippingNode ==  NULL) {
            return;
        }
        
        
        CCParticleSystemQuad* penPar = (CCParticleSystemQuad*)this->getChildByTag(kPenPartTag);
        if (penPar != NULL) {
            penPar->setPosition(location);
        }
        CCTouch *touch = (CCTouch *)pTouches->anyObject();
        CCPoint start = touch->getLocation();
        CCPoint end = touch->getPreviousLocation();
        CCRect rect =whiteCanvas->boundingBox();
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
    //        CCDrawNode* drawer = m_DrawingSp->m_Drawer;
    //        ccColor4F color ;
    //        int line_w = 15 ;
    //
    //        m_DrawingSp->testBrushing(start);
    //
    //        if(ColorManager::shared()->m_DrawType == Draw_Eraser){
    //            color = ccc4FFromccc3B(ccWHITE);
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
    //            color = ccc4FFromccc3B(ColorManager::shared()->m_pColor);
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

void ColorCanvasView::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    m_DrawingSp = NULL;
    m_ClippingNode = NULL;
    CCParticleSystemQuad* penPar = (CCParticleSystemQuad*)this->getChildByTag(kPenPartTag);
    if (penPar != NULL) {
        penPar->removeFromParent();
        penPar = NULL;
        showParColor=false;
    }
    
//    this->showToolsBoard();
}

void ColorCanvasView::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
    CCParticleSystemQuad* penPar = (CCParticleSystemQuad*)this->getChildByTag(kPenPartTag);
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
//    CCString* name = CCString::createWithFormat( "DinoColor/dragon-%d/dragon-%d.plist" ,ColorManager::shared()->m_AnimalTag ,ColorManager::shared()->m_AnimalTag );
    CCString* name = CCString::create( CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/ColoringType_%d_%d.plist",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,ColorManager::shared()->colorAniIndex,ColorManager::shared()->curColorTheme+1,ColorManager::shared()->colorAniIndex)->getCString());
     CCDictionary* pointArray = CCDictionary::createWithContentsOfFile(name->getCString()) ;
    if (pointArray!= NULL) {
        for (int i = 0; i < pointArray->count(); i++) {
            CCString* key = (CCString*)pointArray->allKeys()->objectAtIndex(i);
//            CCString* pngName = CCString::createWithFormat("DinoColor/dragon-%d/%s.png",ColorManager::shared()->m_AnimalTag,key->getCString());
            CCString* pngName = CCString::createWithFormat("DinoColor/ColoringType_%d/ColoringType_%d_%d/%s.png",ColorManager::shared()->curColorTheme+1,ColorManager::shared()->curColorTheme+1,ColorManager::shared()->colorAniIndex,key->getCString());
            CCString* value = (CCString*)pointArray->objectForKey(key->getCString());
            CCPoint pos =CCPointFromString(value->getCString());
            pos.x += v_size.width/2 ;
            pos.y += v_size.height/2 ;
            std::string na =key->getCString();
            if (na.find("line")!= std::string::npos) {
                CCSprite* sprite = CCSprite::create(pngName->getCString());
                sprite->setPosition(pos);
                this->addChild(sprite,1);
//                m_ClipDrawArray->addObject(sprite);
            }else{
                ColorSprite* stencilSpr = ColorSprite::CreateColor(pngName->getCString(), CCPointZero, this, m_DrawArray->count());
                stencilSpr->setAnchorPoint(ccp(0.0, 0.0));
                stencilSpr->setPosition(CCPointZero);
                ColorSprite* sp = ColorSprite::CreateColor(pngName->getCString(), ccp(stencilSpr->getContentSize().width/2, stencilSpr->getContentSize().height/2), this, m_DrawArray->count());
//                ColorNode* sp = ColorNode::createColorNode(CCSizeMake(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
//                sp->setAnchorPoint(ccp(0.0, 0.0));
//                sp->setPosition(CCPointZero);
                sp->curSprName = "ColoringType_"+std::to_string(ColorManager::shared()->curColorTheme+1)+"_"+std::to_string(ColorManager::shared()->colorAniIndex)+key->m_sString;
                
                sp->showLastSceneImage();
                sp->initBrushNode();
//                sp->setColor(ccBLUE);
//                sp->setColor(ccBLUE);
//                CCClippingNode *clip = CCClippingNode::create(sp);
                ColoringClippingNode *clip = ColoringClippingNode::create(stencilSpr);
                clip->initClippingNode();
                clip->setContentSize(CCSizeMake(stencilSpr->getContentSize().width, stencilSpr->getContentSize().height));
                clip->setAnchorPoint(ccp(0.5, 0.5));
                clip->setPosition(pos);
                sp->setTag(20);
                clip->setAlphaThreshold(0.0f);
                this->addChild(clip);
//                CCDrawNode* drawer = CCDrawNode::create();
//                clip->addChild(drawer);
//                sp->m_Drawer = drawer;

                clip->addChild(sp);

                m_DrawArray->addObject(stencilSpr);
                m_ClipDrawArray->addObject(clip);
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

    CCSprite* tmp2 = CCSprite::create("universal/back.png");
    CCSize size2 = tmp2->getContentSize();
    CCRect insetRect2 = CCRectMake(2,2,size2.width, size2.height);
    CCScale9Sprite* sprite2 = CCScale9Sprite::create("universal/back.png", insetRect2) ;
    back  = CCControlButton::create(sprite2) ;
    back->setPreferredSize(size2) ;
    back->setPosition(ccp(poszero.x+ 50,v_size.height-50)) ;
    this->addChild(back, 3) ;
    buyState=ColorManager::shared()->buyState;
    back->addTargetWithActionForControlEvents(this, cccontrol_selector(ColorCanvasView::backClick), CCControlEventTouchUpInside) ;

//    CCSprite* catmp2 = CCSprite::create("universal/camera.png");
//    CCSize casize2 = catmp2->getContentSize();
//    CCRect cainsetRect2 = CCRectMake(2,2,casize2.width, casize2.height);
//    CCScale9Sprite* casprite2 = CCScale9Sprite::create("universal/camera.png", cainsetRect2) ;
//    camerabtu= CCControlButton::create(casprite2) ;
//    camerabtu->setPreferredSize(casize2) ;
//    camerabtu->setPosition(ccp(poszero.x+ catmp2->getContentSize().width/2*3,v_size.height-50)) ;
//    this->addChild(camerabtu, 3) ;
//    camerabtu->addTargetWithActionForControlEvents(this, cccontrol_selector(ColorCanvasView::removeNouesImage), CCControlEventTouchUpInside) ;
    
//    CCSprite* colorBg = CCSprite::create("DinoColor/color_bg.png");
//    colorBg->setPosition(ccp(v_size.width -80 - w_fix-poszero.x,v_size.height/2));
////    toolsBg->setScaleX(0.7);
//    this->addChild(colorBg,2) ;
    
    
    
    toolsBg = CCSprite::create("DinoColor/buttonBg.png");
    toolsBg->setPosition(ccp(v_size.width -50 - w_fix-poszero.x,v_size.height/2));
//    toolsBg->setScaleX(0.7);
    this->addChild(toolsBg,5) ;
    
    CCSprite* buttonSelect = CCSprite::create("DinoColor/toolsUI/buttonSelect.png");
    buttonSelect->setPosition(ccp(v_size.width -50 - w_fix-poszero.x,v_size.height/1.13));
    buttonSelect->setTag(kButtonSelectTag);
    this->addChild(buttonSelect,6) ;
    
    toolsBgInitPos = toolsBg->getPosition();
    
    int firstPendisX = 0;
    
    std::string names[] = {"pencil","paint","crayon","paintbucket","largebrush","eraser"} ;
    for (int i =0; i<6; i++) {
        ButtonNames[i] = names[i];
    }
    CCMenu* penMenu = CCMenu::create();
    penMenu->setPosition(ccp(0,0));
    penMenu->setTag(kPenMenuTag);
    this->addChild(penMenu,10);
       for (int i = 0; i < 5; i++) {
           if (i==0) {
               firstPendisX = -15;
           }else{
               firstPendisX = 0;
           }
           CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s.png",ButtonNames[i].c_str()) ;
           CCSprite* penNormalButton   = CCSprite::create(name->getCString());
//           penNormalButton->setPosition(ccp(toolsBg->getContentSize().width/2, toolsBg->getContentSize().height/1.07-i*100));
//           penNormalButton->setTag(kPenButtonTag+i);
//           penNormalButton->setScale(0.7);
           
//           CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s.png",names[i].c_str()) ;
           CCSprite* penSelectButton   = CCSprite::create(name->getCString());
//           penSelectButton->setScale(0.7);
           CCMenuItemSprite* penButton = CCMenuItemSprite::create(penNormalButton, penSelectButton, this, menu_selector(ColorCanvasView::clickPenButton));
           penButton->setPosition(ccp(v_size.width -50 - w_fix-poszero.x+firstPendisX,v_size.height/1.13-i*100));
           penButton->setTag(kPenButtonTag+i);
           penMenu->addChild(penButton,100);

       }

    

    CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s.png",ButtonNames[5].c_str()) ;
    CCSprite* penNormalButton   = CCSprite::create(name->getCString());
    CCSprite* penSelectButton   = CCSprite::create(name->getCString());
    CCMenuItemSprite* penButton = CCMenuItemSprite::create(penNormalButton, penSelectButton, this, menu_selector(ColorCanvasView::ChangeRraser));
    penButton->setPosition(ccp(v_size.width -40 - w_fix-poszero.x,v_size.height/1.13-5*100));
    penButton->setTag(kPenButtonTag+5);
    penMenu->addChild(penButton,100);
    
    CCMenu* deleteMenu = CCMenu::create();
    deleteMenu->setPosition(ccp(0,0));
    this->addChild(deleteMenu,10);
    CCSprite* deleteNormalButton   = CCSprite::create("DinoColor/toolsUI/normalDelete.png");
    CCSprite* deleteSelectButton   = CCSprite::create("DinoColor/toolsUI/selectDelete.png");
    CCMenuItemSprite* deleteButton = CCMenuItemSprite::create(deleteNormalButton, deleteSelectButton, this, menu_selector(ColorCanvasView::ClearCanvas));
    deleteButton->setPosition(ccp(poszero.x+ 50,v_size.height/1.13-5*100));
    deleteButton->setTag(kPenButtonTag+6);
    deleteButton->setScale(0.6);
    deleteMenu->addChild(deleteButton,100);

    
//    CCSprite* normalBtn = CCSprite::create("DinoColor/toolsbg_normal.png");
//    CCSprite* selectedBtn = CCSprite::create("DinoColor/toolsbg_down.png");
    
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
//        CCSprite* brushIconSpr = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_cover.png",toolsTypeName)->getCString());
//        if (brushIconSpr != NULL) {
//            brushIconSpr->setScale(0.45);
//            brushIconSpr->setRotation(30);
//            brushIconSpr->setTag(ToolsIcon_Tag);
//
//            CCSprite* brushIconShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",toolsTypeName)->getCString());
//            brushIconShadow->setPosition(ccp(brushIconSpr->getContentSize().width/2, brushIconSpr->getContentSize().height/2));
//            brushIconShadow->setColor(ColorManager::shared()->m_pColor);
//            brushIconShadow->setTag(ToolsIconShadow_Tag);
//            brushIconSpr->addChild(brushIconShadow,-1);
//
//            if (i == 0) {
//                brushIconSpr->setPosition(ccp(normalBtn->getContentSize().width/2, normalBtn->getContentSize().height/2+10));
//                normalBtn->addChild(brushIconSpr);
//            } else {
//                brushIconSpr->setPosition(ccp(selectedBtn->getContentSize().width/2, selectedBtn->getContentSize().height/2));
//                selectedBtn->addChild(brushIconSpr);
//            }
//
//        }
//    }
//    brush = CCMenuItemSprite::create(normalBtn, selectedBtn, this, menu_selector(ColorCanvasView::ClickBrush));
//
//    CCSprite* color_normal = CCSprite::create("DinoColor/color-normal.png");
//    CCPoint pos =ccp(color_normal->getContentSize().width/2-20, color_normal->getContentSize().height/2+8);
//    CCSprite* paint = CCSprite::create("DinoColor/paint.png");
//    paint->setPosition(pos);
//    CCSprite* paint_shadow = CCSprite::create("DinoColor/paint-shadow.png");
//    paint_shadow->setPosition(pos);
//    CCSprite* paint_effect = CCSprite::create("DinoColor/paint-effect.png");
//    paint_effect->setPosition(pos);
//
//    color_normal->addChild(paint_shadow,0);
//    color_normal->addChild(paint,0,1);
//    paint->setColor(ccc3(255,7,7));
//    color_normal->addChild(paint_effect);
//
//    CCSprite* color_down = CCSprite::create("DinoColor/color-down.png");
//    CCSprite* paint2 = CCSprite::create("DinoColor/paint.png");
//    pos = ccp(pos.x, pos.y-10);
//    paint2->setPosition(pos);
//    CCSprite* paint_shadow2 = CCSprite::create("DinoColor/paint-shadow.png");
//    paint_shadow2->setPosition(pos);
//    CCSprite* paint_effect2 = CCSprite::create("DinoColor/paint-effect.png");
//    paint_effect2->setPosition(pos);
//
//    color_down->addChild(paint_shadow2,0);
//    color_down->addChild(paint2,0,1);
//    paint2->setColor(ccc3(255,7,7));
//    color_down->addChild(paint_effect2);
//
//
//    color = CCMenuItemSprite::create(color_normal, color_down, this, menu_selector(ColorCanvasView::ClickColor));
//
//    eraser = CCMenuItemSprite::create(CCSprite::create("DinoColor/eraser-normal.png"), CCSprite::create("DinoColor/eraser-down.png"), this, menu_selector(ColorCanvasView::ChangeRraser));
//    eraser->setPosition(ccp(v_size.width -100 - w_fix-poszero.x, v_size.height/5*1.4)) ;
//
//    CCSprite* normalDelete = CCSprite::create("DinoColor/Delete.png");
//    normalDelete->setColor(ccBLACK);
//    CCSprite* selectedDelete = CCSprite::create("DinoColor/Delete.png");
//    CCSprite* disableDelete = CCSprite::create("DinoColor/Delete.png");
//    disableDelete->setColor(ccGRAY);
//    Delete = CCMenuItemSprite::create(normalDelete, selectedDelete, disableDelete,this, menu_selector(ColorCanvasView::ClearCanvas));
//    Delete->setPosition(ccp(v_size.width -100 - w_fix-poszero.x, v_size.height/5*0.6)) ;
//    Delete->setEnabled(false);
//
//    closeMenu = CCMenu::create(brush,color,eraser,Delete,NULL);
//    closeMenu->setPosition(ccp(v_size.width -100 - w_fix-poszero.x,v_size.height/2));
//     this->addChild(closeMenu,1000) ;
//
//    toolsMenuPos = closeMenu->getPosition();
//    closeMenu->alignItemsVerticallyWithPadding(30);
//    brush->selected();
}

void ColorCanvasView::showToolsBoard()
{
    CCPoint centerPos = GameManager::sharedManager()->getCenter();
    CCPoint rightPos = GameManager::sharedManager()->getRightBottomPos();
    
    if (toolsBg != NULL) {
        toolsBg->stopAllActions();
        toolsBg->runAction(CCMoveTo::create(0.2, ccp(toolsBgInitPos.x, toolsBgInitPos.y)));
    }
    
    if (closeMenu != NULL) {
        closeMenu->stopAllActions();
        closeMenu->runAction(CCMoveTo::create(0.2, ccp(toolsMenuPos.x, toolsMenuPos.y)));
    }
}

void ColorCanvasView::hideToolsBoard()
{
    CCPoint rightBottomPos = GameManager::sharedManager()->getRightBottomPos();
    
    if (toolsBg != NULL) {
        toolsBg->runAction(CCMoveTo::create(0.2, ccp(rightBottomPos.x+200, toolsBgInitPos.y)));
    }
    
    if (closeMenu != NULL) {
        closeMenu->runAction(CCMoveTo::create(0.2, ccp(rightBottomPos.x+200, toolsMenuPos.y)));
    }
    
    CCNode* Selectlayer = (CCNode*)this->getChildByTag(9999);
    if (Selectlayer != NULL) {
           
        Selectlayer->removeFromParent();
           //brush->unselected();
    }
    
    CCNode* ColorLayer = (CCNode*)this->getChildByTag(999);
    if (ColorLayer != NULL) {
        ColorLayer->removeFromParent();
        color->unselected();
    }
}
   
void ColorCanvasView::ClearCanvas(CCObject* pSender)
{
//    CCNode* layer = (CCNode*)this->getChildByTag(999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//    }
//    layer = (CCNode*)this->getChildByTag(9999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//    }
    buyState=ColorManager::shared()->buyState;
    if(!buyState){
        for (int i = 0; i< m_ClipDrawArray->count(); i++) {
            ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
            if (sp != NULL) {
                ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
                if (colorSpr != NULL) {
                    colorSpr->clearColorSpr();
                    colorSpr->setColor(ccWHITE);
                    colorSpr->changeBrush();
//                colorSpr->removeAllChildrenWithCleanup(true);
                }
            }

        }

        if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
            if (GameManager::sharedManager()->selectColorPen == 10){
                GameManager::sharedManager()->showInterstitial();
                GameManager::sharedManager()->selectColorPen = 0;
            }else{
                GameManager::sharedManager()->selectColorPen++;
            }
        }
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }


//    CCMenuItemSprite* curClearItem = (CCMenuItemSprite*)pSender;
//    if (curClearItem != NULL) {
//        curClearItem->setEnabled(false);
//    }
    
//    for (int i = 0; i< m_DrawArray->count(); i++) {
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

    CCSprite* buttonSelect = (CCSprite*)this->getChildByTag(kButtonSelectTag);
    int raserMoveX=0;
        if (buttonSelect!=NULL&&!buyState) {
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            touchedButton=true;
            buttonSelect->runAction(CCSequence::create(CCMoveTo::create(0.2, ccp(v_size.width -40 - w_fix-poszero.x,v_size.height/1.13-5*100)),
                                                       CCCallFunc::create(this, callfunc_selector(ColorCanvasView::canTouchButton)),
                                                       NULL));
        }

    
    CCSprite* penMenu = (CCSprite*)this->getChildByTag(kPenMenuTag);
    for (int i=0; i<5; i++) {
        CCSprite* otherPenButton = (CCSprite*)penMenu->getChildByTag(kPenButtonTag+i);
        if(otherPenButton!=NULL){
//            otherPenButton->runAction(CCMoveTo::create(0.2, ccp(v_size.width -50 - w_fix-poszero.x, 0)));
//            otherPenButton->runAction(CCMoveBy::create(0.1, ccp(v_size.width -50 - w_fix-poszero.x, 0)));
            otherPenButton->setPositionX(v_size.width -50 - w_fix-poszero.x);
        }
    }
    if (selectRaser==false&&!buyState) {
        selectRaser = true;
        raserMoveX = -5;
    }else{
        raserMoveX = 0;
    }
        
        CCSprite* raserButton = (CCSprite*)penMenu->getChildByTag(kPenButtonTag+5);
        if (raserButton!=NULL&&!buyState) {
            raserButton->runAction(CCSpawn::create(CCSequence::create(CCScaleTo::create(0.1, 1.2),
                                                                    CCScaleTo::create(0.1, 1.0),
                                                                                       NULL),
                                                 CCEaseIn::create(CCMoveBy::create(0.3, ccp(raserMoveX, 0)), 0.3),
                                                 NULL));
        }
    

    
//    CCNode* layer = (CCNode*)this->getChildByTag(999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//    }
//    layer = (CCNode*)this->getChildByTag(9999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//        brush->unselected();
//    }
    ColorManager::shared()->m_DrawType = Draw_Eraser ;
   // ColorManager::shared()->m_pColor = ccWHITE ;
//    eraser->selected();
//    color->unselected();
//    brush->unselected();
    
    for (int i = 0; i< m_ClipDrawArray->count(); i++) {
        ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
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
        layer->runAction(CCEaseIn::create(CCMoveTo::create(0.3, ccp(layer->getPosition().x+130, layer->getPosition().y)), 0.3));
    }

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") && !CCUserDefault::sharedUserDefault()->getBoolForKey("purchased")){
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
       }else{
           Selectlayer->removeFromParent();
           //brush->unselected();
       }
    brush->selected();
}

void ColorCanvasView::showColorBoard(){
    CCNode* layer = (CCNode*)this->getChildByTag(999);
    if (layer == NULL) {
        ChooseColorLayer* layer = ChooseColorLayer::create();
        layer->setTag(999);
//        layer->SetMenuItem(color);
        this->addChild(layer,3);
//        color->selected();
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
    }else{
        layer->removeFromParent();
//        color->unselected();
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
    }
}

void ColorCanvasView::clickPenButton(CCObject *sender){
    CCMenuItemSprite* penButton = (CCMenuItemSprite*)sender;
    buyState=ColorManager::shared()->buyState;
    int penIndex =penButton->getTag();
    clickEraser = false;
    if (touchedButton==false && penButton!=NULL&&!buyState) {
        selectRaser = false;
        
        ColorManager::shared()->m_DrawType = Draw_Point ;
        
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        CCSprite* buttonSelect = (CCSprite*)this->getChildByTag(kButtonSelectTag);
        selectPosY = penButton->getPosition().y;
        if (buttonSelect!=NULL) {
                touchedButton=true;
                buttonSelect->runAction(CCSequence::create(CCMoveTo::create(0.2, ccp(v_size.width -50 - w_fix-poszero.x, selectPosY)),
                                                           CCCallFunc::create(this, callfunc_selector(ColorCanvasView::canTouchButton)),
                                                           NULL));
        }

        int scaleColor = penButton->getScale();
        penButton->runAction(CCSpawn::create(CCSequence::create(CCScaleTo::create(0.1, scaleColor+0.2),
                                                                CCScaleTo::create(0.1, scaleColor),
                                                                                   NULL),
                                             CCEaseIn::create(CCMoveBy::create(0.3, ccp(-15, 0)), 0.3),
                                             NULL));
        
        
        
        CCSprite* penMenu = (CCSprite*)this->getChildByTag(kPenMenuTag);
        for (int i=0; i<6; i++) {
            CCSprite* otherPenButton = (CCSprite*)penMenu->getChildByTag(kPenButtonTag+i);
            if (i!=penIndex && i<5) {
                otherPenButton->setPositionX(v_size.width -50 - w_fix-poszero.x);
//                otherPenButton->runAction(CCMoveBy::create(0.1, ccp(v_size.width -50 - w_fix-poszero.x, 0)));
            }else if(i==5){
                otherPenButton->setPositionX(v_size.width -40 - w_fix-poszero.x);
            }
        }
        
        
        ColorManager::shared()->SelectBrushTag = penIndex;
        
        ColorManager::shared()->curPenName  = ButtonNames[penIndex-100].c_str() ;
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
        ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
        if (layer != NULL) {
            layer->removeFromParent();
        }
        layer = ChooseColorLayer::create();
        layer->setTag(999);
    //    layer->SetMenuItem(color);
        this->addChild(layer,3);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.changebrush");
    }


}

void ColorCanvasView::canTouchButton(){
    touchedButton = false;
}

void ColorCanvasView::changeBrushCallback()
{
//    CCSprite* pait = ( CCSprite*)color->getSelectedImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
//    pait = ( CCSprite*)color->getNormalImage()->getChildByTag(1);
//    pait->setColor(ColorManager::shared()->m_pColor);
    
    for (int i = 0; i< m_ClipDrawArray->count(); i++) {
        ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
        if (sp != NULL) {
            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            CCPoint posInNode = sp->convertToNodeSpace(start);
//            if (colorSpr->isTouched((CCTouch *)pTouches->anyObject())) {
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
//    CCNode* layer = (CCNode*)this->getChildByTag(999);
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
//    layer = (CCNode*)this->getChildByTag(9999);
//    if (layer != NULL) {
//        layer->removeFromParent();
//        //brush->unselected();
//    }
}

void ColorCanvasView::changeColorCallback()
{
    
    for (int i = 0; i< m_ClipDrawArray->count(); i++) {
        ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
        if (sp != NULL) {
            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
//            CCPoint posInNode = sp->convertToNodeSpace(start);
//            if (colorSpr->isTouched((CCTouch *)pTouches->anyObject())) {
            if (colorSpr != NULL) {
                colorSpr->changeColor();
            }
        }

    }
    
//    for (int i = 0; i < 2; i++) {
//        CCSprite* btnSpr = NULL;
//        if (i == 0) {
//            btnSpr = (CCSprite*)brush->getNormalImage();
//        } else {
//            btnSpr = (CCSprite*)brush->getSelectedImage();
//        }
//
//        if (btnSpr != NULL) {
//            CCSprite* btnIconSpr = (CCSprite*)btnSpr->getChildByTag(ToolsIcon_Tag);
//            CCSprite* btnIconShadow = (CCSprite*)btnIconSpr->getChildByTag(ToolsIconShadow_Tag);
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
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/camera.mp3");
    if (whiteCanvas != NULL&&!buyState) {
//        CCImage* image = DeviceManager::sharedManager()->getRenderUImage(whiteCanvas);
//        DeviceManager::sharedManager()->cameraSelf(image);
////        DeviceManager::sharedManager()->printImage(image);
    }
//    CCImage* image = DeviceManager::sharedManager()->getRenderUImage(CCDirector::sharedDirector()->getRunningScene());
//    DeviceManager::sharedManager()->cameraSelf(image);
    this->scheduleOnce(schedule_selector(ColorCanvasView::ImageVisible), 0.2);
}


void ColorCanvasView::removeNouesImage(){
//    closeMenu->setVisible(false);
//    camerabtu->setVisible(false);
//    toolsBg->setVisible(false);
//    back->setVisible(false);
//    this->scheduleOnce(schedule_selector(ColorCanvasView::camera), 0.2);

}

void ColorCanvasView::ImageVisible(){
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
