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
#include "ColorSprite/ColorSprite.h"
class ColorCanvasView ;

using namespace cocos2d;

typedef enum {
    Draw_Point = 1,
    Draw_Plating = 2,
    Draw_Eraser = 3
    
}DrawType;

typedef enum {
    Brush_Pencil = 100,
    Brush_Paint = 101,
    Brush_Largebrush = 104,
    Brush_Paintbucket = 103,
    Brush_Crayon = 102,
} BrushType;

class ColorManager {
    
    
public:
    static ColorManager* shared();
    void initColorManager();
    void changeCurColor();
    
    Color3B getCurColor(int _colorIndex);
    Texture2D* maskedWithSpriteTexture(Sprite* texturesp, Sprite* masksp, Vec2 location);
    
    void saveTextureToFile(std::string _fileName, ColorSprite* _colorSpr);
    
    Image* loadImageFromBinaryFile(const std::string& _fileName);
    
    void doubleColorChange();
    void trebleColorChange();
    void firstColorValue(int colorIndex);
    void initColorValue();
    
    
    DrawType m_DrawType  = Draw_Point;
    Color3B m_pColor ;
    Color3B secondColor ;
    Color3B thirdColor ;
    Color3B firstColor ;
    
    
    bool changeR;
    bool changeG;
    bool changeB;
    bool buyState;
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
    bool firstPlayColor;
    int aniPosArr[50][2];
    int colorThemeIndex;
    int colorAniIndex;
    float colorThemePos[10];
    bool selectedTheme;
    int curTheme;
    const char* curPenName;
    
    float colorPencilPos[30];
    float colorPaintPos[30];
    float colorCrayonPos[30];
    float colorPaintbucketPos[30];
    float colorLargebrushPos[30];
    
    bool scrollPenBoard;
    
    int curColorTheme;
    bool selectedColorTheme;
    
    bool firstTouchPencil;
    bool firstTouchPaint;
    bool firstTouchCrayon;
    bool firstTouchPaintbucket;
    bool firstTouchLargebrush;
    
    int curPencilIndex;
    int curPaintIndex;
    int curPaintbucketIndex;
    int curLargebrushIndex;
    int curCrayonIndex;
};

#endif /* ColorManager_hpp */
