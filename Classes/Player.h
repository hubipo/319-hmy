#pragma once
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
#define MAX_HP 100.0f
#define SPEAD 200.0f
#include"cocos2d.h"

//template<typename T>
//void createHealthBar(T* obj);

class Player : public cocos2d::Sprite
{
public:
    // static cocos2d::Sprite* createPlayer();
    Player() = default;
    ~Player() = default;

    virtual bool init();

    void onMouseDown(cocos2d::EventMouse* event);

    void createHealthBar(Sprite*);

    void takeDamage();

    CREATE_FUNC(Player);

    bool isMoving;
    int currentHealth;//ССӢ�۵�ǰ��Ѫ��
    cocos2d::ProgressTimer* bloodBar;
    
    //bool isAttacked;

    int money=8;

    cocos2d::Label* MONEY = nullptr;
private:
    cocos2d::Sprite* heroSprite;
    float moveSpeed; // ССӢ�۵��ƶ��ٶ�

    
   
};
#endif //!__PLAYER_H__

#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__
class AIPlayer : public cocos2d::Sprite
{
public:
    AIPlayer() = default;
    ~AIPlayer() = default;

    virtual bool init();


    void createHealthBar(Sprite*);

    void takeDamage();

    CREATE_FUNC(AIPlayer);
    
    int currentHealth;//ССӢ�۵�ǰ��Ѫ��
    cocos2d::ProgressTimer* bloodBar;

private:
    cocos2d::Sprite* heroSprite;
};
#endif