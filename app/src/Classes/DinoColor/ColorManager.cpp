//
//  ColorManager.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#include "ColorManager.h"

static ColorManager* gm = NULL ;

ColorManager* ColorManager::shared()
{
    if (!gm) {
        gm = new ColorManager() ;
    }
    
    return gm ;
}

void ColorManager::initColorManager(){
    yDis=-2360;
    firstPlayColor=true;
    
//    yDis=-2360;
}
