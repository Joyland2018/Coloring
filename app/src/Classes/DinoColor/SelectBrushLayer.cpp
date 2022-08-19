//
//  SelectBrushLayer.cpp
//  DrDino
//
//  Created by chuining meng on 2020/4/30.
//

#include "SelectBrushLayer.h"
#include "GameManager.h"
#include "cocos-ext.h"
#include "ColorManager.h"

#define Tag  100

#define Mark  1000

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
    CCSprite* bg = CCSprite::create("DinoColor/brushswatch.png");
    bg->setPosition(ccp(v_size.width/4*3-poszero.x,v_size.height/2));
    
    this->addChild(bg);
    this->setButton();
    
    return true;
}

void SelectBrush::setButton()
{
    float fix_w = 0 ;
       if (GameManager::sharedManager()->isIphoneX()) {
           fix_w = 160;
       }
    std::string names[] = {"pencil","brush","largebrush"} ;
       for (int i = 0; i < 3; i++) {
           
           CCString* name = CCString::createWithFormat("DinoColor/%s.png",names[i].c_str()) ;
           CCSprite* tmp2 = CCSprite::create(name->getCString());
           CCSize size2 = tmp2->getContentSize();
           CCRect insetRect2 = CCRectMake(0,0,size2.width, size2.height);
           CCScale9Sprite* sprite2 = CCScale9Sprite::create(name->getCString(), insetRect2) ;
           CCControlButton *button = CCControlButton::create(sprite2) ;
           button->setPreferredSize(size2) ;
           button->setTag(Tag+i);
           button->setPosition(ccp(v_size.width/4*3-poszero.x-10, 460 -140*(i))) ;
           this->addChild(button, 3) ;
           CCSprite* mark = CCSprite::create("DinoColor/brush-select.png");
           mark->setTag(Mark);
           mark->setPosition(ccp(size2.width/2, size2.height/2 ));
           button->addChild(mark);
           if (ColorManager::shared()->SelectBrushTag == Tag+i) {
               mark->setVisible(true);
           }else{
              mark->setVisible(false);
           }
           
           button->addTargetWithActionForControlEvents(this, cccontrol_selector(SelectBrush::brushClick), CCControlEventTouchUpInside) ;
       }
}

void SelectBrush::brushClick(CCObject *obj)
{
    int tag = ((CCNode*)obj)->getTag();
    for (int i = 0; i < 3; i++) {
        CCNode* node =this->getChildByTag(Tag+i);
        node->getChildByTag(Mark)->setVisible(false);
    }
    ((CCNode*)obj)->getChildByTag(Mark)->setVisible(true);
    ColorManager::shared()->SelectBrushTag = tag;
    
    switch (ColorManager::shared()->SelectBrushTag) {
        case 100:
            brushBtu->setNormalImage(CCSprite::create("DinoColor/pencil-normal.png"));
            brushBtu->setSelectedImage(CCSprite::create("DinoColor/pencil-down.png"));
            break;
        case 101:
            brushBtu->setNormalImage(CCSprite::create("DinoColor/brush-normal.png"));
            brushBtu->setSelectedImage(CCSprite::create("DinoColor/brush-down.png"));
            break;
        case 102:
            brushBtu->setNormalImage(CCSprite::create("DinoColor/largebrush-normal.png"));
            brushBtu->setSelectedImage(CCSprite::create("DinoColor/largebrush-down.png"));
            break;
        default:
            break;
    }
    brushBtu->selected();
    this->removeFromParent();
}

void SelectBrush::SetMenuItem(CCMenuItemSprite *item)
{
    brushBtu = item;
}
