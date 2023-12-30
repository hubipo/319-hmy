#include "myHero.h"
#include"HelloWorldScene.h"
#include"AppDelegate.h"
USING_NS_CC;

void Hero::getAttack(int iattackValue)
{
    // ��Ѫ��
    this->hp -= iattackValue;

    // Ӣ��������һ��
    this->setColor(cocos2d::Color3B(255, 0, 0));

    // ������ʱһ��ʱ���ȡ��Ⱦɫ״̬
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.5f);
    cocos2d::CallFunc* removeColor = cocos2d::CallFunc::create([this]() {
        this->setColor(cocos2d::Color3B(255, 255, 255));
        });
    cocos2d::Sequence* sequence = cocos2d::Sequence::create(delay, removeColor, nullptr);
    this->runAction(sequence);
}

void Hero::Attack()
{
    // �������ĵ��˲����й���
    Hero* nearestEnemy = nullptr;//findNearestEnemy(); // ������һ�����������ҵ�����ĵ���
    this->HeroMove();
    if (nearestEnemy)
    {
        nearestEnemy->getAttack(this->attackPower); // ��������ĵ���
        attackCount++; // ���������ۼ�

        // ���Ź�������,�����ͼƬ����Ҫ�Լ���
        this->runAction(Sequence::create(
            CallFunc::create([this]() {
                this->setTexture("attack.png"); // �任ͼƬ��ʽ
                }),
            DelayTime::create(1.0f), // �ӳ�1��
                    CallFunc::create([this]() {
                    this->setTexture("normal.png"); // ���ԭ����ͼƬ��ʽ
                        }),
                    nullptr
                            ));
        //���е�ʵ�ִ����ھ���ʵ�ֵĺ����в���ѭ������ͣ����attack������
        //Ȼ�����������times�ٵ���uniqueSkill����
    }
}

//????//�����߼�Ҫ�ǵ��޸�
void Hero::Death()
{
    // ֹͣ���ж���
    this->stopAllActions();

    //���Լ���״̬����Ϊ����
    this->isAlive = 0;

    // ������������
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("death1.png");//�������������������ÿһ֡
    animation->addSpriteFrameWithFile("death2.png");
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
    //float minDistance = -1;  // ��¼��С����
    //Hero* nearestEnemy = nullptr;  // ��¼����ĵ���


    // �������������е�Ӣ��
    /*for (auto hero : this->HerosInScene) {
        if (hero == nullptr || hero == this)
            continue;

        // �ж��Ƿ�Ϊ���ˣ��������������
        /*if (hero->Flag == this->Flag) {
            continue;
        }
        

        // ���㵱ǰӢ�ۺ�����Ӣ��֮��ľ���
        float distance = this->calculateDistance(hero);

        // ����ǵ�һ��Ѱ�ҵ��˻��ߵ�ǰ���˸������������С���������ĵ���
        if (minDistance < 0 || distance < minDistance) {
            minDistance = distance;
            nearestEnemy = hero;
        }
    }*/
    //float minDistance = -1;  // ��¼��С����

    for (auto hero : this->HerosInScene)
    {
        if (hero != nullptr && hero != this)
        {
            // ���㵱ǰӢ�ۺ�����Ӣ��֮��ľ���
            float distance = this->calculateDistance(hero);
            if (distance < this->range)//??????///�����range�������ᱻ�޸�
                return 1;
        }
    }
    return 0;
}



// ���㵱ǰӢ�ۺ���һ��Ӣ��֮��ľ���
float Hero::calculateDistance(Hero* hero) const {
    float dx = this->getPositionX() - hero->getPositionX();
    float dy = this->getPositionY() - hero->getPositionY();
    return std::sqrt(dx * dx + dy * dy);
}

//Ӣ�۵��Զ��ƶ����������������֮��ҪӢ�۾��Ѿ��ߵ��й��������ڹ�����Χ���ˣ�
//������Ҫ�Լ�����Attack()�Ⱥ���
void Hero::HeroMove()
{
    // ��ȡ��ǰӢ��λ��
    Vec2 curPosition = this->getPosition();
    //float minDistance = FLT_MAX; // ��ʼ����С����Ϊ�����
    //Hero* targetHero = nullptr; // Ŀ��Ӣ��ָ��

    // �������ез�Ӣ�ۣ��ҵ���������ĵ���,_enemies�Ǵ洢�з�Ӣ�۵�����
    

    // �����Χ��Ӣ�۵Ļ��Ͳ��������������Χû��Ӣ�۵Ļ��ͼ�����
    if (findNearestHero()) {
        return;
    }

    //Vec2 targetPosition = targetHero->getPosition();

    // ������ƶ�
    float duration = 2.0f; // �ƶ�ʱ��
    // ��ȡ���ڴ�С
    Size winSize = Director::getInstance()->getWinSize();

    // �����м�λ��
    Vec2 centerPosition(winSize.width / 2, winSize.height / 2);


    // �����ƶ�����
    auto moveToCenter = MoveTo::create(duration, centerPosition);

    // �����ص�����
    auto checkCollision = CallFunc::create([this]() {
        if (findNearestHero()) 
        {
            this->stopAllActions();
            return;
        }
        /*        // ��ȡ����������Ӣ�۽ڵ�
        auto heroList = this->getParent()->getChildren();
    for (auto& hero : heroList) {
        // ����ǵ�ǰӢ�ۻ��߲���Ӣ�۽ڵ㣬������
        if (hero == this || !hero->getName().compare("background")) {
            continue;
        }
        // ���㵱ǰӢ������ΧӢ�۵ľ���
        auto distance = this->getPosition().distance(hero->getPosition());
        // �������С��ָ����Χ����ֹͣ�ƶ����������־��Ϣ
        if (distance < range) {
            this->stopAllActions();
            CCLOG("Hero stopped due to collision with another hero.");
            return;
        }
    }
*/
    });

    // �������ж���
    auto sequence = Sequence::create(moveToCenter, checkCollision, nullptr);

    // ִ�����ж���
    this->runAction(sequence);

    /*    // ִ�����ж���
    this->runAction(sequence);    auto moveAction = MoveTo::create(duration, Mid);
    this->stopAllActions(); // ֹͣ��ǰ���ж���
    this->runAction(moveAction);
*/

}

/*//Ӣ�ۼ�װ��֮�󣬱�������Ե�һЩ�仯�����������
    //����������뷨������һ���β���װ���Ķ���Ȼ����װ���������ֵ��ֱ�ӵ���Ӣ�۵���ֵ
bool Hero::AddEquipment(Equipment* iequipment) {
    if (this->equipmentNum == 3)
        return 0;
    // ֱ��ʹ��װ������������������޸�Ӣ������ֵ
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
        if (hero != nullptr && hero != this)//?????//�������޸�Ϊ����
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
        // ֹͣ����Ч��
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
    // ����һ��Soldier����
    Soldier* soldier = new Soldier;

    // ����һ��Sprite���󣬲�����������Ϊhero.png
    Sprite* sprite = Sprite::create("Soldier.png");

    // ����Sprite��λ��
    sprite->setPosition(iVec);

    // ����Sprite�����ű���
    sprite->setScale(iSize);

    // ��Sprite��ӵ�Soldier������
    soldier->addChild(sprite);

    // ����Soldier�����ָ��
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






