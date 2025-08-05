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
#include "ColorSprite.h"
class ColorCanvasView ;

using namespace cocos2d;

typedef enum {
    Draw_Point = 1,
    Draw_Plating = 2,
    Draw_Eraser = 3
    
}DrawType;

typedef enum {
    Brush_Crayon = 100,
    Brush_Paint = 101,
    Brush_Pencil = 102,
    Brush_Paintbucket = 103,
    Brush_Largebrush = 104,
    Brush_Texture = 105,
} BrushType;

class ColorManager {
    
    
public:
    static ColorManager* shared();
    void initColorManager();
    void changeCurColor();
    
    ccColor3B getCurColor(int _colorIndex);
    
    CCTexture2D* maskedWithSpriteTexture(CCSprite* texturesp, CCSprite* masksp,CCPoint location);
    
    void saveTextureToFile(std::string _fileName, ColorSprite* _colorSpr);
    
    CCImage* loadImageFromBinaryFile(const std::string& _fileName);
    
    bool checkIsNeedToRemoveFile(std::string _fileName);
    void removeAllNeedToRemoveFiles();
    void removeTwentyFiveNeedToRemoveFiles();
    bool removeImageBinaryFile(std::string _fileName);
    
    void doubleColorChange();
    void trebleColorChange();
    void firstColorValue(int colorIndex);
    void initColorValue();
    
    
    DrawType m_DrawType  = Draw_Point;
    ccColor3B m_pColor ;
    ccColor3B secondColor ;
    ccColor3B thirdColor ;
    ccColor3B firstColor ;
    
    
    bool changeR;
    bool changeG;
    bool changeB;
    
    bool changeThirdR;
    bool changeThirdG;
    bool changeThirdB;
    
    bool reverseR;
    bool reverseG;
    bool reverseB;
    
    int colorNums;
//    int SelectColorTag = 100 ;
    int SelectColorTag[5];
    int yDis=0;
    int SelectBrushTag = 100 ;
    ColorCanvasView* m_pCanvasLayer ;
    int m_AnimalTag;
    int aniPosArr[50][2];
    int colorThemeIndex;
    int colorAniIndex;
    float colorThemePos[17];
    bool selectedTheme;
    int curTheme;
    const char* curPenName;
    
    float colorPencilPos[50];
    float colorPaintPos[50];
    float colorCrayonPos[50];
    float colorPaintbucketPos[50];
    float colorLargebrushPos[50];
    
    int themeIndexArr[18];
    
    bool scrollPenBoard;
    
    int curColorTheme;
    bool selectedColorTheme;
    
    bool firstTouchPencil;
    bool firstTouchPaint;
    bool firstTouchCrayon;
    bool firstTouchPaintbucket;
    bool firstTouchLargebrush;
    
    bool isMovingColorBlock;
    bool touchedPenButton;
    
    bool isNewbieGuideActive;
    
    int curPencilIndex;
    int curPaintIndex;
    int curPaintbucketIndex;
    int curLargebrushIndex;
    int curCrayonIndex;
    int curSelectColorIndex;
    
    int colorBookIndex;
    int curPaintPenColorIndex;
    int curPencilPenColorIndex;
    int curThemeTotalCount;
};

#endif /* ColorManager_hpp */
