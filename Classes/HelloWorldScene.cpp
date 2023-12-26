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
USING_NS_CC;
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
    //createAndAddSprite(this, "cardboard.jpg", 0.5f, visibleSize.width / 2 + origin.x, origin.y+40, 0);//卡牌栏
    //小小英雄
    my_player = Player::create();
    my_player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(my_player, 0);

    /*    //英雄展示尝试
    auto hero_1 = Soldier::create();
    hero_1->setPosition(Vec2(350, 200));

    auto hero_2 = Soldier::create();
    hero_2->setPosition(Vec2(150, 200));


    this->HeroList.push_back(hero_1);
    this->HeroList.push_back(hero_2);
    hero_1->HerosInScene = this->HeroList;


    // 将英雄添加到当前场景中
    this->addChild(hero_1, 1);
    this->addChild(hero_2 , 1);

    Vec2 Mid((hero_1->getPosition().x + hero_2->getPosition().x) / 2, (hero_1->getPosition().y + hero_2->getPosition().y) / 2);

    hero_1->HeroMove();

    for (auto hero : HeroList)
    {
        hero->update(16.67);
    }
*/

    //如果受到攻击小小英雄就掉血
    if (my_player->isAttacked) {
        my_player->takeDamage();
    }

    /*    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(Scene_ChessBoard::onMouseDown_1, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    createAndAddSprite(this, "menu_1.png", 0.5f, visibleSize.width / 2 + origin.x, origin.y + 40, 1);
    createAndAddSprite(this, "menu_2.png", 0.5f, visibleSize.width / 3 + origin.x, origin.y + 40, 1);
*/

    auto soldier = Soldier::create();    //sunflower card
    soldier->setPosition(Vec2(135, 555));
    this->addChild(soldier, 2);
    heroDate.push_back(soldier);


    /////创建鼠标监听事件，为移动卡牌做准备
    auto listenermo = EventListenerTouchOneByOne::create();
    listenermo->onTouchBegan = CC_CALLBACK_2(Scene_ChessBoard::onTouchBegan, this, soldier);
    //listenermo->onTouchMoved = CC_CALLBACK_2(Scene_ChessBoard::onTouchMoved2, this);
    listenermo->onTouchEnded = CC_CALLBACK_2(Scene_ChessBoard::onTouchEnded, this, soldier);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenermo, this);

    //棋盘图
//= Sprite::create("board1.png");
//创建卡牌框
    auto card_bar_sprite = Sprite::create("CardBar.png");
    card_bar_sprite->setPosition(Vec2(visibleSize.width / 2.0f - 160.0f, visibleSize.height / 2.0f + 120.0f));
    card_bar_sprite->setScale(1.3f);
    board->addChild(card_bar_sprite, 1);

    //*****在卡牌框上创建相应的英雄卡片
/*（此处要随机产生两个英雄，而不是下面示例中的一次性产生）
Hero* hero1 = new Hero;
hero1->init();
然后用图片建立英雄1的对象，设置位置（位置是事先计算出来的卡牌槽的位置
this->addChild(这个英雄，2);
card_date是存储所有卡片的vector，创建卡片之后才要把这个卡片的对象push进去
*/
   
    //坐标初始化开始
//auto visibleSize = Director::getInstance()->getVisibleSize();
//坐标初始化
//计划九宫格
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float ii = 0.15f * i + 0.15f, jj = 0.21f + j * 0.09f;//这里的坐标要通过在图上计算的实际数据修改
            heroPosition[i][j] = Vec2(visibleSize.width * jj, visibleSize.height * ii);//这是一个储存所有合法位置的数组
        }
    }


    /*
//*******************************从这里开始************************


/*代码如下********************************* |||||||||||||||||||||||||||||
/////////////////////////////////////////////////////

 //****************************到这里暂时结束，有一些小函数未列出**********************
 */

    
    return true;
}


//下面这个函数要单列出去，暂时写在这里
bool Scene_ChessBoard::onTouchBegan(Touch* touch, Event* unused_event,Hero* ihero) {
    //判断鼠标
    auto touchPosition = touch->getLocation();
    for (auto& it : heroDate) //遍历卡片槽中所有的卡片类型
    {
        if (mouse_sprite != nullptr) break;//如果当前鼠标选中了某个英雄卡片，那么不再允许选择卡片
        double width_ = it->getContentSize().width / 2;
        double height_ = it->getContentSize().height / 2;//一个卡片的长和宽
        Vec2 card_positon = it->getPosition();//当前卡片槽中卡片的位置
        auto offset_ = card_positon - touchPosition;//用于计算鼠标是否点在这个卡片范围内
        if ((fabs(offset_.x) <= width_) && (fabs(offset_.y) <= height_)) {
            switch (it->heroType) {//判断是哪种英雄卡片
                case HeroType::Soldier://如果是英雄1
                {
                    
                    mouse_sprite = ihero;//这是给mouse_sprite这个临时的Sprite指针赋值
                    //赋值到相应的被选中的英雄卡片，因为it在遍历存储英雄卡片的card_date数组，it指向的正是当前被选中的英雄卡片
                    this->addChild(mouse_sprite, 1);
                    selectedHeroType = HeroType::Soldier;//当前被选中的英雄类型,假设是武士
                    break;
                }
                //etc....
                default: {
                    break;
                }
            }
            return true;
        }
    }
    return false;
}


