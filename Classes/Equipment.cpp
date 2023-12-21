#include"Equipment.h"

EquipmentSystem::EquipmentSystem() {
	addEquipment(1, "腰带", 200, 0, 0, 0, 0, 0);
	addEquipment(2, "蓝水晶", 0, -1, 0, 0, 0, 0);
	addEquipment(3, "大剑", 0, 0, 20, 0, 0, 0);
	addEquipment(4, "护甲", 0, 0, 0, 5, 0, 0);
	addEquipment(5, "弓箭", 0, 0, 0, 0, 0.8, 0);
	addEquipment(6, "拳套", 0, 0, 0, 0, 0, 10);

	//合成装备
	addCombination(7, "狂徒铠甲", 1000, 0, 0, 0, 0, 0,1,1);
	addCombination(8, "蓝BUFF", 0, -4, 0, 0, 0, 0,2,2);
	addCombination(9, "光辉之剑", 0, 0, 60, 0, 0, 0,3,3);
	addCombination(10, "棘刺背心", 0, 0, 0, 20, 0, 0,4,4);
	addCombination(11, "红BUFF", 0, 0, 0, 0, 0.4, 0,5,5);
	addCombination(12, "秘法手套", 0, 0, 0, 0, 0, 40,6,6);
	addCombination(13, "救赎", 500, -2, 0, 0, 0, 0,1,2);
	addCombination(14, "斯特拉克的挑战护手", 500, 0, 30, 0, 0, 0,1,3);
	addCombination(15, "日炎斗篷", 500, 0, 0, 10, 0, 0,1,4);
	addCombination(16, "纳什之牙", 500, 0, 0, 0, 0.6, 0,1,5);
	addCombination(17, "破防者", 500, 0, 0, 0, 0, 25,1,6);
	addCombination(18, "朔极之矛", 0, -2, 30, 0, 0, 0,2,3);
	addCombination(19, "圣盾使的契约", 0, -2, 0,10, 0, 0,2,4);
	addCombination(20, "斯塔缇克电刃", 0, -2, 0, 0, 0.6, 0,2,5);
	addCombination(21, "正义之手", 0, -2, 0, 0, 0, 25,2,6);
	addCombination(22, "夜之锋刃", 0, 0, 30, 10, 0, 0, 3, 4);
	addCombination(23, "巨人捕手", 0, 0, 30, 0, 0.6, 0, 3, 5);
	addCombination(24, "无尽之刃", 0, 0, 30, 0,  0, 25, 3, 6);
	addCombination(25, "泰坦的坚决", 0, 0, 0, 10, 0.6,  0, 4, 5);
	addCombination(26, "坚定之心", 0, 0, 0, 10, 0, 25, 4, 6);
	addCombination(27, "最后的轻语", 0, 0, 0, 0, 0.6, 25, 5, 6);
}

Equipment* EquipmentSystem::addEquipment(int index, const std::string& name, int health, int mana, int attack, int defense, float attackSpeed, int criticalRate)
{
	Equipment* equip = new Equipment(index, name, health, mana, attack, defense, attackSpeed, criticalRate);
	equipmentMap[index] = equip;
}

void EquipmentSystem::addCombination(int index, const std::string& name, int health, int mana, int attack, int defense, float attackSpeed, int criticalRate,int low1,int low2)
{
	combinationMap[std::make_pair(low1, low2)]=addEquipment(index, name, health, mana, attack, defense, attackSpeed, criticalRate);
	combinationMap[std::make_pair(low2, low1)] = combinationMap[std::make_pair(low1, low2)];
}

Equipment* EquipmentSystem::combineEquipment(Equipment* equip1,Equipment*equip2) {
	if (equip1->isLow() && equip2->isLow()) {
		return combinationMap[std::pair<int, int>(equip1->index, equip2->index)];
	}
	else
		return NULL;
}

Equipment* EquipmentSystem::getEquipment(int index) {
	return equipmentMap[index];
}

EquipmentSlot::EquipmentSlot() {
	for (int i = 0; i < 3; i++) {
		slot.push_back(NULL);
	}
}

bool EquipmentSlot::is_combine(Equipment* equip1, Equipment* equip2) {
	if (equip1->index <= 3 && equip2->index <= 3)
		return true;
	return false;
}

bool EquipmentSlot::addInSlot(Equipment*equip) {
	for (int i = 0; i < 3; i++) {
		if(!slot[i])
		{slot[i] = equip; return 1;}
		else if(slot[i]&&is_combine(equip,slot[i]))
		{
			slot[i] = combineEquipment(slot[i], equip);
			return 1;
		}
	}
	return 0;
}

EquipmentColumn::EquipmentColumn() {
	for (int i = 0; i < 12; i++) 
	{
		column.push_back(NULL);
    }
}

bool EquipmentColumn::addInColumn(Equipment* equip) {
	for (int i = 0; i < 12; i++) {
		if (!column[i])
		{
			column[i] = equip;
			return 1;
		}
	}
	return 0;
}

Equipment* EquipmentColumn::popColumn(int index) {
	if (column[index])
	{
		Equipment* temp = column[index];
		column[index] = NULL;
		return temp;
	}
	else
		return NULL;
}