#include "myHero.h"
#include"HelloWorldScene.h"
#include"AppDelegate.h"
USING_NS_CC;

void Hero:: createHealthBar(Sprite* heroSprite)
{
    auto bdSprite1 = Sprite::create("blood_bd.png");
    bdSprite1->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 70));
    bdSprite1->setScale(0.5);
    this->addChild(bdSprite1, 0);//Ѫ����Ӣ�ۺ�Ѫ����ͼ����Player���ӽڵ�

    auto bdSprite2 = Sprite::create("blood_bd.png");
    bdSprite2->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 65));
    bdSprite2->setScale(0.5);
    this->addChild(bdSprite2, 0);//Ѫ����Ӣ�ۺ�Ѫ����ͼ����Player���ӽڵ�
    // ����Ѫ��
    bloodBar = ProgressTimer::create(Sprite::create("blood.png"));
    bloodBar->setScale(0.5);
    bloodBar->setType(ProgressTimer::Type::BAR);
    bloodBar->setMidpoint(Vec2(0, 0.5)); // ���ý��������/?????
    bloodBar->setBarChangeRate(Vec2(1, 0)); // ���ý������仯��
    bloodBar->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 70));
    bloodBar->setPercentage(hp); // ����Ѫ����ʼֵ
    //����
    blueBar = ProgressTimer::create(Sprite::create("bluebar.png"));
    blueBar->setScale(0.5);
    blueBar->setType(ProgressTimer::Type::BAR);
    blueBar->setMidpoint(Vec2(0, 0.5)); // ���ý��������/?????
    blueBar->setBarChangeRate(Vec2(1, 0)); // ���ý������仯��
    blueBar->setPosition(heroSprite->getAnchorPoint() + Vec2(50, 65));
    blueBar->setPercentage(40);// ����Ѫ����ʼֵ

    //currentHealth = 100.0f;//
    this->addChild(bloodBar, 0);
    this->addChild(blueBar, 0);

}
void Hero::takeDamage(int&damage) {
    if (!bloodBar) {
        return;
    }
    //�ܵ����˺�ֵ
    hp -= damage;

    if (hp< 0.0f) {
        hp = 0.0f;
    }
    /*
    * ���Ѫ��Ϊ�㣬Ӣ��ͼƬ��Ϊ����ͼƬ
    */
    bloodBar->setPercentage(hp / MAX_HP1 * 100);//��Ѫ��������ʾ
}
void Hero::Attack(Hero* targetHero)
{
    
    //targetHero->getAttack(this->attackPower);
    targetHero->hp -= this->attackPower;
    targetHero->takeDamage(this->attackPower);
    //this->attackCount++;
    return;
}

//�ж��Ƿ������ĺ���������1������������0������
//????//�����߼�Ҫ�ǵ��޸�
void Hero::Death()
{
    // ֹͣ���ж���
    this->stopAllActions();

    //���Լ���״̬����Ϊ����
    this->isAlive = 0;

    // ������������
    auto animation = Animation::create();
    //animation->addSpriteFrameWithFile("death1.png");//�������������������ÿһ֡
    //animation->addSpriteFrameWithFile("death2.png");
    animation->setDelayPerUnit(0.2f);
    auto animate = Animate::create(animation);
    auto removeSelf = RemoveSelf::create();
    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    this->runAction(sequence);

    // ִ�����������߼������粥����Ч�����ӷ����ȣ�
    // ...
}

// ����������������������Ӣ�۵�λ�õģ�����1�����У�����0����û��
bool Hero::findNearestHero()
{
    for (auto hero : HerosInScene)
    {
        if (hero != nullptr && hero != this&&hero->hp>0)
        {
            // ���㵱ǰӢ�ۺ�����Ӣ��֮��ľ���
            float distance = this->calculateDistance(hero);
            if (distance < this->range)//??????///�����range�������ᱻ�޸�
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
        if (hero != nullptr && hero != this&&hero->hp>0)//?????//�������޸�Ϊ����
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
// ���㵱ǰӢ�ۺ���һ��Ӣ��֮��ľ���
float Hero::calculateDistance(Hero* hero) const {
    float dx = this->getPositionX() - hero->getPositionX();
    float dy = this->getPositionY() - hero->getPositionY();
    return std::sqrt(dx * dx + dy * dy);
}
//սʿ �콣ħ
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
        this->stopAllActions();//��ս�߼����������
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
        // ֹͣ����Ч��
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
//����
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
        this->stopAllActions();//��ս�߼����������
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
        // ֹͣ����Ч��
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
//��� ����ħ
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
        this->stopAllActions();//��ս�߼����������
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
        // ֹͣ����Ч��
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