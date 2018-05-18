/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

#include "CCEditBoxImplAndroid.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "CCEditBox.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <unordered_map>


NS_CC_EXT_BEGIN

// CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
// {
//     return new CCEditBoxImplAndroid(pEditBox);
// }

// CCEditBoxImplAndroid::CCEditBoxImplAndroid(CCEditBox* pEditText)
// : CCEditBoxImpl(pEditText)
// , m_pLabel(NULL)
// , m_pLabelPlaceHolder(NULL)
// , m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
// , m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
// , m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
// , m_colText(ccWHITE)
// , m_colPlaceHolder(ccGRAY)
// , m_nMaxLength(-1)
// {
    
// }

// CCEditBoxImplAndroid::~CCEditBoxImplAndroid()
// {
	
// }

// void CCEditBoxImplAndroid::doAnimationWhenKeyboardMove(float duration, float distance)
// { // don't need to be implemented on android platform.
	
// }

// static const int CC_EDIT_BOX_PADDING = 5;

// bool CCEditBoxImplAndroid::initWithSize(const CCSize& size)
// {
//     int fontSize = getFontSizeAccordingHeightJni(size.height-12);
//     m_pLabel = CCLabelTTF::create("", "", size.height-12);
// 	// align the text vertically center
//     m_pLabel->setAnchorPoint(ccp(0, 0.5f));
//     m_pLabel->setPosition(ccp(CC_EDIT_BOX_PADDING, size.height / 2.0f));
//     m_pLabel->setColor(m_colText);
//     m_pEditBox->addChild(m_pLabel);
	
//     m_pLabelPlaceHolder = CCLabelTTF::create("", "", size.height-12);
// 	// align the text vertically center
//     m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
//     m_pLabelPlaceHolder->setPosition(ccp(CC_EDIT_BOX_PADDING, size.height / 2.0f));
//     m_pLabelPlaceHolder->setVisible(false);
//     m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
//     m_pEditBox->addChild(m_pLabelPlaceHolder);
    
//     m_EditSize = size;
//     return true;
// }

// void CCEditBoxImplAndroid::setFont(const char* pFontName, int fontSize)
// {
// 	if(m_pLabel != NULL) {
// 		m_pLabel->setFontName(pFontName);
// 		m_pLabel->setFontSize(fontSize);
// 	}
	
// 	if(m_pLabelPlaceHolder != NULL) {
// 		m_pLabelPlaceHolder->setFontName(pFontName);
// 		m_pLabelPlaceHolder->setFontSize(fontSize);
// 	}
// }

// void CCEditBoxImplAndroid::setFontColor(const ccColor3B& color)
// {
//     m_colText = color;
//     m_pLabel->setColor(color);
// }

// void CCEditBoxImplAndroid::setPlaceholderFont(const char* pFontName, int fontSize)
// {
// 	if(m_pLabelPlaceHolder != NULL) {
// 		m_pLabelPlaceHolder->setFontName(pFontName);
// 		m_pLabelPlaceHolder->setFontSize(fontSize);
// 	}
// }

// void CCEditBoxImplAndroid::setPlaceholderFontColor(const ccColor3B& color)
// {
//     m_colPlaceHolder = color;
//     m_pLabelPlaceHolder->setColor(color);
// }

// void CCEditBoxImplAndroid::setInputMode(EditBoxInputMode inputMode)
// {
//     m_eEditBoxInputMode = inputMode;
// }

// void CCEditBoxImplAndroid::setMaxLength(int maxLength)
// {
//     m_nMaxLength = maxLength;
// }

// int CCEditBoxImplAndroid::getMaxLength()
// {
//     return m_nMaxLength;
// }

// void CCEditBoxImplAndroid::setInputFlag(EditBoxInputFlag inputFlag)
// {
//     m_eEditBoxInputFlag = inputFlag;
// }

// void CCEditBoxImplAndroid::setReturnType(KeyboardReturnType returnType)
// {
//     m_eKeyboardReturnType = returnType;
// }

