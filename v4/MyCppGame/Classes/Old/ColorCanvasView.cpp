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
#include "DeviceManager.h"
#include "SelectBrushLayer.hpp"
#include "ColorManager.hpp"
#include "SelectColorAniScene.hpp"
#include "BuyLayer.h"
#include "BookLayer.h"
#include "PrintHelper.h"


#define DrawSprite_Tag 10000

#define ToolsIcon_Tag 31
#define ToolsIconShadow_Tag 32

enum{
    kBuyLayerTag = 0,
    kPenMenuTag = 1,
    kPenPartTag = 5,
    kButtonSelectTag = 6,
    kGuideFingerTag = 19,
    kPenButtonTag =  100,
    kBrushColorShadowTag = 200,
    kBrushColorsShadowTag = 201,
    kRaserTag = 2,
    kPaintLineTag=1999,
    kBookLayerTag = 997,
    kBackLayerTag=998,
    kBookBtnTag = 999,
    kLockBackTag = 599,
    kLockMenuTag = 699,
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
//    touchedButton = false;
    selectRaser = false;
    clickEraser = false;
    
    showParColor = false;
    
    this->setTouchEnabled(true);
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    ColorManager::shared()->SelectBrushTag = Brush_Crayon;
//    CCSprite* bg = CCSprite::create("DinoColor/coloring-bg.png");
//    bg->setPosition(winCenter);
//    this->addChild(bg);
//
//   if (GameManager::sharedManager()->isIphoneX()){
//       bg->setScale(1.3);
//   }
    last_ClippingNode = NULL;
    
    m_DrawArray = CCArray::create() ;
//    m_DrawArray->retain();
    CC_SAFE_RETAIN(m_DrawArray);
    m_ClipDrawArray = CCArray::create() ;
//    m_ClipDrawArray->retain();
    CC_SAFE_RETAIN(m_ClipDrawArray);
    
    last_ClipNodeArray = CCArray::create();
    CC_SAFE_RETAIN(last_ClipNodeArray);
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
    whiteCanvas->changeBrush();
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
    clip->saveLastBrushInNode();
    m_DrawArray->addObject(stencilCanvas);
    
//    this->addChild(testBrush);
    
    GradonFile = CCString::createWithFormat("dragon-%d",ColorManager::shared()->m_AnimalTag);
    
    
//    ColorManager::shared()->m_pColor = ccc3(98,170,50);
    this->MakeToolBar();
    this->MakeContent();
    this->showColorBoard();
    
    CCLog("---是否是%d---",GameManager::sharedManager()->canShowColorBookLayer);
    const char* coinRegion = DeviceManager::sharedManager()->getCurrentDinoRegion();
//    if (GameManager::sharedManager()->checkIsInterestInBook() && strcmp(coinRegion, "US") == 0 && GameManager::sharedManager()->canShowColorBookLayer){
////    if (GameManager::sharedManager()->checkIsDayForShowBookLayer()){
//        GameManager::sharedManager()->curBookGameIndex=0;
//        this->schedule(schedule_selector(ColorCanvasView::checkIsCanShowLayer),1);
////    }
//    }
    
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
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ColorCanvasView::changeBrushColorCallback), kChangeBrushColorCallback, NULL);
    
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("ColoringGuide", false)) {
        this->scheduleOnce(schedule_selector(ColorCanvasView::showFirstGuide), 1.5);
    }
}

void ColorCanvasView::onExit()
{
    CCLayer::onExit();
    
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kChangeBrushCallback);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kChangeColorCallback);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kShowPenColorIapCallback);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, kChangeBrushColorCallback);
    
    if (m_DrawArray != NULL) {
        m_DrawArray->removeAllObjects();
        CC_SAFE_RELEASE(m_DrawArray);
        m_DrawArray = NULL;
    }
    
    if (m_ClipDrawArray != NULL) {
        m_ClipDrawArray->removeAllObjects();
        CC_SAFE_RELEASE(m_ClipDrawArray);
        m_ClipDrawArray = NULL;
    }
    
    if (last_ClipNodeArray != NULL) {
        last_ClipNodeArray->removeAllObjects();
        CC_SAFE_RELEASE(last_ClipNodeArray);
        last_ClipNodeArray = NULL;
    }
}

