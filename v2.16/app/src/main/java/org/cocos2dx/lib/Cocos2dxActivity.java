/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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
package org.cocos2dx.lib;

import java.util.Set;

import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

//import com.amazon.device.iap.PurchasingService;
//import com.android.vending.billing.IInAppBillingService;


//import com.appsflyer.AppsFlyerConversionListener;
//import com.appsflyer.AppsFlyerLib;
//import com.jbt.newmatch.JoyPreschool;
//import com.jpt.joyland.MySku;
//import com.jpt.joyland.SampleIapManager;
//import com.jpt.joyland.SamplePurchasingListener;

//import com.jpt.joyland.util.IabBroadcastReceiver.IabBroadcastListener;

//import com.tapjoy.TJConnectListener;
//import com.tapjoy.Tapjoy;
//import com.tapjoy.TapjoyConnectFlag;








import android.Manifest;
import android.app.Activity;
//import android.content.ComponentName;
import android.content.Context;
import android.content.pm.PackageManager;
//import android.content.Intent;
//import android.content.ServiceConnection;
import android.os.Build;
import android.os.Bundle;
//import android.os.IBinder;
import android.os.Message;
import android.view.ViewGroup;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
//import android.support.v4.app.ActivityCompat;
//import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.Toast;

public abstract class Cocos2dxActivity extends Activity implements Cocos2dxHelperListener {
	// ===========================================================
	// Constants
	// ===========================================================
//	public SampleIapManager sampleIapManager;
	private static final String TAG = Cocos2dxActivity.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================
	
	private Cocos2dxGLSurfaceView mGLSurfaceView;
	private Cocos2dxHandler mHandler;
	private static Context sContext = null;
	public static Cocos2dxActivity instance = null;
	
	public static Context getContext() {
		return sContext;
	}
	
//	IInAppBillingService mService;
//
//	ServiceConnection mServiceConn = new ServiceConnection() {
//	@Override
//	public void onServiceConnected(ComponentName arg0, IBinder arg1) {
//		// TODO Auto-generated method stub
//
//	       mService = IInAppBillingService.Stub.asInterface(arg1);
//	}
//
//	@Override
//	public void onServiceDisconnected(ComponentName arg0) {
//		// TODO Auto-generated method stub
//
//	       mService = null;
//	}
//	};
	
	// ===========================================================
	// Constructors
	// ===========================================================
	
	private static final String AF_DEV_KEY = "nkXkoXwwf8Ee2rP37VqDiH";
	private static final int PERMISSION_REQUEST_CODE = 1;
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
//		connectToTapjoy();
//		setupIAPOnCreate();
//		Intent serviceIntent = new Intent("com.android.vending.billing.InAppBillingService.BIND");
//		serviceIntent.setPackage("com.android.vending");
//		bindService(serviceIntent, mServiceConn, Context.BIND_AUTO_CREATE);
		sContext = this;
		instance = this;
    	this.mHandler = new Cocos2dxHandler(this);


		this.init();

		Cocos2dxHelper.init(this, this);
		
//		AppsFlyerConversionListener conversionDataListener =
//			       new AppsFlyerConversionListener() {
//
//					@Override
//					public void onAppOpenAttribution(Map<String, String> arg0) {
//						// TODO Auto-generated method stub
//
//					}
//
//					@Override
//					public void onAttributionFailure(String arg0) {
//						// TODO Auto-generated method stub
//
//					}
//
//					@Override
//					public void onInstallConversionDataLoaded(
//							Map<String, String> arg0) {
//						// TODO Auto-generated method stub
//
//					}
//
//					@Override
//					public void onInstallConversionFailure(String arg0) {
//						// TODO Auto-generated method stub
//
//					}
//			       };
//			       AppsFlyerLib.getInstance().init(AF_DEV_KEY, conversionDataListener, getApplicationContext());
//			       AppsFlyerLib.getInstance().startTracking(this.getApplication());
	}
	

//    /**
//	 * Attempts to connect to Tapjoy
//	 */
//	private void connectToTapjoy() {
//		// OPTIONAL: For custom startup flags.
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
	
	/**
     * Setup for IAP SDK called from onCreate. Sets up {@link SampleIapManager}
     * to handle InAppPurchasing logic and {@link SamplePurchasingListener} for
     * listening to IAP API callbacks
     */