// bool CCEditBoxImplAndroid::isEditing()
// {
//     return false;
// }

// void CCEditBoxImplAndroid::setText(const char* pText)
// {
//     if (pText != NULL)
//     {
//         m_strText = pText;
		
//         if (m_strText.length() > 0)
//         {
//             m_pLabelPlaceHolder->setVisible(false);
			
//             std::string strToShow;
			
//             if (kEditBoxInputFlagPassword == m_eEditBoxInputFlag)
//             {
//                 long length = cc_utf8_strlen(m_strText.c_str());
//                 for (long i = 0; i < length; i++)
//                 {
//                     strToShow.append("\u25CF");
//                 }
//             }
//             else
//             {
//                 strToShow = m_strText;
//             }

// 			m_pLabel->setString(strToShow.c_str());

// 			// Clip the text width to fit to the text box
// 			float fMaxWidth = m_EditSize.width - CC_EDIT_BOX_PADDING * 2;
// 			CCRect clippingRect = m_pLabel->getTextureRect();
// 			if(clippingRect.size.width > fMaxWidth) {
// 				clippingRect.size.width = fMaxWidth;
// 				m_pLabel->setTextureRect(clippingRect);
// 			}

//         }
//         else
//         {
//             m_pLabelPlaceHolder->setVisible(true);
//             m_pLabel->setString("");
//         }
		
//     }
// }

// const char*  CCEditBoxImplAndroid::getText(void)
// {
//     return m_strText.c_str();
// }

// void CCEditBoxImplAndroid::setPlaceHolder(const char* pText)
// {
//     if (pText != NULL)
//     {
//         m_strPlaceHolder = pText;
//         if (m_strPlaceHolder.length() > 0 && m_strText.length() == 0)
//         {
//             m_pLabelPlaceHolder->setVisible(true);
//         }
		
//         m_pLabelPlaceHolder->setString(m_strPlaceHolder.c_str());
//     }
// }

// void CCEditBoxImplAndroid::setPosition(const CCPoint& pos)
// { // don't need to be implemented on android platform.
	
// }

void CCEditBoxImplAndroid::setVisible(bool visible)
{ // don't need to be implemented on android platform.
    setNativeVisible(visible);
}

// void CCEditBoxImplAndroid::setContentSize(const CCSize& size)
// { // don't need to be implemented on android platform.
	
// }

// void CCEditBoxImplAndroid::setAnchorPoint(const CCPoint& anchorPoint)
// { // don't need to be implemented on android platform.
	
// }

// void CCEditBoxImplAndroid::visit(void)
// { // don't need to be implemented on android platform.
    
// }

// void CCEditBoxImplAndroid::onEnter(void)
// { // don't need to be implemented on android platform.
    
// }

// static void editBoxCallbackFunc(const char* pText, void* ctx)
// {
//     CCEditBoxImplAndroid* thiz = (CCEditBoxImplAndroid*)ctx;
//     thiz->setText(pText);
	
//     if (thiz->getDelegate() != NULL)
//     {
//         thiz->getDelegate()->editBoxTextChanged(thiz->getCCEditBox(), thiz->getText());
//         thiz->getDelegate()->editBoxEditingDidEnd(thiz->getCCEditBox());
//         thiz->getDelegate()->editBoxReturn(thiz->getCCEditBox());
//     }
    
//     CCEditBox* pEditBox = thiz->getCCEditBox();
//     if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
//     {
//         cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();

//         cocos2d::extension::KeyboardReturnType returnType = pEditBox->getReturnType();
//         int handler = pEditBox->getScriptEditBoxHandler();
// //        pEngine->executeEvent(handler, "changed",pEditBox);
// //
// //        if (returnType == cocos2d::extension::kKeyboardReturnTypeDone)
// //        {
// //            pEngine->executeEvent(handler, "returnDone", pEditBox);
// //    }
// //        else if (returnType == cocos2d::extension::kKeyboardReturnTypeSend)
// //        {
// //            pEngine->executeEvent(handler, "returnSend", pEditBox);
// //}
// //        else if (returnType == cocos2d::extension::kKeyboardReturnTypeSearch)
// //        {
// //            pEngine->executeEvent(handler, "returnSearch", pEditBox);
// //        }
// //        else if (returnType == cocos2d::extension::kKeyboardReturnTypeGo)
// //        {
// //            pEngine->executeEvent(handler, "returnGo", pEditBox);
// //        }
// //        else
// //        {
// //            pEngine->executeEvent(handler, "return", pEditBox);
// //        }
//         pEngine->executeEvent(handler, "ended",pEditBox);
//     }
// }

