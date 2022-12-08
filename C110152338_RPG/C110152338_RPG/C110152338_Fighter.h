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
	CFighter (int job = 0, int initHP = 0, int initSP = 0, int initLucky = 0, string name="", int in_city = 1);
	~CFighter();
	int getLucky ();
	int physicaldamage ();	
	//int magic_damage(int);
	void show_fighter_detail(CLifeEntity*);
	virtual int attack (CLifeEntity *);
	//virtual int magic_attack(CLifeEntity*,int);
	virtual int defense (CLifeEntity *);	
	virtual int isA ();
	void captureItem (CItem *);
	void shop_captureItem(CItem*);
	int showAllBagItems ();
	bool useBagItems (int no);
	int goto_next_city (int next_dir);
	int get_current_city ();
	void set_job(int);
	int get_move_city(int move_city);
private:
	int cur_city;
	int Lucky;
	int get_job_num;
	CBag *bag;
};

#endif