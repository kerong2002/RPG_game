#include <iostream>
#include <fstream>
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
	Skill_point = 300;
	magic_power = 300;
	max_magic_power = 300;
	weapon = NULL;
	setMoney(500);				//初始金幣
}
void CLifeEntity::set_all_thing(string in_name, int in_hp, int in_sp, int in_maxhp, int in_max_sp, int in_degree, int in_skill_point, int in_magic_power, int in_money, int in_EXP, int in_lucky) {
	maxSP = SP = in_sp;
	maxHP = HP = in_hp;
	//Name = in_name;
	Degree = in_degree;
	EXP = in_EXP;
	Skill_point = in_skill_point;
	magic_power = in_magic_power;
	setMoney(in_money);
	setInitLucky(in_lucky);
}

void CLifeEntity::read_hack_data() {
	ifstream input_f1("hack.txt");
	input_f1 >> Name;
	input_f1 >> HP;
	input_f1 >> SP;
	input_f1 >> maxHP;
	input_f1 >> maxSP;
	input_f1 >> Degree;
	input_f1 >> Skill_point;
	input_f1 >> magic_power;
	int get_money;
	input_f1 >> get_money;
	setMoney(get_money);
	input_f1 >> EXP;
	int get_lucky;
	input_f1 >> get_lucky;
	setInitLucky(get_lucky);
}

void CLifeEntity::out_hack_data() {
	ofstream out_f1("hack.txt");
	out_f1 << Name << endl;
	out_f1 << HP << endl;
	out_f1 << SP << endl;
	out_f1 << maxHP << endl;
	out_f1 << maxSP << endl;
	out_f1 << Degree << endl;
	out_f1 << Skill_point << endl;
	out_f1 << magic_power << endl;
	out_f1 << getMoney() << endl;
	out_f1 << EXP << endl;
	out_f1 << show_Lucky() << endl;
}

