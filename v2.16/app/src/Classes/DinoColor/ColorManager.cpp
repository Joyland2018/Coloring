//
//  ColorManager.cpp
//  JoyLandGerman
//
//  Created by chuining meng on 2020/3/17.
//

#include "ColorManager.hpp"
#include "ColorCanvasView.h"

#define Tag  100

static ColorManager* gm = NULL ;

ColorManager* ColorManager::shared()
{
    if (!gm) {
        gm = new ColorManager() ;
        for (int i = 0; i < 5; i++) {
            gm->SelectColorTag[i] = 100;
        }
    }
    
    return gm ;
}


void ColorManager::initColorManager(){
    yDis=-2360;
    firstPlayColor=true;
    colorThemeIndex = 0;
    colorAniIndex = 0;
    curTheme = 3;
    selectedTheme = false;
    scrollPenBoard = false;
    changeR = false;
    changeG =false;
    changeB = false;
    reverseR = false;
    reverseG = false;
    reverseB = false;

    buyState=false;
    
    curColorTheme = 3;
    selectedColorTheme = false;
//    reverseToFirst = false;
//    changeToSecond = false;
    
    colorNums =0;
    for (int i=0; i<7; i++) {
        colorThemePos[i] = 0.0;
    }
    

    
    this->initColorValue();
    
    curPenName = "pencil";
//    yDis=-2360;
}

void ColorManager::initColorValue(){
    curPaintIndex = 9;
    curPencilIndex = 9;
    curPaintbucketIndex = 9;
    curCrayonIndex = 9;
    curLargebrushIndex = 9;
    
    firstTouchPencil = false;
    firstTouchPaint = false;
    firstTouchCrayon = false;
    firstTouchLargebrush = false;
    firstTouchPaintbucket = false;
    
    for (int i=0; i<30; i++) {
        colorPaintPos[i] = 0.0;
        colorPencilPos[i] = 0.0;
        colorPaintbucketPos[i] = 0.0;
        colorCrayonPos[i] = 0.0;
        colorLargebrushPos[i] = 0.0;
    }
}



void ColorManager::changeCurColor()
{
    int tag = SelectColorTag[SelectBrushTag-100];
    ccColor3B colorVal;
    switch (tag) {
        case 1:
            colorVal = ccc3(248,37,15);
            break;
        case 2:
            colorVal = ccc3(243,148,2);
           break;
        case 3:
            colorVal = ccc3(255,255,50);
            break;
        case 4:
            colorVal = ccc3(98,170,50);
            break;
        case 5:
            colorVal = ccc3(65,199,255);
            break;
        case 6:
            colorVal = ccc3(2,68,246);
            break;
        case 7:
            colorVal = ccc3(197,58,239);
            break;
        case 8:
            colorVal = ccc3(232,89,139);
            break;
        case 9:
            colorVal = ccc3(254,95,78);
            break;
        case 10:
            colorVal = ccc3(180,27,13);
            break;
        case 11:
            colorVal = ccc3(178,59,6);
            break;
        case 12:
            colorVal = ccc3(244,80,8);
            break;
        case 13:
            colorVal = ccc3(255,126,70);
            break;
        case 14:
            colorVal = ccc3(255,181,65);
            break;
        case 15:
            colorVal = ccc3(176,106,2);
            break;
        case 16:
            colorVal = ccc3(174,131,2);
            break;
        case 17:
            colorVal = ccc3(241,188,35);
            break;
        case 18:
            colorVal = ccc3(7,29,64);
            break;
        case 19:
            colorVal = ccc3(255,232,77);
            break;
        case 20:
            colorVal = ccc3(203,188,43);
            break;
        case 21:
            colorVal = ccc3(143,160,29);
            break;
        case 22:
            colorVal = ccc3(204,227,44);
            break;
        case 23:
            colorVal = ccc3(173,239,125);
            break;
        case 24:
            colorVal = ccc3(61,102,29);
            break;
        case 25:
            colorVal = ccc3(2,142,202);
            break;
        case 26:
            colorVal = ccc3(1,93,132);
            break;
        case 27:
            colorVal = ccc3(64,117,254);
            break;
        case 28:
            colorVal = ccc3(1,50,179);
            break;
        case 29:
            colorVal = ccc3(35,0,92);
            break;
        case 30:
            colorVal = ccc3(61,1,160);
            break;
        case 31:
            colorVal = ccc3(120,55,227);
            break;
        case 32:
            colorVal = ccc3(130,2,170);
            break;
        case 33:
            colorVal = ccc3(79,1,103);
            break;
        case 34:
            colorVal = ccc3(93,14,43);
            break;
        case 35:
            colorVal = ccc3(162,24,73);
            break;
        case 36:
            colorVal = ccc3(162,24,73);
            break;
        case 37:
            colorVal = ccc3(0,0,0);
            break;
        case 38:
            colorVal = ccc3(140,140,140);
            break;
        case 39:
            colorVal = ccc3(115,115,115);
            break;
        case 40:
            colorVal = ccc3(89,89,89);
            break;
        case 41:
            colorVal = ccc3(64,64,64);
            break;
        case 42:
            colorVal = ccc3(191,191,191);
            break;
        default:
            break;
    }
    ColorManager::shared()->m_pColor = colorVal;
}

