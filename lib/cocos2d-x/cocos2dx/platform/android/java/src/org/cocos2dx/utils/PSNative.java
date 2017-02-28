package org.cocos2dx.utils;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.util.Vector;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.BatteryManager;
import android.os.Build;
import android.os.Looper;
import android.os.Vibrator;
import android.telephony.TelephonyManager;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;


public class PSNative {	
	static Cocos2dxActivity mContext = null;
	static TelephonyManager mTelephonyManager = null;
	static Vibrator mVibrator = null;

	static PSDialog mCreatingDialog = null;
	static PSDialog mShowingDialog = null;
	static ProgressBar mProgressBar = null;
	static Dialog mIndicatorDialog = null;
	static Vector<PSDialog> mShowingDialogs = null;

	static Drawable mAppIcon = null;
	
	static Intent batteryIntent = null;

	static PSDialog.PSDialogListener mPSDialogListener = new PSDialog.PSDialogListener() {
		@Override
		public void onDismiss(PSDialog dialog) {
			showPreAlert();
		}
	};

	public static void init(Cocos2dxActivity context) {
		mContext = context;
		mTelephonyManager = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);
		mVibrator = (Vibrator) context
				.getSystemService(Context.VIBRATOR_SERVICE);

		mShowingDialogs = new Vector<PSDialog>();
		//检测电池电量
		batteryIntent = context.registerReceiver(null, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
	}

	public static void setAppIcon(Drawable icon) {
		// 当对话框需要带上图像时，调用该方法。null表示不带图像
		mAppIcon = icon;
	}

