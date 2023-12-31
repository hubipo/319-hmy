#include"Player.h"
USING_NS_CC;

bool Player::init()
{
    if (!Sprite::init()) {
        return false;
    }//调用父类init，只写init初始化
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //初始化
    isMoving = false;
    //isAttacked = false;
    moveSpeed = SPEAD; // 小小英雄的移动速度
    currentHealth = MAX_HP;
    //获取屏幕
    //cocos2d::Size screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    //cocos2d::Vec2 spritePosition(screenSize.width / 2, screenSize.height / 2);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 创建英雄精灵
    auto heroSprite = cocos2d::Sprite::create("littleplayer.png");
    heroSprite->setScale(0.3f);
    heroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    heroSprite->setPosition(Vec2(0, 0));
    this->addChild(heroSprite, 0);

    // 创建血条
    createHealthBar(heroSprite);
   
    // 注册鼠标点击事件监听器
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseDown = std::bind(&Player::onMouseDown, this, std::placeholders::_1);//绑定bind
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}
void Player::createHealthBar(Sprite* heroSprite) {
    auto bdSprite = Sprite::create("blood_bd.png");
    bdSprite->setPosition(heroSprite->getAnchorPoint() + Vec2(12, 25));
    bdSprite->setScale(0.5);
    this->addChild(bdSprite, 0);//血条，英雄和血条底图都是Player的子节点

    // 创建血条
    bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setScale(0.5);
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(0, 0.5)); // 设置进度条起点/?????
    bloodBar->setBarChangeRate(Vec2(1, 0)); // 设置进度条变化率
    bloodBar->setPosition(heroSprite->getAnchorPoint() + Vec2(12, 25));
    
    bloodBar->setPercentage(currentHealth); // 设置血条初始值
    
    this->addChild(bloodBar, 0);
}
/*
void Player::onMouseDown(cocos2d::EventMouse* event) {

    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取点击位置
        cocos2d::Vec2 clickPos = mouseEvent->getLocationInView();
        clickPos.y = cocos2d::Director::getInstance()->getVisibleSize().height - clickPos.y; // 反转Y轴坐标
        clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);
        // 计算精灵需要移动的目标位置

        cocos2d::Vec2 targetPos = clickPos;

        // 计算英雄需要移动的距离和时间
        float distance = targetPos.distance(getPosition());
        float duration = distance / moveSpeed;
        // 创建移动动作
        auto moveAction = cocos2d::MoveTo::create(duration, targetPos);

        // 执行移动动作
        runAction(moveAction);


    }
}
*/
void Player::onMouseDown(cocos2d::EventMouse* event) {
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {

        if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT) 
        {
            //移动过程中不能读取鼠标，防止飞出屏幕
            if (!isMoving) {
                isMoving = true;
                // 获取点击位置
                cocos2d::Vec2 clickPos = mouseEvent->getLocationInView();
                clickPos.y = cocos2d::Director::getInstance()->getVisibleSize().height - clickPos.y; // 反转Y轴坐标
                clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);

                // 获取精灵的大小
                cocos2d::Size spriteSize = this->getContentSize();

                // 计算精灵可以移动的区域
                cocos2d::Size screenSize = cocos2d::Director::getInstance()->getVisibleSize();
                cocos2d::Rect moveRect = cocos2d::Rect(spriteSize.width / 2, spriteSize.height / 2, screenSize.width - spriteSize.width, screenSize.height - spriteSize.height);

                // 将目标位置限制在可移动区域内
                cocos2d::Vec2 targetPos = clickPos.getClampPoint(moveRect.origin, moveRect.origin + moveRect.size);

                // 计算英雄需要移动的距离和时间
                float distance = targetPos.distance(getPosition());
                float duration = distance / moveSpeed;
                // 创建移动动作
                //auto moveAction = cocos2d::MoveTo::create(duration, targetPos);
                auto moveAction = cocos2d::Sequence::create(
                    cocos2d::MoveTo::create(duration, targetPos),
                    cocos2d::CallFunc::create([this]() {
                        // 移动完成后，将移动状态设为 false
                        isMoving = false;
                        }),
                    nullptr
                            );
                // 执行移动动作
                runAction(moveAction);
            }
        }
    }
}
void Player::takeDamage() {
    if (!bloodBar) {
        return;
    }
   
    currentHealth -= 40;

   if (currentHealth < 0.0f) {
        currentHealth = 0.0f;
    }
    /*
    * 如果血量为零，英雄图片改为死亡图片
    */
 
    bloodBar->setPercentage(currentHealth);//将血量减少显示
   
}
//整体节点
bool AIPlayer::init()
{
    if (!Sprite::init()) {
        return false;
    }//调用父类init，只写init初始化
     //初始化

    currentHealth = MAX_HP;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 创建英雄精灵
    auto heroSprite = cocos2d::Sprite::create("AIplayer.png");
    heroSprite->setScale(1.0f);
    heroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    heroSprite->setPosition(Vec2(0, 0));
    this->addChild(heroSprite, 0);

    // 创建血条
    createHealthBar(heroSprite);
    return true;
}
void AIPlayer::createHealthBar(Sprite* heroSprite) {
    auto bdSprite = Sprite::create("blood_bd.png");
    bdSprite->setPosition(heroSprite->getAnchorPoint() + Vec2(12, 25));
    bdSprite->setScale(0.5);
    this->addChild(bdSprite, 0);//血条，英雄和血条底图都是Player的子节点

    // 创建血条
    bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setScale(0.5);
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(0, 0.5)); // 设置进度条起点/?????
    bloodBar->setBarChangeRate(Vec2(1, 0)); // 设置进度条变化率
    bloodBar->setPosition(heroSprite->getAnchorPoint() + Vec2(12, 25));
    bloodBar->setPercentage(currentHealth); // 设置血条初始值

    this->addChild(bloodBar, 0);
}
void AIPlayer::takeDamage() {
    if (!bloodBar) {
        return;
    }
 
    currentHealth -= 40;

    if (currentHealth < 0.0f) {
        currentHealth = 0.0f;
    }

    bloodBar->setPercentage(currentHealth);//将血量减少显示

}