ccColor3B ColorManager::getCurColor(int _colorIndex)
{
    ccColor3B colorVal;
    switch (_colorIndex) {
        case 1:
            colorVal = ccc3(248,37,15);
            break;
        case 2:
            colorVal = ccc3(243,148,2);
           break;
        case 3:
            colorVal = ccc3(255,255,50);
            break;
        case 4:
            colorVal = ccc3(98,170,50);
            break;
        case 5:
            colorVal = ccc3(65,199,255);
            break;
        case 6:
            colorVal = ccc3(2,68,246);
            break;
        case 7:
            colorVal = ccc3(197,58,239);
            break;
        case 8:
            colorVal = ccc3(232,89,139);
            break;
        case 9:
            colorVal = ccc3(254,95,78);
            break;
        case 10:
            colorVal = ccc3(180,27,13);
            break;
        case 11:
            colorVal = ccc3(178,59,6);
            break;
        case 12:
            colorVal = ccc3(244,80,8);
            break;
        case 13:
            colorVal = ccc3(255,126,70);
            break;
        case 14:
            colorVal = ccc3(255,181,65);
            break;
        case 15:
            colorVal = ccc3(176,106,2);
            break;
        case 16:
            colorVal = ccc3(174,131,2);
            break;
        case 17:
            colorVal = ccc3(241,188,35);
            break;
        case 18:
            colorVal = ccc3(7,29,64);
            break;
        case 19:
            colorVal = ccc3(255,232,77);
            break;
        case 20:
            colorVal = ccc3(203,188,43);
            break;
        case 21:
            colorVal = ccc3(143,160,29);
            break;
        case 22:
            colorVal = ccc3(204,227,44);
            break;
        case 23:
            colorVal = ccc3(173,239,125);
            break;
        case 24:
            colorVal = ccc3(61,102,29);
            break;
        case 25:
            colorVal = ccc3(2,142,202);
            break;
        case 26:
            colorVal = ccc3(1,93,132);
            break;
        case 27:
            colorVal = ccc3(64,117,254);
            break;
        case 28:
            colorVal = ccc3(1,50,179);
            break;
        case 29:
            colorVal = ccc3(35,0,92);
            break;
        case 30:
            colorVal = ccc3(61,1,160);
            break;
        case 31:
            colorVal = ccc3(120,55,227);
            break;
        case 32:
            colorVal = ccc3(130,2,170);
            break;
        case 33:
            colorVal = ccc3(79,1,103);
            break;
        case 34:
            colorVal = ccc3(93,14,43);
            break;
        case 35:
            colorVal = ccc3(162,24,73);
            break;
        case 36:
            colorVal = ccc3(162,24,73);
            break;
        case 37:
            colorVal = ccc3(0,0,0);
            break;
        case 38:
            colorVal = ccc3(140,140,140);
            break;
        case 39:
            colorVal = ccc3(115,115,115);
            break;
        case 40:
            colorVal = ccc3(89,89,89);
            break;
        case 41:
            colorVal = ccc3(64,64,64);
            break;
        case 42:
            colorVal = ccc3(191,191,191);
            break;
        default:
            break;
    }
    
    return colorVal;
}

