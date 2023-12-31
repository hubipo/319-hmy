#include "myHero.h"
#include"HelloWorldScene.h"
#include"AppDelegate.h"
USING_NS_CC;

void Hero:: createHealthBar(Sprite* heroSprite)
{
    auto bdSprite1 = Sprite::create("blood_bd.png");
    bdSprite1->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 70));
    bdSprite1->setScale(0.5);
    this->addChild(bdSprite1, 0);//血条，英雄和血条底图都是Player的子节点

    auto bdSprite2 = Sprite::create("blood_bd.png");
    bdSprite2->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 65));
    bdSprite2->setScale(0.5);
    this->addChild(bdSprite2, 0);//血条，英雄和血条底图都是Player的子节点
    // 创建血条
    bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setScale(0.5);
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(0, 0.5)); // 设置进度条起点/?????
    bloodBar->setBarChangeRate(Vec2(1, 0)); // 设置进度条变化率
    bloodBar->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 70));
    bloodBar->setPercentage(hp); // 设置血条初始值
    //蓝条
    blueBar = ProgressTimer::create(Sprite::create("bluebar.png"));
    blueBar->setScale(0.5);
    blueBar->setType(ProgressTimer::Type::BAR);
    blueBar->setMidpoint(Vec2(0, 0.5)); // 设置进度条起点/?????
    blueBar->setBarChangeRate(Vec2(1, 0)); // 设置进度条变化率
    blueBar->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 65));
    blueBar->setPercentage(40);// 设置血条初始值

    //currentHealth = 100.0f;//
    this->addChild(bloodBar, 0);
    this->addChild(blueBar, 0);

}
void Hero::takeDamage(int&damage) {
    if (!bloodBar) {
        return;
    }
    //受到的伤害值
    hp -= damage;

    if (hp< 0.0f) {
        hp = 0.0f;
    }
    /*
    * 如果血量为零，英雄图片改为死亡图片
    */
    bloodBar->setPercentage(hp / MAX_HP1 * 100);//将血量减少显示
}
void Hero::Attack(Hero* targetHero)
{
    
    //targetHero->getAttack(this->attackPower);
    targetHero->hp -= this->attackPower;
    targetHero->takeDamage(this->attackPower);
    //this->attackCount++;
    return;
}

//判断是否死亡的函数，返回1则死亡，返回0则不死亡
//????//死亡逻辑要记得修改
void Hero::Death()
{
    // 停止所有动作
    this->stopAllActions();

    //把自己的状态设置为死亡
    this->isAlive = 0;

    // 播放死亡动画
    auto animation = Animation::create();
    //animation->addSpriteFrameWithFile("death1.png");//这里是添加死亡动画的每一帧
    //animation->addSpriteFrameWithFile("death2.png");
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
    for (auto hero : HerosInScene)
    {
        if (hero != nullptr && hero != this&&hero->hp>0)
        {
            // 计算当前英雄和其他英雄之间的距离
            float distance = this->calculateDistance(hero);
            if (distance < this->range)//??????///这里的range可能最后会被修改
                return 1;
        }
    }
    return 0;
}

