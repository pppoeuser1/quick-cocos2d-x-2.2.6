/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.
 
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

/// @cond DO_NOT_SHOW

#include "UIWebView.h"
#include "CCLuaEngine.h"

NS_CC_EXT_BEGIN
        WebView::WebView()
        : _impl(new WebViewImpl(this)),
        _onJSCallback(nullptr),
        _onShouldStartLoading(nullptr),
        _onDidFinishLoading(nullptr),
        _onDidFailLoading(nullptr),
        _LuaHandlerJSCallback(-1),
        _LuaHandlerOnShouldStartLoading(-1),
        _LuaHandlerOnDidFinishLoading(-1),
        _LuaHandlerOnDidFailLoading(-1)
        {
            setContentSize(CCDirector::sharedDirector()->getWinSize());
            
            _onJSCallback = [this](WebView *sender, const std::string &url) {
                _currurl =url;
//                if(_LuaHandlerJSCallback!=-1){
//                    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
//                    stack->pushCCObject(this, "WebView");
//                    stack->pushString(url.c_str());
//                    stack->executeFunctionByHandler(_LuaHandlerJSCallback, 2);
//                    stack->clean();
//                }
                auto sharedScheduler = CCDirector::sharedDirector()->getScheduler();
                sharedScheduler->scheduleSelector(schedule_selector(WebView::onceSchedulerCallback), this, 0, 0, 0, false);
            };
            
            _onShouldStartLoading = [this](WebView *sender, const std::string &url) {
                _currurlStart = url;
                auto sharedScheduler = CCDirector::sharedDirector()->getScheduler();
                sharedScheduler->scheduleSelector(schedule_selector(WebView::onceScheduler_Start), this, 0, 0, 0, false);
                return true;
            };
            
            _onDidFinishLoading = [this](WebView *sender, const std::string &url) {
                _currurlFinish = url;
                auto sharedScheduler = CCDirector::sharedDirector()->getScheduler();
                sharedScheduler->scheduleSelector(schedule_selector(WebView::onceScheduler_Finish), this, 0, 0, 0, false);
            };
            
            _onDidFailLoading = [this](WebView *sender, const std::string &url) {
                _currurlFail = url;
                auto sharedScheduler = CCDirector::sharedDirector()->getScheduler();
                sharedScheduler->scheduleSelector(schedule_selector(WebView::onceScheduler_Fail), this, 0, 0, 0, false);
            };

        }

void WebView::onceSchedulerCallback(float f){
    if(_LuaHandlerJSCallback!=-1){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->pushCCObject(this, "WebView");
        stack->pushString(_currurl.c_str());
        stack->executeFunctionByHandler(_LuaHandlerJSCallback, 2);
        stack->clean();
    }
}

void WebView::onceScheduler_Start(float f){
    if(_LuaHandlerOnShouldStartLoading!=-1){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->pushCCObject(this, "WebView");
        stack->pushString(_currurlStart.c_str());
        stack->executeFunctionByHandler(_LuaHandlerOnShouldStartLoading, 2);
        stack->clean();
    }
}

void WebView::onceScheduler_Finish(float f){
    if(_LuaHandlerOnDidFinishLoading!=-1){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->pushCCObject(this, "WebView");
        stack->pushString(_currurlFinish.c_str());
        stack->executeFunctionByHandler(_LuaHandlerOnDidFinishLoading, 2);
        stack->clean();
    }
}

