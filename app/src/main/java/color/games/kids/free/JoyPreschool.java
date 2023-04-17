/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 http://www.cocos2d-x.org
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
package color.games.kids.free;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONException;
import org.json.JSONObject;

import com.android.billingclient.api.ProductDetails;
import com.android.billingclient.api.ProductDetailsResponseListener;
import com.android.billingclient.api.PurchasesUpdatedListener;
import com.android.billingclient.api.AcknowledgePurchaseParams;
import com.android.billingclient.api.AcknowledgePurchaseResponseListener;
import com.android.billingclient.api.BillingClient;
import com.android.billingclient.api.BillingClientStateListener;
import com.android.billingclient.api.BillingFlowParams;
import com.android.billingclient.api.BillingResult;
import com.android.billingclient.api.Purchase;
//import com.android.billingclient.api.PurchasesUpdatedListener;
import com.android.billingclient.api.SkuDetails;
import com.android.billingclient.api.SkuDetailsParams;
import com.android.billingclient.api.SkuDetailsResponseListener;
//import com.applovin.sdk.AppLovinSdk;
import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.interstitial.InterstitialAd;
//import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.RequestConfiguration;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;
import com.google.android.gms.ads.rewarded.RewardItem;
import com.google.android.gms.ads.rewarded.RewardedAd;
//import com.google.android.gms.ads.rewarded.RewardedAdCallback;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;
//import com.mixpanel.android.mpmetrics.MixpanelAPI;

import com.android.billingclient.api.PurchasesResponseListener;

import static com.google.android.gms.ads.RequestConfiguration.MAX_AD_CONTENT_RATING_G;
import static com.google.android.gms.ads.RequestConfiguration.TAG_FOR_UNDER_AGE_OF_CONSENT_TRUE;
import static com.google.android.gms.ads.mediation.MediationAdRequest.TAG_FOR_CHILD_DIRECTED_TREATMENT_TRUE;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
//import com.mixpanel.android.mpmetrics.MixpanelAPI;

import org.cocos2dx.lib.Cocos2dxHelper;

//import com.amazon.device.iap.PurchasingService;
//import com.amazon.device.iap.model.RequestId;
//import com.jpt.joyland.util.IabBroadcastReceiver.IabBroadcastListener;
//import com.jpt.joyland.util.IabBroadcastReceiver;
//import com.jpt.joyland.util.IabHelper;
//import com.jpt.joyland.util.IabHelper.IabAsyncInProgressException;
//import com.jpt.joyland.util.IabResult;
//import com.jpt.joyland.util.Inventory;
//import com.jpt.joyland.util.Purchase;
//import com.tapjoy.TJConnectListener;
//import com.tapjoy.Tapjoy;
//import com.tapjoy.TapjoyConnectFlag;

import android.Manifest;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.Toast;

public class JoyPreschool extends Cocos2dxActivity implements PurchasesUpdatedListener {

    //	public SampleIapManager sampleIapManager;
    // Does the user have the premium upgrade?
    boolean mIsPremium = false;
    String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAlPOc2kJSoxdG+kuekvqOUy2OB7f/hTw/yexNpjCkyfIjLBJq7AEG7AG3kLqSi4ulUNsMkq7d0LlBDWHLOhWF/0gQncIz0G0vaVtvPq4h3ygB1TKM/CLoKs2NqMOD4wvrGCgD8nbvAdheT20PxU9ZhDEvnbDMnu94m2lCjS5Iq+jzwo+3GHhYT+x3hWGSyvQpXTIXIM6vs83ctOND2tYhCsSYAl2LSIHucEuT5DYYcO4qFNOFg+8TdYE29wbusb9WYUS4U4XzrnBrZd4I9JZRm7KLJnVASZTVb8B6mzuxk3FkdRnNRQXBfy544kszB0uzdSDq6lUDSjXAAExpScydbwIDAQAB";
    // The helper object
//    IabHelper mHelper;
//
    public AdManager mAdManager;
    public IAPManager mIAPManager;
    public ProductDetails allLifetimeSkuDetails;
    public ProductDetails flashSaleSkuDetails;
    public ProductDetails yearlySkuDetails;
    public ProductDetails monthlySkuDetails;

    public int connectFailCount = 0;
    public int connectErrorCount = 0;
    public BillingClientStateListener billingClientStateListener;
//    public SkuDetailsResponseListener skuDetailsResponseListener;
public ProductDetailsResponseListener skuDetailsResponseListener;
    //    // Provides purchase notification while this app is running
//    IabBroadcastReceiver mBroadcastReceiver;
    // Does the user have an active subscription to the infinite gas plan?
    boolean mSubscribedToInfiniteGas = false;

    // Will the subscription auto-renew?
    boolean mAutoRenewEnabled = false;

    // Tracks the currently owned infinite gas SKU, and the options in the Manage dialog
    String mInfiniteGasSku = "";
    String mFirstChoiceSku = "";
    String mSecondChoiceSku = "";

    // Used to select between purchasing gas on a monthly or yearly basis
    String mSelectedSubscriptionPeriod = "";
    // SKUs for our products: the premium upgrade (non-consumable) and gas (consumable)
//    static final String SKU_PREMIUM = "premium";
//    static final String SKU_GAS = "gas";

    // SKU for our subscription (infinite gas)
//    static final String SKU_INFINITE_GAS_MONTHLY = "month.joyland.sub";
//    static final String SKU_INFINITE_GAS_YEARLY = "year.joyland.sub";
    // (arbitrary) request code for the purchase flow
    static final int RC_REQUEST = 10001;

    // How many units (1/4 tank is our unit) fill in the tank.
    static final int TANK_MAX = 4;

    // Current amount of gas in tank, in units
    int mTank;

    public static JoyPreschool joylandInstance;
    public int _buySceneIndex;
    public boolean _isBegin;
    public AdView bannerView;
    public static native void onRewardAdsCallBack();
    public InterstitialAd InterstitialAd;
    public RewardedAd RewardedAds;
    public boolean isCanGetReward;

    public int mBuyIndex;

    public SkuDetails noAdsSkuDetails;
    public SkuDetails primeSkuDetails;

    public int mGameIndex;
    public void cppSetTrack(String _trackStr){
        setMixpanelTrack(_trackStr,"");
    }

    protected void onCreate(Bundle savedInstanceState){
        //获取obb 路径
//        requestPermission();
//        FATE_OBB_PATH =getVirtualObbFileFullpath() ;//这句需要放在super.onCreate上面
        super.onCreate(savedInstanceState);
//    	FATE_OBB_PATH =getVirtualObbFileFullpath();
//		super.onCreate(savedInstanceState);
        hideNavigationBar();

//        AppLovinSdk.initializeSdk(this);
//        RequestConfiguration requestConfiguration = MobileAds.getRequestConfiguration().toBuilder().setTagForChildDirectedTreatment(TAG_FOR_CHILD_DIRECTED_TREATMENT_TRUE).setTagForUnderAgeOfConsent(TAG_FOR_UNDER_AGE_OF_CONSENT_TRUE).setMaxAdContentRating(MAX_AD_CONTENT_RATING_G).build();
//        MobileAds.setRequestConfiguration(requestConfiguration);
//        MobileAds.initialize(this, new OnInitializationCompleteListener() {         //this  当前方法的类； Listener 回调函数
//            @Override           //重写
//            public void onInitializationComplete(InitializationStatus initializationStatus) {
////                createAndLoadBannerAds();
//                createAndLoadInterstitialAds();
////                createAndLoadRewardedAds();
//
//            }
//        });

//		connectToTapjoy();
//		setupIAPOnCreate();

        Log.d(TAG, "Creating IAB helper.");
//        mHelper = new IabHelper(this, base64EncodedPublicKey);
//
//        // enable debug logging (for a production application, you should set this to false).
//        mHelper.enableDebugLogging(true);
//
//        // Start setup. This is asynchronous and the specified listener
//        // will be called once setup completes.
//        Log.d(TAG, "Starting setup.");
//        mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
//            public void onIabSetupFinished(IabResult result) {
//                Log.d(TAG, "Setup finished.");
//
//                if (!result.isSuccess()) {
//                    // Oh noes, there was a problem.
//                    complain("Problem setting up in-app billing: " + result);
//                    return;
//                }
//
//                // Have we been disposed of in the meantime? If so, quit.
//                if (mHelper == null) return;
//
//                // Important: Dynamically register for broadcast messages about updated purchases.
//                // We register the receiver here instead of as a <receiver> in the Manifest
//                // because we always call getPurchases() at startup, so therefore we can ignore
//                // any broadcasts sent while the app isn't running.
//                // Note: registering this listener in an Activity is a bad idea, but is done here
//                // because this is a SAMPLE. Regardless, the receiver must be registered after
//                // IabHelper is setup, but before first call to getPurchases().
//                mBroadcastReceiver = new IabBroadcastReceiver(JoyPreschool.this);
//                IntentFilter broadcastFilter = new IntentFilter(IabBroadcastReceiver.ACTION);
//                registerReceiver(mBroadcastReceiver, broadcastFilter);
//
//                // IAB is fully set up. Now, let's get an inventory of stuff we own.
//                Log.d(TAG, "Setup successful. Querying inventory.");
//                try {
//                    mHelper.queryInventoryAsync(mGotInventoryListener);
//                } catch (IabAsyncInProgressException e) {
//                    complain("Error querying inventory. Another async operation in progress.");
//                }
//            }
//        });
        //IAP
        joylandInstance = this;
//        connectMixpanel();
//        billingClient = BillingClient.newBuilder(this).enablePendingPurchases().setListener(this).build();
//        billingClient.startConnection(new BillingClientStateListener() {
//            @Override
//            public void onBillingSetupFinished(BillingResult billingResult) {
//                if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK){
////                    queryPurchaseStatus();
////                    querySkuDetails();
////                    queryScripSkuDetails();
//                }
//            }
//
//            @Override
//            public void onBillingServiceDisconnected() {
//
//            }
//        });
    }

//	//OBB
//    private void requestPermission(){
//        if (ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
//            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.READ_EXTERNAL_STORAGE)){
//                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 0);
//            }else {
//                ActivityCompat.requestPermissions(this,new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 0);
//            }
//        }
//    }
//
//    @Override
//    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
//        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
//        switch (requestCode){
//            case 0:
//            {
//                if (grantResults.length >0 && grantResults[0] == PackageManager.PERMISSION_GRANTED){
//                    Log.i(TAG,"onRequestPermissionsResult granted");
//                    Cocos2dxActivity.instance.init();
//                    Cocos2dxHelper.init(Cocos2dxActivity.getContext(),Cocos2dxActivity.instance);
//                }else {
//                    requestPermission();
//                    Log.i(TAG,"onRequestPermissionsResult denied");
//                }
//            }
//            break;
//        }
//    }

