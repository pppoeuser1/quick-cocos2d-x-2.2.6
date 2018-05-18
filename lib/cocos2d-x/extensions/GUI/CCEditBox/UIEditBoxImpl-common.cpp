/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren

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
#include "UIEditBoxImpl-common.h"

#define kLabelZOrder  9999

#include "CCEditBox.h"
#include "CCDirector.h"
//#include "2d/CCLabel.h"
 #include "CocoStudio/GUI/UIWidgets/UILabel.h"
//#include "ui/UIHelper.h"
 #include "CocoStudio/GUI/System/UIHelper.h"

static const int CC_EDIT_BOX_PADDING = 5;

NS_CC_EXT_BEGIN

//namespace ui {

EditBoxImplCommon::EditBoxImplCommon(EditBox* pEditText)
: CCEditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBoxInputMode::kEditBoxInputModeSingleLine)
, _editBoxInputFlag(EditBoxInputFlag::kEditBoxInputFlagInitialCapsAllCharacters)
, _keyboardReturnType(KeyboardReturnType::kKeyboardReturnTypeDefault)
, _colText(ccc4(255,255,255,255))
, _colPlaceHolder(ccc4(166,166,166,255))
, _maxLength(-1)
{
}

EditBoxImplCommon::~EditBoxImplCommon()
{
}


bool EditBoxImplCommon::initWithSize(const Size& size)
{
    do 
    {
        
        Rect rect = Rect(0, 0, size.width, size.height);
        
        this->createNativeControl(rect);
        
        initInactiveLabels(size);
        setContentSize(size);
        
        return true;
    }while (0);
    
    return false;
}

void EditBoxImplCommon::initInactiveLabels(const Size& size)
{
    const char* pDefaultFontName = this->getNativeDefaultFontName();

    _label = Label::create();
    _label->setAnchorPoint(Vec2(0, 0.5f));
    _label->setColor(ccc3(255,255,255));
    _label->setVisible(false);
    m_pEditBox->addChild(_label, kLabelZOrder);
    
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
    _labelPlaceHolder->setColor(ccc3(166,166,166));
    m_pEditBox->addChild(_labelPlaceHolder, kLabelZOrder);
    
    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void EditBoxImplCommon::placeInactiveLabels()
{
    _label->setPosition(ccp(CC_EDIT_BOX_PADDING, _contentSize.height / 2.0f));
    _labelPlaceHolder->setPosition(ccp(CC_EDIT_BOX_PADDING, _contentSize.height / 2.0f));
}

void EditBoxImplCommon::setInactiveText(const char* pText)
{
    if(EditBoxInputFlag::kEditBoxInputFlagPassword == _editBoxInputFlag)
    {
        std::string passwordString;
        for(int i = 0; i < strlen(pText); ++i)
            passwordString.append("\u25CF");
        _label->setText(passwordString);
    }
    else
    {
        _label->setText(pText);
    }
    // Clip the text width to fit to the text box
    float fMaxWidth = m_pEditBox->getContentSize().width;
    float fMaxHeight = m_pEditBox->getContentSize().height;
    Size labelSize = _label->getContentSize();
    if(labelSize.width > fMaxWidth || labelSize.height > fMaxHeight)
    {
        //_label->setDimensions(fMaxWidth, fMaxHeight);
        _label->setTextAreaSize(CCSize(fMaxWidth,fMaxHeight));
    }
}
    
void EditBoxImplCommon::setFont(const char* pFontName, int fontSize)
{
    this->setNativeFont(pFontName, fontSize);

    if(strlen(pFontName) > 0)
    {
        //_label->setSystemFontName(pFontName);
        _label->setFontName(pFontName);
    }
    if(fontSize > 0)
    {
        //_label->setSystemFontSize(fontSize);
        _label->setFontSize(fontSize);
    }
}

void EditBoxImplCommon::setFontColor(const Color3B& color)
{
    this->setNativeFontColor(color);
    
    //_label->setTextColor(color);
    _label->setColor(ccc3(color.r,color.g,color.b));
}

void EditBoxImplCommon::setPlaceholderFont(const char* pFontName, int fontSize)
{
    this->setNativePlaceholderFont(pFontName, fontSize);
    
    if( strlen(pFontName) > 0)
    {
        //_labelPlaceHolder->setSystemFontName(pFontName);
        _labelPlaceHolder->setFontName(pFontName);
    }
    if(fontSize > 0)
    {
        //_labelPlaceHolder->setSystemFontSize(fontSize);
        _labelPlaceHolder->setFontSize(fontSize);
    }
}
    
void EditBoxImplCommon::setPlaceholderFontColor(const Color3B &color)
{
    this->setNativePlaceholderFontColor(color);
    
    //_labelPlaceHolder->setTextColor(color);
    _labelPlaceHolder->setColor(ccc3(color.r,color.g,color.b));
}

void EditBoxImplCommon::setInputMode(EditBoxInputMode inputMode)
{
    _editBoxInputMode = inputMode;
    this->setNativeInputMode(inputMode);
}

void EditBoxImplCommon::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    this->setNativeMaxLength(maxLength);
}

