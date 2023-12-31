#pragma once
#ifndef _HERO_
#define _HERO_

//#include"Equipment.h"

//#include"HelloWorldScene.h"
#include"cocos2d.h"


#define MY_FLAG 0
#define ENEMY_FLAG 1

#ifndef __COCOS__
#define __COCOS__
#endif // !__COCOS__
#define soldierMAX_HP 100
USING_NS_CC;
class Hero;
enum class HeroType {
	heroTypeNone = -1,//��������ĸ���Ҳûѡ��
	Soldier,// սʿ
	Shooter,//�㶹����
	Tank, //���
	CherryBomb, //ӣ��ը��
	Squash // �ѹ�
};



class Hero :public Sprite
{
public:
	std::string name;//Ӣ����
	int hp;//����
	int times;//�������Ҫ�Ĵ���
	int armor;//����
	int attackPower;//������
	float attackSpeed;//���٣�����Ĺ��������ǹ���ʱ������װ����������Խ����޸ĵ�ʱ�����������������ȥ��С��
	int range;//������Χ
	int strike;//������
	//std::mutex attackCountMutex;

	int level;//�ȼ�����ѡ1 2 3
	int fee;//�궨���Ӣ���Ǽ��ѿ�
	int equipmentNum = 0;//Ӣ�����ϵ�װ������
	bool isAlive = 1;//�ж�Ӣ���Ƿ���������Ӣ��֮��Ĭ�����Ӣ�۴��
	bool Flag;//������0���Է���1
	void createHealthBar(Sprite* heroSprite, int maxHp);

	HeroType heroType;

	std::vector<Hero*> HerosInScene;
	//�����������������Ӣ�۵����Եģ����ڴ�����ʱ������úõ�,�����ͼ��Ҫ��sprite�����create����
	//virtual Hero* CreateHero() = 0;




	//�ܵ��˺����뷨��Ҫ��Ѫ����Ȼ��Ӣ��������һ��
	void getAttack(int iattackValue);

	//����˺���Ҫ��ɼ������ĵ��ˣ�Ȼ�����һ�ι�����attackCount++
	void Attack(Hero* targetHero);

	//������ʱ��Ӣ�۵Ķ��������絹�أ�Ȼ������֮����ʧ
	void Death();


	//Ӣ�۵Ĺ��������ۼƵ�times֮���һ�����У�֮��attckCount���㣬���¿�ʼ����
	//���Ӧ����һ���麯������ÿһ��Ӣ�۵ľ�����������Ҫд����Ĵ���ʵ��
	virtual void UniqueSkill() = 0;

	//Ӣ�ۼ�װ��֮�󣬱�������Ե�һЩ�仯�����������
	//����������뷨������һ���β���װ���Ķ���Ȼ����װ���������ֵ��ֱ�ӵ���Ӣ�۵���ֵ
	//����ֵ=1�ɹ�������ֵ=0ʧ��
	//bool AddEquipment(Equipment* iequipment);

	//���������������������ĵ��˵�λ�õ�
	Hero* findNearestEnemy();

	bool findNearestHero();

	// ���㵱ǰӢ�ۺ���һ��Ӣ��֮��ľ���
	float calculateDistance(Hero* hero) const;
	virtual void update(float deltaTime) = 0;
};

class Soldier :public Hero
{
public:
	static bool heroCreated;
	Sprite* soldier;
	bool init();
	int attackCount = 0;//Ӣ���ۼƵĹ�����������һ�δ�������һ��


	CREATE_FUNC(Soldier);

	Soldier();
	int getAttackCount() { return attackCount; }
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);

};

#endif

class Shooter :public Hero
{
public:
	Sprite* shooter;
	bool init();
	Shooter();
	int attackCount = 0;//Ӣ���ۼƵĹ�����������һ�δ�������һ��
	int getAttackCount() { return attackCount; }
	CREATE_FUNC(Shooter);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};

class Tank :public Hero
{
public:
	Sprite* tank;
	bool init();
	Tank();
	int attackCount = 0;//Ӣ���ۼƵĹ�����������һ�δ�������һ��
	int getAttackCount() { return attackCount; }
	CREATE_FUNC(Tank);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};
