#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <thread>
#include "C110152338_Monster.h"
#include "C110152338_MonsterData.h"
#include "C110152338_def.h"

using namespace std;
CMonster::CMonster(int initHP, int initSP, int initrough, string init_name, string init_eng_name) : CLifeEntity(initHP, initSP, init_name), RoughDegree(initrough), eng_name(init_eng_name) {
	counter_for_monster_id++;
	cout << "one monster called " << init_name << " (" << init_eng_name << ") is created with <HP, SP, rough> = <" << initHP << ", " << initSP << ", " << initrough << ">" << endl;
}



CMonster::CMonster(const CMonsterType* type) : CLifeEntity(1 + rand() % type->max_hp, 1 + rand() % type->max_sp, type->name), RoughDegree(type->max_rough) {
	counter_for_monster_id++;
	int rand_take = (rand() % 3 + 1);				//亂數產生等級
	eng_name = type->prefix_eng_name + "<" + to_string(rand_take) + ">";
	if (rand_take > 1) {
		this->addMAXHP(this->getHP() * (rand_take - 1));
	}
	cout << "Monster called " << type->name << " (" << eng_name << ") is created with <HP, SP, rough> = <" << this->getHP() << ", " << this->getSP() << ", " << this->getRough() << ">" << endl;
}

void sound_monster_kill() {
	PlaySound(TEXT("monster_kill.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void CMonster::set_skip(bool skip) {
	monster_skip = skip;
}

bool CMonster::get_skip() {
	return monster_skip;
}

//==================<光標移動>=========================
void cursor_movement_Monster(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
int CMonster::getRough() {
	return RoughDegree;
}

int CMonster::physicaldamage() {
	return (rand() % getSP() + getRough());
}
void attack_monster_function(bool skip) {
	ifstream fin_A1("monster_kill.txt");
	string take_animation;
	int cnt = 1;
	thread th_monster_kill(sound_monster_kill);
	//PlaySound(TEXT("among_kill.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		if (skip || _kbhit()) {
			break;
		}
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@') {
				cursor_movement_Monster(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
				cursor_movement_Monster(60 + y, 11 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 35 == 0) {
			cursor_movement_Monster(60, 12);
			cnt -= 35;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
		cursor_movement_Monster(0, 0);
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	for (int y = 0; y < 40; y++) {
		cursor_movement_Monster(60, 12 + y);
		cout << "                                                                                                                        ";
	}
	th_monster_kill.join();
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cursor_movement_Monster(0, 20);
}

int CMonster::attack(CLifeEntity* l) {
	int damage = physicaldamage();
	if (damage > l->getHP())
		damage = l->getHP();

	int avoid = rand() % 100;
	/*
	for (int y = 0; y < 6; y++) {
		cursor_movement_Monster(0, 20 + y);
		cout << "                                                        ";
	}*/
	cursor_movement_Monster(0, 20);

	attack_monster_function(monster_skip);
	if (l->defense(l) >= avoid || damage <= 0) {
		cout << this->getname() << " 突襲而來，但是 " << l->getname() << " 異常幸運，因此躲避了攻擊" << endl;
	}
	else {
		l->gethurt(damage);
		cout << this->getname() << " 突襲而來，造成 " << l->getname() << " " << damage << " 血損失" << endl;
	}
	cursor_movement_Monster(0, 0);
	return (damage);
}

int CMonster::magic_skill_attack(CLifeEntity* l, int pos) {
	int damage = get_skill_damage(pos) - l->defense(l);
	if (damage > l->getHP())
		damage = l->getHP();
	l->gethurt(damage);
	if (damage > 0) {
		cout << "使用技能 ";
		show_skill_name(pos);
		cout << "，造成 " << l->getname() << " " << damage << " 血損失" << endl;
	}
	else {
		cout << "使用技能 ";
		show_skill_name(pos);
		cout << " ，但是 " << l->getname() << " 強力一擋，因此沒有造成任何損失" << endl;
	}
	return (damage > 0 ? damage : 0);
}

int CMonster::defense(CLifeEntity* l) {
	return 0;
}

int CMonster::isA() {
	return emonster;
}

string CMonster::get_basic_data() {
	string output = this->getname() + string("(") + this->eng_name + string(") <HP, SP, rough> = <") + to_string((long double)this->getHP()) + string(", ") + to_string((long double)this->getSP()) + string(", ") + to_string((long double)this->getRough()) + string(">");
	return output;
}

string CMonster::get_monster_name() {
	string output = this->eng_name;
	return output;
}