Hero* Hero::findNearestEnemy()
{
    int minDistance = INT_MAX;
    Hero* targetHero = nullptr;

    for (auto hero : HerosInScene)
    {
        if (hero == nullptr)
            continue;
        if (hero != nullptr && hero != this&&hero->hp>0)//?????//最后可以修改为敌人
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
// 计算当前英雄和另一个英雄之间的距离
float Hero::calculateDistance(Hero* hero) const {
    float dx = this->getPositionX() - hero->getPositionX();
    float dy = this->getPositionY() - hero->getPositionY();
    return std::sqrt(dx * dx + dy * dy);
}
//战士 红剑魔
void Soldier::update(float deltaTime)
{

    Vec2 myPos = this->getPosition();

    Hero* targetHero = findNearestEnemy();

    if (targetHero == nullptr)
        return;
    Vec2 targetPos = targetHero->getPosition();

    Vec2 direction = (targetPos - myPos).getNormalized();

    if (this->findNearestHero())
    {
        this->stopAllActions();//对战逻辑就在这里加
        if (this->attackCount == 5)
        {
            this->UniqueSkill();
            this->Attack(targetHero);
            this->stopUniqueSkill();
            this->attackCount = 0;
            return;
        }
        
        this->Attack(targetHero);
        return;
        
    }

    Vec2 myNewPos = myPos + direction * 50 * deltaTime;
    this->setPosition(myNewPos);
}
void Soldier::UniqueSkill()
{
    this->attackPower += 10;
    this->attackSpeed -= 0.2;
    /*scheduleOnce([this](float dt) {
        // 停止技能效果
        stopUniqueSkill();
        }, 3.0f, "unique_skill_timer");
    unschedule("unique_skill_timer");*/
    
}
void Soldier::stopUniqueSkill()
{
    this->attackPower -= 10;
    this->attackSpeed += 0.2;
}
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
    this->attackPower = 5;
    this->attackSpeed = 0.7;
    this->attackCount = 0;
    this->range = 20;
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
    //healthbar
    createHealthBar(soldier);
    return true;
}
//射手
bool Shooter::init()
{

    if (!Sprite::init()) {
        return false;
    }
    this->heroType = HeroType::Soldier;
    this->name = "Shooter";
    this->hp = 100;
    //this->times = 6;
    this->armor = 3;
    this->attackPower = 5;
    this->attackSpeed = 0.7;
    //this->attackCount = 0;
    this->range = 50;
    //this->strike = 25;
    this->level = 1;
    this->fee = 1;
    this->Flag = 0;

    shooter = Sprite::create("Hero_911.png");
    shooter->setName("Hero_911");
    shooter->setAnchorPoint(Vec2(0, 0));
    shooter->setScale(0.3f);
    this->setContentSize(shooter->getContentSize() * 0.3);


    

    shooter->setPosition(Vec2(0, 0));
    this->addChild(shooter, 0);
    //healthbar
    createHealthBar(shooter);
    return true;
}
void Shooter::update(float deltaTime)
{
    
    Vec2 myPos = this->getPosition();

    Hero* targetHero = findNearestEnemy();

    if (targetHero == nullptr)
        return;
    Vec2 targetPos = targetHero->getPosition();

    Vec2 direction = (targetPos - myPos).getNormalized();

    if (this->findNearestHero())
    {
        this->stopAllActions();//对战逻辑就在这里加
        if (this->attackCount == 5)
        {
            //this->UniqueSkill();
            //this->Attack(targetHero);
            //this->attackCount = 0;
            //return;
        }
        
        this->Attack(targetHero);
        return;
        
    }

    Vec2 myNewPos = myPos + direction * 50 * deltaTime;
    this->setPosition(myNewPos);
}
void Shooter::UniqueSkill()
{
    this->attackPower += 10;
    this->attackSpeed -= 0.2;
    scheduleOnce([this](float dt) {
        // 停止技能效果
        stopUniqueSkill();
        }, 3.0f, "unique_skill_timer");
    unschedule("unique_skill_timer");
}
void Shooter::stopUniqueSkill()
{
    this->attackPower -= 10;
    this->attackSpeed += 0.2;
}
Shooter::Shooter()
{
}
//肉盾 蓝剑魔
bool Tank::init()
{

    if (!Sprite::init()) {
        return false;
    }
    this->heroType = HeroType::Tank;
    this->name = "Tank";
    this->hp = 100;
    //this->times = 6;
    this->armor = 20;
    this->attackPower = 2;
    this->attackSpeed = 0.7;
    //this->attackCount = 0;
    this->range = 20;
    //this->strike = 25;
    this->level = 1;
    this->fee = 1;
    this->Flag = 0;

    tank = Sprite::create("Hero_10010.png");
    tank->setName("Hero_10010");
    tank->setAnchorPoint(Vec2(0, 0));
    tank->setScale(0.3f);
    this->setContentSize(tank->getContentSize() * 0.3);

   

    tank->setPosition(Vec2(0, 0));
    this->addChild(tank, 0);
    //healthbar
    createHealthBar(tank);
    return true;
}
void Tank::update(float deltaTime)
{
    

    Vec2 myPos = this->getPosition();

    Hero* targetHero = findNearestEnemy();

    if (targetHero == nullptr)
        return;
    Vec2 targetPos = targetHero->getPosition();

    Vec2 direction = (targetPos - myPos).getNormalized();

    if (this->findNearestHero())
    {
        this->stopAllActions();//对战逻辑就在这里加
        if (this->attackCount == 5)
        {
            this->UniqueSkill();
            this->Attack(targetHero);
            this->attackCount = 0;
            return;
        }

        this->Attack(targetHero);
        return;

    }

    Vec2 myNewPos = myPos + direction * 50 * deltaTime;
    this->setPosition(myNewPos);
}
void Tank::UniqueSkill()
{
    this->attackPower += 10;
    this->attackSpeed -= 0.2;
    scheduleOnce([this](float dt) {
        // 停止技能效果
        stopUniqueSkill();
        }, 3.0f, "unique_skill_timer");
    unschedule("unique_skill_timer");
}
void Tank::stopUniqueSkill()
{
    this->attackPower -= 10;
    this->attackSpeed += 0.2;
}
Tank::Tank()
{
}