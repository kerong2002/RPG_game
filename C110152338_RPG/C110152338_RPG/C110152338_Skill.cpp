#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_Skill.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_def.h"

using namespace std;

CSkill::CSkill(string inname, int initSize, int initWeight, int initID, int init_attack,int init_skill_cost, int init_skill_level) : CItem(inname, initSize, initWeight, initID) {
	bonus_attack = init_attack;
	skill_cost = init_skill_cost;
	skill_level = init_skill_level;
}

int CSkill::getattackbonus() {
	return bonus_attack;
}

int CSkill::get_skill_cost() {
	return skill_cost;
}

int CSkill::get_skill_level() {
	return skill_level;
}

void CSkill::add_skill_level() {
	skill_level += 1;
}

void CSkill::beUsed(CLifeEntity* le) {
	cout << "玩家使用裝備" << getName() << ", ";
	cout << "生命力從原本 " << le->getMAXHP();
	le->addMAXHP(this->getattackbonus());
	cout << "上升到 " << le->getMAXHP() << endl;
}

void CSkill::UnUsed(CLifeEntity* le) {
	cout << "玩家 " << getName() << " ";
	cout << "生命力從原本 " << le->getMAXHP();
	le->delMAXHP(this->getattackbonus());
	cout << "下降到 " << le->getMAXHP() << endl;
}


int CSkill::isA() {
	return eskill;
}