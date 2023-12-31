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
#include "network/HttpClient.h"
#include "network/SocketIO.h"
#include "myHero.h"
#define BATTLETIME 15
#define REMAININGTIME 15
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
template<typename T>
void createStoreHero(T* obj, Hero* hero, float Pos_X, float Pos_Y);
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
    void sendHttpRequest();
    void onHttpRequestCompleted(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
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
    void onMouseDown_1(cocos2d::EventMouse* event);
    Hero* getSelectedSoldier(const cocos2d::Vec2& clickPosition);
    void updateTimer(float dt);
    void updateBattleTimer(float dt);
    void startBattle();
    void endBattle();   
    void refreshStore();
    void refreshSeat();
    void refreshcallback(Ref* pSender);
    void refreshBoard(int order);
    bool isInside(cocos2d::Rect Pos);
    void deleteStore();
    cocos2d::Vec2 HeroPosInBoard(cocos2d::Vec2 clickPos);
    cocos2d::Vec2 HeroPosInSeat(cocos2d::Vec2 clickPos);
    Hero* randomSprite();
    std::vector< Hero*> HeroInScene;
    void update(float deltaTime);
    
private:
    int Pos[8];
    Hero* InChessBoard[4][8];
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Rect boardRange;
    cocos2d::Rect storeRange;
    cocos2d::Rect seatRange;
    cocos2d::Rect rubbishRange;
    cocos2d::Sprite* STORE;
    cocos2d::Sprite* board;
    cocos2d::Sprite* rubbish_can;
    cocos2d::Label* TimeLabel;
    //cocos2d::Vec2 storePos;
    //Hero* store_1;
    //Hero* store_2;
    Hero* selectedSprite;
    float remainingTime;
    float battleTime;
    Player* my_player;
    bool isSelected;
    CREATE_FUNC(Scene_ChessBoard);
};

#endif __SCENE_CHESSBOARD_H__