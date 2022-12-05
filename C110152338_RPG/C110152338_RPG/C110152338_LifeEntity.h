#ifndef LIFEENTITY_H
#define LIFEENTITY_H

#include <string>
#include "C110152338_weapon.h"

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
	void setMoney(int);
	int showMoney();
	int getMoney();
	void subMoney(int);
	void AddMoney(int);
	void addSP(int);
	void delSP(int);
	int gethurt(int hurt);
	string getname();
	void show_Money_detail(CLifeEntity*);
	void show_HP_detail(CLifeEntity*);
	void show_SP_detail(CLifeEntity*);
	void setname(string);
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
	int Money;
	string Name;
	CWeapon* weapon;

};

#endif