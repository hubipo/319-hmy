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
USING_NS_CC;
/********************************/
//HELLOWORLD
/********************************/
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

/********************************/
//Scene_menu
/********************************/
Scene* Scene_menu::createScene()
{
    return Scene_menu::create();
}
// Print useful error message instead of segfaulting when files are not there.
bool Scene_menu::init()
{
    if (!Scene::init())
        return false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* sprite_1 = Sprite::create("background_menu.png");
    sprite_1->setScale(3.0f);
    if (sprite_1 == NULL)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        sprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_1, -1);
    }
    auto sprite_2 = Sprite::create("menu_1.png");
    sprite_2->setScale(0.8f);
    if (sprite_2 == NULL)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        float x = origin.x + visibleSize.width*1.8 / 10;
        float y = origin.y + visibleSize.height / 10;
        sprite_2->setPosition(Vec2(x, y));
        this->addChild(sprite_2, 0);
    }
    auto sprite_3 = Sprite::create("menu_2.png");
    sprite_3->setScale(0.8f);
    if (sprite_3 == NULL)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        float x = origin.x + visibleSize.width*8.3/10.0;
        float y = origin.y + visibleSize.height / 10;
        sprite_3->setPosition(Vec2(x, y));
        this->addChild(sprite_3, 0);  
    } 
    auto sprite_4 = Sprite::create("menu_3.png");
    sprite_4->setScale(1.3f);
    if (sprite_4 == NULL)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        float x = origin.x + visibleSize.width * 1.8 / 10;
        float y = origin.y + visibleSize.height *6.5/ 10;
        sprite_4->setPosition(Vec2(x, y));
        this->addChild(sprite_4, 0);
    } 
    auto sprite_5 = Sprite::create("menu_4.png");
    sprite_5->setScale(1.3f);
    if (sprite_5 == NULL)
    {
        problemLoading("HelloWorld.png");
    }
    else
    {
        float x = origin.x + visibleSize.width * 8.3 / 10;
        float y = origin.y + visibleSize.height * 6.5 / 10;
        sprite_5->setPosition(Vec2(x, y));
        this->addChild(sprite_5, 0);
    }
    /*********/
    /*label*/
    /*********/
    auto signal=Label::createWithTTF("Teamfight Tactics", "fonts/Marker Felt.ttf", 24);
    if (signal == NULL)
    {
        problemLoading("WRONG");
    }
    else
    {
        signal->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - signal->getContentSize().height));
        signal->enableOutline(Color4B::RED, 1);
        this->addChild(signal, 0);
    }
    /********/
    /*menuItem*/
    /********/
    auto START = MenuItemImage::create("START_menu.png", "START_menu.png", CC_CALLBACK_1(Scene_menu::menuSTART, this));
    START->setScale(2.0f);
    if (START == NULL || START->getContentSize().width <= 0 || START->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2;
        float y = origin.y+visibleSize.height/10;
        START->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(START, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto SETTINGS= MenuItemImage::create("SETTINGS.png", "SETTINGS.png", CC_CALLBACK_1(Scene_menu::menuSETTINGS, this));
    SETTINGS->setScale(0.3f);
    if (SETTINGS == NULL || SETTINGS->getContentSize().width <= 0 || SETTINGS->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x +visibleSize.width*9.5/10.0;
        float y = origin.y+ visibleSize.height*9.3/10;
        SETTINGS->setPosition(Vec2(x, y));
    }
    auto menu_SETTINGS = Menu::create(SETTINGS, NULL);
    menu_SETTINGS->setPosition(Vec2::ZERO);
    this->addChild(menu_SETTINGS, 1);
    //12up
    auto menu_12up = MenuItemImage::create("12.png", "12.png", CC_CALLBACK_1(Scene_menu::menu12up, this));
    menu_12up->setScale(0.8f);
    if (menu_12up == NULL || menu_12up->getContentSize().width <= 0 || menu_12up->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/10;
        float y = origin.y + visibleSize.height*8.5 / 10;
        menu_12up->setPosition(Vec2(x, y));
    }
    auto Menu_12up = Menu::create(menu_12up, NULL);
    Menu_12up->setPosition(Vec2::ZERO);
    this->addChild(Menu_12up, 1);
    return true;
}
void  Scene_menu::menuSTART(Ref* pSender)
{
    auto HELLOWORLD = HelloWorld::createScene();
    //Director::getInstance()->replaceScene(HELLOWORLD);
    // 0*3黑色 255*3白色
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, HELLOWORLD, Color3B(0, 0, 0)));
}
void  Scene_menu::menuSETTINGS(Ref* pSender)
{
    //需要跳到settings中
    auto SETTINGS = HelloWorld::createScene();
    //Director::getInstance()->replaceScene(SETTINGS);
    Director::getInstance()->pushScene(TransitionCrossFade::create(1, SETTINGS));
}
void Scene_menu::menu12up(Ref* pSender)
{
    auto scene_12up = Scene_12up::create();
    Director::getInstance()->pushScene(scene_12up);
}
/**********/
/*12+*/
/**********/
Scene* Scene_12up::createScene()
{
    return Scene_12up::create();
}
// on "init" you need to initialize your instance
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
    Scene_12up->setScale(2.0f);
    if (Scene_12up == NULL || Scene_12up->getContentSize().width <= 0 || Scene_12up->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2;
        Scene_12up->setPosition(Vec2(x, y));
    }
    auto Menu_12up = Menu::create(Scene_12up, NULL);
    Menu_12up->setPosition(Vec2::ZERO);
    this->addChild(Menu_12up, 1);
    return true;
}
void Scene_12up::CLOSE(Ref* pSender)
{ 
    Director::getInstance()->popScene();
    //auto scene = Scene_menu::create();
    //Director::getInstance()->replaceScene(scene);
}