    /**
     * 去应用市场评分
     */
//Review
    public void goToMarket() {
//        if (!isMarketInstalled(this)) {
//            Toast.makeText(this, "There isn't any app market in your mobile.", Toast.LENGTH_SHORT).show();
//            return;
//        }
        String urlStr = "";
//        switch (_index)
//        {
        urlStr = "https://play.google.com/store/apps/details?id=dr.dinosaur.games.kids.free";
//                break;
//        }
        try {
//            Uri uri = Uri.parse("market://details?id="+getPackageName());
//            Uri uri = Uri.parse("https://play.google.com/store/apps/details?id=fun.wordgames.search.offline.stacks.block");
            Uri uri = Uri.parse(urlStr);//游戏链接
            Intent intent = new Intent(Intent.ACTION_VIEW,uri);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            if (intent.resolveActivity(this.getPackageManager()) != null) {
                setMixpanelTrack("Review Dialog Clicked","");
                startActivity(intent);
//                SendRateCallback();
            }
        } catch (Exception e) {
            // 也可以调到某个网页应用市场
            Toast.makeText(this, "There isn't any app market in your mobile.", Toast.LENGTH_SHORT).show();
        }
    }
    //    public void SendRateCallback(){
//        UnityPlayer.UnitySendMessage("Manager","RateCallBack","");
//    }
    Runnable showReviewDialogThread = new Runnable() {
        @Override
        public void run() {
            showReviewDialog();
        }
    };
    public void showReviewDialog()
    {
//        Toast.makeText(this, _str, Toast.LENGTH_SHORT).show();
        final AlertDialog.Builder reviewDialog = new AlertDialog.Builder(this);
        reviewDialog.setTitle(getString(R.string.review_title));
        reviewDialog.setIcon(R.mipmap.icon);
        reviewDialog.setMessage(getString(R.string.review_message));
        reviewDialog.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                goToMarket();
                dialogInterface.dismiss();
            }
        });
        reviewDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                dialogInterface.dismiss();
            }
        });

        reviewDialog.show();
        setMixpanelTrack("Review Dialog Showen","");

    }

    public void ShowReview(){
        handler.post(showReviewDialogThread);
    }

    //Review


