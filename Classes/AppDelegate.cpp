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

 // ���ʹ����Ƶ����
#if USE_AUDIO_ENGINE
// ���� "audio/include/AudioEngine.h"
#include "audio/include/AudioEngine.h"
// ʹ�������ռ� cocos2d::experimental
using namespace cocos2d::experimental;
#endif

// ʹ�������ռ� CC
USING_NS_CC;
//��������ٷ�װһ�����������
// �趨���ֱַ��ʴ�С
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
static cocos2d::Size gameResolutionSize = cocos2d::Size(900, 800);

// AppDelegate ���캯��
AppDelegate::AppDelegate()
{
}

// AppDelegate ��������
AppDelegate::~AppDelegate()
{
    // ���ʹ����Ƶ����
#if USE_AUDIO_ENGINE
// ������Ƶ����
    AudioEngine::end();
#endif
}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs()
{
    // ���� OpenGL ����������: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    // ���� GLView �� GL ����������
    GLView::setGLContextAttrs(glContextAttrs);
}

// ע�����еİ�
static int register_all_packages()
{
    // ���� 0 ��ʾ���������ı�־
    return 0; //flag for packages manager
}

// Ӧ�ó����������
bool AppDelegate::applicationDidFinishLaunching() {
    // ��ʼ������
    auto director = Director::getInstance();
    // ��ȡ OpenGL ��ͼ
    auto glview = director->getOpenGLView();
    // ���û�� OpenGL ��ͼ
    if (!glview) {
        // ���Ŀ��ƽ̨�� Windows, Mac �� Linux
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
// ����һ���µ� OpenGL ��ͼ
        glview = GLViewImpl::createWithRect("game1", cocos2d::Rect(0, 0, gameResolutionSize.width, gameResolutionSize.height));
        // ����
#else
// ����һ���µ� OpenGL ��ͼ
        glview = GLViewImpl::create("game1");
#endif
        // ���õ��ݵ� OpenGL ��ͼ
        director->setOpenGLView(glview);
    }

    // �� FPS ��ʾ
    director->setDisplayStats(true);

    // ���� FPS������㲻�������������Ĭ��ֵ�� 1.0/60
    director->setAnimationInterval(1.0f / 60);

    // ������Ʒֱ���
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    // ��ȡ֡��С
    auto frameSize = glview->getFrameSize();
    // ���֡�ĸ߶ȴ����еȴ�С�ĸ߶�
    if (frameSize.height > mediumResolutionSize.height)
    {
        // ����������������
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    // ���֡�ĸ߶ȴ���С�ߴ�ĸ߶�
    else if (frameSize.height > smallResolutionSize.height)
    {
        // ����������������
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    // ���֡�ĸ߶�С���еȴ�С�ĸ߶�
    else
    {
        // ����������������
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }

    // ע�����еİ�
    register_all_packages();

    // ����һ������������һ���Զ��ͷŵĶ���
    auto scene = Scene_menu::createScene();

    // ����
    director->runWithScene(scene);

    return true;
}



// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
// ��Ӧ�ó�������̨ʱ����������ᱻ���á�ע�⣬���ӵ��绰ʱ�����ᱻ���á�
void AppDelegate::applicationDidEnterBackground() {
    // ֹͣ���ݵĶ���
    Director::getInstance()->stopAnimation();

    // ���ʹ����Ƶ����
#if USE_AUDIO_ENGINE
// ��ͣ������Ƶ
    AudioEngine::pauseAll();
#endif
}

// ��Ӧ�ó����ٴμ���ʱ����������ᱻ����
void AppDelegate::applicationWillEnterForeground() {
    // ��ʼ���ݵĶ���
    Director::getInstance()->startAnimation();

    // ���ʹ����Ƶ����
#if USE_AUDIO_ENGINE
// �ָ�������Ƶ
    AudioEngine::resumeAll();
#endif
}
