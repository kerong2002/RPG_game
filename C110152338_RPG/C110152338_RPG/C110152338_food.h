#ifndef FOOD_H
#define FOOD_H

#include "C110152338_Item.h"

class CFood : public CItem {
public:
	CFood (string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_hp = 0);	
	int gethpbonus ();
	virtual void beUsed (CLifeEntity *);
	virtual void UnUsed (CLifeEntity *);
	virtual int isA ();
private:
	int bonus_hp;
};

#endif