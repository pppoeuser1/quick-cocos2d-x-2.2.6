#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "JniHelper.h"
#include "cocoa/CCString.h"
#include "Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "support/ccUTF8.h"

#define  LOG_TAG    "Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"
#define  EDITBOX_CLASS_NAME "org/cocos2dx/lib/Cocos2dxEditBoxHelper"


static EditTextCallback s_pfEditTextCallback = NULL;
static EditBoxCallbackActionSend s_pfeditBoxCallbackActionSend = NULL;
static void* s_ctx = NULL;

using namespace cocos2d;
using namespace std;

string g_apkPath;

extern "C" {

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(JNIEnv*  env, jobject thiz, jstring apkPath) {
        g_apkPath = JniHelper::jstring2string(apkPath);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetEditTextDialogResult(JNIEnv * env, jobject obj, jbyteArray text) {
        jsize  size = env->GetArrayLength(text);

        if (size > 0) {
            jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
            char* pBuf = (char*)malloc(size+1);
            if (pBuf != NULL) {
                memcpy(pBuf, data, size);
                pBuf[size] = '\0';
                // pass data to edittext's delegate
                if (s_pfEditTextCallback) s_pfEditTextCallback(pBuf, s_ctx);
                free(pBuf);
            }
            env->ReleaseByteArrayElements(text, data, 0);
        } else {
            if (s_pfEditTextCallback) s_pfEditTextCallback("", s_ctx);
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeEditBoxCallbackActionSend(JNIEnv * env, jobject obj) {
        if (s_pfeditBoxCallbackActionSend)
            s_pfeditBoxCallbackActionSend(s_ctx);
        
    }

}

const char * getApkPath() {
    return g_apkPath.c_str();
}

void showDialogJNI(const char * pszMsg, const char * pszTitle) {
    if (!pszMsg) {
        return;
    }

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1;

        if (!pszTitle) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszMsg);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void releaseEdit(){
    s_pfEditTextCallback = NULL;
    s_pfeditBoxCallbackActionSend = NULL;
    s_ctx = NULL;
}

void setTextSendCallback(EditBoxCallbackActionSend pfeditBoxCallbackActionSend)
{
    s_pfeditBoxCallbackActionSend = pfeditBoxCallbackActionSend;
}

void showEditTextDialogJNI(const char* pszTitle, const char* pszMessage, int nInputMode, int nInputFlag, int nReturnType, int nMaxLength, EditTextCallback pfEditTextCallback,EditBoxCallbackActionSend pfeditBoxCallbackActionSend, void* ctx) {
    if (pszMessage == NULL) {
        return;
    }

    s_pfEditTextCallback = pfEditTextCallback;
    s_pfeditBoxCallbackActionSend = pfeditBoxCallbackActionSend;
    s_ctx = ctx;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showEditTextDialog", "(Ljava/lang/String;Ljava/lang/String;IIII)V")) {
        jstring stringArg1;

        if (!pszTitle) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszMessage);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, nInputMode, nInputFlag, nReturnType, nMaxLength);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void terminateProcessJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "terminateProcess", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string getPackageNameJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxPackageName", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return ret;
}

std::string getFileDirectoryJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxWritablePath", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    return ret;
}

std::string getCurrentLanguageJNI() {
    JniMethodInfo t;
    std::string ret("");
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCurrentLanguage", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    return ret;
}

void enableAccelerometerJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setAccelerometerIntervalJNI(float interval) {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setAccelerometerInterval", "(F)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, interval);
        t.env->DeleteLocalRef(t.classID);
    }
}

void disableAccelerometerJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool inDirectoryExistsJNI(const char* path) {
    if (!path) return false;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "inDirectoryExists", "(Ljava/lang/String;)Z")) {
        jstring stringArg1;

        stringArg1 = t.env->NewStringUTF(path);
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(t.classID);
        return ret;
    }

    return false;
}


