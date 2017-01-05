/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#ifndef __Java_org_cocos2dx_lib_Cocos2dxHelper_H__
#define __Java_org_cocos2dx_lib_Cocos2dxHelper_H__

#include <string>

typedef void (*EditTextCallback)(const char* pText, void* ctx);
typedef void (*EditBoxCallbackActionSend)(void* ctx);

extern const char * getApkPath();
extern void showDialogJNI(const char * pszMsg, const char * pszTitle);
extern void showEditTextDialogJNI(const char* pszTitle, const char* pszContent, int nInputMode, int nInputFlag, int nReturnType, int nMaxLength, EditTextCallback pfEditTextCallback, EditBoxCallbackActionSend pfeditBoxCallbackActionSend, void* ctx);
extern void terminateProcessJNI();
extern std::string getCurrentLanguageJNI();
extern std::string getPackageNameJNI();
extern std::string getFileDirectoryJNI();
extern void enableAccelerometerJNI();
extern void disableAccelerometerJNI();
extern void setAccelerometerIntervalJNI(float interval);
extern bool inDirectoryExistsJNI(const char* path);
// functions for CCUserDefault
extern bool getBoolForKeyJNI(const char* pKey, bool defaultValue);
extern int getIntegerForKeyJNI(const char* pKey, int defaultValue);
extern float getFloatForKeyJNI(const char* pKey, float defaultValue);
extern double getDoubleForKeyJNI(const char* pKey, double defaultValue);
extern std::string getStringForKeyJNI(const char* pKey, const char* defaultValue);
extern void setBoolForKeyJNI(const char* pKey, bool value);
extern void setIntegerForKeyJNI(const char* pKey, int value);
extern void setFloatForKeyJNI(const char* pKey, float value);
extern void setDoubleForKeyJNI(const char* pKey, double value);
extern void setStringForKeyJNI(const char* pKey, const char* value);
extern void releaseEdit();

///////////qinxugao
extern void conversionEncodingJNI(const char* src, int byteSize, const char* fromCharset, char* dst, const char* newCharset);
//Added for new Android EditBox
extern int addEditBoxJNI(int left, int top, int width, int height, float scaleX);
extern void removeEditBoxJNI(int index);
extern void setEditBoxViewRectJNI(int index, int left, int top, int width, int height);
extern void setMaxLengthJNI(int index, int maxLength);
extern void openEditBoxKeyboardJNI(int index);
extern void closeEditBoxKeyboardJNI(int index);
extern void setVisibleEditBoxJNI(int index, bool visibility);
extern void setReturnTypeEditBoxJNI(int index, int returnType);
extern void setInputFlagEditBoxJNI(int index, int inputFlag);
extern void setInputModeEditBoxJNI(int index, int inputMode);
extern void setTextEditBoxJNI(int index, const char* text);
extern void setFontEditBoxJNI(int index, const char* fontName, float fontSize);
extern void setFontColorEditBoxJNI(int index, int red, int green, int blue, int alpha);
extern void setPlaceHolderTextEditBoxJNI(int index, const char* text);
extern void setPlaceHolderTextColorEditBoxJNI(int index, int red, int green, int blue, int alpha);
extern void setTextSendCallback(EditBoxCallbackActionSend pfeditBoxCallbackActionSend);

#endif /* __Java_org_cocos2dx_lib_Cocos2dxHelper_H__ */
