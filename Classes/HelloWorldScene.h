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
#include "cocos2d.h"
#include "Player.h"
template <typename T>
void createAndAddSprite(T* obj, const std::string& filename, float scale, float x, float y, int Zorder);
template<typename T1, typename T2>
void createAndAddLabel(T1* obj, T2& label, const std::string& filename, float Pos_X, float Pos_Y, int Zorder);
template<typename T1, typename T2>
void modifyMenuItem(T1* obj, T2& MenuItem, float Pos_X, float Pos_Y, float scale, int Zorder);
template<typename T1, typename T2>
void modifySlider(T1* obj, T2& slider, std::string unselected, std::string selected, std::string normal, std::string pressed, std::string disabled, float Pos_X, float Pos_Y, int maxPercent, int curPercent);
template<typename T1, typename T2>
void modifyCheckBox(T1* obj, T2& checkbox, bool selected, float Pos_X, float Pos_Y, float scale);
#ifndef  __SCENE_MENU_H__
#define  __SCENE_MENU_H__
class Scene_menu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuSTART(cocos2d::Ref* pSender);
    void menuSETTINGS(cocos2d::Ref* pSender);
    void menu12up(cocos2d::Ref* pSender);
    CREATE_FUNC(Scene_menu);
};

#endif  __SCENE_MENU_H__

#ifndef  __SCENE_12UP_H__
#define  __SCENE_12UP_H__
class Scene_12up : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void CLOSE(cocos2d::Ref* pSender);
    CREATE_FUNC(Scene_12up);
};

#endif  __SCENE_12UP_H__

#ifndef __SCENE_SETTING_H__
#define __SCENE_SETTING_H__
class Scene_Setting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void Back_To_Last_Scene(cocos2d::Ref* pSender);
    void End_The_Game(Ref* pSender);
    CREATE_FUNC(Scene_Setting);
};
#endif  __SCENE_SETTING_H__

#ifndef __SCENE_CHESSBOARD_H__
#define __SCENE_CHESSBOARD_H__
class Scene_ChessBoard : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void CARD_CALLBACK(Ref* pSender);
    void onMouseDown_1(cocos2d::EventMouse* event);
    cocos2d::Sprite*getSelectedSprite(const cocos2d::Vec2& clickPosition);
private:
    Player* my_player;
    cocos2d::Sprite* board;
    cocos2d::Sprite* selectedSprite;
    bool isSelected;
    CREATE_FUNC(Scene_ChessBoard);
};

#endif __SCENE_CHESSBOARD_H__