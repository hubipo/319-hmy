#include "myHero.h"
#include"HelloWorldScene.h"
#include"AppDelegate.h"

void Hero::getAttack(int iattackValue)
{
    // 减血量
    this->hp -= iattackValue;

    // 英雄整体变红一下
    this->setColor(cocos2d::Color3B(255, 0, 0));

    // 假设延时一段时间后取消染色状态
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.5f);
    cocos2d::CallFunc* removeColor = cocos2d::CallFunc::create([this]() {
        this->setColor(cocos2d::Color3B(255, 255, 255));
        });
    cocos2d::Sequence* sequence = cocos2d::Sequence::create(delay, removeColor, nullptr);
    this->runAction(sequence);
}

void Hero::Attack()
{
    // 检测最近的敌人并进行攻击
    Hero* nearestEnemy = findNearestEnemy(); // 假设有一个函数用于找到最近的敌人
    if (nearestEnemy)
    {
        nearestEnemy->getAttack(this->attackPower); // 攻击最近的敌人
        attackCount++; // 攻击次数累加

        // 播放攻击动画,这里的图片内容要自己改
        this->runAction(Sequence::create(
            CallFunc::create([this]() {
                this->setTexture("attack.png"); // 变换图片样式
                }),
            DelayTime::create(1.0f), // 延迟1秒
                    CallFunc::create([this]() {
                    this->setTexture("normal.png"); // 变回原来的图片样式
                        }),
                    nullptr
                            ));
        //大招的实现打算在具体实现的函数中采用循环来不停调用attack函数，
        //然后计数到达了times再调用uniqueSkill函数
    }
}


void Hero::Death()
{
    // 停止所有动作
    this->stopAllActions();

    //把自己的状态设置为死亡
    this->isAlive = 0;

    // 播放死亡动画
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("death1.png");//这里是添加死亡动画的每一帧
    animation->addSpriteFrameWithFile("death2.png");
    animation->setDelayPerUnit(0.2f);
    auto animate = Animate::create(animation);
    auto removeSelf = RemoveSelf::create();
    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    this->runAction(sequence);

    // 执行其他死亡逻辑（例如播放音效、增加分数等）
    // ...
}

// 这个函数是用来搜索最近的敌人的位置的
Hero* Hero::findNearestEnemy() {
    // 这里可以根据具体的实现逻辑编写代码
    // 比如遍历敌方英雄列表，计算距离，找到最近的敌人并返回指针

    // 假设enemies是敌方英雄列表
    Hero* nearestEnemy = nullptr;
    constexpr float minDistance = std::numeric_limits<float>::max();  // 初始化为一个较大的值


    /*for (auto enemy : _enemies) {
        // 计算与当前敌人的距离
        float distance = calculateDistance(enemy);

        if (distance < minDistance) {
            minDistance = distance;
            nearestEnemy = enemy;
        }
    }*/
    

    return nearestEnemy;
}



// 计算当前英雄和另一个英雄之间的距离
float Hero::calculateDistance(Hero* hero) const {
    float dx = this->getPositionX() - hero->getPositionX();
    float dy = this->getPositionY() - hero->getPositionY();
    return std::sqrt(dx * dx + dy * dy);
}

//英雄的自动移动，调用完这个函数之后要英雄就已经走到有攻击对象在攻击范围内了，
//但是需要自己调用Attack()等函数
void Hero::HeroMove()
{
    // 获取当前英雄位置
    Vec2 curPosition = this->getPosition();
    float minDistance = FLT_MAX; // 初始化最小距离为无穷大
    Hero* targetHero = nullptr; // 目标英雄指针

    // 遍历所有敌方英雄，找到距离最近的敌人,_enemies是存储敌方英雄的数组
    targetHero = findNearestEnemy();

    // 如果没有敌人存活则不执行移动操作
    if (!targetHero) {
        return;
    }

    // 判断当前英雄是否在攻击范围内，如果不在则向敌人移动
    if (minDistance > this->range) {
        Vec2 targetPosition = targetHero->getPosition();
        // 向敌人移动
        this->runAction(MoveTo::create(1.0f, targetPosition));
    }
}

/*//英雄加装备之后，本身的属性的一些变化调用这个函数
    //这个函数的想法是引入一个形参是装备的对象，然后用装备里面的数值来直接调整英雄的数值
bool Hero::AddEquipment(Equipment* iequipment) {
    if (this->equipmentNum == 3)
        return 0;
    // 直接使用装备对象的属性增量来修改英雄属性值
    this->hp += iequipment->health;
    this->times += iequipment->mana;
    this->armor += iequipment->defense;
    this->attackPower += iequipment->attack;
    this->attackSpeed *= iequipment->attackSpeed;
    this->strike += iequipment->criticalRate;
    this->equipmentNum++;
    return 1;
}*/


void Soldier::UniqueSkill()
{

}

Soldier* Soldier::CreateHero(Vec2 iVec, float iSize)
{
    // 创建一个Soldier对象
    Soldier* soldier = new Soldier;

    // 创建一个Sprite对象，并设置其纹理为hero.png
    Sprite* sprite = Sprite::create("Soldier.png");

    // 设置Sprite的位置
    sprite->setPosition(iVec);

    // 设置Sprite的缩放比例
    sprite->setScale(iSize);

    // 将Sprite添加到Soldier对象中
    soldier->addChild(sprite);

    // 返回Soldier对象的指针
    return soldier;
}

bool Soldier::heroCreated = false;

void Soldier:: createHeroAtMousePos(Event* event)
{
    if (!heroCreated)
    {
        EventMouse* e = dynamic_cast<EventMouse*>(event);
        if (e)
        {
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
            Soldier* hero = CreateHero(heroPos, heroSize);
            // 将英雄添加到当前场景中
            auto scene = Director::getInstance()->getRunningScene();
            scene->addChild(hero);
            hero->heroCreated = true;
        }
    }
}