void ColorCanvasView::selectAdsOrIAP() {
        CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
        if (buyLayer == NULL) {
            buyLayer = (CCLayer*)BuyLayer::nodeWithID(2);
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
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    if (blacklayer==NULL) {
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
        
        ColorManager::shared()->m_DrawType = Draw_Point;
        
        this->resetColorValue();
        
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        ColorManager::shared()->curPenName = "crayon";
        ColorManager::shared()->isNewbieGuideActive = false;
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
    
    if( ColorManager::shared()->scrollPenBoard==false && showParColor==false && ColorManager::shared()->isNewbieGuideActive==false){
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
    ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
    if (deleteMenu != NULL && printMenu != NULL && ColorManager::shared()->isNewbieGuideActive==false) {
        CCMenuItemSprite* deleteItemSpr = (CCMenuItemSprite*)deleteMenu->getChildByTag(kPenButtonTag+6);
        CCMenuItemSprite* printItemSpr = (CCMenuItemSprite*)printMenu->getChildByTag(kPenButtonTag+7);
        CCMenuItemSprite* cancelItemSpr = (CCMenuItemSprite*)printMenu->getChildByTag(kPenButtonTag+8);
        
        if ((deleteItemSpr != NULL && !deleteItemSpr->boundingBox().containsPoint(location)) && (printItemSpr != NULL && !printItemSpr->boundingBox().containsPoint(location)) && (cancelItemSpr != NULL && !cancelItemSpr->boundingBox().containsPoint(location)) && ((layer != NULL && !layer->checkIsTouchingLayer(location)) || layer == NULL)) {
            for (int i = 0; i< m_ClipDrawArray->count(); i++) {
                ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
                if (sp != NULL) {
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
                                colorSpr->clearColorSpr(false);
                                colorSpr->fillColorInSpr(ColorManager::shared()->m_pColor);
    //                            sp->saveLastBrushInNode();
    //                            if (last_ClipNodeArray->count() >= 10) {
    //                                last_ClipNodeArray->removeObjectAtIndex(0);
    //                            }
    //                            last_ClipNodeArray->addObject(sp);
                                this->saveLastBrush(sp);
                            }
                        }else {
                            m_ClippingNode = sp;
                        }
                        break;
                    }
                }

            }
        }
    }
        
//        this->hideToolsBoard();
//    }
    
    
}
 