//    //Mixpanel
//    public void connectMixpanel(){
//        String mixpanelToken = "f58314fb5fa470902ccc7151a8495d40";
//
//        mixpanelInstance = MixpanelAPI.getInstance(joylandInstance,mixpanelToken);
//    }

    //埋点
    public void setMixpanelTrack(String _eventStr,String _eventJSON)
    {   //String转JSONObject
//        JSONObject eventJSON;
//        try {
//            if (mixpanelInstance != null)
//            {
//                if (_eventJSON.contentEquals(""))
//                {
//                    mixpanelInstance.track(_eventStr);
//                }else {
//
//                    eventJSON = new JSONObject(_eventJSON);
//
//
//                    mixpanelInstance.track(_eventStr, eventJSON);
//                }
//            }
//
//        } catch (JSONException e) {
//            e.printStackTrace();
//        }
    }

    public void setMixpanelTimeEvent(String _eventStr)
    {
//        if (mixpanelInstance != null)
//        {
//            mixpanelInstance.timeEvent(_eventStr);
//        }
    }

    public void createIAPManager(){



        mIAPManager = new IAPManager(joylandInstance,base64EncodedPublicKey);

        connectToIAB();
    }

    public void connectToIAB(){
//        JoyPreschool.onIAPCallback(false);
//        billingClientStateListener = null;
        billingClientStateListener = new BillingClientStateListener() {
            @Override
            public void onBillingSetupFinished(BillingResult billingResult) {
                if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK){

                    queryPurchaseStatus();
                    queryInAPPOrScripSkuDetails();
                }else if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.BILLING_UNAVAILABLE){

                    String errorStr = billingResult.getDebugMessage();
                    setMixpanelTrack(errorStr,"");
                    Toast.makeText(JoyPreschool.this,errorStr,Toast.LENGTH_SHORT).show();

                }else {
                    String errorStr = billingResult.getDebugMessage();
                    int errorCode = billingResult.getResponseCode();
                    Toast.makeText(JoyPreschool.this,errorStr,Toast.LENGTH_SHORT).show();
                    if (connectFailCount < 3){
                        if (mIAPManager != null){
                            mIAPManager.connectToIAP(billingClientStateListener);
                        }
//                        new Handler().postDelayed(new Runnable() {
//                            @Override
//                            public void run() {
//                                if (mIAPManager != null){
//                                    mIAPManager.connectToIAP(billingClientStateListener);
//                                }
//                            }
//                        },60000);
                        connectFailCount++;
                    }else {

                    }
                }

            }

            @Override
            public void onBillingServiceDisconnected() {

                setMixpanelTrack("Lian Jie Google Play Shi Bai","");
                Toast.makeText(JoyPreschool.this,"Connect failed.Please try to restart connect Google Play.",Toast.LENGTH_SHORT).show();

                connectErrorCount++;
                if (mIAPManager != null){
                    mIAPManager.connectToIAP(billingClientStateListener);
                }
//                new Handler().postDelayed(new Runnable() {
//                    @Override
//                    public void run() {
//                        if (mIAPManager != null){
//                            mIAPManager.connectToIAP(billingClientStateListener);
//                        }
//                    }
//                },60000);

            }
        };
        if (mIAPManager != null){
            mIAPManager.startConnectIAPService(this,this,billingClientStateListener);
//            checkIsServicesWork.post(checkServicesRunnable);
        }
    }

    public void queryPurchaseStatus(){

        if (mIAPManager != null){
            if (!mIAPManager.isIAPConnecting()){
                if (mIAPManager != null){
                    mIAPManager.connectToIAP(billingClientStateListener);
                }
//                new Handler().postDelayed(new Runnable() {
//                    @Override
//                    public void run() {
//                        if (mIAPManager != null){
//                            mIAPManager.connectToIAP(billingClientStateListener);
//                        }
//                    }
//                },60000);
            }else {


//                List<Purchase> inAppPurchaseList = mIAPManager.queryPurchaseList(BillingClient.SkuType.INAPP);
//                if (inAppPurchaseList != null){
//                    for (Purchase inAppPurchase : inAppPurchaseList){
//                        if (inAppPurchase != null && (inAppPurchase.getSku().equals(IAPManager.ALL_LIFETIME_PRODUCT) || inAppPurchase.getSku().equals(IAPManager.FLASH_SALE_PRODUCT))){
////                        if (inAppPurchase != null && (IAPManager.ALL_LIFETIME_PRODUCT.equals(inAppPurchase.getSkus().get(0)) || IAPManager.FLASH_SALE_PRODUCT.equals(inAppPurchase.getSkus().get(1)))){
//
//                            if (!inAppPurchase.isAcknowledged()){
//                                mIAPManager.handlePurchase(inAppPurchase,acknowledgePurchaseResponseListener);
//                            }
//                            JoyPreschool.onIAPCallback(true);
//                            JoyPreschool.onIAPChangeScene();
//                        }else {
//                            JoyPreschool.onIAPCallback(false);
//                        }
//                    }
//                }

                mIAPManager.queryPurchaseList(BillingClient.SkuType.INAPP, new PurchasesResponseListener() {
                    @Override
                    public void onQueryPurchasesResponse(@NonNull BillingResult billingResult, @NonNull List<Purchase> list) {
                        List<Purchase> inAppPurchaseList = list;
                        if (inAppPurchaseList != null){
                            for (Purchase inAppPurchase : inAppPurchaseList){
//                  5      if (inAppPurchase != null && (inAppPurchase.getSku().equals(IAPManager.ALL_LIFETIME_PRODUCT) || inAppPurchase.getSku().equals(IAPManager.FLASH_SALE_PRODUCT))){
                                if (inAppPurchase != null && (IAPManager.ALL_LIFETIME_PRODUCT.equals(inAppPurchase.getSkus().get(0)))){

                                    if (!inAppPurchase.isAcknowledged()){
                                        mIAPManager.handlePurchase(inAppPurchase,acknowledgePurchaseResponseListener);
                                    }
                                    JoyPreschool.onIAPLifetimeCallback(true);
//                                    JoyPreschool.onIAPChangeScene();
//                                    new Handler().postDelayed(new Runnable() {
//                                        @Override
//                                        public void run() {
//                                            JoyPreschool.onIAPChangeScene();
//                                        }
//                                    },2000);

//                                    new Thread(new Runnable() {
//                                        @Override
//                                        public void run() {
//
//                                            try {
//                                                Thread.sleep(2000); // 休眠1秒
//                                            } catch (InterruptedException e) {
//                                                e.printStackTrace();
//                                            }
//                                            JoyPreschool.onIAPChangeScene();
//                                            /**
//                                             * 延时执行的代码
//                                             */
//
//                                        }
//                                    }).start();
                                }else {
                                    JoyPreschool.onIAPLifetimeCallback(false);
                                }
                            }
                        }
                    }
                });


//                List<Purchase> scriptionPurchaseList = mIAPManager.queryPurchaseList(BillingClient.SkuType.SUBS);
//                if (scriptionPurchaseList != null){
//                    for (Purchase scriptionPurchase : scriptionPurchaseList){
//                        if (scriptionPurchase != null && (scriptionPurchase.getSku().equals(IAPManager.SUB_PRIME_PRODUCT) || scriptionPurchase.getSku().equals(IAPManager.SUB_MEMBER_PRODUCT) || scriptionPurchase.getSku().equals(IAPManager.SUB_YEARLY_PRODUCT) || scriptionPurchase.getSku().equals(IAPManager.SUB_MONTHLY_PRODUCT)) && scriptionPurchase.isAutoRenewing()){
//                            JoyPreschool.onIAPCallback(true);
//                            JoyPreschool.onIAPChangeScene();
//                        }else {
//                            JoyPreschool.onIAPCallback(false);
//                        }
//                    }
//                }
//                mIAPManager.queryPurchaseList(BillingClient.SkuType.SUBS, new PurchasesResponseListener() {
//                    @Override
//                    public void onQueryPurchasesResponse(@NonNull BillingResult billingResult, @NonNull List<Purchase> list) {
//                        List<Purchase> scriptionPurchaseList = list;
//                        if (scriptionPurchaseList != null){
//                            for (Purchase scriptionPurchase : scriptionPurchaseList){
//                                if (scriptionPurchase != null && (IAPManager.SUB_PRIME_PRODUCT.equals(scriptionPurchase.getSkus().get(0)) || IAPManager.SUB_MEMBER_PRODUCT.equals(scriptionPurchase.getSkus().get(0)) || IAPManager.SUB_YEARLY_PRODUCT.equals(scriptionPurchase.getSkus().get(0)) || IAPManager.SUB_MONTHLY_PRODUCT.equals(scriptionPurchase.getSkus().get(0))) && scriptionPurchase.isAutoRenewing()){
//                                    JoyPreschool.onIAPGetCoins(0);
//                                    JoyPreschool.onIAPCallback(true);
//                                    JoyPreschool.onIAPChangeScene();
//                                }else {
//                                    JoyPreschool.onIAPCallback(false);
//                                }
//                            }
//                            JoyPreschool.finishLoadedItemCallback(10);
//                        }
//                    }
//                });

//                List<Purchase> scriptionPurchaseList = mIAPManager.queryPurchaseList(BillingClient.SkuType.SUBS);
//                if (scriptionPurchaseList != null){
//                    for (Purchase scriptionPurchase : scriptionPurchaseList){
//                        if (scriptionPurchase != null && (IAPManager.SUB_PRIME_PRODUCT.equals(scriptionPurchase.getSkus().get(0)) || IAPManager.SUB_MEMBER_PRODUCT.equals(scriptionPurchase.getSkus().get(0)) || IAPManager.SUB_YEARLY_PRODUCT.equals(scriptionPurchase.getSkus().get(0)) || IAPManager.SUB_MONTHLY_PRODUCT.equals(scriptionPurchase.getSkus().get(0))) && scriptionPurchase.isAutoRenewing()){
//                            JoyPreschool.onIAPCallback(true);
//                            JoyPreschool.onIAPChangeScene();
//                        }else {
//                            JoyPreschool.onIAPCallback(false);
//                        }
//                    }
//                }
            }
        }
    }

    public void queryInAPPOrScripSkuDetails(){
        if (mIAPManager != null){
//            if (!mIAPManager.isIAPConnecting()){
//                new Handler().postDelayed(new Runnable() {
//                    @Override
//                    public void run() {
//                        if (mIAPManager != null){
//                            mIAPManager.connectToIAP(billingClientStateListener);
//                        }
//                    }
//                },60000);
//            }else {
            List<String> skuList = new ArrayList<>();
//                skuList.add(IAPManager.NO_ADS_PRODUCT);
//                skuList.add(IAPManager.SUB_PRIME_PRODUCT);
//                skuList.add(IAPManager.SUB_MEMBER_PRODUCT);
            List<String> subscripList = new ArrayList<>();

            skuList.add(IAPManager.ALL_LIFETIME_PRODUCT);


            if (skuDetailsResponseListener != null) {
                skuDetailsResponseListener = null;
            }
//                skuDetailsResponseListener = new SkuDetailsResponseListener() {
//                    @Override
//                    public void onSkuDetailsResponse(BillingResult billingResult, List<SkuDetails> skuDetailsList) {
//                        if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK && skuDetailsList != null) {
//                            for (SkuDetails skuDetails : skuDetailsList) {
//                                if (skuDetails != null) {
//                                    if (skuDetails.getSku().equals(IAPManager.ALL_LIFETIME_PRODUCT)) {
//                                        allLifetimeSkuDetails = skuDetails;
//                                    } else if (skuDetails.getSku().equals(IAPManager.FLASH_SALE_PRODUCT)) {
//                                        flashSaleSkuDetails = skuDetails;
//                                    }
//                                    else if (skuDetails.getSku().equals(IAPManager.SUB_YEARLY_PRODUCT)) {
//                                        yearlySkuDetails = skuDetails;
//                                    } else if (skuDetails.getSku().equals(IAPManager.SUB_MONTHLY_PRODUCT)) {
//                                        monthlySkuDetails = skuDetails;
//                                    }
//                                }
//                            }
//                        }else {
//                            String debugMsgStr = billingResult.getDebugMessage();
////                            Toast.makeText(JoyPreschool.this,debugMsgStr,Toast.LENGTH_SHORT).show();
//                            setMixpanelTrack(debugMsgStr,"");
//                        }
//                        JoyPreschool.finishLoadedItemCallback(10);
//                    }
//                };

            skuDetailsResponseListener = new ProductDetailsResponseListener() {
                @Override
                public void onProductDetailsResponse(@NonNull BillingResult billingResult, @NonNull List<ProductDetails> list) {
                    if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK && list != null) {
                        for (ProductDetails skuDetails : list) {
                            if (skuDetails != null) {
                                if (skuDetails.getProductId().equals(IAPManager.ALL_LIFETIME_PRODUCT)) {
                                    allLifetimeSkuDetails = skuDetails;
                                }
                            }
                        }
                    }else {
                        String debugMsgStr = billingResult.getDebugMessage();
//                            Toast.makeText(JoyPreschool.this,debugMsgStr,Toast.LENGTH_SHORT).show();
                        setMixpanelTrack(debugMsgStr,"");
                    }
                  //  JoyPreschool.finishLoadedItemCallback(10);
                }
            };

            mIAPManager.querySkuDetails(skuList, BillingClient.ProductType.INAPP, skuDetailsResponseListener);
            mIAPManager.querySkuDetails(subscripList, BillingClient.ProductType.SUBS, skuDetailsResponseListener);


//            }
        }
    }

    public void goToBuy(int _buyIndex){
//        int buyIndex = (int)(Math.random()*100);
//        buyIndex = buyIndex%2;

        switch (_buyIndex){
            case 0:
            {
                if (allLifetimeSkuDetails != null && mIAPManager != null){
                    setMixpanelTrack("Show NoAds IAP","");
                    mIAPManager.lauchFlowToIAP(joylandInstance,allLifetimeSkuDetails);
                }else if (allLifetimeSkuDetails == null && mIAPManager != null){
                    setMixpanelTrack("NoAds IAP is NULL","");
                    Toast.makeText(JoyPreschool.this,"Connect failed.Please try to restart connect Google Play.",Toast.LENGTH_SHORT).show();
                    if (mIAPManager != null){
                        queryInAPPOrScripSkuDetails();
                    }
                }
            }
            break;
            case 1:
            {
                if (flashSaleSkuDetails != null && mIAPManager != null){
                    setMixpanelTrack("Show Prime IAP","");
                    mIAPManager.lauchFlowToIAP(joylandInstance,flashSaleSkuDetails);
                }else if (flashSaleSkuDetails == null && mIAPManager != null){
                    setMixpanelTrack("Prime IAP is NULL","");
                    Toast.makeText(JoyPreschool.this,"Connect failed.Please try to restart connect Google Play.",Toast.LENGTH_SHORT).show();
                    if (mIAPManager != null){
                        queryInAPPOrScripSkuDetails();
                    }
                }
            }
            break;
            case 2:
            {
                if (yearlySkuDetails != null && mIAPManager != null){
                    setMixpanelTrack("Show Member IAP","");
                    mIAPManager.lauchFlowToIAP(joylandInstance,yearlySkuDetails);
                }else if (yearlySkuDetails == null && mIAPManager != null){
                    setMixpanelTrack("Member IAP is NULL","");
                    Toast.makeText(JoyPreschool.this,"Connect failed.Please try to restart connect Google Play.",Toast.LENGTH_SHORT).show();
                    if (mIAPManager != null){
                        queryInAPPOrScripSkuDetails();
                    }
                }
            }
            break;
            case 3:
            {
                if (monthlySkuDetails != null && mIAPManager != null){
                    setMixpanelTrack("Show Member IAP","");
                    mIAPManager.lauchFlowToIAP(joylandInstance,monthlySkuDetails);
                }else if (monthlySkuDetails == null && mIAPManager != null){
                    setMixpanelTrack("Member IAP is NULL","");
                    Toast.makeText(JoyPreschool.this,"Connect failed.Please try to restart connect Google Play.",Toast.LENGTH_SHORT).show();
                    if (mIAPManager != null){
                        queryInAPPOrScripSkuDetails();
                    }
                }
            }
            break;
            default:
                break;
        }


    }
    Runnable onBuyProductThread = new Runnable() {
        @Override
        public void run() {
            goToBuy(0);
        }
    };

    public void onBuyProduct(int _buyIndex){
//        mBuyIndex = _buyIndex;
        handler.post(onBuyProductThread);
    }

    public AcknowledgePurchaseResponseListener acknowledgePurchaseResponseListener = new AcknowledgePurchaseResponseListener() {
        @Override
        public void onAcknowledgePurchaseResponse(BillingResult billingResult) {
            if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK)
            {
                Toast.makeText(JoyPreschool.this,"Purchase is confirmed.",Toast.LENGTH_SHORT).show();
            }
        }
    };

    @Override
