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
//HelloWorldScene �� cocos2d-x �����е�һ��ʾ�����������������б�д��Ϸ�߼�����Ⱦ���롣
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

// HelloWorld �࣬�̳��� cocos2d::Scene
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//һ����̬���������ڴ��� HelloWorld ����

    virtual bool init();//��ʼ��������������Ա�д�����ĳ�ʼ�����롣

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//һ���ص����������ڴ���˵���ť�ĵ���¼���

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);//һ���궨�壬�����Զ�ʵ�ֳ����Ĵ���������
};

#endif // __HELLOWORLD_SCENE_H__

#ifndef  __SCENE_MENU_H__
#define  __SCENE_MENU_H__

#include "cocos2d.h"

// Scene_menu �࣬�̳��� cocos2d::Scene
class Scene_menu : public cocos2d::Scene
{
public:
    // ��̬���������ڴ���һ�� Scene_menu ��������
    static cocos2d::Scene* createScene();

    virtual bool init(); // ��ʼ������������ֵ��ʾ��ʼ���Ƿ�ɹ�

    void menuSTART(cocos2d::Ref* pSender);// ��� Start �˵���ʱ���õķ���

    void menuSETTINGS(cocos2d::Ref* pSender);// ��� Settings �˵���ʱ���õķ���

    void menu12up(cocos2d::Ref* pSender); // ��� 12 Up �˵���ʱ���õķ���

    CREATE_FUNC(Scene_menu); // create() ���������ڴ���������һ�� Scene_menu ��������
};

#endif  // __SCENE_MENU_H__

#ifndef  __SCENE_12UP_H__
#define  __SCENE_12UP_H__

#include "cocos2d.h"
// Scene_12up �࣬�̳��� cocos2d::Scene
class Scene_12up : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void CLOSE(cocos2d::Ref* pSender);
    CREATE_FUNC(Scene_12up);
};

#endif  __SCENE_12UP_H__