//    private void setupIAPOnCreate() {
//        sampleIapManager = new SampleIapManager((JoyPreschool) this);
//        final SamplePurchasingListener purchasingListener = new SamplePurchasingListener(sampleIapManager);
//        Log.d(TAG, "onCreate: registering PurchasingListener");
//        PurchasingService.registerListener(this.getApplicationContext(), purchasingListener);
//        Log.d(TAG, "IS_SANDBOX_MODE:" + PurchasingService.IS_SANDBOX_MODE);
//    }

	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
	{

		if (requestCode == PERMISSION_REQUEST_CODE)
		{
			if (grantResults[0] == PackageManager.PERMISSION_GRANTED)
			{
//				this.init();

//				Cocos2dxHelper.init(this, this);
				Cocos2dxActivity.openGame();
			} else
			{
				// Permission Denied
				Toast.makeText(Cocos2dxActivity.this, "Permission Denied", Toast.LENGTH_SHORT).show();
				ActivityCompat.requestPermissions(Cocos2dxActivity.instance,new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},PERMISSION_REQUEST_CODE);
			}
			return;
		}
		super.onRequestPermissionsResult(requestCode, permissions, grantResults);
	}

	public static void checkDangersPermission(){
		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT){
			if (ContextCompat.checkSelfPermission(Cocos2dxActivity.sContext, Manifest.permission.READ_EXTERNAL_STORAGE)
					!= PackageManager.PERMISSION_GRANTED) {
				ActivityCompat.requestPermissions(Cocos2dxActivity.instance,new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},PERMISSION_REQUEST_CODE);

			} else {
				Cocos2dxActivity.openGame();
			}
		}else{
//			this.init();

//			Cocos2dxHelper.init(this, this);
			Cocos2dxActivity.openGame();
		}
	}

	private static native void openGame();

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
    
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

	@Override
	protected void onResume() {
		super.onResume();
//		sampleIapManager.activate();
//        Log.d(TAG, "onResume: call getUserData");
//        PurchasingService.getUserData();
//        Log.d(TAG, "onResume: getPurchaseUpdates");
//        PurchasingService.getPurchaseUpdates(false);
		Cocos2dxHelper.onResume();
		this.mGLSurfaceView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
//		sampleIapManager.deactivate();

		Cocos2dxHelper.onPause();
		this.mGLSurfaceView.onPause();
	}
	
	@Override
    protected void onStop() {
//      Tapjoy.onActivityStop(this);
      super.onStop();
    }
	
	@Override
	public void onDestroy() {
	    super.onDestroy();
//	    if (mService != null) {
//	        unbindService(mServiceConn);
//	    }
	}

	@Override
	public void showDialog(final String pTitle, final String pMessage) {
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_DIALOG;
		msg.obj = new Cocos2dxHandler.DialogMessage(pTitle, pMessage);
		this.mHandler.sendMessage(msg);
	}

	@Override
	public void showEditTextDialog(final String pTitle, final String pContent, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) { 
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_EDITBOX_DIALOG;
		msg.obj = new Cocos2dxHandler.EditBoxMessage(pTitle, pContent, pInputMode, pInputFlag, pReturnType, pMaxLength);
		this.mHandler.sendMessage(msg);
	}
	
	/**
     * Show message on UI
     * 
     * @param message
     */
    public void showMessage(final String message) {
    	Log.d(TAG, "=========================SHOWMESSAGE========================");
        Toast.makeText(Cocos2dxActivity.this, message, Toast.LENGTH_LONG).show();
    }
	
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurfaceView.queueEvent(pRunnable);
	}
	protected static FrameLayout mFrameLayout;
	// ===========================================================
	// Methods
	// ===========================================================
	public void init() {
		
    	// FrameLayout
        ViewGroup.LayoutParams framelayout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
                                       ViewGroup.LayoutParams.FILL_PARENT);
        mFrameLayout = new FrameLayout(this);
        mFrameLayout.setLayoutParams(framelayout_params);

        // Cocos2dxEditText layout
        ViewGroup.LayoutParams edittext_layout_params =
            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
                                       ViewGroup.LayoutParams.WRAP_CONTENT);
        Cocos2dxEditText edittext = new Cocos2dxEditText(this);
        edittext.setLayoutParams(edittext_layout_params);

        // ...add to FrameLayout
        mFrameLayout.addView(edittext);

        // Cocos2dxGLSurfaceView
        this.mGLSurfaceView = this.onCreateView();

        // ...add to FrameLayout
        mFrameLayout.addView(this.mGLSurfaceView);

        // Switch to supported OpenGL (ARGB888) mode on emulator
        if (isAndroidEmulator())
           this.mGLSurfaceView.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);

        this.mGLSurfaceView.setCocos2dxRenderer(new Cocos2dxRenderer());
        this.mGLSurfaceView.setCocos2dxEditText(edittext);

        // Set framelayout as the content view
		setContentView(mFrameLayout);
	}
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	return new Cocos2dxGLSurfaceView(this);
    }

   private final static boolean isAndroidEmulator() {
      String model = Build.MODEL;
      Log.d(TAG, "model=" + model);
      String product = Build.PRODUCT;
      Log.d(TAG, "product=" + product);
      boolean isEmulator = false;
      if (product != null) {
         isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
      }
      Log.d(TAG, "isEmulator=" + isEmulator);
      return isEmulator;
   }

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