//    public void onPurchasesUpdated(BillingResult billingResult, @Nullable List<Purchase> purchases) {
    public void onPurchasesUpdated(BillingResult billingResult, List<Purchase> purchases) {
        if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK && purchases != null){
            Toast.makeText(JoyPreschool.this,"Thank you for purchase",Toast.LENGTH_SHORT).show();
            //replace Scenen or get Product
            //Set UnlockAll=true;
            for (Purchase purchase : purchases){
//                switch (purchase.getSku()){
                setMixpanelTrack("All Life Time Gou Mai Cheng Gong","");
                JoyPreschool.onIAPLifetimeCallback(true);
//                switch (purchase.getSkus().get(0)){
////                    case IAPManager.NO_ADS_PRODUCT:
////                    {
////                        setMixpanelTrack("NoAds IAP Gou Mai Cheng Gong","");
////                    }
////                    break;
//                    case IAPManager.SUB_PRIME_PRODUCT:
//                    {
//                        setMixpanelTrack("Prime IAP Gou Mai Cheng Gong","");
//                    }
//                    break;
//                    case IAPManager.SUB_MEMBER_PRODUCT:
//                    {
//                        setMixpanelTrack("Member IAP Gou Mai Cheng Gong","");
//                    }
//                    break;
//                    case IAPManager.ALL_LIFETIME_PRODUCT:
//                    {
//                        setMixpanelTrack("All Life Time Gou Mai Cheng Gong","");
//                        JoyPreschool.onIAPLifetimeCallback(true);
//                    }
//                    break;
//                    case IAPManager.FLASH_SALE_PRODUCT:
//                    {
//                        setMixpanelTrack("Flash IAP Gou Mai Cheng Gong","");
//                        JoyPreschool.onIAPLifetimeCallback(true);
//                    }
//                    break;
//                    case IAPManager.SUB_YEARLY_PRODUCT:
//                    {
//                        setMixpanelTrack("Yearly IAP Gou Mai Cheng Gong","");
//                        JoyPreschool.onIAPCallback(true);
//                    }
//                    break;
//                    case IAPManager.SUB_MONTHLY_PRODUCT:
//                    {
//                        setMixpanelTrack("Monthly IAP Gou Mai Cheng Gong","");
//                        JoyPreschool.onIAPCallback(true);
//                    }
//                    break;
//                    default:
//                        break;
//                }
                JoyPreschool.onIAPChangeScene();
                mIAPManager.handlePurchase(purchase,acknowledgePurchaseResponseListener);
//                handlePurchase(purchase);
            }
        }else if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.USER_CANCELED){
            Toast.makeText(JoyPreschool.this,"Purchase was canceled",Toast.LENGTH_SHORT).show();
        }else if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.ITEM_ALREADY_OWNED){
            Toast.makeText(JoyPreschool.this,"You have purchased",Toast.LENGTH_SHORT).show();
            JoyPreschool.onIAPLifetimeCallback(true);
            JoyPreschool.onIAPChangeScene();
        }else if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.DEVELOPER_ERROR){
            Toast.makeText(JoyPreschool.this,billingResult.getDebugMessage(),Toast.LENGTH_SHORT).show();
        }else {
            Toast.makeText(JoyPreschool.this,"Unknown error",Toast.LENGTH_SHORT).show();
        }
    }

//    //购买完毕
//    @Override
//    public void onPurchasesUpdated(BillingResult billingResult, @Nullable List<Purchase> purchases) {
////        if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK && purchases != null){
////            Toast.makeText(JoyPreschool.this,"Purchace is ok",Toast.LENGTH_SHORT).show();
//////            JoyPreschool.onIAPCallback(true);
////            for (Purchase purchase : purchases){
////                handlePurchase(purchase);
////            }
////        }else{
////            Toast.makeText(JoyPreschool.this,"Purchace is not ok",Toast.LENGTH_SHORT).show();
////        }
//    }
//
//    //获取购买列表
//    public List<Purchase> queryPurchaseList(String _skuType){
////        if (billingClient != null){
////            Purchase.PurchasesResult purchasesResult = billingClient.queryPurchases(_skuType);
////            if (purchasesResult != null){
////                List<Purchase> purchaseList = purchasesResult.getPurchasesList();
////                return purchaseList;
////            }
////        }
//        return null;
//    }

//    //付费状态
//    public void queryPurchaseStatus(){
//
////            List<Purchase> inAppPurchaseList = queryPurchaseList(BillingClient.SkuType.INAPP);
////            if (inAppPurchaseList != null){
////                for (Purchase inAppPurchase : inAppPurchaseList){
////                    if (inAppPurchase != null && (inAppPurchase.getSku().equals("unlocklifetime.abc.english"))){
////                        if (!inAppPurchase.isAcknowledged()){
////                           handlePurchase(inAppPurchase);
////                        }
//////                        JoyPreschool.onIAPCallback(true);
////                    }else {
//////                        JoyPreschool.onIAPCallback(false);
////                    }
////                }
////            }
////
//////            List<Purchase> scriptionPurchaseList = queryPurchaseList(BillingClient.SkuType.SUBS);
//////            if (scriptionPurchaseList != null){
//////                for (Purchase scriptionPurchase : scriptionPurchaseList){
//////                    if (scriptionPurchase != null && (scriptionPurchase.getSku().equals("monthly.german") || scriptionPurchase.getSku().equals("yearly.german") && scriptionPurchase.isAutoRenewing())){
//////                        JoyPreschool.onIAPCallback(true);
//////                    }else {
//////                        JoyPreschool.onIAPCallback(false);
//////                    }
//////                }
//////            }
//    }
//
//    //非消耗型 查询商品详情
//    public void querySkuDetails(){
////        List<String> skuList = new ArrayList<>();
////        skuList.add("unlocklifetime.abc.english");  //非消耗型产品ID
////        SkuDetailsParams.Builder skuParams = SkuDetailsParams.newBuilder();
////        skuParams.setSkusList(skuList).setType(BillingClient.SkuType.INAPP);
////        billingClient.querySkuDetailsAsync(skuParams.build(), new SkuDetailsResponseListener() {
////            @Override
////            public void onSkuDetailsResponse(BillingResult billingResult, List<SkuDetails> skuDetailsList) {
////                if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK && skuDetailsList != null){
////                    for (SkuDetails skuDetails : skuDetailsList){
////                            if (skuDetails.getSku().equals("unlocklifetime.abc.english")){
////                                noAdsSkuDetails =skuDetails;
////                            }
////                    }
////                }
////            }
////        });
//    }
//
////    //订阅型 查询商品详情
////    public void queryScripSkuDetails(){
////        if (billingClient != null){
////            List<String> scripList = new ArrayList<>();
////            scripList.add("monthly.german");    //订阅商品ID
////            scripList.add("yearly.german");
////            SkuDetailsParams.Builder scripParams = SkuDetailsParams.newBuilder();
////            scripParams.setSkusList(scripList).setType(BillingClient.SkuType.SUBS);
////            billingClient.querySkuDetailsAsync(scripParams.build(), new SkuDetailsResponseListener() {
////                @Override
////                public void onSkuDetailsResponse(BillingResult billingResult, List<SkuDetails> skuDetailsList) {
////                    if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK && skuDetailsList != null){
////                        for (SkuDetails skuDetails : skuDetailsList){
////                            if (skuDetails != null && skuDetails.getSku().equals("monthly.german")){
////                                scripSkuDetails1 = skuDetails;
////                            }else if (skuDetails != null && skuDetails.getSku().equals("yearly.german")){
////                                scripSkuDetails2 = skuDetails;
////                            }
////                        }
////                    }
////                }
////            });
////        }
////    }
//
//  public AcknowledgePurchaseResponseListener acknowledgePurchaseResponseListener = new AcknowledgePurchaseResponseListener() {
//      @Override
//      public void onAcknowledgePurchaseResponse(BillingResult billingResult) {
//
//      }
//  };

    Runnable initAdsThread = new Runnable() {
        @Override
        public void run() {

            RequestConfiguration requestConfiguration = MobileAds.getRequestConfiguration().toBuilder().setTagForChildDirectedTreatment(TAG_FOR_CHILD_DIRECTED_TREATMENT_TRUE).setTagForUnderAgeOfConsent(TAG_FOR_UNDER_AGE_OF_CONSENT_TRUE).setMaxAdContentRating(MAX_AD_CONTENT_RATING_G).build();
            MobileAds.setRequestConfiguration(requestConfiguration);
            MobileAds.initialize(joylandInstance, new OnInitializationCompleteListener() {         //this  当前方法的类； Listener 回调函数
                @Override           //重写
                public void onInitializationComplete(InitializationStatus initializationStatus) {
//                    createAndLoadBannerAds();
//                    createAndLoadInterstitialAds();
                    createAdManager();
                    createIAPManager();
//                createAndLoadRewardedAds();

                }
            });
        }
    };

    public void initAds(){
        handler.post(initAdsThread);
    }

