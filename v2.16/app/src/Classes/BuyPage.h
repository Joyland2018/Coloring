//
//  BuyPage.h
//  JoyPreschool
//
//  Created by LiXiaofei on 2018/2/7.
//

#ifndef BuyPage_h
#define BuyPage_h

#include "cocos2d.h"
#include "GameManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "BuyPage.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

using namespace cocos2d;

#define kRemoveSelf "buylayer.remove"
#define kGetAll "buypage.getall"

class BuyPage : public CCLayer {
public:
    static BuyPage* nodeWithID(int tag);
    bool initWithID(int tag);
    BuyPage();
    virtual ~BuyPage();

    void loadIAPStore(int tag);
    void loadBigStore(int tag);
    const char* getCommodityType(int tag);
    void selectProductID(int tag,bool isRestore);

    void buyClick(CCObject* pSender);
    void watchAdsClick(CCObject* pSender);
//    void restoreClick(CCObject* pSender);

    void cancelBuy(CCObject* pSender);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    virtual void registerWithTouchDispatcher();

    void initNotification();
    void timeout();
    void contactHud();
    void initPurchase(CCString* productID);
    void restorePurchase();
    void createParentsLock();
    void parentsLockCallback(CCObject *sender);

    void productsLoaded(CCNotificationObserver* notification);
    void productPurchased(CCNotificationObserver* notification);
    void productPurchaseFailed(CCNotificationObserver *notification);

    static void setPageIndex(int _pageIndex);

    void setInitPageIndex(int _index);

    void setAllVersion();

private:
    void termsLinkClick(CCObject* pSender);

    void initPrompt(CCObject* _parent);

    static int _curPageIndex;
public:
    bool isBuying;
    bool isTouchTerms;

    CCCallFunc* func;

    int storeIndex;
    int dogIndex;

    int pageIndex;

    int productIndex;

    int locknum[3];
    int accessnum[3];
    int accessIndex;

    bool isTouchBuy;
};

#endif /* BuyPage_h */