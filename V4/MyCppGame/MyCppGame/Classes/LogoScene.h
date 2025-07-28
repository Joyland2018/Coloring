//
//  LogoScene.h
//  GameGarden
//
//  Created by LiXiaofei on 2017/2/23.
//
//

#ifndef LogoScene_h
#define LogoScene_h

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class LogoScene : public Layer {

    
public:
    static Scene* scene();
    
    virtual bool init();
    
    LogoScene();
    virtual ~LogoScene();
    
    virtual void onEnter();
    virtual void onExit();
    
    CREATE_FUNC(LogoScene);
    
private:
    void runGame(float dt);
};

#endif /* LogoScene_h */