void WebView::onceScheduler_Fail(float f){
    if(_LuaHandlerOnDidFailLoading!=-1){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->pushCCObject(this, "WebView");
        stack->pushString(_currurlFail.c_str());
        stack->executeFunctionByHandler(_LuaHandlerOnDidFailLoading, 2);
        stack->clean();
    }
}

        WebView::~WebView()
        {
            CC_SAFE_DELETE(_impl);
            if (_LuaHandlerJSCallback!=-1) {
                CCLuaEngine::defaultEngine()->getLuaStack()->removeScriptHandler(_LuaHandlerJSCallback);
                _LuaHandlerJSCallback = -1;
            }
        }
        
        WebView *WebView::create()
        {
            auto webView = new(std::nothrow) WebView();
            if (webView && webView->init())
            {
                webView->autorelease();
                return webView;
            }
            CC_SAFE_DELETE(webView);
            return nullptr;
        }
        
        void WebView::setJavascriptInterfaceScheme(const std::string &scheme)
        {
            _impl->setJavascriptInterfaceScheme(scheme);
        }
        
        void WebView::loadHTMLString(const std::string &string, const std::string &baseURL)
        {
            _impl->loadHTMLString(string, baseURL);
        }
        
        void WebView::loadURL(const std::string &url)
        {
            _impl->loadURL(url);
        }
        
        void WebView::loadFile(const std::string &fileName)
        {
            _impl->loadFile(fileName);
        }
        
        void WebView::stopLoading()
        {
            _impl->stopLoading();
        }
        
        void WebView::reload()
        {
            _impl->reload();
        }
        
        bool WebView::canGoBack()
        {
            return _impl->canGoBack();
        }
        
        bool WebView::canGoForward()
        {
            return _impl->canGoForward();
        }
        
        void WebView::goBack()
        {
            _impl->goBack();
        }
        
        void WebView::goForward()
        {
            _impl->goForward();
        }
        
        void WebView::evaluateJS(const std::string &js)
        {
            _impl->evaluateJS(js);
        }
        
        void WebView::setScalesPageToFit(bool const scalesPageToFit)
        {
            _impl->setScalesPageToFit(scalesPageToFit);
        }
        
        void WebView::draw()
        {
            _impl->draw();
        }

        void WebView::setVisible(bool visible)
        {
            CCNode::setVisible(visible);
            _impl->setVisible(visible);
        }

//        void WebView::copySpecialProperties(CCNode* model)
//        {
//            WebView* webView = dynamic_cast<WebView*>(model);
//            if (webView)
//            {
//                this->_impl = webView->_impl;
//                this->_onShouldStartLoading = webView->_onShouldStartLoading;
//                this->_onDidFinishLoading = webView->_onDidFinishLoading;
//                this->_onDidFailLoading = webView->_onDidFailLoading;
//                this->_onJSCallback = webView->_onJSCallback;
//            }
//        }

//        void WebView::setOnDidFailLoading(const ccWebViewCallback &callback)
//        {
//            _onDidFailLoading = callback;
//        }
//        
//        void WebView::setOnDidFinishLoading(const ccWebViewCallback &callback)
//        {
//            _onDidFinishLoading = callback;
//        }
//        
//        void WebView::setOnShouldStartLoading(const std::function<bool(WebView *sender, const std::string &url)> &callback)
//        {
//            _onShouldStartLoading = callback;
//        }
//        
//        void WebView::setOnJSCallback(const ccWebViewCallback &callback)
//        {
//            _onJSCallback = callback;
//        }

//        std::function<bool(WebView *sender, const std::string &url)> WebView::getOnShouldStartLoading()const
//        {
//            return _onShouldStartLoading;
//        }
//        
//        WebView::ccWebViewCallback WebView::getOnDidFailLoading()const
//        {
//            return _onDidFailLoading;
//        }
//        
//        WebView::ccWebViewCallback WebView::getOnDidFinishLoading()const
//        {
//            return _onDidFinishLoading;
//        }
//        
//        WebView::ccWebViewCallback WebView::getOnJSCallback()const
//        {
//            return _onJSCallback;
//        }

void WebView::setOnJSCallback(int nLuaFunID){
    if (_LuaHandlerJSCallback!=-1) {
        CCLuaEngine::defaultEngine()->getLuaStack()->removeScriptHandler(_LuaHandlerJSCallback);
        _LuaHandlerJSCallback = -1;
    }
    _LuaHandlerJSCallback = nLuaFunID;
}
void WebView::setOnShouldStartLoading(int nLuaFunID){
    if (_LuaHandlerOnShouldStartLoading!=-1) {
        CCLuaEngine::defaultEngine()->getLuaStack()->removeScriptHandler(_LuaHandlerOnShouldStartLoading);
        _LuaHandlerOnShouldStartLoading = -1;
    }
    _LuaHandlerOnShouldStartLoading = nLuaFunID;
}
void WebView::setOnDidFinishLoading(int nLuaFunID){
    if (_LuaHandlerOnDidFinishLoading!=-1) {
        CCLuaEngine::defaultEngine()->getLuaStack()->removeScriptHandler(_LuaHandlerOnDidFinishLoading);
        _LuaHandlerOnDidFinishLoading = -1;
    }
    _LuaHandlerOnDidFinishLoading = nLuaFunID;
}
void WebView::setOnDidFailLoading(int nLuaFunID){
    if (_LuaHandlerOnDidFailLoading!=-1) {
        CCLuaEngine::defaultEngine()->getLuaStack()->removeScriptHandler(_LuaHandlerOnDidFailLoading);
        _LuaHandlerOnDidFailLoading = -1;
    }
    _LuaHandlerOnDidFailLoading = nLuaFunID;
}

NS_CC_EXT_END

/// @endcond
