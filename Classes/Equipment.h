#pragma once
#include"cocos2d.h"
#include<unordered_map>

class Equipment :public cocos2d::Sprite{
public:
    int index; 
    std::string name;
    int health;
    int mana;
    int attack;
    int defense;
    float attackSpeed;
    int criticalRate;

public:
    Equipment(int index, const std::string& name, int health, int mana, int attack, int defense, float attackSpeed, int criticalRate)
        : index(index), name(name), health(health), mana(mana), attack(attack), defense(defense), attackSpeed(attackSpeed), criticalRate(criticalRate) {};
    bool isLow() { return index <= 6; }
};

struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

class EquipmentSystem :public Equipment{

private:
    std::unordered_map<int, Equipment*> equipmentMap;
    std::unordered_map<std::pair<int, int>, Equipment*, PairHash> combinationMap;//装备合成map
public:
    EquipmentSystem();
    Equipment* combineEquipment(Equipment* equipment1, Equipment* equipment2);
    Equipment* getEquipment(int equipmentIndex);
    Equipment* addEquipment(int index, const std::string& name, int health, int mana, int attack, int defense, float attackSpeed, int criticalRate);
    void addCombination(int index, const std::string& name, int health, int mana, int attack, int defense, float attackSpeed, int criticalRate,int low1,int low2);
}equipmentSystem;

class EquipmentSlot :EquipmentSystem{
private:
    std::vector<Equipment*> slot;
public:
    EquipmentSlot();
    bool is_combine(Equipment*equi1, Equipment* equip2);
    bool addInSlot(Equipment* equip);
};

class EquipmentColumn :EquipmentSystem{
private:
    std::vector<Equipment*> column;
public:
    EquipmentColumn();
    bool addInColumn(Equipment* equip);
    Equipment* popColumn(int index);
};

class EquipmentScattered:EquipmentSystem{
public:
    Equipment* equipScattered;
    EquipmentScattered(Equipment* equip) {
        equipScattered = equip;
    }
};