//不需要中间卡片跟随鼠标走，所以点击完了直接在某个位置生成
void Scene_ChessBoard::onTouchEnded(Touch* touch, Event* unused_event, Hero* ihero) {
    if (mouse_sprite != nullptr && selectedHeroType != HeroType::heroTypeNone) {//
        int row_, col_;
        if (this->judge_vec2_in_row_col(touch->getLocation(), row_, col_)) {//鼠标位置棋盘上，不能在装备栏等位置
            //judge_vec2_in_row_col函数判断位置是否在棋盘上，并且对row_和col_赋值，让我们获取要安放棋子的标准位置
            //将我们种植的一个粗略的范围变成确定的一个点
            if (this->judgeHero(row_, col_) == false) {
                //plants_vs_zombies->judge_plant(row_, col_)数组为true表示这个地方已经有棋子
                //为false表示没放过棋子，可以继续安放棋子在这个格子
                ihero->setPosition(Vec2(row_, col_));
                heroJudgePosition[row_][col_] = true;
                this->HeroList.push_back(ihero);

                //????//更改英雄的图片
                //plantDown(row_, col_, selectedHeroType);//放在这个位置
            }
        }
        selectedHeroType = HeroType::heroTypeNone;//安放棋子在棋盘上动作完成，已选的植物类型置为空
    }
    this->removeChild(mouse_sprite);//清理临时指针
    mouse_sprite = nullptr;//临时指针指向空
}


void Scene_ChessBoard::createHeroAtMousePos(Event* event)
{
        EventMouse* e = dynamic_cast<EventMouse*>(event);
        if (e)
        {
            if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT) {

                // 获取鼠标点击的位置
                Vec2 clickPos = e->getLocationInView();
                clickPos = Director::getInstance()->convertToGL(clickPos);

                // 获取屏幕可见区域大小
                Size visibleSize = Director::getInstance()->getVisibleSize();

                // 计算上下对称位置
                float symmetricalY = visibleSize.height - clickPos.y;

                // 创建英雄对象
                Vec2 heroPos = Vec2(clickPos.x, symmetricalY);
                float heroSize = 0.3f;
                Soldier* hero = Soldier::CreateHero(heroPos, heroSize);

                // 将英雄添加到当前场景中
                this->addChild(hero);
                this->HeroList.push_back(hero);
                this->heroNum++;
                
                for (auto hero : this->HeroList)
                {
                    hero->HerosInScene = this->HeroList;
                    hero->HeroMove();
                    hero->Attack();
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
        // 检查鼠标点击位置是否在图片上
        Sprite* newSelectedSprite = getSelectedSprite(clickPosition);

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
        else
        {
            // 移动图片到鼠标点击位置
            if (selectedSprite && isSelected == 1)
            {
                selectedSprite->setPosition(clickPosition);
                CCLOG("Moved the sprite to (%f, %f)", clickPosition.x, clickPosition.y);
                isSelected = 0;
            }
        }
    }
}

Sprite* Scene_ChessBoard::getSelectedSprite(const cocos2d::Vec2& clickPosition)
{
    // 遍历场景中的精灵，判断是否点击到精灵
    for (auto sprite : this->getChildren())
    {
        if (sprite != board && sprite->getBoundingBox().containsPoint(clickPosition) && dynamic_cast<Sprite*>(sprite))
        {
            return static_cast<Sprite*>(sprite);
        }
    }
    return nullptr;
}

void Scene_ChessBoard::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//判断这个vec2坐标 鼠标点击的位置是不是在草地区域  结合鼠标使用种植植物 
bool Scene_ChessBoard::judge_vec2_in_row_col(Vec2 vec_position, int& _row, int& _col) {
    //特判  ：越界 if(越界) return false
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if ((vec_position.x < visibleSize.width * 0.18) || (vec_position.x > visibleSize.width * 0.95)
        || (vec_position.y < visibleSize.height * 0.13) || (vec_position.y > visibleSize.height * 0.92))	return false;
    int width_ = 125 / 2;
    int height_ = 103 / 2;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            Vec2 offset = vec_position - heroPosition[i][j];
            if ((fabs(offset.x) <= width_) && (fabs(offset.y) <= height_)) {
                _row = i;
                _col = j;
                return true;
            }
        }
    }
    return false;
}

bool Scene_ChessBoard::judgeHero(int row_, int col_) 
{ 
    return heroJudgePosition[row_][col_]; 
}

void Scene_ChessBoard::createPlant(int row_, int col_, HeroType type_) 
{ 
    heroJudgePosition[row_][col_] = true;
}
//在row行col列创建一个某种类型的植物

/********************************/