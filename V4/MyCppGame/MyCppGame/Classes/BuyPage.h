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

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

using namespace cocos2d;

#define kRemoveSelf "buylayer.remove"
#define kGetAll "buypage.getall"

class BuyPage : public Layer {
public:
    static BuyPage* nodeWithID(int tag);
    bool initWithID(int tag);
    BuyPage();
    virtual ~BuyPage();

    void loadIAPStore(int tag);
    void loadBigStore(int tag);
    const char* getCommodityType(int tag);
    void selectProductID(int tag,bool isRestore);

    void buyClick(Ref* pSender);
    void watchAdsClick(Ref* pSender);
//    void restoreClick(Ref* pSender);

    void cancelBuy(Ref* pSender);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

    void initNotification();
    void timeout();
    void contactHud();
    void initPurchase(const std::string& productID);
    void restorePurchase();
    void createParentsLock();
    void parentsLockCallback(Ref *sender);

    void productsLoaded(EventCustom* event);
    void productPurchased(EventCustom* event);
    void productPurchaseFailed(EventCustom *event);

    static void setPageIndex(int _pageIndex);

    void setInitPageIndex(int _index);

    void setAllVersion();

private:
    void termsLinkClick(Ref* pSender);

    void initPrompt(Ref* _parent);

    static int _curPageIndex;
public:
    bool isBuying;
    bool isTouchTerms;

    CallFunc* func;

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