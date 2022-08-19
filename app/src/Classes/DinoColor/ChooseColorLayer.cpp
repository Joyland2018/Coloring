//
//  ChooseColorLayer.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/19.
//

#include "ChooseColorLayer.h"
#include "GameManager.h"
#include "cocos-ext.h"
#include "ColorManager.h"

using namespace cocos2d::extension ;

#define Tag  100

#define Mark  1000

const unsigned int    kNormalTag = 0x1;
const unsigned int    kSelectedTag = 0x2;
const unsigned int    kDisableTag = 0x3;

bool ChooseColorLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    int x_w = 0;
    if (GameManager::sharedManager()->isIphoneX()) {
        x_w=30;
    }
    CCPoint winCenter = GameManager::sharedManager()->getCenter();
    v_size = CCDirector::sharedDirector()->getWinSize();
    poszero = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite* bg = CCSprite::create("DinoColor/swatch.png");
    bg->setPosition(ccp(v_size.width/4*2.6-poszero.x+x_w,v_size.height/2));
    
    this->addChild(bg);
    this->setButton();
    
    return true;
}

void ChooseColorLayer::setButton()
{
    float fix_w = 0 ;
       if (GameManager::sharedManager()->isIphoneX()) {
           fix_w = 160;
       } else if (GameManager::sharedManager()->isAndroidPad()){
           fix_w = -80;
       }
       for (int i = 0; i < 15; i++) {
           
           CCString* name = CCString::createWithFormat("DinoColor/color/color_%d.png",(i+1)) ;
           CCSprite* tmp2 = CCSprite::create(name->getCString());
           CCSize size2 = tmp2->getContentSize();
           CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
           CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
           CCControlButton *button = CCControlButton::create(sprite2) ;
           button->setPreferredSize(size2) ;
           button->setTag(Tag+i);
           button->setPosition(ccp(620+110*(i%3)+fix_w-poszero.x, 540 -110*(i/3))) ;
           this->addChild(button, 3) ;
           CCSprite* mark = CCSprite::create("DinoColor/color-selected.png");
           mark->setTag(Mark);
           mark->setPosition(ccp(size2.width/2, size2.height/2));
           button->addChild(mark);
           if (ColorManager::shared()->SelectColorTag == Tag+i) {
               mark->setVisible(true);
           }else{
              mark->setVisible(false);
           }
           
           button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChooseColorLayer::colorClick), CCControlEventTouchUpInside) ;
       }
}

void ChooseColorLayer::colorClick(CCObject *obj)
{
    int tag = ((CCNode*)obj)->getTag();
    for (int i = 0; i < 15; i++) {
        CCNode* node =this->getChildByTag(Tag+i);
        node->getChildByTag(Mark)->setVisible(false);
    }
    ((CCNode*)obj)->getChildByTag(Mark)->setVisible(true);
    ColorManager::shared()->SelectColorTag = tag;
    ColorManager::shared()->m_DrawType = Draw_Point ;
    switch (tag-Tag+1) {
        case 1:
            ColorManager::shared()->m_pColor = ccc3(255,7,7);
            break;
        case 2:
           ColorManager::shared()->m_pColor = ccc3(255,81,0);
           break;
        case 3:
            ColorManager::shared()->m_pColor = ccc3(255,114,169);
            break;
        case 4:
            ColorManager::shared()->m_pColor = ccc3(255,140,26);
            break;
        case 5:
            ColorManager::shared()->m_pColor = ccc3(243,228,33);
            break;
        case 6:
            ColorManager::shared()->m_pColor = ccc3(163,44,92);
            break;
        case 7:
            ColorManager::shared()->m_pColor = ccc3(0,239,207);
            break;
        case 8:
            ColorManager::shared()->m_pColor = ccc3(121,175,27);
            break;
        case 9:
               ColorManager::shared()->m_pColor = ccc3(71,106,38);
               break;
        case 10:
               ColorManager::shared()->m_pColor = ccc3(40,197,255);
               break;
        case 11:
            ColorManager::shared()->m_pColor = ccc3(53,104,152);
            break;
        case 12:
            ColorManager::shared()->m_pColor = ccc3(15,89,208);
            break;
        case 13:
            ColorManager::shared()->m_pColor = ccc3(164,170,192);
            break;
        case 14:
            ColorManager::shared()->m_pColor = ccc3(0,0,0);
            break;
        case 15:
            ColorManager::shared()->m_pColor = ccc3(255,255,255);
            break;
        default:
            break;
    }
    CCSprite* pait = ( CCSprite*)color->getChildByTag(kSelectedTag)->getChildByTag(1);
    pait->setColor(ColorManager::shared()->m_pColor);
    pait = ( CCSprite*)color->getChildByTag(kNormalTag)->getChildByTag(1);
    pait->setColor(ColorManager::shared()->m_pColor);
    color->unselected();
    this->removeFromParent();
}

void ChooseColorLayer::SetMenuItem(CCMenuItemSprite *item)
{
    color = item;
}
