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

#include "HelloWorldScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "myHero.h"
 /**************************/
 /*模板函数*/
 //添加精灵
template <typename T>
void createAndAddSprite(T* obj, const std::string& filename, float scale, float x, float y, int Zorder)
{
    auto sprite = Sprite::create(filename);
    sprite->setScale(scale);
    if (sprite == nullptr) {
        problemLoading("HelloWorld.png");
    }
    else {
        sprite->setPosition(Vec2(x, y));
        obj->addChild(sprite, Zorder);
    }
}
//添加标签
template<typename T1, typename T2>
void createAndAddLabel(T1* obj, T2& label, const std::string& filename, float Pos_X, float Pos_Y, int Zorder)
{
    label = Label::createWithTTF(filename, "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        label->setPosition(Vec2(Pos_X, Pos_Y));
        obj->addChild(label, Zorder);
    }
}
//添加菜单按钮
template<typename T1, typename T2>
void modifyMenuItem(T1* obj, T2& MenuItem, float Pos_X, float Pos_Y, float scale, int Zorder)
{
    MenuItem->setScale(scale);
    if (MenuItem == nullptr || MenuItem->getContentSize().width <= 0 || MenuItem->getContentSize().height <= 0)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        MenuItem->setPosition(Vec2(Pos_X, Pos_Y));
    }
    auto menu = Menu::create(MenuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    obj->addChild(menu, Zorder);
}
//复选框
template<typename T1, typename T2>
void modifyCheckBox(T1* obj, T2& checkbox, bool selected, float Pos_X, float Pos_Y, float scale)
{
    checkbox->setScale(scale);
    checkbox->setPosition(Vec2(Pos_X, Pos_Y));
    checkbox->setSelected(selected);
    obj->addChild(checkbox);
}
//进度条
template<typename T1, typename T2>
void modifySlider(T1* obj, T2& slider, std::string unselected, std::string selected, std::string normal, std::string pressed, std::string disabled, float Pos_X, float Pos_Y, int maxPercent, int curPercent)
{
    slider->loadBarTexture(unselected);;
    slider->loadSlidBallTextures(normal, pressed, disabled);
    slider->loadProgressBarTexture(selected);
    slider->setPosition(Vec2(Pos_X, Pos_Y));
    slider->setMaxPercent(maxPercent);
    slider->setPercent(curPercent);
    obj->addChild(slider);
}
//无实例的一个精灵
template<typename T> 
void createStoreHero(T*obj,Hero*hero,float Pos_X,float Pos_Y)
{
    auto store = hero;
    store->setPosition(Pos_X, Pos_Y);
    obj->addChild(store);
}
/***********************/
/*全局变量*/
int audio;//背景音


