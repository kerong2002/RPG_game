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
	void set_wear_weapon_ID(int);
	void set_wear_equiment_ID(int);
	int show_wear_weapon_ID();
	int show_wear_eauiment_ID();
	virtual int attack (CLifeEntity *);
	virtual int magic_skill_attack(CLifeEntity*, int );
	virtual int defense (CLifeEntity *);	
	virtual int isA ();
	void captureItem (CItem *);
	void shop_captureItem(CItem*);
	void fish_captureItem(CItem*);
	void house_captureItem(CItem*);
	void save_captureItem(CItem* );
	int showAllBagItems ();
	bool useBagItems (int no);
	bool put_storeItems(int no);
	bool save_bag_Items(int no, int data_save);
	bool save_wear(int data_save);
	bool put_houseItems(int no);
	int goto_next_city (int next_dir);
	int get_current_city ();
	void set_job(int);
	int get_move_city(int move_city);
private:
	int cur_city;
	int Lucky;
	int get_job_num;
	int food_effect;
	bool food_bonus;
	int save_wear_weapon_ID;
	int save_wear_equiment_ID;
	CBag *bag;
};

#endif