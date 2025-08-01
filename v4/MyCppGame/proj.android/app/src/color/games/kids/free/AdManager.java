package color.games.kids.free;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

//import com.applovin.sdk.AppLovinSdk;
import com.google.ads.mediation.admob.AdMobAdapter;
import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.OnPaidEventListener;
import com.google.android.gms.ads.OnUserEarnedRewardListener;
import com.google.android.gms.ads.ResponseInfo;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.RequestConfiguration;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;
import com.google.android.gms.ads.rewarded.OnAdMetadataChangedListener;
import com.google.android.gms.ads.rewarded.RewardItem;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;
import com.google.android.gms.ads.rewarded.ServerSideVerificationOptions;
//import com.kidoz.sdk.api.KidozInterstitial;
//import com.kidoz.sdk.api.KidozSDK;
//import com.kidoz.sdk.api.interfaces.SDKEventListener;
//import com.kidoz.sdk.api.ui_views.interstitial.BaseInterstitial;
//import com.kidoz.sdk.api.ui_views.kidoz_banner.KidozBannerListener;
//import com.kidoz.sdk.api.ui_views.new_kidoz_banner.BANNER_POSITION;
//import com.kidoz.sdk.api.ui_views.new_kidoz_banner.KidozBannerView;

import java.util.Arrays;
import java.util.List;

import static com.google.android.gms.ads.RequestConfiguration.MAX_AD_CONTENT_RATING_G;
import static com.google.android.gms.ads.RequestConfiguration.TAG_FOR_UNDER_AGE_OF_CONSENT_TRUE;
import static com.google.android.gms.ads.mediation.MediationAdConfiguration.TAG_FOR_CHILD_DIRECTED_TREATMENT_TRUE;

public class AdManager {
    public static final int ADS_PLATFORM_ADMOB = 0;
    public static final int ADS_PLATFORM_FACEBOOK = 1;
    public static final int ADS_PLATFORM_MOPUB = 2;
    public static final int ADS_PLATFORM_APPLOVIN = 3;
    public static final int ADS_PLATFORM_UNITYADS = 4;
    public static final int ADS_PLATFORM_VUNGLE = 5;
    public static final int ADS_PLATFORM_IRONSOURCE = 6;
    public static final int ADS_PLATFORM_INMOBI = 7;
    public static final int ADS_PLATFORM_TAPJOY = 8;
    public static final int ADS_PLATFORM_KIDOZ = 9;

    //Normal Ads
//    public static String BANNER_ADS_ID = "ca-app-pub-1842167763606474/1064672645";
    public static String INTERSTITIAL_ADS_ID = "ca-app-pub-1842167763606474/2793618797";
//    public static String REWARDED_ADS_ID = "ca-app-pub-1842167763606474/3688733262";
    //Test Ads
//    public static String BANNER_ADS_ID = "ca-app-pub-3940256099942544/6300978111";
//    public static String INTERSTITIAL_ADS_ID = "ca-app-pub-3940256099942544/8691691433";
//    public static String REWARDED_ADS_ID = "ca-app-pub-3940256099942544/5224354917";
    //Kidoz Ads Config
//    public static final String KIDOZ_PUBLISHERID = "14926";
//    public static final String KIDOZ_TOKEN = "MFP4Fu5IFp8Amkr8lt1Zs5VxqJWslszm";

    public Context mContext;

    //AdMob
    public AdView mBannerView;
    public InterstitialAd mInterstitialAd;
    public RewardedAd mRewardAd;
    //Kidoz Natvie Ads
//    KidozBannerView mKidozBannerView;
//    KidozInterstitial mKidozInterstitialAd;
//    KidozInterstitial mKidozRewardAd;

    public boolean haveClosedAds;

    public InterstitialAdLoadCallback mInterstitialLoadCallback;

    public AdManager(Context context){
        mContext = context;
    }

