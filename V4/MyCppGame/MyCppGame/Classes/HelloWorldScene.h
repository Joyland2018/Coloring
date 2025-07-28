#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
    Size winsize;
    Vec2 poszero;
    int accessIndex;
    int locknum[3];
    int accessnum[3];
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    virtual void onEnter();
    virtual void onExit();
    void clearLock();

    CREATE_FUNC(HelloWorld);
    
    // Event handlers for the new event system
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    // implement the "static node()" method manually
};

#endif // __HELLOWORLD_SCENE_H__