/***********************/
USING_NS_CC;
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
/********************************/
//Scene_menu
/********************************/
Scene* Scene_menu::createScene()
{
    return Scene_menu::create();
}
bool Scene_menu::init()
{
    if (!Scene::init())
        return false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    audio = AudioEngine::play2d("Mymuuuuusic.mp3", true);

    sendHttpRequest();
    /********/
    /*Sprite*/
    /********/
    createAndAddSprite(this, "background_menu.png", 3.0f, visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y, -1);
    createAndAddSprite(this, "menu_1.png", 0.8f, origin.x + visibleSize.width * 1.8 / 10, origin.y + visibleSize.height / 10, 0);
    createAndAddSprite(this, "menu_2.png", 0.8f, origin.x + visibleSize.width * 8.3 / 10.0, origin.y + visibleSize.height / 10, 0);
    createAndAddSprite(this, "menu_3.png", 1.3f, origin.x + visibleSize.width * 1.8 / 10, origin.y + visibleSize.height * 6.5 / 10, 0);
    //createAndAddSprite(this, "menu_4.png", 1.3f, origin.x + visibleSize.width * 8.3 / 10, origin.y + visibleSize.height * 6.5 / 10, 0);
    auto menu_4 = Sprite::create("menu_4.png");
    menu_4->setScale(1.3f);
    if (menu_4 == nullptr) {
        problemLoading("HelloWorld.png");
    }
    else {
        menu_4->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height * 6.5 / 10));
        this->addChild(menu_4, 0);
    }
    auto moveAction = MoveTo::create(1.0f, Vec2(origin.x + visibleSize.width * 8.3 / 10, origin.y + visibleSize.height * 6.5 / 10));
    auto actionSequence = Sequence::create(moveAction, nullptr);
    menu_4->runAction(actionSequence);
    /*******/
    /*Label*/
    /*******/
    Label* signal;
    createAndAddLabel(this, signal, "Teamfight Tactics", origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 9 / 10.0, 0);
    signal->enableOutline(Color4B::RED, 1);
    /**********/
    /*menuItem*/
    /**********/
    auto START = MenuItemImage::create("START_menu.png", "START_menu.png", CC_CALLBACK_1(Scene_menu::menuSTART, this));
    modifyMenuItem(this, START, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10, 2.0f, 1);
    auto SETTINGS = MenuItemImage::create("SETTINGS.png", "SETTINGS.png", CC_CALLBACK_1(Scene_menu::menuSETTINGS, this));
    modifyMenuItem(this, SETTINGS, origin.x + visibleSize.width * 9.5 / 10.0, origin.y + visibleSize.height * 9.3 / 10, 0.3f, 1);
    auto menu_12up = MenuItemImage::create("12.png", "12.png", CC_CALLBACK_1(Scene_menu::menu12up, this));
    modifyMenuItem(this, menu_12up, origin.x + visibleSize.width / 10, origin.y + visibleSize.height * 8.5 / 10, 0.8f, 1);
    return true;
}
void  Scene_menu::menuSTART(Ref* pSender)
{
    auto HELLOWORLD = Scene_ChessBoard::createScene();
    //Director::getInstance()->replaceScene(HELLOWORLD);
    // 0*3黑色 255*3白色
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, HELLOWORLD, Color3B(0, 0, 0)));
}
void  Scene_menu::menuSETTINGS(Ref* pSender)
{
    //需要跳到settings中
    auto SETTINGS = Scene_Setting::createScene();
    Director::getInstance()->pushScene(TransitionCrossFade::create(1, SETTINGS));
}
void Scene_menu::menu12up(Ref* pSender)
{
    auto scene_12up = Scene_12up::create();
    Director::getInstance()->pushScene(TransitionCrossFade::create(1, scene_12up));
}
void Scene_menu::sendHttpRequest()
{
    std::string url = "https://1.tongji.edu.cn/data";  // 设置你要请求的URL

    // 创建一个HTTP请求实例
    auto request = new network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::GET);

    // 设置回调函数，用于处理HTTP响应
    request->setResponseCallback(CC_CALLBACK_2(Scene_menu::onHttpRequestCompleted, this));

    // 发送HTTP请求
    network::HttpClient::getInstance()->send(request);
    request->release();  // 释放请求实例
}
void Scene_menu::onHttpRequestCompleted(network::HttpClient* client, network::HttpResponse* response)
{
    if (!response)
    {
        // 处理请求失败的情况
        return;
    }

    if (!response->isSucceed())
    {
        // 处理服务器返回的错误码
        log("HttpRequest error: %s", response->getErrorBuffer());
        return;
    }

    // 处理服务器返回的数据
    std::vector<char>* data = response->getResponseData();
    std::string result(data->begin(), data->end());
    log("Http response: %s", result.c_str());
}
/**********/
//Scene_12up
/**********/
Scene* Scene_12up::createScene()
{
    return Scene_12up::create();
}
bool Scene_12up::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /********/
    auto Scene_12up = MenuItemImage::create("12up.png", "12up.png", CC_CALLBACK_1(Scene_12up::CLOSE, this));
    modifyMenuItem(this, Scene_12up, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 2.0f, 1);
    return true;
}
void Scene_12up::CLOSE(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/********************************/
//Scene_Setting
/********************************/
Scene* Scene_Setting::createScene()
{
    return Scene_Setting::create();
}
bool Scene_Setting::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   

    Label* Sound;
    createAndAddLabel(this, Sound, "Sound", origin.x + visibleSize.width / 3.0, origin.y + visibleSize.height * 7.5 / 10.0, 1);
    Sound->enableShadow();
    Sound->setColor(Color3B::RED);

    Label* CLOSE;
    createAndAddLabel(this, CLOSE, "END GAME", origin.x + visibleSize.width * 8.0 / 10, origin.y + visibleSize.height * 9.2 / 10.0, 1);
    CLOSE->setScale(0.55f);
    CLOSE->setColor(Color3B(0, 191, 255));
    CLOSE->enableOutline(Color4B::BLACK, 1);

    createAndAddSprite(this, "Setting_background.png", 2.0f, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 0);
    auto BACK = MenuItemImage::create("Back.png", "Back.png", CC_CALLBACK_1(Scene_Setting::Back_To_Last_Scene, this));
    modifyMenuItem(this, BACK, origin.x + visibleSize.width / 10, origin.y + visibleSize.height * 9.2 / 10.0, 0.7f, 1);
    auto close = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Scene_Setting::End_The_Game, this));
    modifyMenuItem(this, close, origin.x + visibleSize.width * 9 / 10, origin.y + visibleSize.height * 9.2 / 10.0, 3.0f, 1);
    //创建一个复选框
    auto checkbox = ui::CheckBox::create("Sound_1.png",
        "Sound_2.png",
        "Sound_4.png",
        "Sound_4.png",
        "Sound_4.png");
    modifyCheckBox(this, checkbox, true, origin.x + visibleSize.width * 0.7 / 3.0, origin.y + visibleSize.height * 7.5 / 10.0, 1.8f);
    checkbox->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
        {
            switch (type)
            {
            case ui::CheckBox::EventType::UNSELECTED:
                AudioEngine::pause(audio);
                break;
            case ui::CheckBox::EventType::SELECTED:
                // 播放音乐
                AudioEngine::resume(audio);
                break;
            default:
                break;
            }
        });
    // 创建一个滑动条
    auto slider = ui::Slider::create();
    modifySlider(this, slider, "huadongtiao_1.png", "hongtiao.png", "huadongtiao_3.png", "huadongtiao_5.png"
        , "huadongtiao_4", origin.x + visibleSize.width * 1.5 / 3.0, origin.y + visibleSize.height * 7.5 / 10.0, 100, 50);
    float percent = 50.0;
    float volume = 0.5f;
    // 设置音乐的音量大小
    AudioEngine::setVolume(audio, volume);

    Label* DISPLAY_V;
    std::string text = std::to_string(static_cast<int>(percent));
    createAndAddLabel(this, DISPLAY_V, text,
        origin.x + visibleSize.width * 2.0 / 3.0,
        origin.y + visibleSize.height * 7.5 / 10.0, 1);

    DISPLAY_V->setColor(Color3B::RED);
    DISPLAY_V->enableShadow();
    slider->addEventListener([=](Ref* sender, ui::Slider::EventType type)
        {
            if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
            {
                // 当滑动条的值发生变化时，执行相应的操作
                float percent = slider->getPercent();
                // 计算音量大小
                float volume = percent / 100.0f;
                // 设置音乐的音量大小
                AudioEngine::setVolume(audio, volume);

                // 将数值转换为字符串
                std::string text = std::to_string(static_cast<int>(percent));
                DISPLAY_V->setString(text);
            }
        });
    return true;
}
void Scene_Setting::Back_To_Last_Scene(Ref* pSender)
{
    Director::getInstance()->popScene();
}
void Scene_Setting::End_The_Game(Ref* pSender)
{
    Director::getInstance()->end();
}
/********************************/
//Ai_Scene1
/********************************/
/*
void Ai_Scene1::buyNewHero() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (round1 == 2) {
        auto soldier2 = Soldier::create();
        soldier2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 50, origin.y + visibleSize.height / 2 + 10));
        this->addChild(soldier2, 0);
    }
    round1++;

}*/
bool Ai_Scene1::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Ai[i][j] = nullptr;
        }
    }
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
    float gridSize = visibleSize.width * 0.0535;
    auto tank = Tank::create();
    Ai[0][4] = dynamic_cast<Hero*>(tank);
    auto soldier = Soldier::create();
    Ai[0][5] = dynamic_cast<Hero*>(soldier);
    auto assassin = Assassin::create();
    Ai[1][7] = dynamic_cast<Hero*>(assassin);
    auto shooter = Shooter::create();
    Ai[2][5] = dynamic_cast<Hero*>(shooter);
    auto tank2 = Tank::create();
    Ai[0][2] = dynamic_cast<Hero*>(tank2);
    createAndAddSprite(this, "board-2d.png", 1.135f, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 0);
    auto BACK = MenuItemImage::create("aiview.png", "aiview.png", CC_CALLBACK_1(Ai_Scene1::Back_To_Last_Scene, this));
    modifyMenuItem(this, BACK, origin.x + visibleSize.width / 10, origin.y + visibleSize.height * 9.2 / 10.0, 1.5f, 1);
    //**++++++++++++++++++++++++++++++++++++++//
   

    viewPlayer = Player::create();
    viewPlayer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(viewPlayer, 2);
    /*
    createAndAddLabel(this, ROUND, "", origin.x + visibleSize.width / 2, visibleSize.height * 9.7 / 10.0, 2);
    ROUND->setColor(Color3B::BLUE);
    ROUND->setString("ROUND " + std::to_string(round2));
    */
    //++++++++++++++++++++++++++++++++++++++
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ai[i][j] != nullptr)
            {
                this->addChild(Ai[i][j]);
                Ai[i][j]->setPosition(originPos.x + gridSize * (8 - (4.5 + i)), originPos.y + gridSize * (8 - (0.5 + j)));
                Ai[i][j]->setVisible(1);
                Ai[i][j]->setScale(0.3f);
                Ai[i][j]->Flag = ENEMY_FLAG;
            }
        }
    }
    //MenuItemImage* eye = MenuItemImage::create("menu_1.png", "menu_1.png", CC_CALLBACK_1(Ai_Scene1::eye, this));
    //modifyMenuItem(this, eye, visibleSize .width*0.5,visibleSize.height*0.5, 1.0f, 1);
    return true;
}
/*void Ai_Scene1::eye(Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
    float gridSize = visibleSize.width * 0.0535;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ai[i][j] != nullptr)
            {
                this->addChild(Ai[i][j]);
                Ai[i][j]->setPosition(originPos.x + gridSize * (4.5 + i), originPos.y + gridSize * (0.5 + j));
                Ai[i][j]->setScale(0.3f);
                Ai[i][j]->setVisible(1);
                Ai[i][j]->Flag = ENEMY_FLAG;
            }
        }
    }
}*/