// functions for CCUserDefault
bool getBoolForKeyJNI(const char* pKey, bool defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getBoolForKey", "(Ljava/lang/String;Z)Z")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

int getIntegerForKeyJNI(const char* pKey, int defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getIntegerForKey", "(Ljava/lang/String;I)I")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

float getFloatForKeyJNI(const char* pKey, float defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getFloatForKey", "(Ljava/lang/String;F)F")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jfloat ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

double getDoubleForKeyJNI(const char* pKey, double defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDoubleForKey", "(Ljava/lang/String;D)D")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jdouble ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, stringArg);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

std::string getStringForKeyJNI(const char* pKey, const char* defaultValue)
{
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getStringForKey", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
        jstring stringArg1 = t.env->NewStringUTF(pKey);
        jstring stringArg2 = t.env->NewStringUTF(defaultValue);
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, stringArg2);
        ret = JniHelper::jstring2string(str);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(str);
        
        return ret;
    }
    
    return defaultValue;
}

void setBoolForKeyJNI(const char* pKey, bool value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setBoolForKey", "(Ljava/lang/String;Z)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setIntegerForKeyJNI(const char* pKey, int value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setIntegerForKey", "(Ljava/lang/String;I)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setFloatForKeyJNI(const char* pKey, float value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setFloatForKey", "(Ljava/lang/String;F)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setDoubleForKeyJNI(const char* pKey, double value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setDoubleForKey", "(Ljava/lang/String;D)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setStringForKeyJNI(const char* pKey, const char* value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setStringForKey", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(pKey);
        jstring stringArg2 = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
    }
}

/////////////////////////////////////editbox

int addEditBoxJNI(int left, int top, int width, int height, float scaleX){
    JniMethodInfo t;

    int ret = -1;
    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "createEditBox", "(IIIIF)I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, left, top, width, height, scaleX);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

void removeEditBoxJNI(int index)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "removeEditBox", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setEditBoxViewRectJNI(int index, int left, int top, int width, int height)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setEditBoxViewRect", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, left, top, width, height);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setMaxLengthJNI(int index, int maxLength)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setMaxLength", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, maxLength);
        t.env->DeleteLocalRef(t.classID);
    }
}

void openEditBoxKeyboardJNI(int index)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "openKeyboard", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void closeEditBoxKeyboardJNI(int index)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "closeKeyboard", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setVisibleEditBoxJNI(int index, bool visibility)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setVisible", "(IZ)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, visibility);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setReturnTypeEditBoxJNI(int index, int returnType)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setReturnType", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, returnType);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setInputFlagEditBoxJNI(int index, int returnType)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setInputFlag", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, returnType);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setInputModeEditBoxJNI(int index, int inputMode)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setInputMode", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, inputMode);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setTextEditBoxJNI(int index, const char* text)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setText", "(ILjava/lang/String;)V")) {
        jstring stringText = StringUtils::newStringUTFJNI(t.env,text);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, stringText);
        t.env->DeleteLocalRef(stringText);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setFontEditBoxJNI(int index, const char* fontName, float fontSize)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setFont", "(ILjava/lang/String;F)V")) {
        jstring stringText = StringUtils::newStringUTFJNI(t.env,fontName);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, stringText, fontSize);

        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringText);
    }
}

void setFontColorEditBoxJNI(int index, int red, int green, int blue, int alpha)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setFontColor", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, red, green, blue, alpha);

        t.env->DeleteLocalRef(t.classID);
    }
}

void setPlaceHolderTextEditBoxJNI(int index, const char* text)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setPlaceHolderText", "(ILjava/lang/String;)V")) {
        jstring stringText = StringUtils::newStringUTFJNI(t.env,text);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, stringText);

        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringText);
    }

}

void setPlaceHolderTextColorEditBoxJNI(int index, int red, int green, int blue, int alpha)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setPlaceHolderTextColor", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, red, green, blue, alpha);

        t.env->DeleteLocalRef(t.classID);
    }
}

void conversionEncodingJNI(const char* src, int byteSize, const char* fromCharset, char* dst, const char* newCharset)
{
    JniMethodInfo methodInfo;

    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "conversionEncoding", "([BLjava/lang/String;Ljava/lang/String;)[B")) {
        jbyteArray strArray = methodInfo.env->NewByteArray(byteSize);
        methodInfo.env->SetByteArrayRegion(strArray, 0, byteSize, reinterpret_cast<const jbyte*>(src));

        jstring stringArg1 = methodInfo.env->NewStringUTF(fromCharset);
        jstring stringArg2 = methodInfo.env->NewStringUTF(newCharset);

        jbyteArray newArray = (jbyteArray)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, strArray, stringArg1, stringArg2);
        jsize theArrayLen = methodInfo.env->GetArrayLength(newArray);
        methodInfo.env->GetByteArrayRegion(newArray, 0, theArrayLen, (jbyte*)dst);

        methodInfo.env->DeleteLocalRef(strArray);
        methodInfo.env->DeleteLocalRef(stringArg1);
        methodInfo.env->DeleteLocalRef(stringArg2);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}









