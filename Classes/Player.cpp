
#include"Player.h"
USING_NS_CC;
/*template<typename T>
void createHealthBar(T* obj) {
    // ����Ѫ�����߼�
    // ����Ѫ����ͼ
    auto bdSprite = Sprite::create("hongtiao.png");
    bdSprite->setPosition(Vec2(100, 80));
    obj->addChild(bdSprite, 0);

    // ����Ѫ��
    auto bloodBar = ProgressTimer::create(Sprite::create("hongtiao.png"));
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(1, 0.5)); // ���ý��������
    bloodBar->setBarChangeRate(Vec2(1, 0)); // ���ý������仯��
    bloodBar->setPosition(Vec2(100, 80));
    bloodBar->setPercentage(100); // ����Ѫ����ʼֵ
    currentHealth = 100.0f;
    obj->addChild(bloodBar, 0);
}*/
/*Sprite* Player::createPlayer()
{
    return Player::create();
    }*/
bool Player::init()
{
    if (!Sprite::init()) {
        return false;
    }//���ø���init��ֻдinit��ʼ��
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ��
    isMoving = false;
    isAttacked = false;
    moveSpeed = SPEAD; // ССӢ�۵��ƶ��ٶ�
    currentHealth = MAX_HP;
    //��ȡ��Ļ
    //cocos2d::Size screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    //cocos2d::Vec2 spritePosition(screenSize.width / 2, screenSize.height / 2);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // ����Ӣ�۾���
    auto heroSprite = cocos2d::Sprite::create("littleplayer.png");
    heroSprite->setScale(0.3f);
    heroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    heroSprite->setPosition(Vec2(0,0));
    this->addChild(heroSprite, 0);
    

    // ����Ѫ��
    createHealthBar(heroSprite);
    /*
    auto bdSprite = Sprite::create("blood_bd.png");
    bdSprite->setPosition(heroSprite->getPosition()+Vec2(25,50));
    this->addChild(bdSprite, 0);

    // ����Ѫ��
    auto bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(0, 0.5)); // ���ý��������
    bloodBar->setBarChangeRate(Vec2(1, 0)); // ���ý������仯��
    bloodBar->setPosition(heroSprite->getPosition() + Vec2(25, 50));
    bloodBar->setPercentage(100); // ����Ѫ����ʼֵ
    currentHealth = 100.0f;
    this->addChild(bloodBar, 0);

    */
    // ע��������¼�������
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseDown = std::bind(&Player::onMouseDown, this, std::placeholders::_1);//��bind
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}
void Player::createHealthBar(Sprite*heroSprite) {
    auto bdSprite = Sprite::create("blood_bd.png");
    bdSprite->setPosition(heroSprite->getAnchorPoint() + Vec2(12, 25));
    bdSprite->setScale(0.5);
    this->addChild(bdSprite, 0);//Ѫ����Ӣ�ۺ�Ѫ����ͼ����Player���ӽڵ�

    // ����Ѫ��
    auto bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setScale(0.5);
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(0, 0.5)); // ���ý��������/?????
    bloodBar->setBarChangeRate(Vec2(1, 0)); // ���ý������仯��
    bloodBar->setPosition(heroSprite->getAnchorPoint() + Vec2(12, 25));
    bloodBar->setPercentage(100); // ����Ѫ����ʼֵ
    //currentHealth = 100.0f;//
    this->addChild(bloodBar, 0);
}
/*
void Player::onMouseDown(cocos2d::EventMouse* event) {

    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ���λ��
        cocos2d::Vec2 clickPos = mouseEvent->getLocationInView();
        clickPos.y = cocos2d::Director::getInstance()->getVisibleSize().height - clickPos.y; // ��תY������
        clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);     
        // ���㾫����Ҫ�ƶ���Ŀ��λ��

        cocos2d::Vec2 targetPos = clickPos;

        // ����Ӣ����Ҫ�ƶ��ľ����ʱ��
        float distance = targetPos.distance(getPosition());
        float duration = distance / moveSpeed;
        // �����ƶ�����
        auto moveAction = cocos2d::MoveTo::create(duration, targetPos);

        // ִ���ƶ�����
        runAction(moveAction);
        
      
    }
}
*/
void Player::onMouseDown(cocos2d::EventMouse* event) {
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        //ֻ�Ҽ������ƶ�ССӢ��
        if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT) {
            //�ƶ������в��ܶ�ȡ��꣬��ֹ�ɳ���Ļ
            if (!isMoving) {
                isMoving = true;
                // ��ȡ���λ��
                cocos2d::Vec2 clickPos = mouseEvent->getLocationInView();
                clickPos.y = cocos2d::Director::getInstance()->getVisibleSize().height - clickPos.y; // ��תY������
                clickPos = cocos2d::Director::getInstance()->convertToGL(clickPos);

                // ��ȡ����Ĵ�С
                cocos2d::Size spriteSize = this->getContentSize();

                // ���㾫������ƶ�������
                cocos2d::Size screenSize = cocos2d::Director::getInstance()->getVisibleSize();
                cocos2d::Rect moveRect = cocos2d::Rect(spriteSize.width / 2, spriteSize.height / 2, screenSize.width - spriteSize.width, screenSize.height - spriteSize.height);

                // ��Ŀ��λ�������ڿ��ƶ�������
                cocos2d::Vec2 targetPos = clickPos.getClampPoint(moveRect.origin, moveRect.origin + moveRect.size);

                // ����Ӣ����Ҫ�ƶ��ľ����ʱ��
                float distance = targetPos.distance(getPosition());
                float duration = distance / moveSpeed;
                // �����ƶ�����
                //auto moveAction = cocos2d::MoveTo::create(duration, targetPos);
                auto moveAction = cocos2d::Sequence::create(
                    cocos2d::MoveTo::create(duration, targetPos),
                    cocos2d::CallFunc::create([this]() {
                        // �ƶ���ɺ󣬽��ƶ�״̬��Ϊ false
                        isMoving = false;
                        }),
                    nullptr
                            );
                // ִ���ƶ�����
                runAction(moveAction);
            }
        }
    }
}
void Player::takeDamage() {
    if (!bloodBar) {
        return;
    }
    float damageAmount = 20.0f; // �ܵ����˺�ֵ
    currentHealth -= damageAmount;

    if (currentHealth < 0.0f) {
        currentHealth = 0.0f;
    }
    /*
    * ���Ѫ��Ϊ�㣬Ӣ��ͼƬ��Ϊ����ͼƬ
    */
    float healthPercentage = currentHealth/MAX_HP;
    bloodBar->setPercentage(healthPercentage);//��Ѫ��������ʾ

}
//����ڵ