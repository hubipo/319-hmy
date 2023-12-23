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
void createAndAddLabel(T1* obj, T2&label, const std::string& filename, float Pos_X, float Pos_Y, int Zorder)
{
    label= Label::createWithTTF(filename, "fonts/Marker Felt.ttf", 24);
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
template<typename T1,typename T2>
void modifyMenuItem(T1*obj,T2& MenuItem, float Pos_X, float Pos_Y, float scale, int Zorder)
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
template<typename T1,typename T2>
void modifyCheckBox(T1*obj,T2&checkbox,bool selected,float Pos_X,float Pos_Y,float scale)
{
    checkbox->setScale(scale);
    checkbox->setPosition(Vec2(Pos_X,Pos_Y));
    checkbox->setSelected(selected);
    obj->addChild(checkbox);
}
//进度条
template<typename T1,typename T2>
void modifySlider(T1*obj,T2&slider,std::string unselected,std::string selected,std::string normal,std::string pressed,std::string disabled,float Pos_X,float Pos_Y ,int maxPercent,int curPercent)
{
    slider->loadBarTexture(unselected);;
    slider->loadSlidBallTextures(normal, pressed, disabled);
    slider->loadProgressBarTexture(selected);
    slider->setPosition(Vec2(Pos_X,Pos_Y));
    slider->setMaxPercent(maxPercent);
    slider->setPercent(curPercent);
    obj->addChild(slider);
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
    audio = AudioEngine::play2d("Mymuuuuusic.mp3",true);
    /********/
    /*Sprite*/
    /********/
    createAndAddSprite(this, "background_menu.png", 3.0f, visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y, -1);
    createAndAddSprite(this, "menu_1.png", 0.8f, origin.x + visibleSize.width * 1.8 / 10, origin.y + visibleSize.height / 10, 0);
    createAndAddSprite(this, "menu_2.png", 0.8f, origin.x + visibleSize.width * 8.3 / 10.0, origin.y + visibleSize.height / 10, 0);
    createAndAddSprite(this, "menu_3.png", 1.3f, origin.x + visibleSize.width * 1.8 / 10, origin.y + visibleSize.height * 6.5 / 10, 0);
    createAndAddSprite(this, "menu_4.png", 1.3f, origin.x + visibleSize.width * 8.3 / 10, origin.y + visibleSize.height * 6.5 / 10, 0);
    /*******/
    /*Label*/
    /*******/
    Label* signal;
    createAndAddLabel(this,signal, "Teamfight Tactics", origin.x + visibleSize.width / 2,origin.y + visibleSize.height*9/10.0, 0);
    signal->enableOutline(Color4B::RED, 1);
    /**********/
    /*menuItem*/
    /**********/
    auto START = MenuItemImage::create("START_menu.png", "START_menu.png", CC_CALLBACK_1(Scene_menu::menuSTART, this));
    modifyMenuItem(this,START, origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10, 2.0f, 1);
    auto SETTINGS= MenuItemImage::create("SETTINGS.png", "SETTINGS.png", CC_CALLBACK_1(Scene_menu::menuSETTINGS, this));
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
    auto Scene_12up = MenuItemImage::create("12up.png", "12up.png",CC_CALLBACK_1(Scene_12up::CLOSE, this));
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
    createAndAddLabel(this, Sound, "Sound", origin.x + visibleSize.width/3.0, origin.y + visibleSize.height*7.5/10.0, 1);
    Sound->enableShadow();
    Sound->setColor(Color3B::RED);
    
    Label* CLOSE;
    createAndAddLabel(this, CLOSE, "END GAME", origin.x + visibleSize.width * 8.0 / 10, origin.y + visibleSize.height * 9.2 / 10.0, 1);
    CLOSE->setScale(0.55f);
    CLOSE->setColor(Color3B(0,191,255));
    CLOSE->enableOutline(Color4B::BLACK,1);

    createAndAddSprite(this, "Setting_background.png", 2.0f, origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2, 0);
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
    modifySlider(this,slider, "huadongtiao_1.png", "hongtiao.png", "huadongtiao_3.png", "huadongtiao_5.png"
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
        if (type ==ui::Slider::EventType::ON_PERCENTAGE_CHANGED) 
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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(Scene_ChessBoard::menuCloseCallback, this));
    modifyMenuItem(this, closeItem, origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2, 1.0f, 1);

    Label* label;
    createAndAddLabel(this, label, "ChessBoard", origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 9 / 10, 1);
   
    createAndAddSprite(this, "board1.png", 2.0f, visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y, 0);
    createAndAddSprite(this, "cardboard.jpg", 0.5f, visibleSize.width / 2 + origin.x, origin.y+40, 0);//卡牌栏
    //小小英雄
    my_player = Player::create();
    my_player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(my_player, 0);
    //如果受到攻击小小英雄就掉血

    if (my_player->isAttacked) {
        my_player->takeDamage();
    }

    return true;
}
void Scene_ChessBoard::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
/********************************/