int EditBoxImplCommon::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplCommon::setInputFlag(EditBoxInputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
    this->setNativeInputFlag(inputFlag);
}

void EditBoxImplCommon::setReturnType(KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
    this->setNativeReturnType(returnType);
}
    
void EditBoxImplCommon::refreshInactiveText()
{
    setInactiveText(_text.c_str());
    if(_text.size() == 0)
    {
        _label->setVisible(false);
        _labelPlaceHolder->setVisible(true);
    }
    else
    {
        _label->setVisible(true);
        _labelPlaceHolder->setVisible(false);
    }
}

void EditBoxImplCommon::setText(const char* text)
{
    this->setNativeText(text);
    _text = text;
    refreshInactiveText();
}

const char*  EditBoxImplCommon::getText(void)
{
    return _text.c_str();
}

void EditBoxImplCommon::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }

        _labelPlaceHolder->setText(_placeHolder.c_str());
        this->setNativePlaceHolder(pText);
    }
}


void EditBoxImplCommon::setVisible(bool visible)
{
    this->setNativeVisible(visible);
}

void EditBoxImplCommon::setContentSize(const Size& size)
{
    _contentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
    placeInactiveLabels();
    
    auto director = cocos2d::CCDirector::sharedDirector();
    auto glview = director->getOpenGLView();
    Size  controlSize = Size(size.width * glview->getScaleX(),size.height * glview->getScaleY());
       
    this->setNativeContentSize(controlSize);

}

// void EditBoxImplCommon::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
// {
//     if(flags)
//     {
//         auto rect = ui::UIHelper::convertBoundingBoxToScreen(_editBox);
//         this->updateNativeFrame(rect);
//     }
// }

void EditBoxImplCommon::visit()
{
    auto rect = cocos2d::ui::UIHelper::convertBoundingBoxToScreen(m_pEditBox);
    this->updateNativeFrame(rect);   
}

void EditBoxImplCommon::onEnter(void)
{
    const char* pText = getText();
    if (pText) {
        setInactiveText(pText);
    }
}

void EditBoxImplCommon::openKeyboard()
{
    _label->setVisible(false);
    _labelPlaceHolder->setVisible(false);

    this->nativeOpenKeyboard();
}

void EditBoxImplCommon::closeKeyboard()
{
    this->nativeCloseKeyboard();
}

void EditBoxImplCommon::onEndEditing(const std::string& text)
{
    this->setNativeVisible(false);
    
    if(text.size() == 0)
    {
        _label->setVisible(false);
        _labelPlaceHolder->setVisible(true);
    }
    else
    {
        _label->setVisible(true);
        _labelPlaceHolder->setVisible(false);
        setInactiveText(text.c_str());
    }
}
    