    public void initialMobileAds(int _adPlatformTag, OnInitializationCompleteListener initializationCompleteListener){
        switch (_adPlatformTag){
            case ADS_PLATFORM_ADMOB:
            {
                List<String> testDeviceIds = Arrays.asList("584744F9DFC0A137D77F670741518481");
                RequestConfiguration configuration =
                        new RequestConfiguration.Builder().setTestDeviceIds(testDeviceIds).build();
                MobileAds.setRequestConfiguration(configuration);
                RequestConfiguration requestConfiguration = MobileAds.getRequestConfiguration().toBuilder().setTagForChildDirectedTreatment(TAG_FOR_CHILD_DIRECTED_TREATMENT_TRUE).setTagForUnderAgeOfConsent(TAG_FOR_UNDER_AGE_OF_CONSENT_TRUE).setMaxAdContentRating(MAX_AD_CONTENT_RATING_G).build();
                MobileAds.setRequestConfiguration(requestConfiguration);
                MobileAds.initialize(mContext, initializationCompleteListener);
            }
            break;
            case ADS_PLATFORM_FACEBOOK:
            {

            }
            break;
            case ADS_PLATFORM_MOPUB:
            {

            }
            break;
//            case ADS_PLATFORM_APPLOVIN:
//            {
//                AppLovinSdk.initializeSdk(mContext);
//            }
//            break;
            case ADS_PLATFORM_UNITYADS:
            {

            }
            break;
            case ADS_PLATFORM_VUNGLE:
            {

            }
            break;
            case ADS_PLATFORM_IRONSOURCE:
            {

            }
            break;
            case ADS_PLATFORM_INMOBI:
            {

            }
            break;
            case ADS_PLATFORM_TAPJOY:
            {

            }
            break;
            case ADS_PLATFORM_KIDOZ:
            {

            }
            break;
            default:
                break;
        }
    }


//    public void initialKidozAds(SDKEventListener initializationCompleteListener){
//
//        KidozSDK.initialize(mContext,KIDOZ_PUBLISHERID,KIDOZ_TOKEN);
//        KidozSDK.setSDKListener(initializationCompleteListener);
//    }

    public void createBannerAds(AdListener listener){
//        mBannerView = new AdView(mContext);
//        mBannerView.setAdSize(AdSize.BANNER);
//        mBannerView.setAdUnitId(BANNER_ADS_ID);
//
//        mBannerView.setAdListener(listener);
    }


//    public void createKidozBannerAds(KidozBannerListener listener) {
//        mKidozBannerView = KidozSDK.getKidozBanner(JoyPreschool.joylandInstance);
//        mKidozBannerView.setBannerPosition(BANNER_POSITION.TOP_CENTER);
//
//        mKidozBannerView.setKidozBannerListener(listener);
//    }

    public void loadBannerAds(){
        if (mBannerView != null){

            Bundle adExtras = new Bundle();
            adExtras.putString("max_ad_content_rating", "G");

            AdRequest adRequest = new AdRequest.Builder().build();
            mBannerView.loadAd(adRequest);

        }
    }

//    public void loadKidozBannerAds(){
//        if (mKidozBannerView != null){
//            mKidozBannerView.load();
//        }
//    }

    public void showOrHideBannerAds(boolean _isShow){
        if (mBannerView != null){
            if (_isShow){
                mBannerView.setVisibility(View.VISIBLE);
            }else {
                mBannerView.setVisibility(View.INVISIBLE);
            }
        }
    }

    public void createInterstitialAds(AdListener listener){
//        mInterstitialAd = new InterstitialAd(mContext);
//        mInterstitialAd.setAdUnitId(INTERSTITIAL_ADS_ID);
//
//        mInterstitialAd.setAdListener(listener);

    }

//    public void createKidozInterstitialAds(BaseInterstitial.IOnInterstitialEventListener listener){
//        mKidozInterstitialAd = new KidozInterstitial(JoyPreschool.joylandInstance,KidozInterstitial.AD_TYPE.INTERSTITIAL);
//        mKidozInterstitialAd.setOnInterstitialEventListener(listener);
//    }

    public void loadInterstitialAds(InterstitialAdLoadCallback listener){
        if (listener != null){
            Bundle adExtras = new Bundle();
            adExtras.putString("max_ad_content_rating", "G");

            AdRequest adRequest = new AdRequest.Builder().build();
            mInterstitialLoadCallback = listener;
            InterstitialAd.load(mContext,INTERSTITIAL_ADS_ID,adRequest,mInterstitialLoadCallback);
            MobileAds.setAppMuted(true);

        }
    }

//    public void loadKidozInterstitialAds(){
//        if (mKidozInterstitialAd != null)
//        {
//            if (!mKidozInterstitialAd.isLoaded()){
//                mKidozInterstitialAd.loadAd();
//            }
//        }
//    }

