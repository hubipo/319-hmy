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
	heroTypeNone = -1,//这个代表哪个类也没选中
	Soldier,// 战士
	Shooter,//豌豆射手
	Tank, //坚果
	CherryBomb, //樱桃炸弹
	Squash // 窝瓜
};



class Hero :public Sprite
{
public:
	std::string name;//英雄名
	int hp;//生命
	int times;//憋大招需要的次数
	int armor;//护甲
	int attackPower;//攻击力
	float attackSpeed;//攻速，这里的攻速意义是攻击时间间隔，装备对这个属性进行修改的时候是往这个数字上面去乘小数
	int range;//攻击范围
	int strike;//暴击率
	//std::mutex attackCountMutex;

	int level;//等级，可选1 2 3
	int fee;//标定这个英雄是几费卡
	int equipmentNum = 0;//英雄身上的装备数量
	bool isAlive = 1;//判断英雄是否存活，创建这个英雄之后默认这个英雄存活
	bool Flag;//己方是0，对方是1
	void createHealthBar(Sprite* heroSprite, int maxHp);

	HeroType heroType;

	std::vector<Hero*> HerosInScene;
	//这个函数是用来设置英雄的属性的，是在创建的时候就设置好的,具体的图像还要调sprite里面的create函数
	//virtual Hero* CreateHero() = 0;




	//受到伤害，想法是要减血量，然后英雄整体变红一下
	void getAttack(int iattackValue);

	//输出伤害，要完成检测最近的敌人，然后进行一次攻击，attackCount++
	void Attack(Hero* targetHero);

	//死亡的时候英雄的动作，比如倒地，然后几秒钟之后消失
	void Death();


	//英雄的攻击次数累计到times之后放一个大招，之后attckCount清零，重新开始计数
	//这个应该是一个虚函数，在每一个英雄的具体子类里面要写具体的大招实现
	virtual void UniqueSkill() = 0;

	//英雄加装备之后，本身的属性的一些变化调用这个函数
	//这个函数的想法是引入一个形参是装备的对象，然后用装备里面的数值来直接调整英雄的数值
	//返回值=1成功，返回值=0失败
	//bool AddEquipment(Equipment* iequipment);

	//这个函数是用来搜索最近的敌人的位置的
	Hero* findNearestEnemy();

	bool findNearestHero();

	// 计算当前英雄和另一个英雄之间的距离
	float calculateDistance(Hero* hero) const;
	virtual void update(float deltaTime) = 0;
};

class Soldier :public Hero
{
public:
	static bool heroCreated;
	Sprite* soldier;
	bool init();
	int attackCount = 0;//英雄累计的攻击次数，放一次大招清零一次


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
	int attackCount = 0;//英雄累计的攻击次数，放一次大招清零一次
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
	int attackCount = 0;//英雄累计的攻击次数，放一次大招清零一次
	int getAttackCount() { return attackCount; }
	CREATE_FUNC(Tank);
	void UniqueSkill();
	void stopUniqueSkill();
	void update(float deltaTime);
};
