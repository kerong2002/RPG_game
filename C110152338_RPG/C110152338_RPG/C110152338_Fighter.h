#ifndef FIGHTER_H
#define FIGHTER_H

#include "C110152338_LifeEntity.h"

#define FIGHTER_MAXHP 100
#define FIGHTER_MAXSP 100
#define FIGHTER_MAXLUCKY 20

class CFood;
class CBag;
class CItem;

class CFighter : public CLifeEntity {
public:
	CFighter (int initHP = 0, int initSP = 0, int initLucky = 0, int in_city = 1);
	~CFighter();
	int getLucky ();
	int physicaldamage ();	
	virtual int attack (CLifeEntity *);
	virtual int defense (CLifeEntity *);	
	virtual int isA ();
	void captureItem (CItem *);
	int showAllBagItems ();
	bool useBagItems (int no);
	int goto_next_city (int next_dir);
	int get_current_city ();
private:
	int cur_city;
	int Lucky;
	CBag *bag;
};

#endif