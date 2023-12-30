#pragma once
#ifndef _HERO_
#define _HERO_

//#include"Equipment.h"

//#include"HelloWorldScene.h"
#include"cocos2d.h"


#ifndef __COCOS__
#define __COCOS__
#endif // !__COCOS__

USING_NS_CC;

enum class HeroType {
	heroTypeNone = -1,//��������ĸ���Ҳûѡ��
	Soldier,// սʿ
	Peashooter,//�㶹����
	WallNut, //���
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


	int level;//�ȼ�����ѡ1 2 3
	int fee;//�궨���Ӣ���Ǽ��ѿ�
	int equipmentNum = 0;//Ӣ�����ϵ�װ������
	int attackCount = 0;//Ӣ���ۼƵĹ�����������һ�δ�������һ��
	bool isAlive = 1;//�ж�Ӣ���Ƿ���������Ӣ��֮��Ĭ�����Ӣ�۴��
	bool Flag;//������0���Է���1

	HeroType heroType;
	Hero* findNearestEnemy();

	std::vector<Hero*> HerosInScene;


	//�����������������Ӣ�۵����Եģ����ڴ�����ʱ������úõ�,�����ͼ��Ҫ��sprite�����create����
	//virtual Hero* CreateHero() = 0;


	void moveTo(Vec2 destination);

	//�ܵ��˺����뷨��Ҫ��Ѫ����Ȼ��Ӣ��������һ��
	void getAttack(int iattackValue);

	//����˺���Ҫ��ɼ������ĵ��ˣ�Ȼ�����һ�ι�����attackCount++
	void Attack();

	//������ʱ��Ӣ�۵Ķ��������絹�أ�Ȼ������֮����ʧ
	void Death();

	//Ӣ�۵������ƶ�����⵽��ǰ�����ĵ�������֮��Ѱ����һ�������Ӣ��Ȼ���ƶ�
	void HeroMove();

	//Ӣ�۵Ĺ��������ۼƵ�times֮���һ�����У�֮��attckCount���㣬���¿�ʼ����
	//���Ӧ����һ���麯������ÿһ��Ӣ�۵ľ�����������Ҫд����Ĵ���ʵ��
	virtual void UniqueSkill() = 0;

	//Ӣ�ۼ�װ��֮�󣬱�������Ե�һЩ�仯�����������
	//����������뷨������һ���β���װ���Ķ���Ȼ����װ���������ֵ��ֱ�ӵ���Ӣ�۵���ֵ
	//����ֵ=1�ɹ�������ֵ=0ʧ��
	//bool AddEquipment(Equipment* iequipment);

	//���������������������ĵ��˵�λ�õ�
	bool findNearestHero();

	// ���㵱ǰӢ�ۺ���һ��Ӣ��֮��ľ���
	float calculateDistance(Hero* hero) const;

};

class Soldier :public Hero
{
public:
	static bool heroCreated;
	Sprite* soldier;
    bool init();

	CREATE_FUNC(Soldier);

	Soldier();
	static Soldier* CreateHero(Vec2 iVec,float iSize);
	bool onTouchBegan(Touch* touch, Event* event);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};

#endif
