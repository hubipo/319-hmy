/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef  _APP_DELEGATE_H_  // 防止头文件重复包含
#define  _APP_DELEGATE_H_  // 定义预处理器宏

#include "cocos2d.h"  // 包含cocos2d头文件

 /**
 @brief    The cocos2d Application.  // cocos2d应用程序

 Private inheritance here hides part of interface from Director.  // 私有继承在这里隐藏了来自Director的部分接口
 */
class  AppDelegate : private cocos2d::Application  // AppDelegate类，私有继承自cocos2d::Application
{
public:
    AppDelegate();  // 构造函数
    virtual ~AppDelegate();  // 虚析构函数

    virtual void initGLContextAttrs();  // 初始化GL上下文属性

    /**
    @brief    Implement Director and Scene init code here.  // 在这里实现Director和Scene的初始化代码
    @return true    Initialize success, app continue.  // 初始化成功，应用程序继续
    @return false   Initialize failed, app terminate.  // 初始化失败，应用程序终止
    */
    virtual bool applicationDidFinishLaunching();  // 应用程序完成启动

    /**
    @brief  Called when the application moves to the background  // 当应用程序移动到后台时调用
    @param  the pointer of the application  // 应用程序的指针
    */
    virtual void applicationDidEnterBackground();  // 应用程序进入后台

    /**
    @brief  Called when the application reenters the foreground  // 当应用程序重新进入前台时调用
    @param  the pointer of the application  // 应用程序的指针
    */
    virtual void applicationWillEnterForeground();  // 应用程序将进入前台
};

#endif // _APP_DELEGATE_H_  // 结束防止头文件重复包含的预处理器宏```


