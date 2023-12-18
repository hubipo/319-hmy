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
//HelloWorldScene 是 cocos2d-x 引擎中的一个示例场景，可以在其中编写游戏逻辑和渲染代码。
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

// HelloWorld 类，继承自 cocos2d::Scene
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//一个静态函数，用于创建 HelloWorld 场景

    virtual bool init();//初始化函数，这里可以编写场景的初始化代码。

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//一个回调函数，用于处理菜单按钮的点击事件。

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);//一个宏定义，用于自动实现场景的创建方法。
};

#endif // __HELLOWORLD_SCENE_H__

#ifndef  __SCENE_MENU_H__
#define  __SCENE_MENU_H__

#include "cocos2d.h"

// Scene_menu 类，继承自 cocos2d::Scene
class Scene_menu : public cocos2d::Scene
{
public:
    // 静态方法，用于创建一个 Scene_menu 场景对象
    static cocos2d::Scene* createScene();

    virtual bool init(); // 初始化方法，返回值表示初始化是否成功

    void menuSTART(cocos2d::Ref* pSender);// 点击 Start 菜单项时调用的方法

    void menuSETTINGS(cocos2d::Ref* pSender);// 点击 Settings 菜单项时调用的方法

    void menu12up(cocos2d::Ref* pSender); // 点击 12 Up 菜单项时调用的方法

    CREATE_FUNC(Scene_menu); // create() 方法，用于创建并返回一个 Scene_menu 场景对象
};

#endif  // __SCENE_MENU_H__

#ifndef  __SCENE_12UP_H__
#define  __SCENE_12UP_H__

#include "cocos2d.h"
// Scene_12up 类，继承自 cocos2d::Scene
class Scene_12up : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void CLOSE(cocos2d::Ref* pSender);
    CREATE_FUNC(Scene_12up);
};

#endif  __SCENE_12UP_H__