//    Runnable noAdsThread = new Runnable() {
//        @Override
//        public void run() {
//            if (billingClient != null){
////                int select =(int)(Math.random()*100);
////                select = select%2;
//                if (mBuyIndex == 1){
//                    BillingFlowParams flowParams = BillingFlowParams.newBuilder().setSkuDetails(noAdsSkuDetails).build();  //非消耗型
//                    billingClient.launchBillingFlow(joylandInstance,flowParams);
//                }
////                else if (mBuyIndex == 4){
////                    BillingFlowParams flowParams = BillingFlowParams.newBuilder().setSkuDetails(noAdsSkuDetails2).build();  //非消耗型
////                    billingClient.launchBillingFlow(joylandInstance,flowParams);
////                }else if (mBuyIndex == 3){
////                    BillingFlowParams flowParams = BillingFlowParams.newBuilder().setSkuDetails(scripSkuDetails1).build();   //订阅型
////                    billingClient.launchBillingFlow(joylandInstance,flowParams);
////                }else if (mBuyIndex == 2){
////                    BillingFlowParams flowParams = BillingFlowParams.newBuilder().setSkuDetails(scripSkuDetails2).build();   //订阅型
////                    billingClient.launchBillingFlow(joylandInstance,flowParams);
////                }
//            }
//
//        }
//    };
//    public void buyProduct(int _buyIndex){
//        mBuyIndex = _buyIndex;
//       handler.post(noAdsThread);
//    }

//    public void handlePurchase(Purchase purchase){
//        if (purchase != null && purchase.getPurchaseState() == Purchase.PurchaseState.PURCHASED){
//            if (!purchase.isAcknowledged()){
//                AcknowledgePurchaseParams acknowledgePurchaseParams = AcknowledgePurchaseParams.newBuilder().setPurchaseToken(purchase.getPurchaseToken()).build();
//               billingClient.acknowledgePurchase(acknowledgePurchaseParams,acknowledgePurchaseResponseListener);
//            }
//        }
//    }
    /**
     * Attempts to connect to Tapjoy
     */
//    public static  native void chooseAllScene();        //场景切换

//    public static native void onIAPCallback(boolean _unlock);
//    public static native void getIAPInfo(boolean _isUnlock);
    public static native void onIAPLifetimeCallback(boolean _isUnlock);
    public static native void onIAPChangeScene();
//    public static native void beginToGame();
//    public static  native void chooseAllScene();        //场景切换

    //Banner广告
    public void createAndLoadBannerAds(){
//        bannerView = new AdView(this);
//        bannerView.setAdSize(AdSize.BANNER);
//        bannerView.setAdUnitId("ca-app-pub-1842167763606474/1064672645");
//        bannerView.setAdListener(new AdListener(){
//            @Override
//            public void onAdLoaded() {
//                super.onAdLoaded();
//            }
//
//            @Override
//            public void onAdFailedToLoad(int i) {
//                super.onAdFailedToLoad(i);
//            }
//
//            @Override
//            public void onAdClicked() {
//                super.onAdClicked();
//                setMixpanelTrack("BannerAds Clicked","");
//            }
//        });
//        loadBannerAds();
//
//        //将Banner设置为不可见
////        bannerView.setVisibility(View.INVISIBLE);
//
//        //把banner广告显示在游戏中
//        RelativeLayout relativeLayout = new RelativeLayout(joylandInstance);
//        Cocos2dxActivity.mFrameLayout.addView(relativeLayout);
//
//        RelativeLayout.LayoutParams bannerViewParams = new RelativeLayout.LayoutParams(640, RelativeLayout.LayoutParams.WRAP_CONTENT);
//        bannerViewParams.addRule(RelativeLayout.CENTER_HORIZONTAL);
//        relativeLayout.addView(bannerView,bannerViewParams);
    }

    public void loadBannerAds(){
//        if (bannerView != null){
//            AdRequest adRequest = new AdRequest.Builder().build();
//            bannerView.loadAd(adRequest);
//        }
    }
    //建立新线程展示广告
    Handler handler = new Handler();
    Runnable onShowBannerThread = new Runnable() {
        @Override
        public void run() {
//            if (bannerView != null){
//                bannerView.setVisibility(View.VISIBLE);
//            }

        }
    };
    public void onShowBannerAds(){
//        handler.post(onShowBannerThread);
    }
    //建立新线程隐藏广告
    Runnable noBannerThread = new Runnable() {
        @Override
        public void run() {
//            if (bannerView != null){
//                bannerView.setVisibility(View.INVISIBLE);
//            }

        }
    };
    public void noBannerAds(){
//        handler.post(noBannerThread);
    }

    public void createAdManager(){
        mAdManager = new AdManager(joylandInstance);

        if (mAdManager != null){
            mAdManager.initialMobileAds(AdManager.ADS_PLATFORM_APPLOVIN, null);
            mAdManager.initialMobileAds(AdManager.ADS_PLATFORM_ADMOB, new OnInitializationCompleteListener() {
                @Override
                public void onInitializationComplete(InitializationStatus initializationStatus) {
//                    JoyPreschool.finishLoadedItemCallback(10);
//                    mAdManager.createBannerAds(new AdListener(){
//                        @Override
//                        public void onAdLoaded() {
//                            super.onAdLoaded();
//                            if (mAdManager.mBannerView != null){
//                            if (_isShow){
//                                mAdManager.mBannerView.setVisibility(View.VISIBLE);
//                            }else {
//                                mAdManager.mBannerView.setVisibility(View.INVISIBLE);
//                            }
//
//                            }
//                        }
//
//                        @Override
//                        public void onAdFailedToLoad(LoadAdError loadAdError) {
//                            super.onAdFailedToLoad(loadAdError);
//                        }
//
//                        @Override
//                        public void onAdOpened() {
//                            super.onAdOpened();
//                        }
//
//                        @Override
//                        public void onAdClicked() {
//                            super.onAdClicked();
//                            setMixpanelTrack("BannerAds Clicked","");
//                        }
//                    });

                    mAdManager.createInterstitialAds(new AdListener(){
                        @Override
                        public void onAdLoaded() {
                            super.onAdLoaded();
                        }

                        @Override
                        public void onAdFailedToLoad(LoadAdError loadAdError) {
                            super.onAdFailedToLoad(loadAdError);
                        }

                        @Override
                        public void onAdOpened() {
                            super.onAdOpened();
                            setMixpanelTrack("Cha Ye Ads Show","");
                        }

                        @Override
                        public void onAdClicked() {
                            super.onAdClicked();
                            setMixpanelTrack("Cha Ye Ads Clicked","");
                        }

                        @Override
                        public void onAdClosed() {
                            super.onAdClosed();
//                            mAdManager.loadInterstitialAds();
                        }
                    });

//                    mAdManager.createAndLoadRewardAds();
//                    loadBannerAndShowInView();
                    mAdManager.loadInterstitialAds(new InterstitialAdLoadCallback(){
                        @Override
                        public void onAdLoaded(@NonNull InterstitialAd interstitialAd) {
                            mAdManager.mInterstitialAd = interstitialAd;
                            mAdManager.mInterstitialAd.setFullScreenContentCallback(new FullScreenContentCallback() {
                                @Override
                                public void onAdDismissedFullScreenContent() {
                                    super.onAdDismissedFullScreenContent();
                                }

                                @Override
                                public void onAdShowedFullScreenContent() {
                                    super.onAdShowedFullScreenContent();

                                    mAdManager.mInterstitialAd = null;
                                    if (mAdManager.mInterstitialLoadCallback != null){
                                        mAdManager.loadInterstitialAds(mAdManager.mInterstitialLoadCallback);
                                    }
                                }

                                @Override
                                public void onAdFailedToShowFullScreenContent(@NonNull AdError adError) {
                                    super.onAdFailedToShowFullScreenContent(adError);

                                    mAdManager.mInterstitialAd = null;
                                }
                            });
                        }

                        @Override
                        public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                            mAdManager.mInterstitialAd = null;
                        }



                    });
                }
            });
        }
    }

    Runnable onShowInterstitialThread = new Runnable() {
        @Override
        public void run() {
            if (mAdManager != null){
                if (mAdManager.mInterstitialAd != null)
                {
                    mAdManager.showInterstitialAds();
//                }else {
//                    mAdManager.showKidozInterstitialAds();
                }
            }
        }
    };

    public void onShowInterstitial(){
        handler.post(onShowInterstitialThread);
    }


