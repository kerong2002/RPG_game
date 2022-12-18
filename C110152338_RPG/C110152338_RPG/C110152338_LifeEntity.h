#ifndef LIFEENTITY_H
#define LIFEENTITY_H

#include <string>
#include "C110152338_weapon.h"
#include "C110152338_Equiment.h"
#include "C110152338_Skill.h"
#include "C110152338_food.h"
#include "C110152338_legend_armor.h"

#define MAXBLOODBARLEN 40
using namespace std;

class CLifeEntity {
public:
	CLifeEntity(int initHP = 0, int initSP = 0, string initname = "");
	void setInitSPHP(int initHP = 0, int initSP = 0);
	void set_all_thing(string , int, int, int, int, int, int, int, int, int, int);
	void read_hack_data();
	void out_hack_data();
	void file_read_data();
	void out_all_thing();
	void setInitLucky(int);
	void set_output_data_num(int);
	int show_output_data_num();
	bool isdead();
	void setHP(int);
	void addHP(int);
	int getHP();
	int getMAXHP();
	int getSP();
	int getMAXSP();
	int getDegree();
	int getEXP();
	void setMoney(int);
	int showMoney();
	int getMoney();
	void AddLucky(int);
	int show_Lucky();
	void subMoney(int);
	void AddMoney(int);
	void addSP(int);
	void delSP(int);
	int showMagic_power();
	void addMagic_power(int);
	void delMagic_power(int);
	void AddEXP(int);
	int showSkill_point();
	void AddSkill_point(int);
	void SubSkill_point(int);
	void AddDegree(int);
	void addMAXHP(int);
	void delMAXHP(int);
	int gethurt(int hurt);
	string getname();
	int  show_skill_list();
	void show_skill_name(int);
	int get_skill_damage(int);
	int choose_attack();
	void set_Initjob(int);
	int get_Initjob();
	int showMAXHP();
	void show_Money_detail(CLifeEntity*);
	void show_HP_detail(CLifeEntity*);
	void show_SP_detail(CLifeEntity*);
	void show_EXP_detail(CLifeEntity*);
	void show_Degree_detail(CLifeEntity*);
	void setname(string);
	void set_kill_counter();
	int show_kill_counter();
	void setEquiment(CEquiment* in_equiment) { equiment = in_equiment; }
	CWeapon* getWeapon() { return weapon; };
	CFood* getFood() { return food; };
	CEquiment* getEquiment() { return equiment; };
	void setWeapon(CWeapon* in_weapon) { weapon = in_weapon; }
	bool kill(CLifeEntity*);
	virtual int attack(CLifeEntity*) = 0;
	virtual int magic_skill_attack(CLifeEntity*,int)=0;
	//virtual int magic_attack(CLifeEntity*);
	virtual int defense(CLifeEntity*) = 0;
	virtual int isA() = 0;
private:
	void fightstatus(CLifeEntity* f, CLifeEntity* s);
	void bloodbarshow(string title, int maxvalue, int value);
	int maxSP, maxHP;
	int SP, HP;
	int EXP;
	int Degree;
	int Money;
	int Lucky;
	int out_data_num;
	int kill_counter;
	int Skill_point;
	int magic_power;
	int max_magic_power;
	int job_num;
	string Name;
	CWeapon* weapon;
	CEquiment* equiment;
	CFood* food;
};

#endif