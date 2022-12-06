#ifndef LIFEENTITY_H
#define LIFEENTITY_H

#include <string>
#include "C110152338_weapon.h"
#include "C110152338_Equiment.h"

#define MAXBLOODBARLEN 40
using namespace std;

class CLifeEntity {
public:
	CLifeEntity(int initHP = 0, int initSP = 0, string initname = "");
	void setInitSPHP(int initHP = 0, int initSP = 0);
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
	void subMoney(int);
	void AddMoney(int);
	void addSP(int);
	void delSP(int);
	void AddEXP(int);
	void AddDegree(int);
	void addMAXHP(int);
	void delMAXHP(int);
	int gethurt(int hurt);
	string getname();
	void show_Money_detail(CLifeEntity*);
	void show_HP_detail(CLifeEntity*);
	void show_SP_detail(CLifeEntity*);
	void show_EXP_detail(CLifeEntity*);
	void show_Degree_detail(CLifeEntity*);
	void setname(string);
	void set_kill_counter();
	int show_kill_counter();
	CEquiment* getEquiment() { return equiment; };
	void setEquiment(CEquiment* in_equiment) { equiment = in_equiment; }
	CWeapon* getWeapon() { return weapon; };
	void setWeapon(CWeapon* in_weapon) { weapon = in_weapon; }
	bool kill(CLifeEntity*);
	virtual int attack(CLifeEntity*) = 0;
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
	int kill_counter;
	string Name;
	CWeapon* weapon;
	CEquiment* equiment;

};

#endif