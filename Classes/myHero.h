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
#define MAX_HP1 500.0

USING_NS_CC;
class Hero;
enum class HeroType {
	heroTypeNone = -1,//��������ĸ���Ҳûѡ��
	Soldier,// սʿ
	Shooter,//����
	Tank, //̹��
	Wei, //ε
	Dragon, // ��������
	Assassin
};
class Hero :public Sprite
{
public:
	std::string name;//Ӣ����
	int hp;//����
	int blue = 40;
	int times;//�������Ҫ�Ĵ���
	int armor;//����
	int attackPower;//������
	float attackSpeed;//���٣�����Ĺ��������ǹ���ʱ������װ����������Խ����޸ĵ�ʱ�����������������ȥ��С��
	int range;//������Χ
	int strike;//������
	int speed;
	int attackCount = 0;//Ӣ���ۼƵĹ�����������һ�δ�������һ��
	//std::mutex attackCountMutex;

	int level;//�ȼ�����ѡ1 2 3
	int fee;//�궨���Ӣ���Ǽ��ѿ�
	int equipmentNum = 0;//Ӣ�����ϵ�װ������
	bool isAlive = 1;//�ж�Ӣ���Ƿ���������Ӣ��֮��Ĭ�����Ӣ�۴��
	bool Flag;//������0���Է���1

	cocos2d::ProgressTimer* bloodBar;
	cocos2d::ProgressTimer* blueBar;

	HeroType heroType;

	std::vector<Hero*> HerosInScene;
	//�����������������Ӣ�۵����Եģ����ڴ�����ʱ������úõ�,�����ͼ��Ҫ��sprite�����create����
	//virtual Hero* CreateHero() = 0;
	void createHealthBar(Sprite* heroSprite);

	void takeDamage(int&damage);

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


	CREATE_FUNC(Soldier);

	Soldier();
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
	CREATE_FUNC(Tank);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};

class Wei :public Hero
{
public:
	Sprite* wei;
	bool init();
	Wei();
	CREATE_FUNC(Wei);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};

class Dragon :public Hero
{
public:
	Sprite* dragon;
	bool init();
	Dragon();
	CREATE_FUNC(Dragon);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};

class Assassin :public Hero
{
public:
	Sprite* assassin;
	bool init();
	Assassin();
	CREATE_FUNC(Assassin);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};