static void editBoxCallbackActionSend(void* ctx){
    CCEditBoxImplAndroid* thiz = (CCEditBoxImplAndroid*)ctx;
    if (thiz) {
        CCEditBox* pEditBox = thiz->getCCEditBox();
        if (pEditBox) {
            int handler = pEditBox->getScriptEditBoxHandler();
            if (handler) {
                cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
                pEngine->executeEvent(handler, "returnSend",pEditBox);
            }
        }
    }
}

// void CCEditBoxImplAndroid::openKeyboard()
// {
//     if (m_pDelegate != NULL)
//     {
//         m_pDelegate->editBoxEditingDidBegin(m_pEditBox);
//     }
//     CCEditBox* pEditBox = this->getCCEditBox();
//     if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
//     {
//         cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
//         pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
//     }
	
//     showEditTextDialogJNI(  m_strPlaceHolder.c_str(),
// 						  m_strText.c_str(),
// 						  m_eEditBoxInputMode,
// 						  m_eEditBoxInputFlag,
// 						  m_eKeyboardReturnType,
// 						  m_nMaxLength,
// 						  editBoxCallbackFunc,
//                           editBoxCallbackActionSend,
// 						  (void*)this  );
	
// }

// void CCEditBoxImplAndroid::closeKeyboard()
// {
// 	releaseEdit();
// }




//////////////新增/////////