Scene* Ai_Scene1::createScene() {

    return Ai_Scene1::create();
}
void Ai_Scene1::Back_To_Last_Scene(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/********************************/
//Ai_Scene2
/********************************/
bool Ai_Scene2::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto tank = Tank::create();
    Ai[0][4] = dynamic_cast<Hero*>(tank);
    auto soldier = Soldier::create();
    Ai[0][5] = dynamic_cast<Hero*>(soldier);
    auto assassin = Assassin::create();
    Ai[1][7] = dynamic_cast<Hero*>(assassin);
    auto shooter = Shooter::create();
    Ai[2][5] = dynamic_cast<Hero*>(shooter);
    auto tank2 = Tank::create();
    Ai[0][2] = dynamic_cast<Hero*>(tank2);
    auto shooter2 = Shooter::create();
    Ai[3][0] = dynamic_cast<Hero*>(shooter2);
    createAndAddSprite(this, "board-2d.png", 1.135f, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 0);
    auto BACK = MenuItemImage::create("aiview.png", "aiview.png", CC_CALLBACK_1(Ai_Scene2::Back_To_Last_Scene, this));
    modifyMenuItem(this, BACK, origin.x + visibleSize.width / 10, origin.y + visibleSize.height * 9.2 / 10.0, 1.5f, 1);
    //**++++++++++++++++++++++++++++++++++++++//
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
    float gridSize = visibleSize.width * 0.0535;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ai[i][j] != nullptr)
            {
                this->addChild(Ai[i][j]);
                Ai[i][j]->setPosition(originPos.x + gridSize * (8 - (4.5 + i)), originPos.y + gridSize * (8 - (0.5 + j)));
                Ai[i][j]->setScale(0.3f);
                Ai[i][j]->setVisible(1);
                Ai[i][j]->Flag = ENEMY_FLAG;
            }
        }
    }
    Label* ROUND = new Label;

    viewPlayer = Player::create();
    viewPlayer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(viewPlayer, 2);
   

    /*
    createAndAddLabel(this, ROUND, "", origin.x + visibleSize.width / 2, visibleSize.height * 9.7 / 10.0, 2);
    ROUND->setColor(Color3B::BLUE);
    ROUND->setString("ROUND " + std::to_string(round2));
    */
    //++++++++++++++++++++++++++++++++++++++

    return true;
}

