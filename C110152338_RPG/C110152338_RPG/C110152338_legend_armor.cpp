#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_legend_armor.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_def.h"

using namespace std;

CLegend_Armor::CLegend_Armor(string inname, int initSize, int initWeight, int initID, int init_attack, int init_armor_cost, int init_armor_level) : CItem(inname, initSize, initWeight, initID) {
	bonus_attack = init_attack;
	armor_cost = init_armor_cost;
	armor_level = init_armor_level;
}

int CLegend_Armor::getattackbonus() {
	return bonus_attack;
}

int CLegend_Armor::get_armor_cost() {
	return armor_cost;
}

int CLegend_Armor::get_armor_level() {
	return armor_level;
}

void CLegend_Armor::add_armor_level() {
	armor_level += 1;
}

void CLegend_Armor::beUsed(CLifeEntity* le) {
	cout << "���a�ϥθ˳�" << getName() << ", ";
	cout << "�ͩR�O�q�쥻 " << le->getMAXHP();
	le->addMAXHP(this->getattackbonus());
	cout << "�W�ɨ� " << le->getMAXHP() << endl;
}

void CLegend_Armor::UnUsed(CLifeEntity* le) {
	cout << "���a " << getName() << " ";
	cout << "�ͩR�O�q�쥻 " << le->getMAXHP();
	le->delMAXHP(this->getattackbonus());
	cout << "�U���� " << le->getMAXHP() << endl;
}


int CLegend_Armor::isA() {
	return earmor;
}