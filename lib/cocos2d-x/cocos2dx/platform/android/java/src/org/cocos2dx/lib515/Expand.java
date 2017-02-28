/*
  android 功能函数大集合
  2017.1.6

*/  
package org.cocos2dx.lib515;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;

public class Expand {
  private static Activity _activity = null;
  private static Expand expand = null;  
    //静态工厂方法   
    public static Expand getInstance() {  
         if (expand == null) {    
             expand = new Expand();  
         }    
        return expand; 
    }  

  public void setActivity(Activity activty){
     _activity = activty;
  }
  
  //是否安装了应用
  public static boolean isPkgInstalled(Context ctx, String packageName){
    PackageManager pm = ctx.getPackageManager();
    try {
      pm.getPackageInfo(packageName, 0);
    } catch (NameNotFoundException e) {
      return false;
    }
    return true;
  }  

  //用浏览器打开网页
  public static void openWithWeb(String url) {
     // Uri uri = Uri.parse(url);
     // Intent intent = new Intent(Intent.ACTION_VIEW, uri);  	  
  	 final String strUrl = url;
	 Intent intent = new Intent(Intent.ACTION_VIEW);         
     Uri content_url = Uri.parse(strUrl);
     intent.setData(content_url);    
     String packageName = "com.android.browser";
     if(isPkgInstalled(_activity,packageName)){
       intent.setClassName(packageName,packageName+".BrowserActivity");
     }     
     _activity.startActivity(intent);

 }





}