Scene* Ai_Scene2::createScene() {

    return Ai_Scene2::create();
}
void Ai_Scene2::Back_To_Last_Scene(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/********************************/
//Ai_Scene3
/********************************/
bool Ai_Scene3::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto tank = Tank::create();
    Ai[0][4] = dynamic_cast<Hero*>(tank);
    auto soldier = Soldier::create();
    Ai[0][5] = dynamic_cast<Hero*>(soldier);
    auto assassin = Assassin::create();
    Ai[1][7] = dynamic_cast<Hero*>(assassin);
    auto shooter = Shooter::create();
    Ai[2][5] = dynamic_cast<Hero*>(shooter);
    auto tank2 = Tank::create();
    Ai[0][2] = dynamic_cast<Hero*>(tank2);
    auto shooter2 = Shooter::create();
    Ai[3][0] = dynamic_cast<Hero*>(shooter2);
    auto soldier2= Soldier::create();
    Ai[1][1] = dynamic_cast<Hero*>(soldier2);
    auto soldier3 = Soldier::create();
    Ai[1][6] = dynamic_cast<Hero*>(soldier3);
    auto assassin2 = Assassin::create();
    Ai[0][0] = dynamic_cast<Hero*>(assassin2);
    auto shooter3 = Shooter::create();
    Ai[3][1] = dynamic_cast<Hero*>(shooter3);
    auto assassin3 = Assassin::create();
    Ai[1][4] = dynamic_cast<Hero*>(assassin3);

    createAndAddSprite(this, "board-2d.png", 1.135f, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 0);
    auto BACK = MenuItemImage::create("aiview.png", "aiview.png", CC_CALLBACK_1(Ai_Scene3::Back_To_Last_Scene, this));
    modifyMenuItem(this, BACK, origin.x + visibleSize.width / 10, origin.y + visibleSize.height * 9.2 / 10.0, 1.5f, 1);
    //**++++++++++++++++++++++++++++++++++++++//
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
    float gridSize = visibleSize.width * 0.0535;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ai[i][j] != nullptr)
            {
                this->addChild(Ai[i][j]);
                Ai[i][j]->setPosition(originPos.x + gridSize *(8-(4.5 + i)), originPos.y + gridSize * (8-(0.5 + j)));
                Ai[i][j]->setScale(0.3f);
                Ai[i][j]->setVisible(1);
                Ai[i][j]->Flag = ENEMY_FLAG;
            }
        }
    }
    Label* ROUND = new Label;
    
    viewPlayer = Player::create();
    viewPlayer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(viewPlayer, 2);
    /*
    createAndAddLabel(this, ROUND, "", origin.x + visibleSize.width / 2, visibleSize.height * 9.7 / 10.0, 2);
    ROUND->setColor(Color3B::BLUE);
    ROUND->setString("ROUND " + std::to_string(round2));
    */
    //++++++++++++++++++++++++++++++++++++++

    return true;
}

Scene* Ai_Scene3::createScene() {

    return Ai_Scene3::create();
}
void Ai_Scene3::Back_To_Last_Scene(Ref* pSender)
{
    Director::getInstance()->popScene();
}

/********************************/
//BOOK
/********************************/
Scene* Scene_Book::createScene() 
{
    return Scene::create();
}
bool Scene_Book::init()
{
    if (!Scene::init())
    {
        return false;
    }  
    auto visibleSize = Director::getInstance()->getVisibleSize();
    MenuItemImage* book = MenuItemImage::create("list.png", "list.png", CC_CALLBACK_1(Scene_Book::Back_To_Last_Scene, this));
    modifyMenuItem(this, book, visibleSize.width * 0.57, visibleSize.height * 0.5, 1.135f, 0);
    return true;
}
void Scene_Book::Back_To_Last_Scene(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/********************************/
//Scene_ChessBoard
/********************************/
Scene* Scene_ChessBoard::createScene()
{
    return Scene_ChessBoard::create();
}
bool Scene_ChessBoard::init()
{
    if (!Scene::init())
    {
        return false;
    }
   
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    for (int i = 0; i < 8; i++)
    {
        Pos[i] = 0;
    }
    //计时
    remainingTime = REMAININGTIME;
    battleTime = BATTLETIME; // 对战时间为1分钟
    this->schedule(CC_SCHEDULE_SELECTOR(Scene_ChessBoard::updateTimer), 1.0f);
    // 创建显示剩余时间的Label
    createAndAddLabel(this, TimeLabel, "", origin.x + visibleSize.width * 1.3 / 10.0, origin.y + visibleSize.height * 9.7 / 10.0, 2);
    /*TimeLabel = Label::createWithSystemFont("", "fonts/Marker Felt.ttf", 24);
    TimeLabel->setPosition(Vec2(origin.x + visibleSize.width*1.3/10.0, origin.y+visibleSize.height*9.8/10.0 ));*/
    TimeLabel->enableOutline(Color4B::MAGENTA,1);
    TimeLabel->setScale(0.5f);
    //this->addChild(TimeLabel,2);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            InChessBoard[i][j] = nullptr;
            Ai1[i][j] = nullptr;
        }
    }
    
    ///////

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Scene_ChessBoard::menuCloseCallback, this));
    modifyMenuItem(this, closeItem, origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2, 1.0f, 1);
    auto refresh_store = MenuItemImage::create("refresh_store.png","refresh_Store_click.png",CC_CALLBACK_1(Scene_ChessBoard::refreshcallback, this));
    modifyMenuItem(this, refresh_store, visibleSize.width * 0.98, 100, 0.18f, 1);
    auto BOOK = MenuItemImage::create("BOOK.png", "BOOK.png", CC_CALLBACK_1(Scene_ChessBoard::Book, this));
    modifyMenuItem(this, BOOK, visibleSize.width * 0.85, 220, 0.7f, 1);
    //Label* label;
    //createAndAddLabel(this, label, "ChessBoard", origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 9 / 10, 1);

    board = Sprite::create("board-2d.png");
    board->setScale(1.135f);
    if (board == nullptr) {
        problemLoading("HelloWorld.png");
    }
    else {
        board->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(board, 0);
    }

   STORE= Sprite::create("STORE.png");
   //STORE->setScale(0.1f);
    if (STORE == nullptr)
    {
        problemLoading("HelloWorld.png");
    }
    else {
        STORE->setPosition(Vec2(visibleSize.width*0.965,220));
        this->addChild(STORE, 0);
        storeRange.setRect(STORE->getPosition().x - STORE->getContentSize().width / 2, STORE->getPosition().y - STORE->getContentSize().height / 2, STORE->getContentSize().width, STORE->getContentSize().height);
    }
    rubbish_can = Sprite::create("rubbish_can1.png");
    //STORE->setScale(0.1f);
    if (rubbish_can == nullptr)
    {
        problemLoading("HelloWorld.png");
    }
    else {
 
        rubbish_can->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height * 0.09));
        rubbish_can->setAnchorPoint(Vec2(0, 0));
        this->addChild(rubbish_can, 2);
        rubbishRange.setRect(rubbish_can->getPosition().x , rubbish_can->getPosition().y , rubbish_can->getContentSize().width, rubbish_can->getContentSize().height);
    }
    boardRange.setRect(visibleSize.width * 0.357, visibleSize.height * 0.21, visibleSize.width * 0.2128, visibleSize.width * 0.4256);
    seatRange.setRect(visibleSize.width * 0.357, visibleSize.height * 0.09, visibleSize.width * 0.0535 * 8, visibleSize.width * 0.054);
    
    //storePos = Vec2(STORE->getPosition().x - STORE->getContentSize().width / 2, STORE->getPosition().y - STORE->getContentSize().height / 2);
    //createAndAddSprite(this, "board1.png", 2.0f, visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y, 0);
    //createAndAddSprite(this, "cardboard.jpg", 0.5f, visibleSize.width / 2 + origin.x, origin.y + 40, 0);//卡牌栏
    
    //英雄展示
