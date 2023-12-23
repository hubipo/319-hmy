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
#include"Player.h"
USING_NS_CC;

bool Player:: init()
    {
        if (!Node::init()) {
            return false;
        }//调用父类init，只写init初始化

        // 创建英雄精灵
        auto heroSprite = cocos2d::Sprite::create("player.png");
        heroSprite->setPosition(Vec2(100, 100));
        this->addChild(heroSprite);

        // 创建血条
        auto healthBar = createHealthBar();
        this->addChild(healthBar);

        // 注册鼠标点击事件监听器
        auto listener = cocos2d::EventListenerMouse::create();
        listener->onMouseDown = std::bind(&Player::onMouseDown, this, std::placeholders::_1);//绑定bind
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


        return true;
    }
void Player::onMouseDown(cocos2d::EventMouse* event) {
    // 获取点击位置
    cocos2d::Vec2 clickPos = cocos2d::Director::getInstance()->convertToGL(event->getLocationInView());

    // 计算英雄需要移动的距离和时间
    float distance = clickPos.distance(PlayerSprite->getPosition());
    float duration = distance / moveSpeed;

    // 创建移动动作
    auto moveAction = cocos2d::MoveTo::create(duration, clickPos);

    // 执行移动动作
    PlayerSprite->runAction(moveAction);
}
cocos2d::Node* Player::createHealthBar() {
    // 创建血条的逻辑
    // 创建血条底图
    auto bdSprite = Sprite::create("blood_bd.png");
    bdSprite->setPosition(Vec2(100, 80));
    this->addChild(bdSprite);

    // 创建血条
    auto bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(1, 0.5)); // 设置进度条起点
    bloodBar->setBarChangeRate(Vec2(1, 0)); // 设置进度条变化率
    bloodBar->setPosition(Vec2(100, 80));
    bloodBar->setPercentage(100); // 设置血条初始值
    currentHealth = 100.0f;
    this->addChild(bloodBar);

    return this;
}
void Player::takeDamage() {

    float damageAmount = 20.0f; // 受到的伤害值
    currentHealth -= damageAmount;

    if (currentHealth < 0.0f) {
        currentHealth = 0.0f;
    }

    float healthPercentage = currentHealth;
    bloodBar->setPercentage(healthPercentage);//将血量减少显示

}
//整体节点