	public static void createAlert(final String title, final String message,
			final Vector<String> buttonTitles, final int listener) {
		if (mContext == null) {
			return;
		}

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mCreatingDialog = new PSDialog(mContext).setCancelable(false)
						.setMessage(message).setTitle(title)
						.setLuaListener(listener)
						.setListener(mPSDialogListener).setIcon(mAppIcon);

				for (int i = 0; i < buttonTitles.size(); i++) {
					addAlertButton(buttonTitles.get(i));
				}

				if (mShowingDialog != null && mShowingDialog.isShowing()) {
					mShowingDialogs.add(mShowingDialog);
					mShowingDialog.hide();
				}

				mCreatingDialog.show();
				mShowingDialog = mCreatingDialog;
				mCreatingDialog = null;
			}
		});
	}

	@Deprecated
	/**
	 * this function will appear thread unsafe problem...
	 */
	public static void createAlert(final String title, final String message,
			final String defalutButtonTitle, final int listener) {
		if (mContext == null) {
			return;
		}

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mCreatingDialog = new PSDialog(mContext).setCancelable(false)
						.setMessage(message).setTitle(title)
						.setLuaListener(listener)
						.setListener(mPSDialogListener);

				addAlertButton(defalutButtonTitle);

				if (mShowingDialog != null && mShowingDialog.isShowing()) {
					mShowingDialogs.add(mShowingDialog);
					mShowingDialog.hide();
				}

				mCreatingDialog.show();
				mShowingDialog = mCreatingDialog;
				mCreatingDialog = null;
			}
		});
	}

	public static int addAlertButton(final String buttonTitle) {
		if (mCreatingDialog == null)
			return 0;

		return mCreatingDialog.addAlertButton(buttonTitle);
	}

	public static void showAlert() {
		if (mCreatingDialog == null) {
			return;
		}

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (mShowingDialog != null && mShowingDialog.isShowing()) {
					mShowingDialogs.add(mShowingDialog);
					mShowingDialog.hide();
				}

				mCreatingDialog.show();
				mShowingDialog = mCreatingDialog;
				mCreatingDialog = null;
			}
		});
	}

	public static void showAlertLua(final int luaFunctionId) {
		if (mCreatingDialog == null) {
			return;
		}

		mContext.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				mCreatingDialog.setLuaListener(luaFunctionId);
				showAlert();
			}
		});
	}

	public static void cancelAlert() {
		if (mShowingDialog == null)
			return;

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mShowingDialog.dismiss();
				mShowingDialog = null;
			}
		});
	}

	public static void showPreAlert() {
		if (mShowingDialogs.size() > 0) {
			mShowingDialog = mShowingDialogs.firstElement();
			mShowingDialogs.remove(0);
			mShowingDialog.show();
		} else {
			mShowingDialog = null;
		}
	}

	public static void openURL(String url) {
		if (mContext == null) {
			return;
		}
		Uri uri = Uri.parse(url);
		mContext.startActivity(new Intent(Intent.ACTION_VIEW, uri));
	}

	public static String getInputText(String title, String message,
			String defaultValue) {
		return "";
	}

	private static String getMacAddress() {
		WifiManager wifi = (WifiManager) mContext
				.getSystemService(Context.WIFI_SERVICE);
		WifiInfo info = wifi.getConnectionInfo();
		if (info == null)
			return null;
		return info.getMacAddress();
	}

	public static String getOpenUDID() {
		String id = null;
		if (mTelephonyManager != null) {
			id = mTelephonyManager.getDeviceId();
		}
		if (id == null) {
			id = getMacAddress();
		}
		if (id == null) {
			id = "";
		}
		return id;
	}

	public static String getDeviceName() {
		return Build.USER;
	}
	
	public static String getDeviceBrandAndModel(){
		return Build.BRAND+" "+Build.MODEL;
	}
	public static String getDeviceModel(){
		return Build.MODEL;
	}
	public static String getDeviceBrand(){
		return Build.BRAND;
	}
	
	public static String getDeviceSystemVersion(){
    	return Build.VERSION.RELEASE;
    }
	
	public static String getDeviceId(){
    	//DEVICE_ID 非手机无法获得
    	TelephonyManager tm = (TelephonyManager)mContext.getSystemService(Context.TELEPHONY_SERVICE);
    	if(tm!=null){
    		try{
    			String deviceId = tm.getDeviceId();    			
    			if(deviceId!=null){
        			return deviceId;
        		}
    		}catch(Exception e){
    			e.printStackTrace();
    		}
    	}
    	
    	//cpu序列号
    	String cpuSerial = getIdentifierByCpu();
    	if(cpuSerial!=null && cpuSerial!=""){
    		return cpuSerial;
    	}
    	
    	//mac地址 如果Wifi关闭的时候，硬件设备可能无法返回。
    	String macAdd = getMacAddress();
    	if(macAdd!=null && macAdd!=""){
    		return macAdd;
    	}        	

    	return "null";
    }
    public static String getIdentifierByCpu() {
        String identifier = null;
        String cmdStr = "cat /proc/cpuinfo";
        Process process;
        try {
          process = Runtime.getRuntime().exec(cmdStr);
          InputStreamReader reader = new InputStreamReader(process.getInputStream());
          LineNumberReader lineReader = new LineNumberReader(reader);
          String line = "";
          while ((line = lineReader.readLine()) != null) {
            if (line.startsWith("Serial")) {
              identifier = line.split(":")[1];              
            }
          }
        } catch (IOException e) {
        	e.printStackTrace();
        }
        return identifier;
    }

	public static void vibrate(int time) {
		if (mVibrator == null) {
			return;
		}
		mVibrator.vibrate((long)time);
	}

	public static void vibrate(long[] pattern, int repeatcout) {
		if (mVibrator == null) {
			return;
		}
		mVibrator.vibrate(pattern, repeatcout);
	}
	
	//复制到剪切板
    public static void copylua(final String value){
    	if(Looper.myLooper()==null){
    		Looper.prepare();
    	}
    	android.text.ClipboardManager c = (android.text.ClipboardManager) mContext.getSystemService(Context.CLIPBOARD_SERVICE);
		c.setText(value);
    }
    
    // 得到版本号
    public static String getCurrentVersionName() throws NameNotFoundException{
    	PackageManager manager = mContext.getPackageManager();
    	if(manager!=null){
    		PackageInfo info = manager.getPackageInfo(mContext.getPackageName(), 0);
    		if(info!=null){
    			return info.versionName;
    		}
    	}
    	return "";
    }   
    // 得到版本号
    public static int getCurrentVersionCode() throws NameNotFoundException{
    	PackageManager manager = mContext.getPackageManager();
    	PackageInfo info = manager.getPackageInfo(mContext.getPackageName(), 0);
    	if(info!=null){
    		return info.versionCode;
    	}
    	return 0;
    }
    
    // 得到包名
    public static String getPackageName(){
    	String str = mContext.getPackageName();
    	return str;
    }

    public static int getBatteryLevel(){
        int level = batteryIntent.getIntExtra(BatteryManager.EXTRA_LEVEL, -1);
        int scale = batteryIntent.getIntExtra(BatteryManager.EXTRA_SCALE, -1);
        if(level==-1 || scale==-1){
        	return 50;
        }
        return level*100/scale;
    }
    
    public static boolean isNetworkAvailable(){
    	ConnectivityManager connectivity = (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
    	if(connectivity != null){ 
    		NetworkInfo info = connectivity.getActiveNetworkInfo();
    		if(info!=null){
    			return info.isAvailable();
    		}
    	}
		return false;
    }

	public static Context getAppContext() {
		return mContext;
	}
	
	public static void showActivityIndicator() {
		if (mIndicatorDialog == null) {
			mContext.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					mIndicatorDialog = new Dialog(mContext);
					mIndicatorDialog.getWindow().setBackgroundDrawable(new ColorDrawable(0));
					mIndicatorDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
					ProgressBar pb = new ProgressBar(mContext);
				    RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);    
				    lp.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE); 
				    mIndicatorDialog.addContentView(pb, lp);
				    mIndicatorDialog.show();
				}
			});
		}

	}
	
	public static void hideActivityIndicator() {
		if (mIndicatorDialog == null) {
			return;
		}
		mIndicatorDialog.dismiss();
		mIndicatorDialog = null;

	}
}