//    //插页式广告
//    public void createAndLoadInterstitialAds(){
//        InterstitialAd = new InterstitialAd(this);
//        InterstitialAd.setAdUnitId("ca-app-pub-1842167763606474/9855599711");
//        loadInterstitialAds();
//
//    }
//
//    public void loadInterstitialAds(){
//        AdRequest adRequest = new AdRequest.Builder().build();
//        InterstitialAd.loadAd(adRequest);
//        InterstitialAd.setAdListener(new AdListener(){
//            public void onAdLoaded(){
//            }
//
//            @Override
//            public void onAdFailedToLoad(int i) {
//                super.onAdFailedToLoad(i);
//            }
//
//            @Override
//            public void onAdOpened() {
//                super.onAdOpened();
//                setMixpanelTrack("Cha Ye Ads Show","");
//            }
//
//            @Override
//            public void onAdClicked() {
//                super.onAdClicked();
//                setMixpanelTrack("Cha Ye Ads Clicked","");
//            }
//
//            @Override
//            public void onAdClosed() {
//                super.onAdClosed();             //super 集成父类
//                loadInterstitialAds();
//            }
//        });
//    }
//
//    //建立新线程展示广告
//    Runnable interstitialThread = new Runnable() {
//        @Override
//        public void run() {
//            if (InterstitialAd != null){
//                InterstitialAd.show();
//            }
//
//        }
//    };
//    public void showInterstitialAds(){
//        handler.post(interstitialThread);
//    }


    //激励视频
    public void createAndLoadRewardedAds(){
//         if (RewardedAds!=null){                                                                 //强制设置为空
//             RewardedAds = null;
//         }
//         RewardedAds = new RewardedAd(this, "ca-app-pub-1842167763606474/7493016755");
//         loadRewardedAds();
    }
//
//     public void loadRewardedAds(){
//         RewardedAdLoadCallback adLoadCallback = new RewardedAdLoadCallback() {
//             public void onRewardedAdLoaded() {
//                 // Ad successfully loaded.
//             }
//
//             @Override
//             public void onRewardedAdFailedToLoad(int i) {
//                 super.onRewardedAdFailedToLoad(i);
//
//             }
//         };
//         RewardedAds.loadAd(new AdRequest.Builder().build(), adLoadCallback);
//     }
//     //建立新线程展示广告
//     Runnable rewardThread = new Runnable() {
//         @Override
//         public void run() {
//             if (RewardedAds != null){
//                 if (RewardedAds.isLoaded()){
//                     RewardedAdCallback adCallback = new RewardedAdCallback() {
//                         @Override
//                         public void onRewardedAdOpened() {
//                             // Ad opened.
//                             setMixpanelTrack("Reward Ads Show","");
//                         }
//
//                         @Override
//                         public void onRewardedAdFailedToShow(int i) {
//                             super.onRewardedAdFailedToShow(i);
//                         }
//
//                         public void onUserEarnedReward(@NonNull RewardItem reward) {
//                             // User earned reward.
//                             isCanGetReward = true;
//                             setMixpanelTrack("Huo De Reward","");
//
//                         }
//
//                         @Override
//                         public void onRewardedAdClosed() {
//                             super.onRewardedAdClosed();
//                             if (isCanGetReward == true){
//                                 JoyPreschool.onRewardAdsCallBack();
//                                 isCanGetReward = false;
//                             }
//                             createAndLoadRewardedAds();
//
//                         }
//
//                     };
//                     RewardedAds.show(joylandInstance,adCallback);
//                 }else{
//                     createAndLoadRewardedAds();
//                 }
//
//             }
//
//         }
//     };
//     public void showRewardAds(){
//         handler.post(rewardThread);
//     }

    //激励视频

    public String getObbFileName() {
//        PackageInfo info = null;
//        try {
//            info = super.getPackageManager().getPackageInfo(super.getPackageName(), 0);
//            String fileName = "main." + info.versionCode + "." + getPackageName() + ".obb";
//
//            return fileName;
//        } catch (PackageManager.NameNotFoundException e) {
//            e.printStackTrace();
//        }
        return "";
    }
//    public String getVirtualObbFileFullpath(){
//        File sdcardDir = Environment.getExternalStorageDirectory();
//        String _path = getObbDir().getPath() + "/" + getObbFileName();
//        Log.e("===_path===", _path);
//        return _path;
//    }
//public String getVirtualObbFileFullpath(){
//    if (Environment.getExternalStorageState()
//            .equals(Environment.MEDIA_MOUNTED)) {
//        File sdcardDir = Environment.getExternalStorageDirectory();
//        String _path = getObbDir().getAbsolutePath() + "/" + getObbFileName();
////        String _path = sdcardDir+"/Android/obb/"+getPackageName()+"/"+ getObbFileName();
//        Log.e("===_path===", _path);
//        File f=new File(getObbDir().getAbsolutePath() + "/");
////          File f=new File(strFile);
//        if(!f.exists())
////          if(!f.canRead())
//        {
//            boolean isMkdir = f.mkdir();
//            if (isMkdir){
//                return _path;
//            }else {
//                return null;
//            }
////             return false;
//        }
//
//        return _path;
//    }else {
//        return null;
//    }
//}

    //跳转链接
    public void goToMarket(int _index){
        String urlStr = "";
        switch (_index){
            case 0:
                urlStr = "https://play.google.com/store/apps/details?id=word.fry.all";
                break;
            case 1:
                urlStr = "https://play.google.com/store/apps/details?id=fun.wordgames.search.offline.stacks.block";
                break;
            case 2:
                urlStr = "https://play.google.com/store/apps/details?id=shape.puzzle.games.toddlers.free";
                break;
            case 3:
                urlStr = "https://play.google.com/store/apps/details?id=free.firstwords.sightword.kids";
                break;
            case 4:
                urlStr = "https://play.google.com/store/apps/details?id=com.jpt.joyland&hl=en_US";
                break;
//            case 5:
////                urlStr = "https://sites.google.com/view/jeutschland/home";
//                break;
            default:
                break;
        }
        try {
            Uri uri = Uri.parse(urlStr);
            Intent intent = new Intent(Intent.ACTION_VIEW, uri);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            if (intent.resolveActivity(this.getPackageManager()) != null){
                startActivity(intent);
            }
        }catch (Exception e){
            // 也可以调到某个网页应用市场
            Toast.makeText(this, "There isn't any app market in your mobile.", Toast.LENGTH_SHORT).show();
        }
    }

    public static JoyPreschool rtnActivity(){
        return joylandInstance;
    }




    /**
     * Attempts to connect to Tapjoy
     */
//	private void connectToTapjoy() {
    // OPTIONAL: For custom startup flags.
//		Hashtable<String, Object> connectFlags = new Hashtable<String, Object>();
//		connectFlags.put(TapjoyConnectFlag.ENABLE_LOGGING, "true");
//
//		// If you are not using Tapjoy Managed currency, you would set your own user ID here.
//		//	connectFlags.put(TapjoyConnectFlag.USER_ID, "A_UNIQUE_USER_ID");
//
//		// Connect with the Tapjoy server.  Call this when the application first starts.
//		// REPLACE THE SDK KEY WITH YOUR TAPJOY SDK Key.
//		String tapjoySDKKey = "4lhV7gXxQdmpkaUocOUs7QECKlbcNDMs9nPawRyMYW8a-E56aGxtNxUUDwJs";
//
////		Tapjoy.setGcmSender("34027022155");
//
//		Tapjoy.setDebugEnabled(true);
//
//		// NOTE: This is the only step required if you're an advertiser.
//		Tapjoy.connect(this, tapjoySDKKey, connectFlags, new TJConnectListener() {
//			@Override
//			public void onConnectSuccess() {
//				Log.i(TAG, "Tapjoy sdk is success.");
//			}
//
//			@Override
//			public void onConnectFailure() {
//				Log.i(TAG, "Tapjoy sdk is failed.");
//			}
//		});
//	}