void CLifeEntity::set_output_data_num(int pos) {
	out_data_num = pos;
}
int  CLifeEntity::show_output_data_num() {
	return out_data_num;
}
void  CLifeEntity::file_read_data() {
	if (out_data_num == 1) {
		ifstream input_f1("play1.txt");
		input_f1 >> Name;
		if (Name == "射手") {
			set_Initjob(1);
		}
		else if (Name == "法師") {
			set_Initjob(2);
		}
		else if (Name == "召喚師") {
			set_Initjob(3);
		}
		else if (Name == "戰士") {
			set_Initjob(4);
		}
		else if (Name == "輔助") {
			set_Initjob(5);
		}
		input_f1 >> HP;
		input_f1 >> SP;
		input_f1 >> maxHP;
		input_f1 >> maxSP;
		input_f1 >> Degree;
		input_f1 >> Skill_point;
		input_f1 >> magic_power;
		int get_money;
		input_f1 >> get_money;
		setMoney(get_money);
		input_f1 >> EXP;
		int get_lucky;
		input_f1 >> get_lucky;
		setInitLucky(get_lucky);
	}
	else if (out_data_num == 2) {
		ifstream input_f2("play2.txt");
		input_f2 >> Name;
		if (Name == "射手") {
			set_Initjob(1);
		}
		else if (Name == "法師") {
			set_Initjob(2);
		}
		else if (Name == "召喚師") {
			set_Initjob(3);
		}
		else if (Name == "戰士") {
			set_Initjob(4);
		}
		else if (Name == "輔助") {
			set_Initjob(5);
		}
		input_f2 >> HP;
		input_f2 >> SP;
		input_f2 >> maxHP;
		input_f2 >> maxSP;
		input_f2 >> Degree;
		input_f2 >> Skill_point;
		input_f2 >> magic_power;
		int get_money;
		input_f2 >> get_money;
		setMoney(get_money);
		input_f2 >> EXP;
		int get_lucky;
		input_f2 >> get_lucky;
		setInitLucky(get_lucky);
	}
	else if (out_data_num == 3) {
		ifstream input_f3("play3.txt");
		input_f3 >> Name;
		if (Name == "射手") {
			set_Initjob(1);
		}
		else if (Name == "法師") {
			set_Initjob(2);
		}
		else if (Name == "召喚師") {
			set_Initjob(3);
		}
		else if (Name == "戰士") {
			set_Initjob(4);
		}
		else if (Name == "輔助") {
			set_Initjob(5);
		}
		input_f3 >> HP;
		input_f3 >> SP;
		input_f3 >> maxHP;
		input_f3 >> maxSP;
		input_f3 >> Degree;
		input_f3 >> Skill_point;
		input_f3 >> magic_power;
		int get_money;
		input_f3 >> get_money;
		setMoney(get_money);
		input_f3 >> EXP;
		int get_lucky;
		input_f3 >> get_lucky;
		setInitLucky(get_lucky);
	}
}
void CLifeEntity::out_all_thing() {
	if (out_data_num == 1) {
		ofstream out_f1("play1.txt");
		out_f1 << Name << endl;
		out_f1 << HP << endl;
		out_f1 << SP << endl;
		out_f1 << maxHP << endl;
		out_f1 << maxSP << endl;
		out_f1 << Degree << endl;
		out_f1 << Skill_point << endl;
		out_f1 << magic_power << endl;
		out_f1 << getMoney() << endl;
		out_f1 << EXP << endl;
		out_f1 << show_Lucky() << endl;
	}
	else if (out_data_num == 2) {
		ofstream out_f2("play2.txt");
		out_f2 << Name << endl;
		out_f2 << HP << endl;
		out_f2 << SP << endl;
		out_f2 << maxHP << endl;
		out_f2 << maxSP << endl;
		out_f2 << Degree << endl;
		out_f2 << Skill_point << endl;
		out_f2 << magic_power << endl;
		out_f2 << getMoney() << endl;
		out_f2 << EXP << endl;
		out_f2 << show_Lucky() << endl;
	}
	else if (out_data_num == 3) {
		ofstream out_f3("play3.txt");
		out_f3 << Name << endl;
		out_f3 << HP << endl;
		out_f3 << SP << endl;
		out_f3 << maxHP << endl;
		out_f3 << maxSP << endl;
		out_f3 << Degree << endl;
		out_f3 << Skill_point << endl;
		out_f3 << magic_power << endl;
		out_f3 << getMoney() << endl;
		out_f3 << EXP << endl;
		out_f3 << show_Lucky() << endl;
	}

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
	addSP(indegree * 5);
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

void  CLifeEntity::show_HP_detail(CLifeEntity* fighter) {
	cout << "玩家血量：" << fighter->getHP() << "/" << fighter->showMAXHP();
	//cout << "玩家幸運值：" << initLucky;
}
void  CLifeEntity::show_SP_detail(CLifeEntity* fighter) {
	cout << "玩家傷害：" << fighter->getSP();
}
void  CLifeEntity::show_Money_detail(CLifeEntity* fighter) {
	cout << "玩家金錢：$" << fighter->getMoney();
}
void  CLifeEntity::show_Degree_detail(CLifeEntity* fighter) {
	cout << "玩家等級：<" << fighter->getDegree() << ">";
}
void  CLifeEntity::show_EXP_detail(CLifeEntity* fighter) {
	cout << "玩家經驗：" << setw(2) << setfill('0') << fighter->getEXP() << " / 50";
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
	HP = inHP + HP;
}

int CLifeEntity::showMAXHP() {
	return maxHP;
}

void CLifeEntity::delMAXHP(int inHP) {
	maxHP -= inHP;
	HP -= inHP;
}

int CLifeEntity::getHP() {
	return (HP > 0 ? HP : 0);
}

int CLifeEntity::showMagic_power() {
	return magic_power;
}
void CLifeEntity::addMagic_power(int init_magic_power) {
	if (magic_power + init_magic_power <= max_magic_power) {
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

void CLifeEntity::show_skill_name(int pos) {
	CItemData* id = CGlobalInfo::itm_data;
	cout << id->skill_array[pos]->getName();
}

int CLifeEntity::get_skill_damage(int pos) {
	CItemData* id = CGlobalInfo::itm_data;
	return id->skill_array[pos]->getattackbonus() * id->skill_array[pos]->get_skill_level();
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
	//cout << get_jo_num;
	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	for (int i = 0; i <= 4; i++) {
		cursor_movement_Life(63, 21 + i);
		cout << id->skill_array[i]->getName();
		cursor_movement_Life(76, 21 + i);
		if (id->skill_array[i]->get_skill_level() == 0) {
			cout << id->skill_array[i]->getattackbonus();
		}
		else {
			cout << id->skill_array[i]->getattackbonus() * id->skill_array[i]->get_skill_level();
		}
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
			return -3;
		}
		if (key == 13) {
			int compare_skill_point = id->skill_array[choose_pos]->getattackbonus();
			if (id->skill_array[choose_pos]->get_skill_level() == 0) {
				cursor_movement_Life(63, 27);
				cout << "                                                               ";
				cursor_movement_Life(63, 27);
				cout << "玩家尚未學會此技能";
			}
			else if (magic_power < compare_skill_point) {
				cursor_movement_Life(63, 27);
				cout << "                                                               ";
				cursor_movement_Life(63, 27);
				cout << "玩家魔力值不夠施放技能";
			}
			else {
				//return choose_pos;         //改掉職業限定技能
				if (get_Initjob() != choose_pos + 1) {
					cursor_movement_Life(63, 27);
					cout << "                                                              ";
					cursor_movement_Life(63, 27);
					cout << "玩家不可施放非此職業的技能";
				}
				else {
					return choose_pos;
				}
			}
		}
		if (key == 'w' || key == 'W') {
			cursor_movement_Life(60, 21 + choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement_Life(60, 21 + choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 4) {
			choose_pos = 0;
		}
		if (choose_pos < 0) {
			choose_pos = 4;
		}
		cursor_movement_Life(60, 21 + choose_pos);
		cout << ">>";
	}
	return -3;

}
int CLifeEntity::choose_attack() {
	system("color 0F");
	cursor_movement_Life(63, 20);
	cout << "                                                ";
	cursor_movement_Life(63, 20);
	cout << "<普通攻擊>";
	cursor_movement_Life(63, 21);
	cout << "                                                ";
	cursor_movement_Life(63, 21);
	cout << "<技能攻擊>";
	cursor_movement_Life(60, 20);

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
				if (back_get == -3) {
					for (int i = 0; i <= 8; i++) {
						cursor_movement_Life(0, 19 + i);
						cout << "                                                                                               ";
						cursor_movement_Life(0, 0);
					}
					cursor_movement_Life(63, 20);
					cout << "                                                                          ";
					cursor_movement_Life(63, 20);
					cout << "<普通攻擊>";
					cursor_movement_Life(63, 21);
					cout << "                                                                           ";
					cursor_movement_Life(63, 21);
					cout << "<技能攻擊>";
					cursor_movement_Life(60, 20);
				}
				else {
					for (int i = 0; i <= 8; i++) {
						cursor_movement_Life(60, 19 + i);
						cout << "                                                                          ";
					}
					cursor_movement_Life(63, 20);
					cout << "                                                                          ";
					cursor_movement_Life(63, 21);
					cout << "                                                                           ";
					cursor_movement_Life(60, 20);
					return back_get;
				}
			}
			//cout << "not do";
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
	return -2;
}
bool CLifeEntity::kill(CLifeEntity* enemy) {
	int f_damage = 0, s_damage = 0;
	CLifeEntity* first, * second;
	CItemData* id = CGlobalInfo::itm_data;
	int whofirst;
	while (!this->isdead() && !enemy->isdead()) {
		int get_skill_or_normal = choose_attack();
		set_pos();
		//cout << get_skill_or_normal;
		//system("pause");
		if (get_skill_or_normal == -2) {
			//system("pause");
			whofirst = rand() % 2;
			if (whofirst == 0) {
				cursor_movement_Life(0, 19);
				cout << "                                                   ";
				cursor_movement_Life(0, 19);
				cout << "對方搶得先機，先出手傷人" << endl;
				first = (CLifeEntity*)enemy;
				second = (CLifeEntity*)this;
			}
			else {
				cursor_movement_Life(0, 19);
				cout << "                                                   ";
				cursor_movement_Life(0, 19);
				cout << "你搶得先機，先出手傷人" << endl;
				first = (CLifeEntity*)this;
				second = (CLifeEntity*)enemy;
			}
			cursor_movement_Life(0, 20);
			fightstatus(enemy, this);
			s_damage = first->attack(second);
			cursor_movement_Life(0, 20);
			fightstatus(enemy, this);
			Sleep(2000);
			if (second->isdead()) {
				Sleep(1000);
				break;
			}
			cursor_movement_Life(0, 20);
			fightstatus(enemy, this);
			f_damage = second->attack(first);
			cursor_movement_Life(0, 20);
			fightstatus(enemy, this);
			Sleep(2000);
		}
		else {
			first = (CLifeEntity*)enemy;
			second = (CLifeEntity*)this;
			set_pos();
			if (second->isdead()) {
				Sleep(1000);
				break;
			}
			cursor_movement_Life(0, 20);
			fightstatus(enemy, this);
			delMagic_power((id->skill_array[get_skill_or_normal]->getattackbonus()));
			f_damage = second->magic_skill_attack(first, get_skill_or_normal);
			cursor_movement_Life(0, 20);
			fightstatus(enemy, this);
			Sleep(2000);
		}
		cursor_movement_Life(60, 4);
		cout << "                                       ";
		cursor_movement_Life(60, 4);
		cout << "玩家血量：" << HP << "/" << maxHP;
		cursor_movement_Life(60, 5);
		cout << "                                       ";
		cursor_movement_Life(60, 5);
		cout << "玩家傷害：" << SP;
		cursor_movement_Life(60, 6);
		cout << "                                       ";
		cursor_movement_Life(60, 6);
		cout << "玩家金錢：$" << Money;
		cursor_movement_Life(60, 7);
		cout << "                                       ";
		cursor_movement_Life(60, 7);
		cout << "玩家幸運：☆" << Lucky;
		cursor_movement_Life(60, 8);
		cout << "                                       ";
		cursor_movement_Life(60, 8);
		cout << "玩家等級：<" << Degree << ">";
		cursor_movement_Life(60, 9);
		cout << "                                       ";
		cursor_movement_Life(60, 9);
		cout << "玩家經驗：" << setw(2) << setfill('0') << EXP << " / 50";
		cursor_movement_Life(60, 10);
		cout << "                                       ";
		cursor_movement_Life(60, 10);
		cout << "技能點數：" << Skill_point;
		cursor_movement_Life(60, 11);
		cout << "                                       ";
		cursor_movement_Life(60, 11);
		cout << "魔力點數：" << setw(3) << setfill('0') << magic_power << " / 300";
	}
	cursor_movement_Life(0, 27);
	if (this->isdead())
		return 0;
	return 1;
}
void CLifeEntity::set_Initjob(int init_job) {
	job_num = init_job;
}
int CLifeEntity::get_Initjob() {
	return job_num;
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