void ColorManager::firstColorValue(int colorIndex){
    ccColor3B colorVal;
    if (strcmp(curPenName, "pencil")==0){
        colorNums =2;
        switch (colorIndex) {
            case 12:
                colorVal = ccc3(255, 183, 87);
                secondColor = ccc3(248, 37, 15);
                break;
            case 13:
                colorVal = ccc3(2, 58, 205);
                secondColor = ccc3(136, 177, 251);
                break;
            case 14:
                colorVal = ccc3(253, 89, 152);
                secondColor = ccc3(0, 22, 252);
                break;
            case 15:
                colorVal = ccc3(62, 246, 196);
                secondColor = ccc3(6, 141, 163);
                break;
            default:
                break;
        }
    }else if (strcmp(curPenName, "paint")==0){
        switch (colorIndex) {
            case 12:
                colorVal = ccc3(234, 37, 88);
                secondColor = ccc3(101, 89, 252);
                thirdColor = ccc3(249,170,212);
                colorNums =3;
                break;
            case 13:
                colorVal = ccc3(51, 248, 4);
                secondColor = ccc3(248, 245, 66);
                thirdColor = ccc3(140,35,249);
                colorNums =3;
                break;
            case 14:
                colorVal = ccc3(254, 250, 90);
                secondColor = ccc3(10, 243, 224);
                thirdColor = ccc3(242,64,219);
                colorNums =3;
                break;
            case 15:
                colorVal = ccc3(74, 98, 250);
                secondColor = ccc3(58, 234, 3);
                colorNums =2;
                break;
            default:
                break;
        }
    }

    changeThirdR = false;
    changeThirdG = false;
    changeThirdB = false;
    
    changeR = false;
    changeG =false;
    changeB = false;
    reverseR = false;
    reverseG = false;
    reverseB = false;
    
    firstColor = colorVal;
    m_pColor = colorVal;
}

