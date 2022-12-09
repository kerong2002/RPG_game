#ifndef LEGEND_ARMOR_H
#define LEGEND_ARMOR_H

#include "C110152338_Item.h"

class CLegend_Armor : public CItem {
public:
	CLegend_Armor(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_attack = 0, int init_armor_cost = 0, int init_armor_level = 0);
	int getattackbonus();
	int get_armor_cost();
	int get_armor_level();
	void add_armor_level();
	virtual void beUsed(CLifeEntity*);
	virtual void UnUsed(CLifeEntity*);
	virtual int isA();
private:
	int bonus_attack;
	int armor_cost;
	int armor_level;
};

#endif