//


    // Listener that's called when we finish querying the items and subscriptions we own
//    IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
//        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
//            Log.d(TAG, "Query inventory finished.");
//
//            // Have we been disposed of in the meantime? If so, quit.
//            if (mHelper == null) return;
//
//            // Is it a failure?
//            if (result.isFailure()) {
//                complain("Failed to query inventory: " + result);
//                return;
//            }
//
////            if (inventory.hasPurchase(SKU_ANDROID_TEST_PURCHASE_GOOD)) {
////            	   mHelper.consumeAsync(inventory.getPurchase(SKU_ANDROID_TEST_PURCHASE_GOOD),null);
////            }
//
//            Log.d(TAG, "Query inventory was successful.");
//
//            /*
//             * Check for items we own. Notice that for each purchase, we check
//             * the developer payload to see if it's correct! See
//             * verifyDeveloperPayload().
//             */
//
//            // Do we have the premium upgrade?
//            Purchase premiumPurchase = inventory.getPurchase(SKU_PREMIUM);
//            mIsPremium = (premiumPurchase != null && verifyDeveloperPayload(premiumPurchase));
//            Log.d(TAG, "User is " + (mIsPremium ? "PREMIUM" : "NOT PREMIUM"));
//
//            // First find out which subscription is auto renewing
//            Purchase gasMonthly = inventory.getPurchase(SKU_INFINITE_GAS_MONTHLY);
//            Purchase gasYearly = inventory.getPurchase(SKU_INFINITE_GAS_YEARLY);
//            if (gasMonthly != null && gasMonthly.isAutoRenewing()) {
//                mInfiniteGasSku = SKU_INFINITE_GAS_MONTHLY;
//                mAutoRenewEnabled = true;
//            	JoyPreschool.getIAPInfo(true);
//            } else if (gasYearly != null && gasYearly.isAutoRenewing()) {
//                mInfiniteGasSku = SKU_INFINITE_GAS_YEARLY;
//                mAutoRenewEnabled = true;
//            	JoyPreschool.getIAPInfo(true);
//            } else {
//                mInfiniteGasSku = "";
//                mAutoRenewEnabled = false;
//            	JoyPreschool.getIAPInfo(false);
//            }
//
//            // The user is subscribed if either subscription exists, even if neither is auto
//            // renewing
//            mSubscribedToInfiniteGas = (gasMonthly != null && verifyDeveloperPayload(gasMonthly))
//                    || (gasYearly != null && verifyDeveloperPayload(gasYearly));
//            Log.d(TAG, "User " + (mSubscribedToInfiniteGas ? "HAS" : "DOES NOT HAVE")
//                    + " infinite gas subscription.");
//            if (mSubscribedToInfiniteGas) mTank = TANK_MAX;
//
//            // Check for gas delivery -- if we own gas, we should fill up the tank immediately
//            Purchase gasPurchase = inventory.getPurchase(SKU_GAS);
//            if (gasPurchase != null && verifyDeveloperPayload(gasPurchase)) {
//                Log.d(TAG, "We have gas. Consuming it.");
//                try {getObbFileName
//                    mHelper.consumeAsync(inventory.getPurchase(SKU_GAS), mConsumeFinishedListener);
//                } catch (IabAsyncInProgressException e) {
//                    complain("Error consuming gas. Another async operation in progress.");
//                }
//                return;
//            }
//
////            updateUi();
////            setWaitScreen(false);
//            Log.d(TAG, "Initial inventory query finished; enabling main UI.");
//        }
//    };

    /**
     * Setup for IAP SDK called from onCreate. Sets up {@link SampleIapManager}
     * to handle InAppPurchasing logic and {@link SamplePurchasingListener} for
     * listening to IAP API callbacks
     */
//    private void setupIAPOnCreate() {
//        sampleIapManager = new SampleIapManager(this);
//        final SamplePurchasingListener purchasingListener = new SamplePurchasingListener(sampleIapManager);
//        Log.d(TAG, "onCreate: registering PurchasingListener");
//        PurchasingService.registerListener(this.getApplicationContext(), purchasingListener);
//        Log.d(TAG, "IS_SANDBOX_MODE:" + PurchasingService.IS_SANDBOX_MODE);
//    }

    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // JoyPreschool should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return glSurfaceView;
    }

    public void hideNavigationBar(){
        if (Build.VERSION.SDK_INT > 11 && Build.VERSION.SDK_INT < 19){
            View view = getWindow().getDecorView();
            view.setSystemUiVisibility(View.GONE);
        }else if (Build.VERSION.SDK_INT >= 19){
            View decorView = getWindow().getDecorView();
            int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN;
            decorView.setSystemUiVisibility(uiOptions);
        }
    }
    /**
     * Call {@link PurchasingService#getProductData(Set)} to get the product
     * availability
     */
    @Override
    protected void onStart() {
        super.onStart();
//        Log.d(TAG, "onStart: call getProductData for skus: " + MySku.values());
//        final Set<String> productSkus = new HashSet<String>();
//        for (final MySku mySku : MySku.values()) {
//        	Log.d(TAG, "skus: " + mySku.getSku());
//            productSkus.add(mySku.getSku());
//        }
//        PurchasingService.getProductData(productSkus);

//        Tapjoy.onActivityStart(this);
    }
    /**
     * Calls {@link PurchasingService#getUserData()} to get current Amazon
     * user's data and {@link PurchasingService#getPurchaseUpdates(boolean)} to
     * get recent purchase updates
     */
    @Override
    protected void onResume() {
        super.onResume();
        hideNavigationBar();
//        sampleIapManager.activate();
//        Log.d(TAG, "onResume: call getUserData");
//        PurchasingService.getUserData();
//        Log.d(TAG, "onResume: getPurchaseUpdates");
//        PurchasingService.getPurchaseUpdates(false);

    }

    /**
     * Deactivate Sample IAP manager on main activity's Pause event
     */
    @Override
    protected void onPause() {
        super.onPause();
//        sampleIapManager.deactivate();
    }

    @Override
    protected void onStop() {
//      Tapjoy.onActivityStop(this);
        super.onStop();
    }

    // We're being destroyed. It's important to dispose of the helper here!
    @Override
    public void onDestroy() {
        super.onDestroy();

        // very important:
//        if (mBroadcastReceiver != null) {
//            unregisterReceiver(mBroadcastReceiver);
//        }

        // very important:
        Log.d(TAG, "Destroying helper.");
//        if (mHelper != null) {
//            mHelper.disposeWhenFinished();
//            mHelper = null;
//        }
    }

    /** Verifies the developer payload of a purchase. */
//    boolean verifyDeveloperPayload(Purchase p) {
//        String payload = p.getDeveloperPayload();
//
//        /*
//         * TODO: verify that the developer payload of the purchase is correct. It will be
//         * the same one that you sent when initiating the purchase.
//         *
//         * WARNING: Locally generating a random string when starting a purchase and
//         * verifying it here might seem like a good approach, but this will fail in the
//         * case where the user purchases an item on one device and then uses your app on
//         * a different device, because on the other device you will not have access to the
//         * random string you originally generated.
//         *
//         * So a good developer payload has these characteristics:
//         *
//         * 1. If two different users purchase an item, the payload is different between them,
//         *    so that one user's purchase can't be replayed to another user.
//         *
//         * 2. The payload must be such that you can verify it even when the app wasn't the
//         *    one who initiated the purchase flow (so that items purchased by the user on
//         *    one device work on other devices owned by the user).
//         *
//         * Using your own server to store and verify developer payloads across app
//         * installations is recommended.
//         */
//
//        return true;
//    }

//    public static void onBuySomething(int itemID){
    //do what you wanna
//    	RequestId requestId = null;
//    	Log.d(TAG, String.format("Sku===========%d", itemID));
//        switch (itemID) {
//            case 0:
//                requestId = PurchasingService.purchase(MySku.SUB_YEAR.getSku());
//                Log.d(TAG, "Sku===========year");
//                break;
//            case 1:
//                requestId = PurchasingService.purchase(MySku.SUB_MONTH.getSku());
//                Log.d(TAG, "Sku===========month");
//                break;
//            default:
//                break;
//        }
//
//        Log.d(TAG, "onBuyMagazineClick: requestId (" + requestId + ")");