/*   auto soldier1 = Soldier::create();
    soldier1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100, origin.y + visibleSize.height / 2 - 100));
    this->addChild(soldier1, 0);

    auto soldier2 = Soldier::create();
    soldier2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100, origin.y + visibleSize.height / 2 + 100));
    this->addChild(soldier2, 0);

    HeroInScene.push_back(soldier1);
    HeroInScene.push_back(soldier2);
    
    HerosInScene = this->HeroInScene;
    HerosInScene = this->HeroInScene;*/

    my_player = Player::create();
    my_player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(my_player, 2);

    ai_player = AIPlayer::create();
    ai_player->setPosition(Vec2(origin.x + visibleSize.width *0.7, origin.y + visibleSize.height *0.9));
    this->addChild(ai_player, 2);
    //如果受到攻击小小英雄就掉血
     //money

    createAndAddLabel(this, my_player->MONEY, "", origin.x + visibleSize.width / 2, visibleSize.height * 9.7 / 10.0, 2);
    my_player->MONEY->setColor(Color3B::YELLOW);
    my_player->MONEY->setString("MONEY " + std::to_string(my_player->money));

  
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(Scene_ChessBoard::onMouseDown_1, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    refreshStore();
    
    Round = 1;
    //AI scene
    //setAiHero = true;
    
    

    auto VIEW_AI = MenuItemImage::create("aiview.png", "aiview.png", CC_CALLBACK_1(Scene_ChessBoard::goto_ai, this));
    modifyMenuItem(this, VIEW_AI, origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.9, 1.5f, 1);

    

    return true;
}
//ai
void Scene_ChessBoard::goto_ai(Ref* pSender) {
   
    if (Round == 1) {
        ai1 = Ai_Scene1::create();
        Director::getInstance()->pushScene(TransitionCrossFade::create(1, ai1));
    }
    else if (Round == 2 || Round == 3) {
        ai2 = Ai_Scene2::create();
        Director::getInstance()->pushScene(TransitionCrossFade::create(1, ai2));
    }
    else {
        ai3 = Ai_Scene3::create();
        Director::getInstance()->pushScene(TransitionCrossFade::create(1, ai3));
    }

}
cocos2d::Vec2 Scene_ChessBoard::HeroPosInSeat(cocos2d::Vec2 clickPos) 
{
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.12);
    float gridSize = visibleSize.width * 0.0535;
    float offsetX = clickPos.x - originPos.x;
    int col = static_cast<int>(offsetX / gridSize);
    float centerX = originPos.x + col * gridSize + gridSize / 2;
    return Vec2(centerX, visibleSize.height * 0.12);
}
cocos2d::Vec2 Scene_ChessBoard::HeroPosInBoard(cocos2d::Vec2 clickPos)
{
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
    float gridSize = visibleSize.width * 0.0535;
    float offsetX = clickPos.x - originPos.x;
    float offsetY = clickPos.y - originPos.y;

    int col = static_cast<int>(offsetX / gridSize);
    int row = static_cast<int>(offsetY / gridSize);

    float centerX = originPos.x + col * gridSize + gridSize / 2;
    float centerY = originPos.y + row * gridSize + gridSize / 2;

    return Vec2(centerX, centerY);
}
//order为0时代表游戏开始时候
//order为1时代表游戏结束时候的回溯
void Scene_ChessBoard::Book(Ref* pSender)
{
    auto book = Scene_Book::create();
    Director::getInstance()->pushScene(TransitionCrossFade::create(1, book));
}
void Scene_ChessBoard::refreshBoard(int order)
{
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
    float gridSize = visibleSize.width * 0.0535;
    Rect Grid;
    if (order == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                InChessBoard[i][j] = nullptr;
                Grid.setRect(originPos.x + i * gridSize, originPos.y + j * gridSize, gridSize, gridSize);
                for (auto hero : this->getChildren())
                {
                    if (Grid.containsPoint(hero->getPosition()))
                        InChessBoard[i][j] = dynamic_cast<Hero*>(hero);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (InChessBoard[i][j] != nullptr)
                {
                    InChessBoard[i][j]->hp = 500;
                    InChessBoard[i][j]->bloodBar->setPercentage(MAX_HP1/MAX_HP1*100);
                    InChessBoard[i][j]->setPosition(originPos.x +gridSize*(0.5+i), originPos.y + (j+0.5) * gridSize);
                    InChessBoard[i][j]->setVisible(1);
                }
            }
        }
    }
}
void Scene_ChessBoard::deleteStore()
{
    Hero* store_sprite_1 = getSelectedSoldier(Vec2(visibleSize.width * 9 / 10.0 + origin.x, 170));
    if (store_sprite_1)
        store_sprite_1->removeFromParent();
    Hero* store_sprite_2 = getSelectedSoldier(Vec2(visibleSize.width * 9 / 10.0 + origin.x, 270));
    if (store_sprite_2)
        store_sprite_2->removeFromParent();
}
void Scene_ChessBoard::refreshStore()
{
    deleteStore();
    createStoreHero(this, randomSprite(), visibleSize.width * 9 / 10.0 + origin.x, 170);
    createStoreHero(this, randomSprite(), visibleSize.width * 9 / 10.0 + origin.x, 270);
}
Hero* Scene_ChessBoard::randomSprite()
{
    int x;
    Hero* store_sprite;
    x = random() % 6;
    if (x == 0)
    {
        //创建soldier
        store_sprite = Soldier::create();
        return store_sprite;
    }
    if (x == 1)
    {
        //创建其他英雄
        store_sprite = Shooter::create();
        return store_sprite;
    }
    if (x == 2)
    {
        //创建其他英雄
        store_sprite = Tank::create();
        return store_sprite;
    }
    if (x == 3)
    {
        store_sprite = Wei::create();
        return store_sprite;
    }
    if (x == 4)
    {
        store_sprite = Dragon::create();
        return store_sprite;
    }
    if (x == 5)
    {
        store_sprite = Assassin::create();
        return store_sprite;
    }
}
void Scene_ChessBoard::refreshcallback(Ref* pSender)
{
    if (my_player->money >= 2)
    {
        my_player->money -= 2;
        my_player->MONEY->setString("MONEY " + std::to_string(my_player->money));

        refreshStore();
    }
}
bool Scene_ChessBoard::isInside(cocos2d::Rect Pos)
{
    for (auto sprite : this->getChildren())
    {
        if (sprite!=board&&Pos.containsPoint(sprite->getPosition()))
            return 1;
    }
    return 0;
}
void Scene_ChessBoard::refreshSeat()
{
    auto store_1 = Sprite::create("hero_10086.png");
    Rect Seats;
    for (int i = 0; i < 8; i++)
    {
        Pos[i] = 0;
        Seats.setRect(visibleSize.width * 0.38 - store_1->getContentSize().width / 20 + visibleSize.width * 0.054 * i,
            visibleSize.height * 0.12 - store_1->getContentSize().height / 20, store_1->getContentSize().width/10.0, store_1->getContentSize().height/10.0);
        if (isInside(Seats))
            Pos[i] = 1;
    }
}
Hero* Scene_ChessBoard::getSelectedSoldier(const cocos2d::Vec2& clickPosition)
{
    // 遍历场景中的精灵，判断是否点击到精灵
    for (auto sprite : this->getChildren())
    {
        if (sprite != board && sprite != STORE && sprite->getBoundingBox().containsPoint(clickPosition))
        {
            return dynamic_cast<Hero*>(sprite);
        }
    }
    return nullptr;
}
void Scene_ChessBoard::refreshAiBoard(int round, int order)
{
    Vec2 originPos = Vec2(visibleSize.width * 0.357, visibleSize.height * 0.21);
  
    float gridSize = visibleSize.width * 0.0535;
    auto tank = Tank::create();
    Ai1[0][4] = dynamic_cast<Hero*>(tank);
    auto soldier = Soldier::create();
    Ai1[0][5] = dynamic_cast<Hero*>(soldier);
    auto assassin = Assassin::create();
    Ai1[1][7] = dynamic_cast<Hero*>(assassin);
    auto shooter = Shooter::create();
    Ai1[2][5] = dynamic_cast<Hero*>(shooter);
    
    /*int num = round + 4;
    while (1)
    {
        int x = random() % 4;
        int y = random() % 8;
        Hero* hero = randomSprite();
        if (Ai1[x][y] == nullptr)
        {
            Ai1[x][y] = dynamic_cast<Hero*>(hero);
            num--;
        }
        if (num < 1)
            break;
    }*/
    if (round == 1) {
        auto tank2 = Tank::create();
        Ai1[0][2] = dynamic_cast<Hero*>(tank2);
    }
    else if (round == 2) {
        auto tank2 = Tank::create();
        Ai1[0][2] = dynamic_cast<Hero*>(tank2);
        auto shooter2 = Shooter::create();
        Ai1[3][0] = dynamic_cast<Hero*>(shooter2);
    }
    else {
        auto tank2 = Tank::create();
        Ai1[0][2] = dynamic_cast<Hero*>(tank2);
        auto shooter2 = Shooter::create();
        Ai1[3][0] = dynamic_cast<Hero*>(shooter2);
        auto soldier2 = Soldier::create();
        Ai1[1][1] = dynamic_cast<Hero*>(soldier2);
        auto soldier3 = Soldier::create();
        Ai1[1][6] = dynamic_cast<Hero*>(soldier3);
        auto assassin2 = Assassin::create();
        Ai1[0][0] = dynamic_cast<Hero*>(assassin2);
        auto shooter3 = Shooter::create();
        Ai1[3][1] = dynamic_cast<Hero*>(shooter3);
        auto assassin3 = Assassin::create();
        Ai1[1][4] = dynamic_cast<Hero*>(assassin3);
    }
    if (order == 1)
    {
        for (auto hero : this->HeroInScene)
        {
            if (hero->Flag == 1)
            {
                hero->hp = 0;
                hero->setVisible(0);
            }
        }
        for (auto hero : this->HeroInScene)
            hero->HerosInScene = this->HeroInScene;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (Ai1[i][j] != nullptr)
                {
                    this->addChild(Ai1[i][j]);
                    Ai1[i][j]->setPosition(originPos.x + gridSize * (4.5 + i), originPos.y + gridSize * (0.5 + j));
                    Ai1[i][j]->setScale(0.3f);
                    Ai1[i][j]->Flag = ENEMY_FLAG;
                    this->HeroInScene.push_back(Ai1[i][j]);
                    for (auto ihero : this->HeroInScene)
                    {
                        if (ihero == nullptr)
                            continue;
                        ihero->HerosInScene = this->HeroInScene;
                    }
                }
            }
        }
    }
}
void Scene_ChessBoard::onMouseDown_1(cocos2d::EventMouse* event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    Vec2 clickPosition = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
    if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
    {
        refreshSeat();
        // 检查鼠标点击位置是否在图片上
        Hero* newSelectedSprite = getSelectedSoldier(clickPosition);
        if (storeRange.containsPoint(clickPosition) && newSelectedSprite&&my_player->money>=1)
        {
            //**//////
            my_player->money -= 1;
            my_player->MONEY->setString("MONEY " + std::to_string(my_player->money));
            for (unsigned int i = 0; i < 8; i++)
            {
                if (Pos[i] == 0)
                {
                    newSelectedSprite->setPosition(Vec2(visibleSize.width * 0.38 + visibleSize.width * 0.054 * i, visibleSize.height * 0.12));
                    newSelectedSprite->setScale(0.3f);
                    Pos[i] = 1;
                    break;
                }
            }
        }
        else  if (boardRange.containsPoint(clickPosition) && remainingTime > 0)
        {
            if (newSelectedSprite)
            {
                // 如果之前已经选中了一个精灵，则取消选中状态
                if (selectedSprite)
                {
                    // 取消选中状态的处理代码
                    // ...
                }

                // 更新选中的精灵
                selectedSprite = newSelectedSprite;
                CCLOG("Selected the sprite");
                isSelected = 1;
            }
            else if (!storeRange.containsPoint(clickPosition) && selectedSprite)
            {
                // 移动图片到鼠标点击位置
                if (selectedSprite && isSelected == 1)
                {
                   // selectedSprite->setPosition(HeroPosInBoard(clickPosition));
                    auto moveAction = MoveTo::create(0.3f, Vec2(HeroPosInBoard(clickPosition)));
                    auto actionSequence = Sequence::create(moveAction, nullptr);
                    selectedSprite->runAction(actionSequence);
                    HeroInScene.push_back(selectedSprite);
                    selectedSprite->HerosInScene = this->HeroInScene;
                    CCLOG("Moved the sprite to (%f, %f)", clickPosition.x, clickPosition.y);
                    isSelected = 0;
                }
            }
        }
        else  if (seatRange.containsPoint(clickPosition))
        {
            if (newSelectedSprite)
            {
                // 如果之前已经选中了一个精灵，则取消选中状态
                if (selectedSprite)
                {
                    // 取消选中状态的处理代码
                    // ...
                }

                // 更新选中的精灵
                selectedSprite = newSelectedSprite;
                CCLOG("Selected the sprite");
                isSelected = 1;
            }
            else if (!storeRange.containsPoint(clickPosition) && selectedSprite)
            {
                // 移动图片到鼠标点击位置
                if (selectedSprite && isSelected == 1)
                {
                    for (auto it = HeroInScene.begin(); it != HeroInScene.end(); it++)
                    {
                        auto hero = *it;
                        if (hero == nullptr)
                        {
                            continue;
                        }
                        if (*it == selectedSprite)
                        {
                            selectedSprite->hp = 0;
                            HeroInScene.erase(it);
                            for (auto ihero : this->HeroInScene)
                            {
                                ihero->HerosInScene = this->HeroInScene;
                            }
                            break;
                        }
                    }
                    
                    //selectedSprite->setPosition(HeroPosInSeat(clickPosition));
                    auto moveAction = MoveTo::create(0.3f, Vec2(HeroPosInSeat(clickPosition)));
                    auto actionSequence = Sequence::create(moveAction, nullptr);
                    selectedSprite->runAction(actionSequence);
                    CCLOG("Moved the sprite to (%f, %f)", clickPosition.x, clickPosition.y);
                    isSelected = 0;
                }
            }
        }
        else if (rubbishRange.containsPoint(clickPosition) && selectedSprite)
        {
            if (newSelectedSprite)
            {
                // 如果之前已经选中了一个精灵，则取消选中状态
                if (selectedSprite)
                {
                    // 取消选中状态的处理代码
                    // ...
                }

                // 更新选中的精灵
                selectedSprite = newSelectedSprite;
                CCLOG("Selected the sprite");
                isSelected = 1;
            }
            else if (!storeRange.containsPoint(clickPosition) && selectedSprite)
            {
                // 移动图片到鼠标点击位置
                if (selectedSprite && isSelected == 1)
                {
                    for (auto it = HeroInScene.begin(); it != HeroInScene.end(); it++)
                    {
                        auto hero = *it;
                        if (hero == nullptr)
                        {
                            continue;
                        }
                        if (*it == selectedSprite)
                        {
                            selectedSprite->hp = 0;
                            HeroInScene.erase(it);
                            for (auto ihero : this->HeroInScene)
                            {
                                ihero->HerosInScene = this->HeroInScene;
                            }
                            break;
                        }
                    }
                    selectedSprite->removeFromParent();
                    my_player->money++;
                    my_player->MONEY->setString("MONEY " + std::to_string(my_player->money));
                    CCLOG("Moved the sprite to (%f, %f)", clickPosition.x, clickPosition.y);
                    isSelected = 0;
                }
            }
        }
    }
}
void Scene_ChessBoard::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void Scene_ChessBoard::updateTimer(float dt)
{
    remainingTime -= dt;

    if (remainingTime <= 0.0f)
    {
        // 开始对战
        startBattle();
    }
    // 更新剩余时间Label的显示内容
    int seconds = static_cast<int>(remainingTime);
    TimeLabel->setString("remaining time: " + std::to_string(seconds) + "s");
}
void Scene_ChessBoard::startBattle()
{
    // 停止计时器
    this->unschedule(CC_SCHEDULE_SELECTOR(Scene_ChessBoard::updateTimer));

    // 执行对战逻辑，例如播放音效、开始计分等
    // ...
   /* if (Round == 1) {
        auto soldier1 = Soldier::create();
        soldier1->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100, origin.y + visibleSize.height / 2 + 100));
        soldier1->Flag = ENEMY_FLAG;
        this->addChild(soldier1, 0);
        this->HeroInScene.push_back(soldier1);
        for (auto ihero : this->HeroInScene)
            ihero->HerosInScene = this->HeroInScene;
    }*/
    refreshAiBoard(Round, 0);
    refreshBoard(0);
    scheduleUpdate();
    // 创建并运行对战计时器
    this->schedule(CC_SCHEDULE_SELECTOR(Scene_ChessBoard::updateBattleTimer), 1.0f);
}
void Scene_ChessBoard::updateBattleTimer(float dt)
{
    battleTime -= dt;

    if (battleTime <= 0.0f)
    {
        // 对战时间结束
        endBattle();
    }
    else
    {
        // 更新对战时间Label的显示内容
        int seconds = static_cast<int>(battleTime);
        TimeLabel->setString("battle time: " + std::to_string(seconds) + "s");
    }
}
void Scene_ChessBoard::endBattle()
{
    // 停止对战计时器
    this->unschedule(CC_SCHEDULE_SELECTOR(Scene_ChessBoard::updateBattleTimer));
    //my_player->takeDamage();
    my_player->money += my_player->money / 5 + 6;
    my_player->MONEY->setString("MONEY " + std::to_string(my_player->money));
    // 执行对战结束的逻辑，例如显示得分、播放结束动画等
    // ...
   
    unscheduleUpdate();
    
    int attack = 0;
    for (auto hero : this->HeroInScene)
    {
        if (hero->Flag == 1 && hero->hp > 0)
            attack = 1;
    }
    if (attack == 1) 
    {
        my_player->takeDamage();
    }
    else 
    {
        ai_player->takeDamage();
    }
    //win or lose
    if (my_player->currentHealth == 0)
    {
        createAndAddSprite(this, "board-2d.png", 1.3f, visibleSize.width * 0.6, visibleSize.height * 0.5, 2);
        MenuItemImage* bedefeated = MenuItemImage::create("beDefeated.png", "beDefeated.png", CC_CALLBACK_1(Scene_ChessBoard::THE_END, this));
        modifyMenuItem(this, bedefeated, visibleSize.width * 0.6, visibleSize.height * 0.5,3.0f, 2);
        AudioEngine::pause(audio);
    } 
    if (ai_player->currentHealth == 0)
    {
        createAndAddSprite(this, "board-2d.png", 1.3f, visibleSize.width * 0.6, visibleSize.height * 0.5, 2);
        MenuItemImage* win = MenuItemImage::create("win.png", "win.png", CC_CALLBACK_1(Scene_ChessBoard::THE_END, this));
        modifyMenuItem(this, win, visibleSize.width * 0.6, visibleSize.height * 0.5, 2.0f, 2);
        AudioEngine::pause(audio);
    }
    refreshBoard(1);
    refreshAiBoard(Round, 1);
    ++Round;
    
     // 重新开始计时器
    remainingTime =REMAININGTIME; // 重新设置剩余时间
    battleTime = BATTLETIME; // 重新设置对战时间
    this->schedule(CC_SCHEDULE_SELECTOR(Scene_ChessBoard::updateTimer), 1.0f);
}
void Scene_ChessBoard::update(float deltaTime)
{
    for (auto hero : HeroInScene)
    {
        if (hero == nullptr)
            continue;
        if (hero->hp <= 0)
        {
            hero->setVisible(0);
            continue;
        }
        hero->update(deltaTime);
    }
}
void Scene_ChessBoard::THE_END(Ref* pSender)
{
    auto Scene = Scene_menu::create();
    Director::getInstance()->replaceScene(Scene);
}