#define  LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,"",__VA_ARGS__)
static void editBoxEditingDidBegin(int index);
static void editBoxEditingDidChanged(int index, const std::string& text);
static void editBoxEditingDidEnd(int index, const std::string& text);
static void editBoxEditingDidReturn(int index, const std::string& text);
extern "C"{
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingDidBegin(JNIEnv *env, jclass, jint index) {
        editBoxEditingDidBegin(index);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingChanged(JNIEnv *env, jclass, jint index, jstring text) {
        std::string textString = StringUtils::getStringUTFCharsJNI(env,text);
        editBoxEditingDidChanged(index, textString);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingDidEnd(JNIEnv *env, jclass, jint index, jstring text) {
        std::string textString = StringUtils::getStringUTFCharsJNI(env,text);
        editBoxEditingDidEnd(index, textString);
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxEditBoxHelper_editBoxEditingDidReturn(JNIEnv *env, jclass, jint index, jstring text) {
        std::string textString = StringUtils::getStringUTFCharsJNI(env,text);
        editBoxEditingDidReturn(index, textString);
    }
}

static std::unordered_map<int, CCEditBoxImplAndroid*> s_allEditBoxes;


CCEditBoxImpl* __createSystemEditBox(EditBox* editBox)
{
    return new CCEditBoxImplAndroid(editBox);
}


CCEditBoxImplAndroid::CCEditBoxImplAndroid(EditBox* pEditText)
: EditBoxImplCommon(pEditText)
, _editBoxIndex(-1)
{
}

CCEditBoxImplAndroid::~CCEditBoxImplAndroid()
{
    s_allEditBoxes.erase(_editBoxIndex);
    removeEditBoxJNI(_editBoxIndex);
}


void CCEditBoxImplAndroid::createNativeControl(const Rect& frame)
{
    auto director = cocos2d::CCDirector::sharedDirector();
    auto glView = director->getOpenGLView();
    auto frameSize = glView->getFrameSize();
    
    auto winSize = director->getWinSize();
    auto leftBottom = m_pEditBox->convertToWorldSpace(ccp(0,0));
    
    auto contentSize = frame.size;
    auto rightTop = m_pEditBox->convertToWorldSpace(Point(contentSize.width, contentSize.height));
    
    auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
    auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
    auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
    auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
    LOGD("scaleX = %f", glView->getScaleX());
    _editBoxIndex = addEditBoxJNI(uiLeft, uiTop, uiWidth, uiHeight, glView->getScaleX());
    s_allEditBoxes[_editBoxIndex] = this;

    //设置回调
    //setTextSendCallback(editBoxCallbackActionSend);
   
}

void CCEditBoxImplAndroid::setNativeFont(const char* pFontName, int fontSize)
{
    auto director = cocos2d::CCDirector::sharedDirector();
    auto glView = director->getOpenGLView();
    setFontEditBoxJNI(_editBoxIndex, pFontName, fontSize * glView->getScaleX());
}

void CCEditBoxImplAndroid::setNativeFontColor(const Color3B& color)
{
    setFontColorEditBoxJNI(_editBoxIndex, color.r, color.g, color.b, 255);
}

void CCEditBoxImplAndroid::setNativePlaceholderFont(const char* pFontName, int fontSize)
{
    CCLOG("Wraning! You can't change Andriod Hint fontName and fontSize");
}

void CCEditBoxImplAndroid::setNativePlaceholderFontColor(const Color3B& color)
{
    setPlaceHolderTextColorEditBoxJNI(_editBoxIndex, color.r, color.g, color.b, 2555);
}

void CCEditBoxImplAndroid::setNativeInputMode(EditBoxInputMode inputMode)
{
    setInputModeEditBoxJNI(_editBoxIndex, static_cast<int>(inputMode));
}

void CCEditBoxImplAndroid::setNativeMaxLength(int maxLength)
{
    setMaxLengthJNI(_editBoxIndex, maxLength);
}


void CCEditBoxImplAndroid::setNativeInputFlag(EditBoxInputFlag inputFlag)
{
    setInputFlagEditBoxJNI(_editBoxIndex, static_cast<int>(inputFlag));
}

void CCEditBoxImplAndroid::setNativeReturnType(KeyboardReturnType returnType)
{
    setReturnTypeEditBoxJNI(_editBoxIndex, static_cast<int>(returnType));
}

bool CCEditBoxImplAndroid::isEditing()
{
    return false;
}

void CCEditBoxImplAndroid::setNativeText(const char* pText)
{
    setTextEditBoxJNI(_editBoxIndex, pText);
}

void CCEditBoxImplAndroid::setNativePlaceHolder(const char* pText)
{
    setPlaceHolderTextEditBoxJNI(_editBoxIndex, pText);
}


void CCEditBoxImplAndroid::setNativeVisible(bool visible)
{ // don't need to be implemented on android platform.
    setVisibleEditBoxJNI(_editBoxIndex, visible);
}

void CCEditBoxImplAndroid::updateNativeFrame(const Rect& rect)
{

    setEditBoxViewRectJNI(_editBoxIndex, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void CCEditBoxImplAndroid::nativeOpenKeyboard()
{
    //it will also open up the soft keyboard
    setVisibleEditBoxJNI(_editBoxIndex,true);
}


void CCEditBoxImplAndroid::nativeCloseKeyboard()
{
    closeEditBoxKeyboardJNI(_editBoxIndex);
}

void editBoxEditingDidBegin(int index)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingDidBegin();
    }
}
void editBoxEditingDidChanged(int index, const std::string& text)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingChanged(text);
    }
}

void editBoxEditingDidEnd(int index, const std::string& text)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingDidEnd(text);
    }
}

void editBoxEditingDidReturn(int index, const std::string& text)
{
    auto it = s_allEditBoxes.find(index);
    if (it != s_allEditBoxes.end())
    {
        s_allEditBoxes[index]->editBoxEditingDidReturn(text);
    }
}

const char* CCEditBoxImplAndroid::getNativeDefaultFontName()
{
    return "";
}



NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

