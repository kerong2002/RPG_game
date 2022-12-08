#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include "C110152338_GlobalInfo.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_ItemData.h"

CLifeEntity::CLifeEntity(int initHP, int initSP, string initname) {
	kill_counter = 0;
	maxSP = SP = initSP;
	maxHP = HP = initHP;
	Name = initname;
	Degree = 1;
	EXP = 0;
	Skill_point = 500;
	magic_power = 10;
	max_magic_power = 300;
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

void CLifeEntity::setInitLucky(int initLucky) {
	Lucky = initLucky;
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
	AddLucky(indegree);
	cout << "<等級、傷害提升!!>" << endl;
	//cout << "加錢";
}

void CLifeEntity::AddLucky(int inLucky) {
	Lucky += inLucky;
}

int CLifeEntity::show_Lucky() {
	return Lucky;
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

int  CLifeEntity::showSkill_point() {
	return Skill_point;
}
void  CLifeEntity::AddSkill_point(int initSkill_point) {
	Skill_point += initSkill_point;
}

void  CLifeEntity::SubSkill_point(int initSkill_point) {
	Skill_point -= initSkill_point;
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

int CLifeEntity::showMagic_power() {
	return magic_power;
}
void CLifeEntity::addMagic_power(int init_magic_power) {
	if(magic_power + init_magic_power <= max_magic_power){
		magic_power += init_magic_power;
	}
	else {
		magic_power = max_magic_power;
	}
	
}
void CLifeEntity::delMagic_power(int init_magic_power) {
	magic_power -= init_magic_power;
	if (magic_power < 0) {
		magic_power = 0;
	}
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
int  CLifeEntity::show_skill_list() {
	cursor_movement_Life(63, 19);
	cout << "                                                ";
	cursor_movement_Life(75, 19);
	cout << "<技能清單>";
	cursor_movement_Life(63, 20);
	cout << "                                                ";
	cursor_movement_Life(63, 20);
	cout << " 名稱      傷害值      等級";
	CItemData* id = CGlobalInfo::itm_data;

	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	for (int i = 0; i <= 4; i++) {
		cursor_movement_Life(63, 21 + i);
		cout << id->skill_array[i]->getName();
		cursor_movement_Life(76, 21 + i);
		cout << id->skill_array[i]->getattackbonus();
		cursor_movement_Life(88, 21 + i);
		cout << id->skill_array[i]->get_skill_level();
	}
	int choose_pos = 0;
	cursor_movement_Life(60, 21);
	cout << ">>";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 27) {
			return 2;
		}
		if (key == 13) {
			int compare_skill_point = id->skill_array[choose_pos]->getattackbonus();
			if (id->skill_array[choose_pos]->get_skill_level() == 0) {
				cursor_movement_Life(63, 27);
				cout << "                                                               ";
				cursor_movement_Life(63, 27);
				cout << "玩家尚未學會此技能";
			}
			else if (magic_power<compare_skill_point) {
				cursor_movement_Life(63, 27);
				cout << "                                                               ";
				cursor_movement_Life(63, 27);
				cout << "玩家魔力值不夠施放技能";
			}
			else {
				return choose_pos;
			}
		}
		if (key == 'w' || key == 'W') {
			cursor_movement_Life(60, 21+choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement_Life(60, 21+choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 4) {
			choose_pos = 0;
		}
		if (choose_pos < 0) {
			choose_pos = 4;
		}
		cursor_movement_Life(60, 21+ choose_pos);
		cout << ">>";
	}
	return -1;
	
}
void CLifeEntity::choose_attack() {
	system("color 0F");
	cursor_movement_Life(63, 20);
	cout << "                                                ";
	cursor_movement_Life(63, 20);
	cout << "<普通攻擊>";
	cursor_movement_Life(63, 21);
	cout << "                                                ";
	cursor_movement_Life(63, 21);
	cout << "<技能攻擊>";
	cursor_movement_Life(60,20);
	
	int choose_pos = 0;
	cout << ">>";
	cursor_movement_Life(0, 0);
	int key = 0;
	while (true) {
		key = _getch();
		if (key == 13) {
			if (choose_pos == 0) {
				break;
			}
			else {
				int back_get = show_skill_list();
				if (back_get == -1) {
					for (int i = 0; i <= 8; i++) {
						cursor_movement_Life(60, 19 + i);
						cout << "                                               ";
					}
					cursor_movement_Life(63, 20);
					cout << "                                                ";
					cursor_movement_Life(63, 20);
					cout << "<普通攻擊>";
					cursor_movement_Life(63, 21);
					cout << "                                                ";
					cursor_movement_Life(63, 21);
					cout << "<技能攻擊>";
					cursor_movement_Life(60, 20);
				}
				else {
					for (int i = 0; i <= 8; i++) {
						cursor_movement_Life(60, 19 + i);
						cout << "                                               ";
					}
					cursor_movement_Life(63, 20);
					cout << "                                                ";
					cursor_movement_Life(63, 20);
					cout << "<普通攻擊>";
					cursor_movement_Life(63, 21);
					cout << "                                                ";
					cursor_movement_Life(63, 21);
					cout << "<技能攻擊>";
					cursor_movement_Life(60, 20);
					//magic_attack(enemy,back_get);
				}
				//cout << "not do";
			}
		}
		if (key == 'w' || key == 'W') {
			cursor_movement_Life(60, choose_pos + 20);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement_Life(60, choose_pos + 20);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 1) {
			choose_pos = 0;
		}
		if (choose_pos < 0) {
			choose_pos = 1;
		}
		cursor_movement_Life(60, choose_pos + 20);
		cout << ">>";
	}
	cursor_movement_Life(60, 20);
	cout << "                                                      ";
	cursor_movement_Life(60, 21);
	cout << "                                                      ";
}
bool CLifeEntity::kill(CLifeEntity* enemy) {
	int f_damage = 0, s_damage = 0;
	CLifeEntity* first, * second;
	int whofirst;
	while (!this->isdead() && !enemy->isdead()) {
		choose_attack();
		set_pos();
		
		//system("pause");
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
	if (kill_counter > 6) {
		kill_counter = 0;
	}
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
