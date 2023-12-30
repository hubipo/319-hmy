#include "myHero.h"
#include"HelloWorldScene.h"
#include"AppDelegate.h"
USING_NS_CC;

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
    Hero* nearestEnemy = nullptr;//findNearestEnemy(); // 假设有一个函数用于找到最近的敌人
    this->HeroMove();
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

//????//死亡逻辑要记得修改
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

// 这个函数是用来搜索最近的英雄的位置的，返回1就是有，返回0就是没有
bool Hero::findNearestHero()
{
    //float minDistance = -1;  // 记录最小距离
    //Hero* nearestEnemy = nullptr;  // 记录最近的敌人


    // 遍历场景中所有的英雄
    /*for (auto hero : this->HerosInScene) {
        if (hero == nullptr || hero == this)
            continue;

        // 判断是否为敌人，如果不是则跳过
        /*if (hero->Flag == this->Flag) {
            continue;
        }
        

        // 计算当前英雄和其他英雄之间的距离
        float distance = this->calculateDistance(hero);

        // 如果是第一次寻找敌人或者当前敌人更近，则更新最小距离和最近的敌人
        if (minDistance < 0 || distance < minDistance) {
            minDistance = distance;
            nearestEnemy = hero;
        }
    }*/
    //float minDistance = -1;  // 记录最小距离

    for (auto hero : this->HerosInScene)
    {
        if (hero != nullptr && hero != this)
        {
            // 计算当前英雄和其他英雄之间的距离
            float distance = this->calculateDistance(hero);
            if (distance < this->range)//??????///这里的range可能最后会被修改
                return 1;
        }
    }
    return 0;
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
    //float minDistance = FLT_MAX; // 初始化最小距离为无穷大
    //Hero* targetHero = nullptr; // 目标英雄指针

    // 遍历所有敌方英雄，找到距离最近的敌人,_enemies是存储敌方英雄的数组
    

    // 如果周围有英雄的话就不继续动，如果周围没有英雄的话就继续动
    if (findNearestHero()) {
        return;
    }

    //Vec2 targetPosition = targetHero->getPosition();

    // 向敌人移动
    float duration = 2.0f; // 移动时间
    // 获取窗口大小
    Size winSize = Director::getInstance()->getWinSize();

    // 计算中间位置
    Vec2 centerPosition(winSize.width / 2, winSize.height / 2);


    // 创建移动动作
    auto moveToCenter = MoveTo::create(duration, centerPosition);

    // 创建回调函数
    auto checkCollision = CallFunc::create([this]() {
        if (findNearestHero()) 
        {
            this->stopAllActions();
            return;
        }
        /*        // 获取场景中所有英雄节点
        auto heroList = this->getParent()->getChildren();
    for (auto& hero : heroList) {
        // 如果是当前英雄或者不是英雄节点，则跳过
        if (hero == this || !hero->getName().compare("background")) {
            continue;
        }
        // 计算当前英雄与周围英雄的距离
        auto distance = this->getPosition().distance(hero->getPosition());
        // 如果距离小于指定范围，则停止移动，并输出日志信息
        if (distance < range) {
            this->stopAllActions();
            CCLOG("Hero stopped due to collision with another hero.");
            return;
        }
    }
*/
    });

    // 创建序列动作
    auto sequence = Sequence::create(moveToCenter, checkCollision, nullptr);

    // 执行序列动作
    this->runAction(sequence);

    /*    // 执行序列动作
    this->runAction(sequence);    auto moveAction = MoveTo::create(duration, Mid);
    this->stopAllActions(); // 停止当前所有动作
    this->runAction(moveAction);
*/

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


Hero* Hero::findNearestEnemy()
{
    int minDistance = INT_MAX;
    Hero* targetHero = nullptr;

    for (auto hero : this->HerosInScene)
    {
        if (hero != nullptr && hero != this)//?????//最后可以修改为敌人
        {
            float distance = this->calculateDistance(hero);
            if (distance < minDistance)
            {
                minDistance = distance;
                targetHero = hero;
            }
        }
    }
    return targetHero;
}


void Hero::moveTo(Vec2 destination)
{
    auto moveAction = MoveTo::create(2, destination);
    this->runAction(moveAction);
}


void Soldier::UniqueSkill()
{
    this->attackPower += 10;
    this->attackSpeed -= 0.2;
    scheduleOnce([this](float dt) {
        // 停止技能效果
        stopUniqueSkill();
        }, 3.0f, "unique_skill_timer");
    unschedule("unique_skill_timer");
}

void Soldier::stopUniqueSkill()
{
    this->attackPower -= 10;
    this->attackSpeed += 0.2;
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

Soldier::Soldier()
{
}


bool Soldier::init()
{

    if (!Sprite::init()) {
        return false;
    }
    this->heroType = HeroType::Soldier;
    this->name = "Soldier";
    this->hp = 100;
    this->times = 6;
    this->armor = 5;
    this->attackPower = 20;
    this->attackSpeed = 0.7;
    this->range = 50;
    this->strike = 25;
    this->level = 1;
    this->fee = 1;
    this->Flag = 0;
    soldier = Sprite::create("Hero_10086.png");
    soldier->setName("Hero_10086");
    soldier->setAnchorPoint(Vec2(0, 0));
    soldier->setScale(0.3f);
    this->setContentSize(soldier->getContentSize() * 0.3);

    soldier->setPosition(Vec2(0, 0));
    this->addChild(soldier, 0);

   
    return true;
}
void Soldier::update(float deltaTime)
{
    Vec2 myPos = this->getPosition();

    Hero* targetHero = findNearestEnemy();

    Vec2 targetPos = targetHero->getPosition();

    Vec2 direction = (targetPos - myPos).getNormalized();

    if (this->findNearestHero())
    {
        this->stopAllActions();
        return;
    }

    Vec2 myNewPos = myPos + direction * 50 * deltaTime;
    this->setPosition(myNewPos);
}