void ColorManager::doubleColorChange(){
    
//    CCLOG("---第一个颜色的R%d---",m_pColor.r);
//    CCLOG("---第一个颜色的G%d---",m_pColor.g);
//    CCLOG("---第一个颜色的B%d---",m_pColor.b);
        if (m_pColor.r>secondColor.r && changeR ==false) {
                CCLOG("---第一个颜色的R%d---",m_pColor.r);
            //    CCLOG("---第一个颜色的G%d---",m_pColor.g);
            //    CCLOG("---第一个颜色的B%d---",m_pColor.b);
            reverseR = false;
            if (m_pColor.r-5<secondColor.r) {
                m_pColor.r=secondColor.r;
            }else{
                m_pColor.r-= 5;
            }
            
//            CCLOG("---颜色变小---");
        }else if(m_pColor.r<secondColor.r && changeR ==false){
            reverseR = false;
            if (m_pColor.r+5>secondColor.r) {
                m_pColor.r=secondColor.r;
            }else{
                m_pColor.r+= 5;
            }
//            if(changeThirdR == true){
                changeThirdR = false;
//            }
//            m_pColor.r+=5;
//            CCLOG("---颜色变大---");
        }
        if (m_pColor.r == secondColor.r){
            if(changeR == false &&  reverseR == false){
                changeR = true;

//                changeThirdR = false;
//            }else if(changeR == true &&  reverseR == true){
//                changeR = false;
            }
//            if(changeThirdR == true){
                changeThirdR = false;
//            }
        }
        
        if (m_pColor.g>secondColor.g && changeG ==false) {
            reverseG = false;
            if (m_pColor.g-5<secondColor.g) {
                m_pColor.g=secondColor.g;
            }else{
                m_pColor.g-= 5;
            }
//            if(changeThirdG == true){
                changeThirdG = false;
//            }
        }else if(m_pColor.g<secondColor.g && changeG ==false){
            reverseG = false;
            if (m_pColor.g+5>secondColor.g) {
                m_pColor.g=secondColor.g;
            }else{
                m_pColor.g+= 5;
            }
//            if(changeThirdG == true){
                changeThirdG = false;
//            }
        }
        
        if (m_pColor.g == secondColor.g ){
            if(changeG == false && reverseG == false){
                changeG = true;
//                changeThirdG = false;
//            }else if(changeG == true && reverseG == true){
//                changeG = false;
            }
//            if(changeThirdG == true){
//                changeThirdG = false;
//            }
        }
        

        
        if (m_pColor.b>secondColor.b && changeB ==false) {
            if (m_pColor.b-5<secondColor.b) {
                m_pColor.b=secondColor.b;
            }else{
                m_pColor.b-= 5;
            }
            reverseB = false;
//            if(changeThirdB == true){
                changeThirdB = false;
//            }
        }else if(m_pColor.b<secondColor.b && changeB ==false){
            if (m_pColor.b+5>secondColor.b) {
                m_pColor.b=secondColor.b;
            }else{
                m_pColor.b+= 5;
            }
            reverseB = false;
//            if(changeThirdB == true){
                changeThirdB = false;
//            }
        }
        if (m_pColor.b == secondColor.b ){
            if(changeB == false &&  reverseB == false){
                changeB = true;
//                changeThirdB = false;
//            }else if(changeB == true && reverseB == true){
//                changeB = false;
            }
//            if(changeThirdB == true){
////                changeThirdB = false;
//            }
        }
    if (changeR==true && changeG==true && changeB==true) {
        if (colorNums==2) {
            if ( m_pColor.r<firstColor.r) {
    //            m_pColor.r+= 5;
                if (m_pColor.r+5>firstColor.r) {
                    m_pColor.r=firstColor.r;
                }else{
                    m_pColor.r+= 5;
                }
//                CCLOG("---颜色变回来加---");
                reverseR = true;
            }else if(m_pColor.r>firstColor.r){
    //            m_pColor.r-= 5;
                if (m_pColor.r-5<firstColor.r) {
                    m_pColor.r=firstColor.r;
                }else{
                    m_pColor.r-= 5;
                }
//                CCLOG("---颜色变回来减---");
                reverseR = true;
            }
            
            if (m_pColor.g<firstColor.g) {
    //            m_pColor.g+= 5;
                if (m_pColor.g+5>firstColor.g) {
                    m_pColor.g=firstColor.g;
                }else{
                    m_pColor.g+= 5;
                }
                reverseG = true;
            }else if(m_pColor.g>firstColor.g){
    //            m_pColor.g-= 5;
                if (m_pColor.g-5<firstColor.g) {
                    m_pColor.g=firstColor.g;
                }else{
                    m_pColor.g-= 5;
                }
                reverseG = true;
            }
            
            if (m_pColor.b<firstColor.b) {
    //            m_pColor.b+= 5;
                if (m_pColor.b+5>firstColor.b) {
                    m_pColor.b=firstColor.b;
                }else{
                    m_pColor.b+= 5;
                }
                reverseB = true;
            }else if( m_pColor.b>firstColor.b){
    //            m_pColor.b-=5;
                if (m_pColor.b-5<firstColor.b) {
                    m_pColor.b=firstColor.b;
                }else{
                    m_pColor.b-= 5;
                }
                reverseB = true;
            }
            
            if (m_pColor.r == firstColor.r ){
                if(changeR == true && reverseR == true){
                    changeR = false;
                    reverseR = false;
                }
            }
            
            if (m_pColor.g == firstColor.g ){
                if(changeG == true && reverseG == true){
                    changeG = false;
                    reverseG = false;
                }
            }
            
            if (m_pColor.b == firstColor.b ){
                if(changeB == true && reverseB == true){
                    changeB = false;
                    reverseB = false;
                }
            }
        }else if(colorNums==3){
            //r\g\b都变为第二个颜色
            this->trebleColorChange();
        }

    }
}


