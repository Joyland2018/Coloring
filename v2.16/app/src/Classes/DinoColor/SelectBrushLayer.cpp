//
//  SelectBrushLayer.cpp
//  DrDino
//
//  Created by chuining meng on 2020/4/30.
//

#include "SelectBrushLayer.hpp"
#include "GameManager.h"
#include "cocos-ext.h"
#include "ColorManager.hpp"

#define Tag  100

#define Mark  1000
#define ToolsIcon_Tag 31
#define ToolsIconShadow_Tag 32

using namespace cocos2d::extension ;

bool SelectBrush::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
//    CCSprite* bg = CCSprite::create("DinoColor/swatch_new.png");
//    bg->setPosition(ccp(v_size.width/4*3-poszero.x,v_size.height/2));
//
//    this->addChild(bg);
//
//    CCSprite* stencilNode = CCSprite::create("DinoColor/swatch_new.png");
//    stencilNode->setContentSize(CCSizeMake(stencilNode->getContentSize().width-10, stencilNode->getContentSize().height));
//    stencilNode->setAnchorPoint(ccp(0.0, 0.0));
//    stencilNode->setPosition(ccp(-10, 0));

//    CCClippingNode* brushLayerClipper = CCClippingNode::create(stencilNode);
//    brushLayerClipper->setPosition(ccp(0,0));
////    brushLayerClipper->setInverted(true);
//    brushLayerClipper->setAlphaThreshold(0.0f);
//
//    contentNode = CCLayer::create();
//    contentNode->setContentSize(CCSizeMake(bg->getContentSize().width-20, bg->getContentSize().height));
//    contentNode->setPosition(ccp(0, 0));
//    brushLayerClipper->addChild(contentNode);
//    bg->addChild(brushLayerClipper);
    
//    CCSprite* bgCover = CCSprite::create("DinoColor/swatch_new_cover.png");
//    bgCover->setPosition(ccp(bg->getPosition().x, bg->getPosition().y));
//    this->addChild(bgCover,2);
    
    this->setButton();
    
    return true;
}

void SelectBrush::setButton()
{
    
//    float fix_w = 0 ;
//       if (GameManager::sharedManager()->isIphoneX()) {
//           fix_w = 160;
//       }
//    std::string names[] = {"pencil","paint","largebrush","paintbucket","crayon"} ;
//       for (int i = 0; i < 5; i++) {
//
//           CCString* name = CCString::createWithFormat("DinoColor/toolsUI/%s_tools_cover.png",names[i].c_str()) ;
//           CCSprite* tmp2 = CCSprite::create(name->getCString());
//           CCSize size2 = tmp2->getContentSize();
//           CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
//           CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
//           CCControlButton *button = CCControlButton::create(sprite2) ;
//           button->setPreferredSize(size2) ;
//           button->setTag(Tag+i);
//           button->setPosition(ccp(contentNode->getContentSize().width/3*2, contentNode->getContentSize().height-(contentNode->getContentSize().height/6)*(i+1))) ;
//           button->setScale(0.9);
////           button->setPosition(ccp(0, 0)) ;
//           contentNode->addChild(button, 3) ;
//
//           CCSprite* brushIconShadow = NULL;
//           if (i == 4) {
//               CCTexture2D* texture = ColorManager::shared()->maskedWithSpriteTexture(CCSprite::create(CCString::createWithFormat("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[i]-99)->getCString()), CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",names[i].c_str())->getCString()), ccp(0.5, 0.5));
//               brushIconShadow = CCSprite::createWithTexture(texture);
//           }else {
//               brushIconShadow = CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",names[i].c_str())->getCString());
//
//               ccColor3B brushColor = ColorManager::shared()->getCurColor(ColorManager::shared()->SelectColorTag[i]-99);
//               brushIconShadow->setColor(brushColor);
//           }
//
//           brushIconShadow->setPosition(ccp(tmp2->getContentSize().width/2, tmp2->getContentSize().height/2));
//           brushIconShadow->setTag(ToolsIconShadow_Tag);
//           button->addChild(brushIconShadow,-1);
//
//           CCSprite* mark = CCSprite::create("DinoColor/brush-select.png");
//           mark->setTag(Mark);
//           mark->setPosition(ccp(size2.width/2, size2.height/2 ));
//           button->addChild(mark);
//           if (ColorManager::shared()->SelectBrushTag == Tag+i) {
//               mark->setVisible(true);
//           }else{
//              mark->setVisible(false);
//           }
//
//           button->addTargetWithActionForControlEvents(this, cccontrol_selector(SelectBrush::brushClick), CCControlEventTouchUpInside) ;
//       }
}

