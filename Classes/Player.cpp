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
        }//���ø���init��ֻдinit��ʼ��

        // ����Ӣ�۾���
        auto heroSprite = cocos2d::Sprite::create("player.png");
        heroSprite->setPosition(Vec2(100, 100));
        this->addChild(heroSprite);

        // ����Ѫ��
        auto healthBar = createHealthBar();
        this->addChild(healthBar);

        // ע��������¼�������
        auto listener = cocos2d::EventListenerMouse::create();
        listener->onMouseDown = std::bind(&Player::onMouseDown, this, std::placeholders::_1);//��bind
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


        return true;
    }
void Player::onMouseDown(cocos2d::EventMouse* event) {
    // ��ȡ���λ��
    cocos2d::Vec2 clickPos = cocos2d::Director::getInstance()->convertToGL(event->getLocationInView());

    // ����Ӣ����Ҫ�ƶ��ľ����ʱ��
    float distance = clickPos.distance(PlayerSprite->getPosition());
    float duration = distance / moveSpeed;

    // �����ƶ�����
    auto moveAction = cocos2d::MoveTo::create(duration, clickPos);

    // ִ���ƶ�����
    PlayerSprite->runAction(moveAction);
}
cocos2d::Node* Player::createHealthBar() {
    // ����Ѫ�����߼�
    // ����Ѫ����ͼ
    auto bdSprite = Sprite::create("blood_bd.png");
    bdSprite->setPosition(Vec2(100, 80));
    this->addChild(bdSprite);

    // ����Ѫ��
    auto bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(1, 0.5)); // ���ý��������
    bloodBar->setBarChangeRate(Vec2(1, 0)); // ���ý������仯��
    bloodBar->setPosition(Vec2(100, 80));
    bloodBar->setPercentage(100); // ����Ѫ����ʼֵ
    currentHealth = 100.0f;
    this->addChild(bloodBar);

    return this;
}
void Player::takeDamage() {

    float damageAmount = 20.0f; // �ܵ����˺�ֵ
    currentHealth -= damageAmount;

    if (currentHealth < 0.0f) {
        currentHealth = 0.0f;
    }

    float healthPercentage = currentHealth;
    bloodBar->setPercentage(healthPercentage);//��Ѫ��������ʾ

}
//����ڵ