void ColorCanvasView::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCLOG("---%d---",ColorManager::shared()->scrollPenBoard);
    if( ColorManager::shared()->scrollPenBoard==false && ColorManager::shared()->isNewbieGuideActive==false){
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
            if(DeviceManager::sharedManager()->getIsPad()){
                rect.origin.x -=15 ;
                rect.origin.y +=20 ;
                CCSize curWinSize = GameManager::sharedManager()->getViewVisibleSize();
                if (curWinSize.width > 860) {
                    rect.size.width -= 535 ;
                    rect.size.height -= 20 ;
                } else {
                    rect.size.width -= 600 ;
                    rect.size.height -= 40 ;
                }
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
    if(ColorManager::shared()->isNewbieGuideActive==false){
        if (m_ClippingNode != NULL && last_ClipNodeArray != NULL ) {
    //        last_ClippingNode = m_ClippingNode;
    //        m_ClippingNode->saveLastBrushInNode();
    //        if (last_ClipNodeArray->count() >= 10) {
    //            last_ClipNodeArray->removeObjectAtIndex(0);
    //        }
    //        last_ClipNodeArray->addObject(m_ClippingNode);
            this->saveLastBrush(m_ClippingNode);
        }
        m_ClippingNode = NULL;
        CCParticleSystemQuad* penPar = (CCParticleSystemQuad*)this->getChildByTag(kPenPartTag);
        if (penPar != NULL) {
            penPar->removeFromParent();
            penPar = NULL;
            showParColor=false;
        }
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

void ColorCanvasView::saveLastBrush(ColoringClippingNode *_saveColoringNode){
    if (_saveColoringNode != NULL) {
        
        _saveColoringNode->saveLastBrushInNode();
        if (last_ClipNodeArray->count() >= 10) {
            ColoringClippingNode* lastClippingNode = (ColoringClippingNode*)last_ClipNodeArray->objectAtIndex(0);
            if (lastClippingNode != NULL) {
                lastClippingNode->removeFirstBrushInNode();
                last_ClipNodeArray->removeObjectAtIndex(0);
            }
        }
        last_ClipNodeArray->addObject(_saveColoringNode);
        if (printMenu != NULL) {
            CCMenuItemSprite* cancelMenuItem = (CCMenuItemSprite*)printMenu->getChildByTag(kPenButtonTag+8);
            if (cancelMenuItem != NULL) {
                cancelMenuItem->setEnabled(true);
            }
        }
    }
}

void ColorCanvasView::cancelLastBrush(){
//    if (last_ClippingNode != NULL) {
//        last_ClippingNode->cancelLastBrushInNode();
//    }
    
    if (last_ClipNodeArray != NULL) {
        int clipNodeArrCount = last_ClipNodeArray->count();
        if (clipNodeArrCount > 0) {
            
            ColoringClippingNode* lastClippingNode = (ColoringClippingNode*)last_ClipNodeArray->objectAtIndex(clipNodeArrCount-1);
            if (lastClippingNode != NULL) {
                last_ClipNodeArray->removeObjectAtIndex(clipNodeArrCount-1);
                lastClippingNode->cancelLastBrushInNode();
            }
            
            if (last_ClipNodeArray->count() <= 0) {
                if (printMenu != NULL) {
                    CCMenuItemSprite* cancelMenuItem = (CCMenuItemSprite*)printMenu->getChildByTag(kPenButtonTag+8);
                    if (cancelMenuItem != NULL) {
                        cancelMenuItem->setEnabled(false);
                    }
                }
            }
        }
    }
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
                sprite->setTag(kPaintLineTag);
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
                sp->changeBrush();
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
                clip->saveLastBrushInNode();

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
    
    std::string names[] = {"crayon","paint","pencil","paintbucket","largebrush","eraser"} ;
    for (int i =0; i<6; i++) {
        ButtonNames[i] = names[i];
    }
    CCMenu* penMenu = CCMenu::create();
    penMenu->setPosition(ccp(0,0));
    penMenu->setTag(kPenMenuTag);
    this->addChild(penMenu,10);
    
    
    int colorArr[5]={18,11,6,23,31};
    
    CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
    if (BookLayer==NULL) {
        for (int i = 0; i < 5; i++) {
            if (i==0) {
                firstPendisX = -15;
            }else{
                firstPendisX = 0;
            }
            
            
            
//            CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s.png",ButtonNames[i].c_str()) ;
            CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s_line.png",ButtonNames[i].c_str()) ;
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
            penButton->setScale(0.5);
            penMenu->addChild(penButton,100);
            
            CCString* bgName = CCString::createWithFormat("DinoColor/toolsUI/%s_bg.png",ButtonNames[i].c_str()) ;
            CCSprite* penSelectBg  = CCSprite::create(bgName->getCString());
 //           penSelectButton->setScale(0.7);
            penSelectBg->setPosition(ccp(penButton->getContentSize().width/2, penButton->getContentSize().height/2));
            penButton->addChild(penSelectBg,-1);
            
            
            CCSprite* brushShadow = NULL;
            
//            if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>11 && i<16) {
//                brushShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_shadow%d.png",ButtonNames[i].c_str(),i)->getCString());
////                brushShadow->setVisible(false);
//                brushShadow->setTag(kBrushColorsShadowTag);
//            }else{
                brushShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_shadow.png",ButtonNames[i].c_str())->getCString());
                ccColor3B brushColor;
                brushColor = ColorManager::shared()->getCurColor(colorArr[i]);
//                if((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && i>15){
//                    brushColor = ColorManager::shared()->getCurColor(colorArr[i]);
//                }else{
//                    brushColor = ColorManager::shared()->getCurColor(colorArr[i]);
//                }
                brushShadow->setColor(brushColor);
                brushShadow->setTag(kBrushColorShadowTag);
//            }
            brushShadow->setPosition(ccp(penButton->getContentSize().width/2, penButton->getContentSize().height/2));
            penButton->addChild(brushShadow,-1);
        }
    }


    

    CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s.png",ButtonNames[5].c_str()) ;
    CCSprite* penNormalButton   = CCSprite::create(name->getCString());
    CCSprite* penSelectButton   = CCSprite::create(name->getCString());
    CCMenuItemSprite* penButton = CCMenuItemSprite::create(penNormalButton, penSelectButton, this, menu_selector(ColorCanvasView::ChangeRraser));
    penButton->setPosition(ccp(v_size.width -40 - w_fix-poszero.x,v_size.height/1.13-5*100));
    penButton->setTag(kPenButtonTag+5);
    penMenu->addChild(penButton,100);
    
    int iphoneXoffX_x=0;
    int ipadInitX_x=50;
    int ipadOffX_x=0;
    if (GameManager::sharedManager()->isIphoneX()) {
        iphoneXoffX_x=80;
        
    }
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    float ipadOffY_y=0;
    float btnScale=0.7;
    if (winSize.width < 900) {
        btnScale=0.5;
        ipadOffX_x=-18;
    }
    
    CCLog("---%d---",ipadOffX_x);
    
    deleteMenu = CCMenu::create();
    deleteMenu->setPosition(ccp(0,0));
    this->addChild(deleteMenu,10);
    CCSprite* deleteNormalButton   = CCSprite::create("DinoColor/toolsUI/normalDelete.png");
    CCSprite* deleteSelectButton   = CCSprite::create("DinoColor/toolsUI/selectDelete.png");
    CCMenuItemSprite* deleteButton = CCMenuItemSprite::create(deleteNormalButton, deleteSelectButton, this, menu_selector(ColorCanvasView::ClearCanvas));
    if (winSize.width < 900) {
        ipadOffY_y=0.2;
    }
    deleteButton->setPosition(ccp(poszero.x+ipadInitX_x+ ipadOffX_x +iphoneXoffX_x,v_size.height/1.13-(5+ipadOffY_y)*100));
    deleteButton->setTag(kPenButtonTag+6);
    deleteButton->setScale(btnScale);
    deleteMenu->addChild(deleteButton,100);
    
    
    printMenu = CCMenu::create();
    printMenu->setPosition(ccp(0,0));
    this->addChild(printMenu,10);
    CCSprite* printNormalButton   = CCSprite::create("DinoColor/toolsUI/normalPrint.png");
    CCSprite* printSelectButton   = CCSprite::create("DinoColor/toolsUI/selectPrint.png");
    CCMenuItemSprite* printButton = CCMenuItemSprite::create(printNormalButton, printSelectButton, this, menu_selector(ColorCanvasView::createParentsLock));
    if (winSize.width < 900) {
        ipadOffY_y=0.7;
    }
    printButton->setPosition(ccp(poszero.x+ipadInitX_x+ ipadOffX_x+iphoneXoffX_x,v_size.height/1.13-(3.1+ipadOffY_y)*103));
    printButton->setTag(kPenButtonTag+7);
    printButton->setScale(btnScale);
    printMenu->addChild(printButton,100);
    
    camerabtu = CCMenu::create();
    camerabtu->setPosition(ccp(0,0));
    this->addChild(camerabtu,10);
    CCSprite* cameraNormalButton   = CCSprite::create("DinoColor/toolsUI/normalCamera.png");
    CCSprite* cameraSelectButton   = CCSprite::create("DinoColor/toolsUI/selectCamera.png");
    CCMenuItemSprite* cameraButton = CCMenuItemSprite::create(cameraNormalButton, cameraSelectButton, this, menu_selector(ColorCanvasView::removeNouesImage));
    if (winSize.width < 900) {
        ipadOffY_y=0.95;
    }
    cameraButton->setPosition(ccp(poszero.x+ipadInitX_x+ ipadOffX_x+iphoneXoffX_x,v_size.height/1.13-(2.22+ipadOffY_y)*103));
    cameraButton->setTag(kPenButtonTag+9);
    cameraButton->setScale(btnScale);
    camerabtu->addChild(cameraButton,100);

    CCSprite* cancelNormalButton   = CCSprite::create("DinoColor/toolsUI/normalCancle.png");
    CCSprite* cancelSelectButton   = CCSprite::create("DinoColor/toolsUI/selectCancle.png");
    CCSprite* cancelDisableButton = CCSprite::create("DinoColor/toolsUI/disableCancle.png");
    CCMenuItemSprite* cancelButton = CCMenuItemSprite::create(cancelNormalButton, cancelSelectButton, cancelDisableButton, this, menu_selector(ColorCanvasView::cancelLastBrush));
    if (winSize.width < 900) {
        ipadOffY_y=0.45;
    }
    cancelButton->setPosition(ccp(poszero.x+ipadInitX_x+ ipadOffX_x+iphoneXoffX_x,v_size.height/1.13-(3.9+ipadOffY_y)*105));
    cancelButton->setTag(kPenButtonTag+8);
    cancelButton->setEnabled(false);
    cancelButton->setScale(btnScale);
    printMenu->addChild(cancelButton,100);
    
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
    if(ColorManager::shared()->isNewbieGuideActive==false){
        ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
        if (layer!=NULL) {
            layer->removeFinger();
        }
        
        CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
        if(blacklayer==NULL){
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            for (int i = 0; i< m_ClipDrawArray->count(); i++) {
                ColoringClippingNode* sp = (ColoringClippingNode*)m_ClipDrawArray->objectAtIndex(m_ClipDrawArray->count()-(i+1));
                if (sp != NULL) {
                    ColorSprite* colorSpr = (ColorSprite*)sp->getChildByTag(20);
                    if (colorSpr != NULL) {
                        colorSpr->clearColorSpr(true);
                        colorSpr->setColor(ccWHITE);
                        colorSpr->saveLastBrushInSpr();
                        colorSpr->changeBrush();
        //                colorSpr->removeAllChildrenWithCleanup(true);
                    }
                }

            }
            if (last_ClipNodeArray != NULL) {
                int clipNodeArrCount = last_ClipNodeArray->count();
                if (clipNodeArrCount > 0) {
                    for (int i = 0; i < clipNodeArrCount; i++) {
                        
                        ColoringClippingNode* lastClippingNode = (ColoringClippingNode*)last_ClipNodeArray->objectAtIndex(i);
                        if (lastClippingNode != NULL) {
                            lastClippingNode->removeAllBrushArrInNode();
                        }
                    }
                    last_ClipNodeArray->removeAllObjects();
                    
                    if (last_ClipNodeArray->count() <= 0) {
                        if (printMenu != NULL) {
                            CCMenuItemSprite* cancelMenuItem = (CCMenuItemSprite*)printMenu->getChildByTag(kPenButtonTag+8);
                            if (cancelMenuItem != NULL) {
                                cancelMenuItem->setEnabled(false);
                            }
                        }
                    }
                }
            }
        }
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
    if(ColorManager::shared()->isNewbieGuideActive==false){
        ColorManager::shared()->curPenName  = ButtonNames[5].c_str();
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        CCSprite* buttonSelect = (CCSprite*)this->getChildByTag(kButtonSelectTag);
        int raserMoveX=0;
            if (buttonSelect!=NULL) {
                ColorManager::shared()->touchedPenButton=true;
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
        if (selectRaser==false) {
            selectRaser = true;
            raserMoveX = -5;
        }else{
            raserMoveX = 0;
        }
            
            CCSprite* raserButton = (CCSprite*)penMenu->getChildByTag(kPenButtonTag+5);
            if (raserButton!=NULL) {
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
        if (layer!=NULL && clickEraser==false) {
            clickEraser = true;
            layer->runAction(CCEaseIn::create(CCMoveTo::create(0.3, ccp(layer->getPosition().x+130, layer->getPosition().y)), 0.3));
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
        layer->removeFromParentAndCleanup(true);
//        color->unselected();
        CCLOG("---当前画笔%s---",ColorManager::shared()->curPenName);
    }
}

void ColorCanvasView::clickPenButton(CCObject *sender){
    CCMenuItemSprite* penButton = (CCMenuItemSprite*)sender;
    int penIndex =penButton->getTag();
    clickEraser = false;
    if (ColorManager::shared()->touchedPenButton==false && penButton!=NULL && ColorManager::shared()->isMovingColorBlock==false && ColorManager::shared()->isNewbieGuideActive==false) {
        selectRaser = false;
        
        ColorManager::shared()->m_DrawType = Draw_Point ;
        
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        CCSprite* buttonSelect = (CCSprite*)this->getChildByTag(kButtonSelectTag);
        selectPosY = penButton->getPosition().y;
        if (buttonSelect!=NULL) {
            ColorManager::shared()->touchedPenButton=true;
                buttonSelect->runAction(CCSequence::create(CCMoveTo::create(0.2, ccp(v_size.width -50 - w_fix-poszero.x, selectPosY)),
                                                           CCCallFunc::create(this, callfunc_selector(ColorCanvasView::canTouchButton)),
                                                           NULL));
        }

        int scaleColor = penButton->getScale();
        penButton->runAction(CCSpawn::create(CCSequence::create(CCScaleTo::create(0.1, 0.7),
                                                                CCScaleTo::create(0.1, 0.5),
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
            layer->removeFromParentAndCleanup(true);
        }
        layer = ChooseColorLayer::create();
        layer->setTag(999);
    //    layer->SetMenuItem(color);
        this->addChild(layer,3);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.changebrush");
    }
    

}

void ColorCanvasView::canTouchButton(){
    ColorManager::shared()->touchedPenButton = false;
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

void ColorCanvasView::changeBrushColorCallback(){
    int curSelColorIndex=0;
    if (strcmp(ColorManager::shared()->curPenName, "paint")==0) {
        curSelColorIndex=ColorManager::shared()->curPaintPenColorIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "largebrush")==0){
        curSelColorIndex=ColorManager::shared()->curLargebrushIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "crayon")==0){
        curSelColorIndex=ColorManager::shared()->curCrayonIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "pencil")==0){
        curSelColorIndex=ColorManager::shared()->curPencilPenColorIndex;
    }else if (strcmp(ColorManager::shared()->curPenName, "paintbucket")==0){
        curSelColorIndex=ColorManager::shared()->curPaintbucketIndex;
    }
    CCSprite* penMenu = (CCSprite*)this->getChildByTag(kPenMenuTag);
    if(penMenu){
        CCSprite* penButton = (CCSprite*)penMenu->getChildByTag(kPenButtonTag+(ColorManager::shared()->SelectBrushTag-100));
        if(penButton){
            CCSprite* penShadowButton = (CCSprite*)penButton->getChildByTag(kBrushColorShadowTag);
            CCSprite* penColorsShadowButton = (CCSprite*)penButton->getChildByTag(kBrushColorsShadowTag);
            if(penShadowButton){
                CCLog("---当前索引值%d---",ColorManager::shared()->curSelectColorIndex);
                CCLog("---当前xuan索引值%d---",curSelColorIndex);
                if ((strcmp(ColorManager::shared()->curPenName, "pencil")==0 || strcmp(ColorManager::shared()->curPenName, "paint")==0) && ColorManager::shared()->curSelectColorIndex>11 && ColorManager::shared()->curSelectColorIndex<16) {
                    if(penColorsShadowButton){
                        penColorsShadowButton->removeFromParentAndCleanup(true);
                    }
                    penColorsShadowButton = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_shadow%d.png",ColorManager::shared()->curPenName,ColorManager::shared()->curSelectColorIndex)->getCString());
                    penColorsShadowButton->setTag(kBrushColorsShadowTag);
                    penColorsShadowButton->setPosition(ccp(penButton->getContentSize().width/2, penButton->getContentSize().height/2));
                    penButton->addChild(penColorsShadowButton,-1);
                }else{
                    if(penColorsShadowButton){
                        penColorsShadowButton->removeFromParentAndCleanup(true);
                    }
                    ccColor3B brushColor;
                    brushColor = ColorManager::shared()->getCurColor(curSelColorIndex);
                    penShadowButton->setColor(brushColor);
                }
                
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
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/camera.mp3");
    if (whiteCanvas != NULL && blacklayer==NULL ) {
        CCImage* image = DeviceManager::sharedManager()->getRenderUImage(whiteCanvas);
        DeviceManager::sharedManager()->cameraSelf(image);
//        DeviceManager::sharedManager()->printImage(image);
    }
//    CCImage* image = DeviceManager::sharedManager()->getRenderUImage(CCDirector::sharedDirector()->getRunningScene());
//    DeviceManager::sharedManager()->cameraSelf(image);
    this->scheduleOnce(schedule_selector(ColorCanvasView::showAllButtons), 0.2);
}


void ColorCanvasView::removeNouesImage(){
////    closeMenu->setVisible(false);
//    camerabtu->setVisible(false);
////    toolsBg->setVisible(false);
//    back->setVisible(false);
    ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
    if (layer!=NULL) {
        layer->removeFinger();
    }
    
    if(ColorManager::shared()->isNewbieGuideActive==false){
        hideAllButtons();
        this->scheduleOnce(schedule_selector(ColorCanvasView::camera), 0.2);
    }

}

void ColorCanvasView::ImageVisible(){
//    closeMenu->setVisible(true);
    camerabtu->setVisible(true);
//    toolsBg->setVisible(true);
    back->setVisible(true);
}


void ColorCanvasView::resetColorValue(){
    ColorManager::shared()->curPaintIndex = 11;
    ColorManager::shared()->curPencilIndex = 6;
    ColorManager::shared()->curPaintbucketIndex = 23;
    ColorManager::shared()->curCrayonIndex = 18;
    ColorManager::shared()->curLargebrushIndex = 31;
    
    ColorManager::shared()->firstTouchPaint = false;
    ColorManager::shared()->firstTouchCrayon = false;
    ColorManager::shared()->firstTouchPencil = false;
    ColorManager::shared()->firstTouchLargebrush = false;
    ColorManager::shared()->firstTouchPaintbucket = false;
    
    ColorManager::shared()->curPaintPenColorIndex=0;
    ColorManager::shared()->curPencilPenColorIndex=0;
    
    for (int i=0; i<50; i++) {
        ColorManager::shared()->colorPaintPos[i] = 0.0;
        ColorManager::shared()->colorPencilPos[i] = 0.0;
        ColorManager::shared()->colorPaintbucketPos[i] = 0.0;
        ColorManager::shared()->colorCrayonPos[i] = 0.0;
        ColorManager::shared()->colorLargebrushPos[i] = 0.0;
    }
}


void ColorCanvasView::openBookPage() {
//    DeviceManager::sharedManager()->showiOSVideo(1);
    this->showBookPageBtn(0);
}

void ColorCanvasView::showBookPageBtn(int pageId) {
//    CCPoint center = GameManager::getCenter();
//
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
//
//    if (blacklayer == NULL) {
//        CCLayer* BookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
//        if (BookLayer == NULL) {
////#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
////        buyLayer = (CCLayer*)BuyLayer::nodeWithID(_pageId);
////#else
//            BookLayer = (CCLayer*)BookLayer::nodeWithID(0);
////        buyLayer->setInitPageIndex(0);
////#endif
//            BookLayer->setTag(kBookLayerTag);
//            this->addChild(BookLayer, 300);
//
//            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
//            blacklayer->ignoreAnchorPointForPosition(false);
//            blacklayer->setPosition(center);
//            BookLayer->addChild(blacklayer,-1);
//        }
//    }

}


void ColorCanvasView::checkIsCanShowLayer(){
    CCLayer* bookLayer = (CCLayer*)this->getChildByTag(kBookLayerTag);
    if (!GameManager::sharedManager()->checkIsInterestInBook()){
        this->unschedule(schedule_selector(ColorCanvasView::checkIsCanShowLayer));
    }else if (GameManager::sharedManager()->checkIsCanShowBookLayer() && bookLayer == NULL){
        this->openBookPage();
        GameManager::sharedManager()->canShowColorBookLayer=false;
        GameManager::sharedManager()->recordBookLayerInfo();
        this->unschedule(schedule_selector(ColorCanvasView::checkIsCanShowLayer));
    }
}


void ColorCanvasView::onPrintCurScene(CCObject *obj){
    // 保存当前场景为图片
    CCSize winSizes = GameManager::sharedManager()->getViewVisibleSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float widthOffX=0.4;
    float widthX_x=0.05;
    float heightOffY=0.02;
    if (winSizes.width < 900) {  //老式pad
        widthOffX=0.64;
        widthX_x=0.048;
        heightOffY=0.1;
    }else if (winSizes.width < 930) {
        widthOffX=0.7;
        widthX_x=0.05;
        heightOffY=0.1;
    }else if (winSizes.width < 1136) {
        widthOffX=0.7;
        widthX_x=0.05;
        heightOffY=0.07;
    }
    
    if(GameManager::sharedManager()->isIphoneX()){
        widthOffX=0.47;
        widthX_x=0.04;
        heightOffY=0.02;
    }
    
    float x = winSize.width*widthX_x; // 起始横坐标（point）
    float y = winSize.height*heightOffY; // 起始纵坐标（point）
    float w = winSize.width*widthOffX; // 宽度
    float h = winSize.height; // 高度
    const char* filename = "printScene.png";
        
    DeviceManager::sharedManager()->printSceneAddedToFile(filename, x, y, w, h);
    
    this->showAllButtons();
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
        schedule_selector(ColorCanvasView::callPrintImage),
        this, 0, 0, 0.3f, false);
}

void ColorCanvasView::callPrintImage(float dt) {
    printImageIOS("printScene.png");
}

void ColorCanvasView::onClickPrintBtn(CCObject* obj){
   
    this->hideAllButtons();

    this->runAction(CCSequence::create(
        CCDelayTime::create(0.05),
        CCCallFuncN::create(this, callfuncN_selector(ColorCanvasView::onPrintCurScene)),
        nullptr
    ));
}

void ColorCanvasView::hideAllButtons() {
    if (camerabtu) camerabtu->setVisible(false);
    if (back) back->setVisible(false);
    if (deleteMenu) deleteMenu->setVisible(false);
    if (printMenu) printMenu->setVisible(false);
}

void ColorCanvasView::showAllButtons() {
    if (camerabtu) camerabtu->setVisible(true);
    if (back) back->setVisible(true);
    if (deleteMenu) deleteMenu->setVisible(true);
    if (printMenu) printMenu->setVisible(true);
}


void ColorCanvasView::createParentsLock(){
    CCSize winsize = CCEGLView::sharedOpenGLView()->getVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
   
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    
    if (blacklayer == NULL && ColorManager::shared()->isNewbieGuideActive==false) {
        ChooseColorLayer* layer = (ChooseColorLayer*)this->getChildByTag(999);
        if (layer!=NULL) {
            layer->removeFinger();
        }
        //SimpleAudioEngine::sharedEngine()->playEffect("pressBt.mp3");
        accessIndex = 0;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winsize.width, winsize.height);
        blacklayer->ignoreAnchorPointForPosition(false);
        blacklayer->setTag(kBackLayerTag);
        blacklayer->setPosition(center);
        this->addChild(blacklayer,100);
        
        CCSprite* lock_back = CCSprite::create("di.png");
        lock_back->setPosition(ccp(blacklayer->boundingBox().size.width/2, blacklayer->boundingBox().size.height/2));
        lock_back->setTag(kLockBackTag);
        blacklayer->addChild(lock_back);
        
        
        for (int i=0; i<4; i++) {
            // locknum[0] = arc4random() % 7+3;
            CCString* name ;
            if (i == 0) {
                locknum[0] = arc4random() % 3+7;
                name = CCString::createWithFormat("w%d.png", locknum[0]) ;
            }
            else if (i == 1) {
                name = CCString::create("jia.png") ;
            } else if (i == 2) {
                locknum[1] = arc4random() % 8+2;
                if (locknum[0]+locknum[1] == 9) {
                    locknum[1]+=2 ;
                }
                if (locknum[0]+locknum[1] == 10) {
                    locknum[1]+=1 ;
                }
                name = CCString::createWithFormat("w%d.png", locknum[1]) ;
            }else{
                name = CCString::create("deng.png") ;
            }
            CCSprite* lable = CCSprite::create(name->getCString());
            
            lable->setPosition(ccp(lock_back->boundingBox().size.width/3+ (i - 1)*lable->boundingBox().size.width, lock_back->boundingBox().size.height/4*3 + 36));
            lock_back->addChild(lable);
        }
        
        
        CCMenu* lockmenu = CCMenu::create();
        lockmenu->setPosition(CCPointZero);
        lockmenu->setTag(kLockMenuTag);
        for (int i=0; i<9; i++) {
            CCMenuItemImage* num = CCMenuItemImage::create(CCString::createWithFormat("%d.png", i+1)->getCString(), CCString::createWithFormat("%d.png", i+1)->getCString(), this, menu_selector(ColorCanvasView::parentsLockCallback));
            num->setTag(i);
            int acX = i % 3 - 1;
            int acY = i / 3 - 1;
            num->setPosition(ccp(lock_back->boundingBox().size.width/2 + acX*(num->boundingBox().size.width+20), lock_back->boundingBox().size.height/3*2 - acY*(num->boundingBox().size.height - 5) - 143));
            lockmenu->addChild(num);
        }
        
        
        CCMenuItemImage* close = CCMenuItemImage::create("x.png", "x.png", this, menu_selector(ColorCanvasView::parentsLockCallback));
        close->setTag(40);
        close->setPosition(ccp(lock_back->boundingBox().size.width - 20, lock_back->boundingBox().size.height - 20));
        lockmenu->addChild(close);
        
        
        lock_back->addChild(lockmenu);
    }

}

void ColorCanvasView::parentsLockCallback(cocos2d::CCObject *sender){
    //SimpleAudioEngine::sharedEngine()->playEffect("pressBt.mp3");
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    CCSprite* lockback = (CCSprite*)blacklayer->getChildByTag(kLockBackTag);
    int tag = ((CCMenuItem*)sender)->getTag();
    CCPoint point ;
    if (tag < 9) {
        CCSprite* show = CCSprite::create(CCString::createWithFormat("w%d.png", tag+1)->getCString());
        if (accessIndex < 1) {
            point  = ccp(lockback->boundingBox().size.width/5*4 + (accessIndex - 1)*(show->boundingBox().size.width ), lockback->boundingBox().size.height/4*3 + 36) ;
        }else{
            point = ccp(lockback->boundingBox().size.width/5*4 + (accessIndex - 1)*(show->boundingBox().size.width )-15, lockback->boundingBox().size.height/4*3 + 36) ;
        }
        
        show->setPosition(point);
        show->setTag(20 + accessIndex);
        lockback->addChild(show);
        
        accessnum[accessIndex++] = tag;
        
    }
    
    if (tag == 40) {
        this->setTouchEnabled(true) ;
        blacklayer->removeFromParentAndCleanup(true);
    }
    if (accessIndex == 2){
        accessIndex = 0;
        
        int result = locknum[0]+locknum[1] ;
        int inputNumber = (accessnum[0]+1)*10+ (accessnum[1]+1);
        bool flag = false;
        if (result == inputNumber) {
            flag = true ;
        }
        if (flag) {
            this->runAction(CCSequence::create(CCDelayTime::create(0.2),CCCallFunc::create(this, callfunc_selector(ColorCanvasView::clearLock)),
                                               CCDelayTime::create(0.1),
                                               CCCallFuncN::create(this, callfuncN_selector(ColorCanvasView::onClickPrintBtn)),
                                               NULL)) ;
        }else{
            for (int i=0; i<2; i++) {
                CCSprite* sprite = (CCSprite*)lockback->getChildByTag(20 + i);
                sprite->scheduleOnce(schedule_selector(CCNode::removeFromParentAndCleanup), 0.1);
            }
        }
    }
}

void ColorCanvasView::clearLock()
{
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    blacklayer->removeFromParentAndCleanup(true);
}

void ColorCanvasView::showFirstGuide(){
    CCPoint centerPos = GameManager::sharedManager()->getCenter();
    CCSize curWinSize = GameManager::sharedManager()->getViewVisibleSize();
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
    if (guideFinger == NULL) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pizza/animate/pick.plist");
            
        guideFinger = CCSprite::createWithSpriteFrameName("touch0.png");
        guideFinger->setTag(kGuideFingerTag);
        guideFinger->setScale(0.5);
        guideFinger->setOpacity(0);
        this->addChild(guideFinger, 1002);
        
        CCArray* frame = CCArray::create();
        for (int m =0; m<2; m++) {
            CCString *name = CCString::createWithFormat("touch%d.png",m);
            frame->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frame);
        animation->setDelayPerUnit(0.3f);
        animation->setLoops(3);
        
    }
    if (guideFinger != NULL) {
        CCPoint initGuidePos = ccp(curWinSize.width/2-100, curWinSize.height/4*3);
        CCPoint targetGuidePos = ccp(curWinSize.width/2+200, curWinSize.height/4*3-50);
        
        guideFinger->setPosition(ccp(curWinSize.width/2-100, curWinSize.height/4*3));
        
        ccBezierConfig bezier;

        bezier.controlPoint_1 = ccp(initGuidePos.x+660,initGuidePos.y+100);
        bezier.controlPoint_2 = ccp(initGuidePos.x-610,targetGuidePos.y-100);
        bezier.endPosition = ccp(targetGuidePos.x,targetGuidePos.y);
        CCBezierTo* bezierTo = CCBezierTo::create(2.5, bezier);
        
        guideFinger->runAction(CCSequence::create(CCFadeTo::create(0.5, 255),bezierTo,CCFadeTo::create(0.5, 0),CCCallFunc::create(this, callfunc_selector(ColorCanvasView::removeFirstGuide)),NULL));
    }

}

void ColorCanvasView::resetGuideFingerPos()
{
    CCPoint centerPos = GameManager::sharedManager()->getCenter();
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
//    CCSprite* creamKnife = (CCSprite*)this->getChildByTag(kCreamKnifeTag);
//    if (guideFinger != NULL && creamKnife!=NULL) {
//        guideFinger->setPosition(ccp(creamKnife->getPosition().x, centerPos.y));
//    }
}

void ColorCanvasView::removeFirstGuide()
{
    CCSprite* guideFinger = (CCSprite*)this->getChildByTag(kGuideFingerTag);
    if (guideFinger != NULL) {
        guideFinger->stopAllActions();
        guideFinger->removeFromParentAndCleanup(true);
        guideFinger = NULL;
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("ColoringGuide", true);
}