void ColorManager::trebleColorChange(){
    if (changeThirdR==false || changeThirdG==false || changeThirdB==false) {
        CCLOG("---第二个颜色的R%d---",m_pColor.r);
        CCLOG("---第二个颜色的G%d---",m_pColor.g);
        CCLOG("---第二个颜色的B%d---",m_pColor.b);
        if ( m_pColor.r<thirdColor.r) {
    //            m_pColor.r+= 5;
            if (m_pColor.r+5>thirdColor.r) {
                m_pColor.r=thirdColor.r;
            }else{
                m_pColor.r+= 5;
            }
//            CCLOG("---颜色变回来加---");
            reverseR = true;
        }else if(m_pColor.r>thirdColor.r){
    //            m_pColor.r-= 5;
            if (m_pColor.r-5<thirdColor.r) {
                m_pColor.r=thirdColor.r;
            }else{
                m_pColor.r-= 5;
            }
//            CCLOG("---颜色变回来减---");
            reverseR = true;
        }
        
        if (m_pColor.r == thirdColor.r){
            if(changeThirdR == false){
                changeThirdR = true;
            }
        }
        
        
        if (m_pColor.g<thirdColor.g) {
    //            m_pColor.g+= 5;
            if (m_pColor.g+5>thirdColor.g) {
                m_pColor.g=thirdColor.g;
            }else{
                m_pColor.g+= 5;
            }
            reverseG = true;
        }else if(m_pColor.g>thirdColor.g){
    //            m_pColor.g-= 5;
            if (m_pColor.g-5<thirdColor.g) {
                m_pColor.g=thirdColor.g;
            }else{
                m_pColor.g-= 5;
            }
            reverseG = true;
        }
        
        if (m_pColor.g == thirdColor.g){
            if(changeThirdG == false){
                changeThirdG = true;
            }
        }
        
        if (m_pColor.b<thirdColor.b) {
    //            m_pColor.b+= 5;
            if (m_pColor.b+5>thirdColor.b) {
                m_pColor.b=thirdColor.b;
            }else{
                m_pColor.b+= 5;
            }
            reverseB = true;
        }else if( m_pColor.b>thirdColor.b){
    //            m_pColor.b-=5;
            if (m_pColor.b-5<thirdColor.b) {
                m_pColor.b=thirdColor.b;
            }else{
                m_pColor.b-= 5;
            }
            reverseB = true;
        }
        
        if (m_pColor.b == thirdColor.b){
            if(changeThirdB == false){
                changeThirdB = true;
            }
        }
    }
    //r\g\b都变为第三个颜色
    if (changeThirdR==true && changeThirdG==true && changeThirdB==true) {
//        CCLOG("---第一个颜色的R%d---",firstColor.r);
//        CCLOG("---第一个颜色的G%d---",firstColor.g);
//        CCLOG("---第一个颜色的B%d---",firstColor.b);
        
        CCLOG("---第三个颜色的R%d---",m_pColor.r);
        CCLOG("---第三个颜色的G%d---",m_pColor.g);
        CCLOG("---第三个颜色的B%d---",m_pColor.b);
        
        
            if ( m_pColor.r<firstColor.r) {
    //            m_pColor.r+= 5;
                if (m_pColor.r+5>firstColor.r) {
                    m_pColor.r=firstColor.r;
//                    changeR = false;
//                    reverseR = false;
                }else{
                    m_pColor.r+= 5;
                }
//                CCLOG("---颜色变回来加---");
                reverseR = true;
            }else if(m_pColor.r>firstColor.r){
    //            m_pColor.r-= 5;
                if (m_pColor.r-5<firstColor.r) {
                    m_pColor.r=firstColor.r;
//                    changeR = false;
//                    reverseR = false;
                }else{
                    m_pColor.r-= 5;
                }
//                CCLOG("---颜色变回来减---");
                reverseR = true;
            }
            
            if (m_pColor.g<firstColor.g) {
    //            m_pColor.g+= 5;
                if (m_pColor.g+5>firstColor.g) {
                    m_pColor.g=firstColor.g;
//                    changeG = false;
//                    reverseG = false;
                }else{
                    m_pColor.g+= 5;
                }
                reverseG = true;
            }else if(m_pColor.g>firstColor.g){
    //            m_pColor.g-= 5;
                if (m_pColor.g-5<firstColor.g) {
                    m_pColor.g=firstColor.g;
//                    changeG = false;
//                    reverseG = false;
                }else{
                    m_pColor.g-= 5;
                }
                reverseG = true;
            }
            
            if (m_pColor.b<firstColor.b) {
    //            m_pColor.b+= 5;
                if (m_pColor.b+5>firstColor.b) {
                    m_pColor.b=firstColor.b;
//                    changeB = false;
//                    reverseB = false;
                }else{
                    m_pColor.b+= 5;
                }
                reverseB = true;
            }else if( m_pColor.b>firstColor.b){
    //            m_pColor.b-=5;
                if (m_pColor.b-5<firstColor.b) {
                    m_pColor.b=firstColor.b;
//                    changeB = false;
//                    reverseB = false;
                }else{
                    m_pColor.b-= 5;
                }
                reverseB = true;
            }
        

        
//        if (m_pColor.r == firstColor.r ){
//            if(changeR == true && reverseR == true){
////                changeR = false;
//                reverseR = false;
//
//            }
//        }
//
//        if (m_pColor.g == firstColor.g ){
//            if(changeG == true && reverseG == true){
////                changeG = false;
//                reverseG = false;
//
//            }
//        }
//
//        if (m_pColor.b == firstColor.b ){
//            if(changeB == true && reverseB == true){
////                changeB = false;
//                reverseB = false;
//
//            }
//        }
        //r\g\b都变为第一个颜色
        if(m_pColor.r == firstColor.r  && m_pColor.g == firstColor.g && m_pColor.b == firstColor.b){
            changeR = false;
            changeG = false;
            changeB = false;
            reverseR = false;
            reverseG = false;
            reverseB = false;
        }
    }

}

