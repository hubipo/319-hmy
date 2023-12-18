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

#ifndef  _APP_DELEGATE_H_  // ��ֹͷ�ļ��ظ�����
#define  _APP_DELEGATE_H_  // ����Ԥ��������

#include "cocos2d.h"  // ����cocos2dͷ�ļ�

 /**
 @brief    The cocos2d Application.  // cocos2dӦ�ó���

 Private inheritance here hides part of interface from Director.  // ˽�м̳�����������������Director�Ĳ��ֽӿ�
 */
class  AppDelegate : private cocos2d::Application  // AppDelegate�࣬˽�м̳���cocos2d::Application
{
public:
    AppDelegate();  // ���캯��
    virtual ~AppDelegate();  // ����������

    virtual void initGLContextAttrs();  // ��ʼ��GL����������

    /**
    @brief    Implement Director and Scene init code here.  // ������ʵ��Director��Scene�ĳ�ʼ������
    @return true    Initialize success, app continue.  // ��ʼ���ɹ���Ӧ�ó������
    @return false   Initialize failed, app terminate.  // ��ʼ��ʧ�ܣ�Ӧ�ó�����ֹ
    */
    virtual bool applicationDidFinishLaunching();  // Ӧ�ó����������

    /**
    @brief  Called when the application moves to the background  // ��Ӧ�ó����ƶ�����̨ʱ����
    @param  the pointer of the application  // Ӧ�ó����ָ��
    */
    virtual void applicationDidEnterBackground();  // Ӧ�ó�������̨

    /**
    @brief  Called when the application reenters the foreground  // ��Ӧ�ó������½���ǰ̨ʱ����
    @param  the pointer of the application  // Ӧ�ó����ָ��
    */
    virtual void applicationWillEnterForeground();  // Ӧ�ó��򽫽���ǰ̨
};

#endif // _APP_DELEGATE_H_  // ������ֹͷ�ļ��ظ�������Ԥ��������```