    public void showInterstitialAds(){
        if (mInterstitialAd != null){
            mInterstitialAd.show(JoyPreschool.joylandInstance);
        }else if (mInterstitialLoadCallback != null){
            loadInterstitialAds(mInterstitialLoadCallback);
        }
    }


    public void createAndLoadRewardAds(){
        if (mRewardAd != null){
            mRewardAd = null;
        }
        haveClosedAds = false;
        mRewardAd = new RewardedAd() {
            @Override
            public void setServerSideVerificationOptions(@Nullable ServerSideVerificationOptions serverSideVerificationOptions) {

            }

            @Override
            public void setOnAdMetadataChangedListener(@Nullable OnAdMetadataChangedListener onAdMetadataChangedListener) {

            }

            @Nullable
            @Override
            public OnAdMetadataChangedListener getOnAdMetadataChangedListener() {
                return null;
            }

            @NonNull
            @Override
            public Bundle getAdMetadata() {
                return null;
            }

            @Override
            public void show(@NonNull Activity activity, @NonNull OnUserEarnedRewardListener onUserEarnedRewardListener) {

            }

            @NonNull
            @Override
            public RewardItem getRewardItem() {
                return null;
            }

            @NonNull
            @Override
            public ResponseInfo getResponseInfo() {
                return null;
            }

            @Override
            public void setOnPaidEventListener(@Nullable OnPaidEventListener onPaidEventListener) {

            }

            @Nullable
            @Override
            public OnPaidEventListener getOnPaidEventListener() {
                return null;
            }

            @Override
            public void setFullScreenContentCallback(@Nullable FullScreenContentCallback fullScreenContentCallback) {

            }

            @Nullable
            @Override
            public FullScreenContentCallback getFullScreenContentCallback() {
                return null;
            }

            @NonNull
            @Override
            public String getAdUnitId() {
                return null;
            }

            @Override
            public void setImmersiveMode(boolean b) {

            }
        };

        RewardedAdLoadCallback rewardedAdLoadCallback = new RewardedAdLoadCallback() {
            @Override
            public void onAdLoaded(@NonNull RewardedAd rewardedAd) {
                super.onAdLoaded(rewardedAd);
                mRewardAd = rewardedAd;
                mRewardAd.setFullScreenContentCallback(new FullScreenContentCallback() {
                    @Override
                    public void onAdShowedFullScreenContent() {
                        super.onAdShowedFullScreenContent();
                    }

                    @Override
                    public void onAdFailedToShowFullScreenContent(@NonNull AdError adError) {
                        super.onAdFailedToShowFullScreenContent(adError);
                    }

                    @Override
                    public void onAdDismissedFullScreenContent() {
                        super.onAdDismissedFullScreenContent();
                        onRewardedAdClosed();
                    }
                });
            }

            @Override
            public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                super.onAdFailedToLoad(loadAdError);


            }
        };

        if (mRewardAd != null && rewardedAdLoadCallback != null){
            Bundle adExtras = new Bundle();
            adExtras.putString("max_ad_content_rating", "G");

            AdRequest adRequest = new AdRequest.Builder().build();

//            mRewardAd.loadAd(adRequest,rewardedAdLoadCallback);
//            RewardedAd.load(mContext, REWARDED_ADS_ID, adRequest, rewardedAdLoadCallback);
        }
    }


    public void showRewardAds(Activity activity, OnUserEarnedRewardListener rewardedAdCallback){
        if (mRewardAd != null){
            mRewardAd.show(activity,rewardedAdCallback);
        }else {
            createAndLoadRewardAds();
        }
    }

    public void onRewardedAdClosed(){
        if (haveClosedAds){
            haveClosedAds = false;
//            cooking.games.kids.icecream.JoyPreschool.onRewardAdsCallback();
        }else {

        }
        createAndLoadRewardAds();
    }


}
