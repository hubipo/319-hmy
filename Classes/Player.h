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
#ifndef __PLAYER_H__
#define __PLAYER_H__
//constexpr int MY_HP = 100;

#include"cocos2d.h"

class Player : public cocos2d::Node {
public:
    virtual bool init();

    void onMouseDown(cocos2d::EventMouse* event);

    cocos2d::Node* createHealthBar();

    void takeDamage();
private:
    cocos2d::Sprite* PlayerSprite;
    float moveSpeed = 200.0f; // ССӢ�۵��ƶ��ٶ�

    cocos2d::ProgressTimer* bloodBar;
    float currentHealth;//ССӢ�۵�ǰ��Ѫ��
};
/*
class GameScene : public cocos2d::Scene {
public:
    virtual bool init() {
        if (!Scene::init()) {
            return false;
        }

        // ����Ӣ��
        auto hero = Hero::create();
        this->addChild(hero);

        return true;
    }
};*/
#endif //!__PLAYER_H__