CCTexture2D* ColorManager::maskedWithSpriteTexture(CCSprite* texturesp, CCSprite* masksp,CCPoint location)
{
    CCRenderTexture* newRendertexture = CCRenderTexture::create(masksp->getContentSize().width, masksp->getContentSize().height);
    
    masksp->setPosition(ccp(masksp->getContentSize().width*location.x, masksp->getContentSize().height*location.y));
    texturesp->setPosition(ccp(masksp->getContentSize().width*location.x, masksp->getContentSize().height*location.y));
    
    masksp->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO});
    texturesp->setBlendFunc((ccBlendFunc){GL_DST_ALPHA, GL_ZERO});
    
    newRendertexture->begin();
    masksp->visit();
    texturesp->visit();
    newRendertexture->end();
    newRendertexture->cleanup();
    
    return newRendertexture->getSprite()->getTexture();
}

CCImage* ColorManager::loadImageFromBinaryFile(const std::string &_fileName)
{
    std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath()+_fileName+".bin";
    // Open the file
    FILE* file = fopen(fullPath.c_str(), "rb");
    if (!file) {
        // Handle error
        return nullptr;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
//    rewind(file);

    // Allocate a buffer to hold the file contents
    char* buffer = new char[fileSize];

    // Read the file contents into the buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);


    // Create a CCImage from the binary data
    CCImage* image = new CCImage();
    if (!image->initWithImageData(buffer, static_cast<int>(bytesRead))) {
        // Handle error
        delete[] buffer;
        delete image;
        return nullptr;
    }

    // Clean up the buffer
    delete[] buffer;
    // Close the file
    fclose(file);
//    image->autorelease();
    
    return image;
}

void ColorManager::saveTextureToFile(std::string _fileName, ColorSprite *_colorSpr)
{
    CCSize sprSize = _colorSpr->getContentSize();
    CCRenderTexture* saverenderTexture = CCRenderTexture::create(sprSize.width, sprSize.height, kCCTexture2DPixelFormat_RGBA8888);
    saverenderTexture->begin();
    _colorSpr->visit();
    saverenderTexture->end();
    
    std::string localPath = CCFileUtils::sharedFileUtils()->getWritablePath()+_fileName+".bin";
    CCImage* saveImage = saverenderTexture->newCCImage();
    saveImage->saveToFile(localPath.c_str());
    saveImage->release();
    
}



