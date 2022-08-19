//
//  ColorManager.hpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#ifndef ColorManager_hpp
#define ColorManager_hpp

#include <stdio.h>
#include "cocos2d.h"
class ColorCanvasView ;

using namespace cocos2d;

typedef enum {
    Draw_Point = 1,
    Draw_Plating = 2,
    Draw_Eraser = 3
    
}DrawType;

class ColorManager {
    
    
public:
    static ColorManager* shared();
    void initColorManager();
    DrawType m_DrawType  = Draw_Point;
    ccColor3B m_pColor ;
    int SelectColorTag = 100 ;
    int yDis=0;
    int SelectBrushTag = 100 ;
    ColorCanvasView* m_pCanvasLayer ;
    int m_AnimalTag;
    bool firstPlayColor;
    int aniPosArr[40][2];
};

#endif /* ColorManager_hpp */
