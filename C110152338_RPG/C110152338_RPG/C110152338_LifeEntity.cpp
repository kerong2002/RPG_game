#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "C110152338_GlobalInfo.h"
#include "C110152338_LifeEntity.h"

CLifeEntity::CLifeEntity(int initHP, int initSP, string initname) {
	kill_counter = 0;
	maxSP = SP = initSP;
	maxHP = HP = initHP;
	Name = initname;
	Degree = 1;
	EXP = 0;
	weapon = NULL;
	setMoney(500);				//初始金幣
}
//==================<光標移動>=========================
void cursor_movement_Life(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
void CLifeEntity::setInitSPHP(int initHP, int initSP) {
	maxSP = SP = initSP;
	maxHP = HP = initHP;
}

void CLifeEntity::setMoney(int initMoney) {
	Money = initMoney;
}

int CLifeEntity::showMoney() {
	return Money;
}

void CLifeEntity::AddMoney(int inMoney) {
	Money = inMoney + Money;
	//cout << "加錢";
}

void CLifeEntity::AddEXP(int inexp) {
	EXP += inexp;
	if (EXP >= 50) {
		AddDegree(EXP / 50);
	}
	EXP %= 50;
	//cout << "加錢";
}

void CLifeEntity::AddDegree(int indegree) {
	Degree += indegree;
	addSP(indegree*5);
	cout << "<等級、傷害提升!!>" << endl;
	//cout << "加錢";
}

void CLifeEntity::setHP(int inHP) {
	HP = inHP > maxHP ? maxHP : inHP;
}

void  CLifeEntity::show_HP_detail(CLifeEntity*fighter) {
	cout << "玩家血量：" << fighter->getHP();
	//cout << "玩家幸運值：" << initLucky;
}
void  CLifeEntity::show_SP_detail(CLifeEntity*fighter) {
	cout << "玩家傷害：" << fighter->getSP();
}
void  CLifeEntity::show_Money_detail(CLifeEntity* fighter) {
	cout << "玩家金錢：$" << fighter->getMoney();
}
void  CLifeEntity::show_Degree_detail(CLifeEntity* fighter) {
	cout << "玩家等級：<" << fighter->getDegree()<<">";
}
void  CLifeEntity::show_EXP_detail(CLifeEntity* fighter) {
	cout << "玩家經驗：" << setw(2) << setfill('0')<<fighter->getEXP() << " / 50";
}

int  CLifeEntity::getMoney() {
	return Money;
}

int  CLifeEntity::getDegree() {
	return Degree;
}

int  CLifeEntity::getEXP() {
	return EXP;
}

void  CLifeEntity::subMoney(int  take) {
	Money -= take;
}
void CLifeEntity::addHP(int inHP) {
	HP = (inHP + HP) > maxHP ? maxHP : (HP + inHP);
}

void CLifeEntity::addSP(int inSP) {
	SP = inSP + SP;
}

void CLifeEntity::delSP(int inSP) {
	SP -= inSP;
}

void CLifeEntity::addMAXHP(int inHP) {
	maxHP = inHP + maxHP;
	HP = maxHP;
}

void CLifeEntity::delMAXHP(int inHP) {
	maxHP -= inHP;
	HP = maxHP;
}

int CLifeEntity::getHP() {
	return (HP > 0 ? HP : 0);
}

int CLifeEntity::getMAXHP() {
	return (maxHP);
}

int CLifeEntity::getSP() {
	return SP;
}

int CLifeEntity::getMAXSP() {
	return (maxSP);
}

bool CLifeEntity::isdead() {
	return (HP <= 0);
}

int  CLifeEntity::gethurt(int hurt) {
	if (hurt > HP)
		setHP(0);
	else if (hurt > 0)
		setHP(HP - hurt);
	return HP;
}

string CLifeEntity::getname() {
	return Name;
}

void CLifeEntity::setname(string inname) {
	Name = inname;
}
void set_pos() {
	for (int y = 0; y <= 5; y++) {
		cursor_movement_Life(0, 20 + y);
		cout << "                                                                    ";
	}
	cursor_movement_Life(0, 20);
}
bool CLifeEntity::kill(CLifeEntity* enemy) {
	int f_damage = 0, s_damage = 0;
	CLifeEntity* first, * second;
	int whofirst;
	while (!this->isdead() && !enemy->isdead()) {
		set_pos();
		whofirst = rand() % 2;
		if (whofirst == 0) {
			cout << "對方搶得先機，先出手傷人" << endl;
			first = (CLifeEntity*)enemy;
			second = (CLifeEntity*)this;
		}
		else {
			cout << "你搶得先機，先出手傷人" << endl;
			first = (CLifeEntity*)this;
			second = (CLifeEntity*)enemy;
		}
		set_pos();
		s_damage = first->attack(second);
		fightstatus(enemy, this);
		if (second->isdead()) {
			Sleep(1000);
			break;
		}
		set_pos();
		f_damage = second->attack(first);
		fightstatus(enemy, this);
		Sleep(2000);
	}
	if (this->isdead())
		return 0;
	return 1;
}

void CLifeEntity::fightstatus(CLifeEntity* f, CLifeEntity* s) {
	cout << endl << f->getname() << endl;
	bloodbarshow(string("HP"), f->getMAXHP(), f->getHP());
	cout << s->getname() << endl;
	bloodbarshow(string("HP"), s->getMAXHP(), s->getHP());
	cout << endl;
}


void  CLifeEntity::set_kill_counter() {
	kill_counter += 1;
}

int  CLifeEntity::show_kill_counter() {
	return kill_counter;
}

void CLifeEntity::bloodbarshow(string title, int maxvalue, int value) {
	cout << title << "     |";
	float hpslotlen = (float)maxvalue / MAXBLOODBARLEN;
	int numhp = (int)ceil(value / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << "#";
	}
	numhp = (int)floor((maxvalue - value) / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << " ";
	}
	cout << "|" << endl;
}