void EditBoxImplCommon::editBoxEditingDidBegin()
{
    // LOGD("textFieldShouldBeginEditing...");
    CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();
    
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidBegin(m_pEditBox);
    }
    
//#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != m_pEditBox && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        // cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "began", m_pEditBox);
        // cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        // cocos2d::ScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->sendEvent(&event);

        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        int handler = m_pEditBox->getScriptEditBoxHandler();
        pEngine->executeEvent(handler, "began",m_pEditBox);
    }
//#endif
}


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

void EditBoxImplCommon::editBoxEditingDidEnd(const std::string& text)
{
    // LOGD("textFieldShouldEndEditing...");
    _text = text;
    this->refreshInactiveText();
    
    CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidEnd(m_pEditBox);
//        pDelegate->editBoxReturn(m_pEditBox);
    }
    
    if (m_pEditBox != nullptr)
    {
        this->onEndEditing(text);
    }

//#if CC_ENABLE_SCRIPT_BINDING
    if (m_pEditBox != nullptr && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        //cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "ended", m_pEditBox);
        //cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        //CCScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
        //memset(data.eventName, 0, sizeof(data.eventName));
        //strncpy(data.eventName, "return", sizeof(data.eventName));
        //event.data = (void *)&data;
        //CCScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);

        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        int handler = m_pEditBox->getScriptEditBoxHandler();
        //pEngine->executeEvent(handler, "returnSend",m_pEditBox);   
        pEngine->executeEvent(handler, "ended",m_pEditBox);
//        cocos2d::extension::KeyboardReturnType returnType = m_pEditBox->getReturnType();
//        if (returnType == cocos2d::extension::kKeyboardReturnTypeDone)
//        {
//           pEngine->executeEvent(handler, "returnDone", m_pEditBox);
//        }
//        else if (returnType == cocos2d::extension::kKeyboardReturnTypeSend)
//        {
//           pEngine->executeEvent(handler, "returnSend", m_pEditBox);
//        }
//        else if (returnType == cocos2d::extension::kKeyboardReturnTypeSearch)
//        {
//           pEngine->executeEvent(handler, "returnSearch", m_pEditBox);
//        }
//        else if (returnType == cocos2d::extension::kKeyboardReturnTypeGo)
//        {
//           pEngine->executeEvent(handler, "returnGo", m_pEditBox);
//        }
//        else
//        {
//           pEngine->executeEvent(handler, "return", m_pEditBox);
//        }
        

    }
//#endif
    //在事件里会删除自己所以不能把东西放在事件后面了
    // if (m_pEditBox != nullptr)
    // {
    //     this->onEndEditing(text);
    // }

}


void EditBoxImplCommon::editBoxEditingDidReturn(const std::string& text)
{
    
    CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();
    if (pDelegate != nullptr)
    {
//        pDelegate->editBoxEditingDidEnd(m_pEditBox);
        pDelegate->editBoxReturn(m_pEditBox);
    }
    
    
    //#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != m_pEditBox && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        // cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "changed", m_pEditBox);
        // cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        // CCScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        int handler = m_pEditBox->getScriptEditBoxHandler();
        pEngine->executeEvent(handler, "returnSend",m_pEditBox);
    }
    //#endif
}


void EditBoxImplCommon::editBoxEditingChanged(const std::string& text)
{
    // LOGD("editBoxTextChanged...");
    CCEditBoxDelegate *pDelegate = m_pEditBox->getDelegate();
    _text = text;
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxTextChanged(m_pEditBox, text);
    }
    
//#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != m_pEditBox && 0 != m_pEditBox->getScriptEditBoxHandler())
    {
        // cocos2d::CommonScriptData data(m_pEditBox->getScriptEditBoxHandler(), "changed", m_pEditBox);
        // cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        // CCScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        int handler = m_pEditBox->getScriptEditBoxHandler();
        pEngine->executeEvent(handler, "changed",m_pEditBox);
    }
//#endif
}


//}

NS_CC_EXT_END