void SelectBrush::brushClick(CCObject *obj)
{
//    int tag = ((CCNode*)obj)->getTag();
//    for (int i = 0; i < 5; i++) {
//        CCNode* node =contentNode->getChildByTag(Tag+i);
//        node->getChildByTag(Mark)->setVisible(false);
//    }
//    ((CCNode*)obj)->getChildByTag(Mark)->setVisible(true);
//    ColorManager::shared()->SelectBrushTag = tag;
//    
//    ColorManager::shared()->changeCurColor();
//    
//    const char* toolsTypeName = "";
//    
//    switch (ColorManager::shared()->SelectBrushTag) {
//        case Brush_Pencil:
//        {
//            toolsTypeName = "pencil";
//        }
//            break;
//        case Brush_Paint:
//        {
//            toolsTypeName = "paint";
//        }
//            break;;
//        case Brush_Largebrush:
//        {
//            toolsTypeName = "largebrush";
//        }
//            break;
//        case Brush_Paintbucket:
//        {
//            toolsTypeName = "paintbucket";
//        }
//            break;
//        case Brush_Crayon:
//        {
//            toolsTypeName = "crayon";
//        }
//            break;
//        default:
//            break;
//    }
//    
//    for (int i = 0; i < 2; i++) {
//        CCSprite* btnSpr = NULL;
//        if (i == 0) {
//            btnSpr = (CCSprite*)brushBtu->getNormalImage();
//        } else {
//            btnSpr = (CCSprite*)brushBtu->getSelectedImage();
//        }
//        
//        if (btnSpr != NULL) {
//            CCSprite* btnIconSpr = (CCSprite*)btnSpr->getChildByTag(ToolsIcon_Tag);
//            CCSprite* btnIconShadow = (CCSprite*)btnIconSpr->getChildByTag(ToolsIconShadow_Tag);
//            btnIconShadow->setColor(ccWHITE);
//            
//            CCTexture2D* btnCoverTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_cover.png",toolsTypeName)->getCString());
//            CCTexture2D* btnShadowTexture = NULL;
//            
//            if (ColorManager::shared()->SelectBrushTag == Brush_Crayon) {
//                btnShadowTexture = ColorManager::shared()->maskedWithSpriteTexture(CCSprite::create(CCString::createWithFormat("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[4]-99)->getCString()), CCSprite::create(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",toolsTypeName)->getCString()), ccp(0.5, 0.5));
//            }else {
//                btnShadowTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("DinoColor/toolsUI/%s_tools_shadow.png",toolsTypeName)->getCString());
//                btnIconShadow->setColor(ColorManager::shared()->m_pColor);
//            }
//            btnIconSpr->setTexture(btnCoverTexture);
//            btnIconShadow->setTexture(btnShadowTexture);
////            btnIconShadow->setColor(ColorManager::shared()->m_pColor);
//        }
//    }
//    
////    switch (ColorManager::shared()->SelectBrushTag) {
////        case 100:
////            brushBtu->setNormalImage(CCSprite::create("DinoColor/pencil-normal.png"));
////            brushBtu->setSelectedImage(CCSprite::create("DinoColor/pencil-down.png"));
////            break;
////        case 101:
////            brushBtu->setNormalImage(CCSprite::create("DinoColor/brush-normal.png"));
////            brushBtu->setSelectedImage(CCSprite::create("DinoColor/brush-down.png"));
////            break;
////        case 102:
////            brushBtu->setNormalImage(CCSprite::create("DinoColor/largebrush-normal.png"));
////            brushBtu->setSelectedImage(CCSprite::create("DinoColor/largebrush-down.png"));
////            break;
////        default:
////            break;
////    }
//    brushBtu->selected();
//    CCNotificationCenter::sharedNotificationCenter()->postNotification("colorcanvas.changebrush");
//    this->removeFromParent();
}

void SelectBrush::SetMenuItem(CCMenuItemSprite *item)
{
    brushBtu = item;
}
