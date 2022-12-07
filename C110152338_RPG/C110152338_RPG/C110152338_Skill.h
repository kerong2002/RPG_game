#ifndef SKILL_H
#define SKILL_H

#include "C110152338_Item.h"

class CSkill : public CItem {
public:
	CSkill(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_attack = 0, int init_skill_cost = 0, int init_skill_level = 0);
	int getattackbonus();
	int get_skill_cost();
	int get_skill_level();
	void add_skill_level();
	virtual void beUsed(CLifeEntity*);
	virtual void UnUsed(CLifeEntity*);
	virtual int isA();
private:
	int bonus_attack;
	int skill_cost;
	int skill_level;
};

#endif