package color.games.kids.free;


import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

import com.android.billingclient.api.AcknowledgePurchaseParams;
import com.android.billingclient.api.AcknowledgePurchaseResponseListener;
import com.android.billingclient.api.BillingClient;
import com.android.billingclient.api.BillingClientStateListener;
import com.android.billingclient.api.BillingFlowParams;
import com.android.billingclient.api.BillingResult;
import com.android.billingclient.api.Purchase;
import com.android.billingclient.api.PurchasesResponseListener;
import com.android.billingclient.api.PurchasesUpdatedListener;
import com.android.billingclient.api.SkuDetails;
import com.android.billingclient.api.SkuDetailsParams;
import com.android.billingclient.api.SkuDetailsResponseListener;

import java.util.List;

public class IAPManager {

    public Context mContext;
    public String mSignatureBase64 = null;

//    public static final String NO_ADS_PRODUCT = "noads";
//    public static final String SUB_PRIME_PRODUCT = "prime";
//    public static final String SUB_MEMBER_PRODUCT = "member";

    public static final String ALL_LIFETIME_PRODUCT = "coloring.game.lifetime";
//    public static final String FLASH_SALE_PRODUCT = "flashsale";
//    public static final String SUB_YEARLY_PRODUCT = "dr.dino.yearly";
//    public static final String SUB_MONTHLY_PRODUCT = "dr.dino.monthly";

    public String productID;

    public BillingClient mBillingClient;

    public IAPManager(Context context, String base64PublicKey){
        mContext = context;
        mSignatureBase64 = base64PublicKey;
    }

    public void startConnectIAPService(Activity activity, PurchasesUpdatedListener listener, BillingClientStateListener clientStateListener){
        if (mBillingClient != null){
            mBillingClient = null;
        }

        mBillingClient = BillingClient.newBuilder(activity).setListener(listener).enablePendingPurchases().build();
        connectToIAP(clientStateListener);
//        mBillingClient.isReady();
    }

    public void connectToIAP(BillingClientStateListener clientStateListener){
        if (mBillingClient != null){
            mBillingClient.startConnection(clientStateListener);
        }
    }

    public boolean isIAPConnecting(){
        boolean isBillingReady = mBillingClient.isReady();
        boolean isConnecting = (mBillingClient != null && isBillingReady);
        return isConnecting;
    }

//    public List<Purchase> queryPurchaseList(String _skuType){
//        if (mBillingClient != null){
//            Purchase.PurchasesResult purchasesResult = mBillingClient.queryPurchases(_skuType);
//            if (purchasesResult != null){
//                List<Purchase> purchaseList = purchasesResult.getPurchasesList();
//                return purchaseList;
//            }
//        }
//        return null;
//    }

    public void queryPurchaseList(String _skuType, PurchasesResponseListener _responseListener){
        if (mBillingClient != null){
            mBillingClient.queryPurchasesAsync(_skuType, _responseListener);

        }
    }

    public void querySkuDetails(List<String> _skuList, String _skuType, SkuDetailsResponseListener listener){
        if (mBillingClient != null && mBillingClient.isReady()){
            SkuDetailsParams.Builder params = SkuDetailsParams.newBuilder();
            params.setSkusList(_skuList).setType(_skuType);

            mBillingClient.querySkuDetailsAsync(params.build(),listener);
        }
    }

    public void lauchFlowToIAP(Activity activity,SkuDetails _skuDetails){
        if (mBillingClient != null && mBillingClient.isReady() && _skuDetails != null){
            BillingFlowParams flowParams = BillingFlowParams.newBuilder().setSkuDetails(_skuDetails).build();
            int responseCode = mBillingClient.launchBillingFlow(activity,flowParams).getResponseCode();
            if (responseCode != 0) {
                Toast.makeText(JoyPreschool.joylandInstance,responseCode + ":Current region does not support Google payments",Toast.LENGTH_SHORT);
            }
        }
    }

    public void handlePurchase(Purchase purchase, AcknowledgePurchaseResponseListener listener){
        if (mBillingClient != null){
            if (purchase != null && purchase.getPurchaseState() == Purchase.PurchaseState.PURCHASED){
                if (!purchase.isAcknowledged()){
                    AcknowledgePurchaseParams acknowledgePurchaseParams = AcknowledgePurchaseParams.newBuilder().setPurchaseToken(purchase.getPurchaseToken()).build();
                    mBillingClient.acknowledgePurchase(acknowledgePurchaseParams,listener);
                }
            }
        }
    }
}
