#ifndef WEAPON_H
#define WEAPON_H

#include "C110152338_Item.h"

class CWeapon : public CItem {
public:
	CWeapon (string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_attack = 0);	
	int getattackbonus ();
	int get_armor_cost();
	int get_armor_level();
	void add_armor_level();
	virtual void beUsed (CLifeEntity *);
	virtual void UnUsed (CLifeEntity *);
	virtual int isA ();
private:
	int bonus_attack;
};

#endif