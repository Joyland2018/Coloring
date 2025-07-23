//
//  SelectBrushLayer.hpp
//  DrDino
//
//  Created by chuining meng on 2020/4/30.
//

#ifndef SelectBrushLayer_hpp
#define SelectBrushLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
class SelectBrush : public Layer {
        
public:
    Size v_size;
    Vec2 poszero;
    CREATE_FUNC(SelectBrush);
    virtual bool init();
    static cocos2d::Scene* scene();
    
    void setButton();
    void brushClick(Ref* obj);
    ui::Widget* brushBtu;
    Layer* contentNode;
    
    void SetMenuItem(ui::Widget* item);
};

#endif /* SelectBrushLayer_hpp */
