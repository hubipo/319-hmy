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

#include "AppDelegate.h"
#include "HelloWorldScene.h"

 // #define USE_AUDIO_ENGINE 1

 // 如果使用音频引擎
#if USE_AUDIO_ENGINE
// 包含 "audio/include/AudioEngine.h"
#include "audio/include/AudioEngine.h"
// 使用命名空间 cocos2d::experimental
using namespace cocos2d::experimental;
#endif

// 使用命名空间 CC
USING_NS_CC;
//好像可以再封装一下下面的内容
// 设定各种分辨率大小
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
static cocos2d::Size gameResolutionSize = cocos2d::Size(900, 800);

// AppDelegate 构造函数
AppDelegate::AppDelegate()
{
}

// AppDelegate 析构函数
AppDelegate::~AppDelegate()
{
    // 如果使用音频引擎
#if USE_AUDIO_ENGINE
// 结束音频引擎
    AudioEngine::end();
#endif
}

// 初始化 OpenGL 上下文属性
void AppDelegate::initGLContextAttrs()
{
    // 设置 OpenGL 上下文属性: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    // 设置 GLView 的 GL 上下文属性
    GLView::setGLContextAttrs(glContextAttrs);
}

// 注册所有的包
static int register_all_packages()
{
    // 返回 0 表示包管理器的标志
    return 0; //flag for packages manager
}

// 应用程序完成启动
bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化导演
    auto director = Director::getInstance();
    // 获取 OpenGL 视图
    auto glview = director->getOpenGLView();
    // 如果没有 OpenGL 视图
    if (!glview) {
        // 如果目标平台是 Windows, Mac 或 Linux
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
// 创建一个新的 OpenGL 视图
        glview = GLViewImpl::createWithRect("game1", cocos2d::Rect(0, 0, gameResolutionSize.width, gameResolutionSize.height));
        // 否则
#else
// 创建一个新的 OpenGL 视图
        glview = GLViewImpl::create("game1");
#endif
        // 设置导演的 OpenGL 视图
        director->setOpenGLView(glview);
    }

    // 打开 FPS 显示
    director->setDisplayStats(true);

    // 设置 FPS，如果你不调用这个函数，默认值是 1.0/60
    director->setAnimationInterval(1.0f / 60);

    // 设置设计分辨率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    // 获取帧大小
    auto frameSize = glview->getFrameSize();
    // 如果帧的高度大于中等大小的高度
    if (frameSize.height > mediumResolutionSize.height)
    {
        // 设置内容缩放因子
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    // 如果帧的高度大于小尺寸的高度
    else if (frameSize.height > smallResolutionSize.height)
    {
        // 设置内容缩放因子
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    // 如果帧的高度小于中等大小的高度
    else
    {
        // 设置内容缩放因子
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }

    // 注册所有的包
    register_all_packages();

    // 创建一个场景，它是一个自动释放的对象
    auto scene = Scene_menu::createScene();

    // 运行
    director->runWithScene(scene);

    return true;
}



// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
// 当应用程序进入后台时，这个函数会被调用。注意，当接到电话时，它会被调用。
void AppDelegate::applicationDidEnterBackground() {
    // 停止导演的动画
    Director::getInstance()->stopAnimation();

    // 如果使用音频引擎
#if USE_AUDIO_ENGINE
// 暂停所有音频
    AudioEngine::pauseAll();
#endif
}

// 当应用程序再次激活时，这个函数会被调用
void AppDelegate::applicationWillEnterForeground() {
    // 开始导演的动画
    Director::getInstance()->startAnimation();

    // 如果使用音频引擎
#if USE_AUDIO_ENGINE
// 恢复所有音频
    AudioEngine::resumeAll();
#endif
}