//    }

    public void onBuySomething(int itemID){
        Log.d(TAG, "Buy gas button clicked.");

        if (mSubscribedToInfiniteGas) {
            complain("No need! You're subscribed to infinite gas. Isn't that awesome?");
            return;
        }

        if (mTank >= TANK_MAX) {
            complain("Your tank is full. Drive around a bit!");
            return;
        }

        // launch the gas purchase UI flow.
        // We will be notified of completion via mPurchaseFinishedListener
//        setWaitScreen(true);
        Log.d(TAG, "Launching purchase flow for gas.");

        /* TODO: for security, generate your payload here for verification. See the comments on
         *        verifyDeveloperPayload() for more info. Since this is a SAMPLE, we just use
         *        an empty string, but on a production app you should carefully generate this. */
        String payload = "";

//        try {
//            mHelper.launchPurchaseFlow(this, SKU_GAS, RC_REQUEST,
//                    mPurchaseFinishedListener, payload);
//        } catch (IabAsyncInProgressException e) {
//            complain("Error launching purchase flow. Another async operation in progress.");
////            setWaitScreen(false);
//        }
    }

    public void setBuyIndex(int _itemIndex){
        this._buySceneIndex = _itemIndex;
    }

    public void alertExit(){
//		AlertDialog alertDialog = new AlertDialog.Builder(this). 
//             setTitle("Exit Joyland"). 
//             setMessage("Are you sure?"). 
//             setIcon(R.drawable.icon). 
//             setPositiveButton("YES", new DialogInterface.OnClickListener() { 
//                  
//                 @Override 
//                 public void onClick(DialogInterface dialog, int which) { 
//                     // TODO Auto-generated method stub  
//                	 System.out.println("OK");
//                	 System.exit(0);
//                 } 
//             }). 
//             setNegativeButton("NO", new DialogInterface.OnClickListener() { 
//                  
//                 @Override 
//                 public void onClick(DialogInterface dialog, int which) { 
//                     // TODO Auto-generated method stub  
//                	 System.out.println("Cancel");
//                 } 
//             }). 
//             create(); 
//    	AlertDialog alertDialog = new AlertDialog.Builder(joylandInstance).setTitle("Exit Joyland").setMessage("Are your sure?").setIcon(R.drawable.icon).setPositiveButton("YES", new DialogInterface.OnClickListener() {
//			
//			@Override
//			public void onClick(DialogInterface arg0, int arg1) {
//				// TODO Auto-generated method stub
//				
//			}
//		}).setNegativeButton("NO", new DialogInterface.OnClickListener() {
//			
//			@Override
//			public void onClick(DialogInterface arg0, int arg1) {
//				// TODO Auto-generated method stub
//				
//			}
//		}).create();
//		alertDialog.show(); 
    }

    /**
     * Callback on failed purchase updates response
     * {@link PurchaseUpdatesRequestStatus#FAILED}
     *
     * @param requestId
     */
//    public void onPurchaseUpdatesResponseFailed(final String requestId) {
//        Log.d(TAG, "onPurchaseUpdatesResponseFailed: for requestId (" + requestId + ")");
//    }
    void complain(String message) {
        Log.e(TAG, "**** TrivialDrive Error: " + message);
//        alert("Error: " + message);
    }

    void alert(String message) {
        AlertDialog.Builder bld = new AlertDialog.Builder(this);
        bld.setMessage(message);
        bld.setNeutralButton("OK", null);
        Log.d(TAG, "Showing alert dialog: " + message);
        bld.create().show();
    }

    private static final String TAG = "SampleIAPSubscriptionsApp";
    private static final String DOWNLOADTAG = "DownladAssetsManager";

    // Called when consumption is complete
//    IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
//        public void onConsumeFinished(Purchase purchase, IabResult result) {
//            Log.d(TAG, "Consumption finished. Purchase: " + purchase + ", result: " + result);
//
//            // if we were disposed of in the meantime, quit.
//            if (mHelper == null) return;
//
//            // We know this is the "gas" sku because it's the only one we consume,
//            // so we don't check which sku was consumed. If you have more than one
//            // sku, you probably should check...
//            if (result.isSuccess()) {
//                // successfully consumed, so we apply the effects of the item in our
//                // game world's logic, which in our case means filling the gas tank a bit
//                Log.d(TAG, "Consumption successful. Provisioning.");
//                mTank = mTank == TANK_MAX ? TANK_MAX : mTank + 1;
////                saveData();
//                alert("You filled 1/4 tank. Your tank is now " + String.valueOf(mTank) + "/4 full!");
//            }
//            else {
//                complain("Error while consuming: " + result);
//            }
////            updateUi();
////            setWaitScreen(false);
//            Log.d(TAG, "End consumption flow.");
//        }
//    };
//
// // Callback for when a purchase is finished
//    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
//        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
//            Log.d(TAG, "Purchase finished: " + result + ", purchase: " + purchase);
//
//            // if we were disposed of in the meantime, quit.
//            if (mHelper == null) return;
//
//            if (result.isFailure()) {
//                complain("Error purchasing: " + result);
////                setWaitScreen(false);
//                return;
//            }
//            if (!verifyDeveloperPayload(purchase)) {
//                complain("Error purchasing. Authenticity verification failed.");
////                setWaitScreen(false);
//                return;
//            }
//
//            Log.d(TAG, "Purchase successful.");
//
//            if (purchase.getSku().equals(SKU_GAS)) {
//                // bought 1/4 tank of gas. So consume it.
//                Log.d(TAG, "Purchase is gas. Starting gas consumption.");
//                try {
//                    mHelper.consumeAsync(purchase, mConsumeFinishedListener);
//                } catch (IabAsyncInProgressException e) {
//                    complain("Error consuming gas. Another async operation in progress.");
////                    setWaitScreen(false);
//                    return;
//                }
//            }
//            else if (purchase.getSku().equals(SKU_PREMIUM)) {
//                // bought the premium upgrade!
//                Log.d(TAG, "Purchase is premium upgrade. Congratulating user.");
//                alert("Thank you for upgrading to premium!");
//                mIsPremium = true;
////                updateUi();
////                setWaitScreen(false);
//            }
//            else if (purchase.getSku().equals(SKU_INFINITE_GAS_MONTHLY)
//                    || purchase.getSku().equals(SKU_INFINITE_GAS_YEARLY)) {
//                // bought the infinite gas subscription
//                Log.d(TAG, "Infinite gas subscription purchased.");
//                alert("Thank you for subscribing to Joyland!");
//                mSubscribedToInfiniteGas = true;
//                mAutoRenewEnabled = purchase.isAutoRenewing();
//                mInfiniteGasSku = purchase.getSku();
//                mTank = TANK_MAX;
//                JoyPreschool.onIAPCallback(joylandInstance._buySceneIndex);
//
////                updateUi();
////                setWaitScreen(false);
//            }
//        }
//    };

    // "Subscribe to infinite gas" button clicked. Explain to user, then start purchase
    // flow for subscription.
//    public void onInfiniteGasButtonClicked(int itemID) {
//        if (!mHelper.subscriptionsSupported()) {
//            complain("Subscriptions not supported on your device yet. Sorry!");
//            return;
//        }
//
//        String requestId = null;
//
//        if (!mSubscribedToInfiniteGas || !mAutoRenewEnabled) {
//            // Both subscription options should be available
//        	switch (itemID) {
//        		case 0:
//        			requestId = SKU_INFINITE_GAS_YEARLY;
//        			Log.d(TAG, "Sku===========year");
//        			break;
//        		case 1:
//        			requestId = SKU_INFINITE_GAS_MONTHLY;
//        			Log.d(TAG, "Sku===========month");
//        			break;
//        		default:
//        			break;
//        	}
//        }
//        /* TODO: for security, generate your payload here for verification. See the comments on
//         *        verifyDeveloperPayload() for more info. Since this is a SAMPLE, we just use
//         *        an empty string, but on a production app you should carefully generate
//         *        this. */
//        String payload = "";
//
//        Log.d(TAG, "Launching purchase flow for gas subscription.");
//        try {
//            mHelper.launchSubscriptionPurchaseFlow(this, requestId, RC_REQUEST, mPurchaseFinishedListener, payload);
//        } catch (IabAsyncInProgressException e) {
//            complain("Error launching purchase flow. Another async operation in progress.");
////            setWaitScreen(false);
//        }
//
//    }

    public void testCocos2dxAssetsManager(int _percent){
        Log.e(DOWNLOADTAG,"downloading...."+_percent);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "onActivityResult(" + requestCode + "," + resultCode + "," + data);
//        if (mHelper == null) return;

        // Pass on the activity result to the helper for handling
//        if (!mHelper.handleActivityResult(requestCode, resultCode, data)) {
//            // not handled, so handle it ourselves (here's where you'd
//            // perform any handling of activity results not related to in-app
//            // billing...
//            super.onActivityResult(requestCode, resultCode, data);
//        }
//        else {
//            Log.d(TAG, "onActivityResult handled by IABUtil.");
//        }
    }

    /**
     * Set the magazine subscription button status on UI
     *
     * @param productAvailable
     * @param userSubscribed
     */
    public void setMagazineSubsAvail(final boolean productAvailable, final boolean userCanSubscribe) {
//        if (productAvailable) {
//            if (userCanSubscribe) {
//            	JoyPreschool.getIAPInfo(true);
//            } else {
//            	JoyPreschool.getIAPInfo(false);
//            }
//        } else {
//        	JoyPreschool.getIAPInfo(false);
//        }

    }
//
//    public static native void onIAPCallback(int select);


    static {
        System.loadLibrary("cocos2dcpp");
    }

//	@Override
//	public void receivedBroadcast() {
//		// TODO Auto-generated method stub
//		// Received a broadcast notification that the inventory of items has changed
//        Log.d(TAG, "Received broadcast notification. Querying inventory.");
////        try {
////            mHelper.queryInventoryAsync(mGotInventoryListener);
////        } catch (IabAsyncInProgressException e) {
////            complain("Error querying inventory. Another async operation in progress.");
////        }
//	}
}