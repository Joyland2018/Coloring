//
//  SelectBrushLayer.cpp
//  DrDino
//
//  Created by chuining meng on 2020/4/30.
//

#include "SelectBrushLayer.hpp"
#include "../GameManager.h"
#include "cocos-ext.h"
#include "ColorManager.hpp"

#define Tag  100

#define Mark  1000
#define ToolsIcon_Tag 31
#define ToolsIconShadow_Tag 32

using namespace cocos2d::extension ;

bool SelectBrush::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Vec2 winCenter = GameManager::sharedManager()->getCenter();
    v_size = Director::getInstance()->getVisibleSize();
    poszero = Director::getInstance()->getVisibleOrigin();
//    Sprite* bg = Sprite::create("DinoColor/swatch_new.png");
//    bg->setPosition(Vec2(v_size.width/4*3-poszero.x,v_size.height/2));
//
//    this->addChild(bg);
//
//    Sprite* stencilNode = Sprite::create("DinoColor/swatch_new.png");
//    stencilNode->setContentSize(Size(stencilNode->getContentSize().width-10, stencilNode->getContentSize().height));
//    stencilNode->setAnchorPoint(Vec2(0.0, 0.0));
//    stencilNode->setPosition(Vec2(-10, 0));

//    ClippingNode* brushLayerClipper = ClippingNode::create(stencilNode);
//    brushLayerClipper->setPosition(Vec2(0,0));
////    brushLayerClipper->setInverted(true);
//    brushLayerClipper->setAlphaThreshold(0.0f);
//
//    contentNode = Layer::create();
//    contentNode->setContentSize(Size(bg->getContentSize().width-20, bg->getContentSize().height));
//    contentNode->setPosition(Vec2(0, 0));
//    brushLayerClipper->addChild(contentNode);
//    bg->addChild(brushLayerClipper);
    
//    Sprite* bgCover = Sprite::create("DinoColor/swatch_new_cover.png");
//    bgCover->setPosition(Vec2(bg->getPosition().x, bg->getPosition().y));
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
//           std::string name = StringUtils::format("DinoColor/toolsUI/%s_tools_cover.png",names[i].c_str()) ;
//           Sprite* tmp2 = Sprite::create(name);
//           Size size2 = tmp2->getContentSize();
//           Rect insetRect2 = Rect(0,0,size2.width, size2.height);
//           ui::Scale9Sprite* sprite2 = ui::Scale9Sprite::create(name, insetRect2) ;
//           ui::Button *button = ui::Button::create() ;
//           button->setPreferredSize(size2) ;
//           button->setTag(Tag+i);
//           button->setPosition(Vec2(contentNode->getContentSize().width/3*2, contentNode->getContentSize().height-(contentNode->getContentSize().height/6)*(i+1))) ;
//           button->setScale(0.9);
////           button->setPosition(Vec2(0, 0)) ;
//           contentNode->addChild(button, 3) ;
//
//           Sprite* brushIconShadow = NULL;
//           if (i == 4) {
//               Texture2D* texture = ColorManager::shared()->maskedWithSpriteTexture(Sprite::create(StringUtils::format("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[i]-99)), Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",names[i].c_str())), Vec2(0.5, 0.5));
//               brushIconShadow = Sprite::createWithTexture(texture);
//           }else {
//               brushIconShadow = Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",names[i].c_str()));
//
//               Color3B brushColor = ColorManager::shared()->getCurColor(ColorManager::shared()->SelectColorTag[i]-99);
//               brushIconShadow->setColor(brushColor);
//           }
//
//           brushIconShadow->setPosition(Vec2(tmp2->getContentSize().width/2, tmp2->getContentSize().height/2));
//           brushIconShadow->setTag(ToolsIconShadow_Tag);
//           button->addChild(brushIconShadow,-1);
//
//           Sprite* mark = Sprite::create("DinoColor/brush-select.png");
//           mark->setTag(Mark);
//           mark->setPosition(Vec2(size2.width/2, size2.height/2 ));
//           button->addChild(mark);
//           if (ColorManager::shared()->SelectBrushTag == Tag+i) {
//               mark->setVisible(true);
//           }else{
//              mark->setVisible(false);
//           }
//
//           button->addCallback(CC_CALLBACK_1(SelectBrush::brushClick, this)) ;
//       }
}

void SelectBrush::brushClick(Ref *obj)
{
//    int tag = ((Node*)obj)->getTag();
//    for (int i = 0; i < 5; i++) {
//        Node* node =contentNode->getChildByTag(Tag+i);
//        node->getChildByTag(Mark)->setVisible(false);
//    }
//    ((Node*)obj)->getChildByTag(Mark)->setVisible(true);
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
//        Sprite* btnSpr = NULL;
//        if (i == 0) {
//            btnSpr = (Sprite*)brushBtu->getNormalImage();
//        } else {
//            btnSpr = (Sprite*)brushBtu->getSelectedImage();
//        }
//        
//        if (btnSpr != NULL) {
//            Sprite* btnIconSpr = (Sprite*)btnSpr->getChildByTag(ToolsIcon_Tag);
//            Sprite* btnIconShadow = (Sprite*)btnIconSpr->getChildByTag(ToolsIconShadow_Tag);
//            btnIconShadow->setColor(Color3B::WHITE);
//            
//            Texture2D* btnCoverTexture = Director::getInstance()->getTextureCache()->addImage(StringUtils::format("DinoColor/toolsUI/%s_tools_cover.png",toolsTypeName));
//            Texture2D* btnShadowTexture = NULL;
//            
//            if (ColorManager::shared()->SelectBrushTag == Brush_Crayon) {
//                btnShadowTexture = ColorManager::shared()->maskedWithSpriteTexture(Sprite::create(StringUtils::format("DinoColor/crayon_texture/crayon_texture_%d.png",ColorManager::shared()->SelectColorTag[4]-99)), Sprite::create(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",toolsTypeName)), Vec2(0.5, 0.5));
//            }else {
//                btnShadowTexture = Director::getInstance()->getTextureCache()->addImage(StringUtils::format("DinoColor/toolsUI/%s_tools_shadow.png",toolsTypeName));
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
////            brushBtu->setNormalImage(Sprite::create("DinoColor/pencil-normal.png"));
////            brushBtu->setSelectedImage(Sprite::create("DinoColor/pencil-down.png"));
////            break;
////        case 101:
////            brushBtu->setNormalImage(Sprite::create("DinoColor/brush-normal.png"));
////            brushBtu->setSelectedImage(Sprite::create("DinoColor/brush-down.png"));
////            break;
////        case 102:
////            brushBtu->setNormalImage(Sprite::create("DinoColor/largebrush-normal.png"));
////            brushBtu->setSelectedImage(Sprite::create("DinoColor/largebrush-down.png"));
////            break;
////        default:
////            break;
////    }
//    brushBtu->selected();
//    NotificationCenter::getInstance()->postNotification("colorcanvas.changebrush");
//    this->removeFromParent();
}

void SelectBrush::SetMenuItem(ui::Widget *item)
{
    brushBtu = item;
}
