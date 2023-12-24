#include "myHero.h"
#include"HelloWorldScene.h"
#include"AppDelegate.h"

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
    Hero* nearestEnemy = findNearestEnemy(); // ������һ�����������ҵ�����ĵ���
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

// ���������������������ĵ��˵�λ�õ�
Hero* Hero::findNearestEnemy() {
    // ������Ը��ݾ����ʵ���߼���д����
    // ��������з�Ӣ���б�������룬�ҵ�����ĵ��˲�����ָ��

    // ����enemies�ǵз�Ӣ���б�
    Hero* nearestEnemy = nullptr;
    constexpr float minDistance = std::numeric_limits<float>::max();  // ��ʼ��Ϊһ���ϴ��ֵ


    /*for (auto enemy : _enemies) {
        // �����뵱ǰ���˵ľ���
        float distance = calculateDistance(enemy);

        if (distance < minDistance) {
            minDistance = distance;
            nearestEnemy = enemy;
        }
    }*/
    

    return nearestEnemy;
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
    float minDistance = FLT_MAX; // ��ʼ����С����Ϊ�����
    Hero* targetHero = nullptr; // Ŀ��Ӣ��ָ��

    // �������ез�Ӣ�ۣ��ҵ���������ĵ���,_enemies�Ǵ洢�з�Ӣ�۵�����
    targetHero = findNearestEnemy();

    // ���û�е��˴����ִ���ƶ�����
    if (!targetHero) {
        return;
    }

    // �жϵ�ǰӢ���Ƿ��ڹ�����Χ�ڣ����������������ƶ�
    if (minDistance > this->range) {
        Vec2 targetPosition = targetHero->getPosition();
        // ������ƶ�
        this->runAction(MoveTo::create(1.0f, targetPosition));
    }
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


void Soldier::UniqueSkill()
{

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

void Soldier:: createHeroAtMousePos(Event* event)
{
    if (!heroCreated)
    {
        EventMouse* e = dynamic_cast<EventMouse*>(event);
        if (e)
        {
            // ��ȡ�������λ��
            Vec2 clickPos = e->getLocationInView();
            clickPos = Director::getInstance()->convertToGL(clickPos);

            // ��ȡ��Ļ�ɼ������С
            Size visibleSize = Director::getInstance()->getVisibleSize();

            // �������¶Գ�λ��
            float symmetricalY = visibleSize.height - clickPos.y;

            // ����Ӣ�۶���
            Vec2 heroPos = Vec2(clickPos.x, symmetricalY);
            float heroSize = 0.3f;
            Soldier* hero = CreateHero(heroPos, heroSize);
            // ��Ӣ����ӵ���ǰ������
            auto scene = Director::getInstance()->getRunningScene();
            scene->addChild(hero);
            hero->heroCreated = true;
        }
    }
}









