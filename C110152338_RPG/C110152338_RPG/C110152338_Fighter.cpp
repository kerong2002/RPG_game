#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
#include "C110152338_Profession.h"
#include "C110152338_cursor_movement_fighter.h"
#include "C110152338_Fighter.h"
#include "C110152338_Equiment.h"
#include "C110152338_food.h"
#include "C110152338_Bag.h"
#include "C110152338_def.h"
#include "C110152338_GlobalInfo.h"
#include "C110152338_MapData.h"




using namespace std;

CFighter::CFighter(int job, int initHP, int initSP, int initLucky, string name, int in_city) {
	/*if (initHP == 0 && initSP == 0 && initLucky == 0) {
		initHP =initHP;
		initSP = initSP;
		initLucky = initLucky;
		setname(name);
	}*/
	//initHP = initHP;
	//initSP = initSP;
	//initLucky = initLucky;
	get_job_num = job;
	food_effect = 0;
	setname(name);
	setInitSPHP(initHP, initSP);
	set_Initjob(job);
	Lucky = initLucky;
	setInitLucky(Lucky);
	cur_city = in_city;
	bag = new CBag();
	cursor_movement_fighter(60, 4);
	cout << "玩家血量：" << initHP<<"/" << showMAXHP();
	cursor_movement_fighter(60, 5);
	cout << "玩家傷害：" << initSP;
	cursor_movement_fighter(60, 6);
	cout << "玩家金錢：$" << showMoney();
	cursor_movement_fighter(60, 7);
	cout << "玩家幸運：☆" << show_Lucky();
	cursor_movement_fighter(60, 8);
	cout << "玩家等級：<" << getDegree() << ">";
	cursor_movement_fighter(60, 9);
	cout << "玩家經驗：" << setw(2) << setfill('0') << getEXP() << " / 50";
	cursor_movement_fighter(60, 10);
	cout << "技能點數：" << showSkill_point();
	cursor_movement_fighter(60, 11);
	cout << "魔力點數：" << setw(3) << setfill('0') << showMagic_power() << " / 300";
	cursor_movement_fighter(0, 20);			//調整游標位置
	//cout << "One Fighter is created with (maxHP, maxSP, maxLucky) = (" << initHP << ", " << initSP << ", " << initLucky << ")" <<endl; 
}

CFighter::~CFighter() {
	if (bag)
		delete bag;
}

void CFighter::set_wear_weapon_ID(int pos) {
	save_wear_weapon_ID = pos + 15;
}
void CFighter::set_wear_equiment_ID(int pos) {
	save_wear_equiment_ID = pos + 33;
}
int CFighter::show_wear_weapon_ID() {
	return save_wear_weapon_ID;
}
int CFighter::show_wear_eauiment_ID() {
	return save_wear_equiment_ID;
}
void CFighter::show_fighter_detail(CLifeEntity* fighter) {
	cursor_movement_fighter(60, 4);
	cout << "                                       ";
	cursor_movement_fighter(60, 4);
	show_HP_detail(fighter);
	cursor_movement_fighter(60, 5);
	cout << "                                       ";
	cursor_movement_fighter(60, 5);
	show_SP_detail(fighter);
	cursor_movement_fighter(60, 6);
	cout << "                                       ";
	cursor_movement_fighter(60, 6);
	show_Money_detail(fighter);
	cursor_movement_fighter(60, 7);
	cout << "                                       ";
	cursor_movement_fighter(60, 7);
	cout << "玩家幸運：☆" << show_Lucky();
	cursor_movement_fighter(60, 8);
	cout << "                                       ";
	cursor_movement_fighter(60, 8);
	show_Degree_detail(fighter);
	cursor_movement_fighter(60, 9);
	cout << "                                       ";
	cursor_movement_fighter(60, 9);
	show_EXP_detail(fighter);
	cursor_movement_fighter(60, 10);
	cout << "                                       ";
	cursor_movement_fighter(60, 10);
	cout << "技能點數：" << showSkill_point();
	cursor_movement_fighter(60, 11);
	cout << "                                       ";
	cursor_movement_fighter(60, 11);
	cout << "魔力點數：" << setw(3) << setfill('0') << showMagic_power() << " / 300";
}
int CFighter::get_move_city(int move_city) {
	cur_city = move_city;
	return cur_city;
}

int CFighter::getLucky() {
	return Lucky;
}

int CFighter::physicaldamage() {
	return (rand() % getSP());
}

//==================<建立顏色>==========================
void SetColor_fighter(int color = 7) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void skill_1_attack_function() {
	ifstream fin_A1("Hanzo.txt");
	string take_animation;
	int cnt = 1;
	PlaySound(TEXT("skill_1_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@' || take_animation[y] == '.') {
				SetColor_fighter();
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
				SetColor_fighter(176);
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 26 == 0) {
			cursor_movement_fighter(60, 12);
			cnt -= 26;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
	}
	for (int y = 0; y < 40; y++) {
		cursor_movement_fighter(60, 15 + y);
		cout << "                                                                                                                        ";
	}
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("color 0F");
	cursor_movement_fighter(0, 0);
}

void skill_2_attack_function() {
	ifstream fin_A1("among_skill.txt");
	string take_animation;
	int cnt = 1;
	PlaySound(TEXT("skill_2_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@') {
				SetColor_fighter();
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
				SetColor_fighter(192);
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 23 == 0) {
			cursor_movement_fighter(60, 12);
			cnt -= 23;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
	}
	for (int y = 0; y < 40; y++) {
		cursor_movement_fighter(60, 15 + y);
		cout << "                                                                                                                        ";
	}
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("color 0F");
	cursor_movement_fighter(0, 0);
}

void skill_3_attack_function() {
	ifstream fin_A1("Pharah.txt");
	string take_animation;
	int cnt = 1;
	PlaySound(TEXT("skill_3_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@') {
				SetColor_fighter();
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
				SetColor_fighter(157);
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 36 == 0) {
			cursor_movement_fighter(60, 12);
			cnt -= 36;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
	}
	for (int y = 0; y < 40; y++) {
		cursor_movement_fighter(60, 15 + y);
		cout << "                                                                                                                        ";
	}
	PlaySound(NULL , NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("color 0F");
	cursor_movement_fighter(0, 0);
}

void skill_4_attack_function() {
	ifstream fin_A1("Genji.txt");
	string take_animation;
	int cnt = 1;
	
	PlaySound(TEXT("skill_4_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@') {
				SetColor_fighter();
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
				SetColor_fighter(172);
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 26 == 0) {
			cursor_movement_fighter(60, 12);
			cnt -= 26;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
	}
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	for (int y = 0; y < 40; y++) {
		cursor_movement_fighter(60, 12 + y);
		cout << "                                                                                                                        ";
	}
	system("color 0F");
	cursor_movement_fighter(0, 0);
}
void skill_5_attack_function() {
	PlaySound(TEXT("skill_5_sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	for (int x = 0; x < 4; x++) {
		ifstream fin_A1("Beam.txt");
		string take_animation;
		int cnt = 1;
		
		while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
			fin_A1 >> take_animation;
			for (int y = 0; y < take_animation.length(); y++) {
				if (take_animation[y] == '@') {
					SetColor_fighter();
					cursor_movement_fighter(60 + y, 11 + cnt);
					cout << " ";
				}
				else {
					SetColor_fighter(214);
					cursor_movement_fighter(60 + y, 11 + cnt);
					cout << take_animation[y];
				}
			}
			cout << endl;
			if (cnt % 21 == 0) {
				cursor_movement_fighter(60, 12);
				cnt -= 21;
				//Sleep(40);
				//system("cls");
				//for(int yy=0;yy<)
			}
			cnt += 1;
		}
	}
	for (int y = 0; y < 40; y++) {
		cursor_movement_fighter(60, 12 + y);
		cout << "                                                                                                                        ";
	}
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("color 0F");
	cursor_movement_fighter(0, 0);
}
void attack_function() {
	ifstream fin_A1("among.txt");
	string take_animation;
	int cnt = 1;
	PlaySound(TEXT("among_kill.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@') {
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 37 == 0) {
			cursor_movement_fighter(60, 12);
			cnt -= 37;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
	}
	for (int y = 0; y < 40; y++) {
		cursor_movement_fighter(60, 15 + y);
		cout << "                                                                                                                        ";
	}
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cursor_movement_fighter(0, 0);
}
int CFighter::attack(CLifeEntity* l) {
	int damage = physicaldamage() - l->defense(l);
	if (damage > l->getHP())
		damage = l->getHP();
	l->gethurt(damage);
	attack_function();
	cursor_movement_fighter(0, 20);
	if (damage > 0) {
		cout << this->getname() << " 猛力一揮，造成 " << l->getname() << " " << damage << " 血損失" << endl;
	}
	else {
		cout << this->getname() << " 猛力一揮，但是 " << l->getname() << " 強力一擋，因此沒有造成任何損失" << endl;
	}
	if (food_effect) {
		//cout << "<特殊食品，加乘而外傷害200↑> 剩餘：(" << food_effect << ")回合" << endl;
		food_effect -= 1;
	}
	if (food_bonus == true && food_effect == 0) {
		delSP(200);
		cursor_movement_fighter(0, 30);
		cout << "特殊食品，加乘效果消除，扣除200而外傷害" << endl;
		cursor_movement_fighter(0, 20);
	}
	if (food_effect == 0) {
		food_bonus = false;
	}
	return (damage > 0 ? damage : 0);
}


int CFighter::magic_skill_attack(CLifeEntity* l, int pos) {
	int damage = get_skill_damage(pos) - l->defense(l);
	if (damage > l->getHP())
		damage = l->getHP();
	l->gethurt(damage);
	if (pos == 0) {
		skill_1_attack_function();
	}
	else if (pos == 1) {
		skill_2_attack_function();
	}
	else if (pos == 2) {
		skill_3_attack_function();
	}
	else if (pos == 3) {
		skill_4_attack_function();
	}
	else if (pos == 4) {
		skill_5_attack_function();
	}
	cursor_movement_fighter(0, 20);
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

int CFighter::defense(CLifeEntity* l) {
	return 	getLucky();
}
void CFighter::shop_captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " 從商店獲取 " << in_item->getName() << endl;
}

void CFighter::fish_captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " 從釣魚獲取 " << in_item->getName() << endl;
}

void CFighter::house_captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " 從倉庫獲取 " << in_item->getName() << endl;
}

void CFighter::captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " 從地上撿起 " << in_item->getName() << endl;
}

void CFighter::save_captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	//cout << this->getname() << " 從地上撿起 " << in_item->getName() << endl;
}

int CFighter::showAllBagItems() {
	return bag->showAllItems();
}

bool CFighter::put_storeItems(int no) {
	CBagEntry* ne = bag->item_lookup(no);
	if (!ne) {
		return false;
	}
	if (ne->itm->isA() == eweapon) {
		ofstream out_f("house.txt");
		out_f << ne->itm->getID() + 15 << endl;
		out_f << ne->itm->getName();
		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag->item_delete(ne);
		}
		this->showAllBagItems();
	}
	else if (ne->itm->isA() == efood) {
		ofstream out_f("house.txt");
		out_f << ne->itm->getID() << endl;
		out_f << ne->itm->getName();
		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag->item_delete(ne);
		}
		this->showAllBagItems();
	}
	else {
		cout << "您的裝備不可放置在倉庫當中" << endl;
	}

	return true;
}

bool CFighter::put_houseItems(int no) {
	CBagEntry* ne = bag->item_lookup(no);
	if (!ne) {
		return false;
	}
	int cnt = 0;
	ifstream fin_h("house.txt");
	vector<int> ID;
	vector<int> amout;
	int take_ID;
	int take_amout;
	while (fin_h >> take_ID) {
		fin_h >> take_amout;
		cnt += 1;
		ID.push_back(take_ID);
		amout.push_back(take_amout);
	}
	if (ne->itm->isA() == eweapon) {
		int search = -1;
		for (int x = 0; x < cnt; x++) {
			if (ID[x] == ne->itm->getID() + 15) {
				search = x;
				break;
			}
		}
		if (search == -1) {
			ID.push_back(ne->itm->getID() + 15);
			amout.push_back(1);
			cnt += 1;
		}
		else {
			amout[search] += 1;
		}
		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag->item_delete(ne);
		}
		this->showAllBagItems();
		ofstream fout_h("house.txt");
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	else if (ne->itm->isA() == efood) {
		int search = -1;
		for (int x = 0; x < cnt; x++) {
			if (ID[x] == ne->itm->getID()) {
				search = x;
				break;
			}
		}
		if (search == -1) {
			ID.push_back(ne->itm->getID());
			amout.push_back(1);
			cnt += 1;
		}
		else {
			amout[search] += 1;
		}
		ofstream fout_h("house.txt");
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
		ne->deleteNum();
		if (ne->getNum() == 0) {
			bag->item_delete(ne);
		}
		this->showAllBagItems();
	}
	else {
		cout << "您的裝備不可放置在倉庫當中" << endl;
	}
	ID.clear();
	amout.clear();
	return true;
}

bool CFighter::save_wear(int data_save) {
	if (data_save == 1) {
		int cnt = 0;
		vector<int> ID;
		vector<int> amout;
		int weapon_ID = show_wear_weapon_ID();
		int equiment_ID = show_wear_eauiment_ID();
		if (weapon_ID > 15 && weapon_ID <= 33) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == weapon_ID) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(weapon_ID);
				amout.push_back(1);
				cnt += 1;
			}
			else {
				amout[search] += 1;
			}
		}
		if (equiment_ID > 33) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == equiment_ID) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(equiment_ID);
				amout.push_back(1);
				cnt += 1;
			}
			else {
				amout[search] += 1;
			}
		}
		ofstream fout_h("save_bag1.txt", ios::app);
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	else if (data_save == 2) {
		int cnt = 0;
		vector<int> ID;
		vector<int> amout;
		int weapon_ID = show_wear_weapon_ID();
		int equiment_ID = show_wear_eauiment_ID();
		if (weapon_ID > 15 && weapon_ID <= 33) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == weapon_ID) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(weapon_ID);
				amout.push_back(1);
				cnt += 1;
			}
			else {
				amout[search] += 1;
			}
		}
		if (equiment_ID > 33) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == equiment_ID) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(equiment_ID);
				amout.push_back(1);
				cnt += 1;
			}
			else {
				amout[search] += 1;
			}
		}
		ofstream fout_h("save_bag2.txt", ios::app);
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	else if (data_save == 3) {
		int cnt = 0;
		vector<int> ID;
		vector<int> amout;
		int weapon_ID = show_wear_weapon_ID();
		int equiment_ID = show_wear_eauiment_ID();
		if (weapon_ID > 15 && weapon_ID <= 33) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == weapon_ID) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(weapon_ID);
				amout.push_back(1);
				cnt += 1;
			}
			else {
				amout[search] += 1;
			}
		}
		if (equiment_ID > 33) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == equiment_ID) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(equiment_ID);
				amout.push_back(1);
				cnt += 1;
			}
			else {
				amout[search] += 1;
			}
		}
		ofstream fout_h("save_bag3.txt", ios::app);
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	return true;
}

bool CFighter::save_bag_Items(int no, int data_save) {
	CBagEntry* ne = bag->item_lookup(no);
	if (!ne) {
		return false;
	}
	if (data_save == 1) {
		int cnt = 0;
		vector<int> ID;
		vector<int> amout;
		if (ne->itm->isA() == eweapon) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID() + 15) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID() + 15);
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		else if (ne->itm->isA() == efood) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID()) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID());
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		else if (ne->itm->isA() == eequiment) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID() + 33) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID() + 33);
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		ofstream fout_h("save_bag1.txt", ios::app);
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	else if (data_save == 2) {
		int cnt = 0;
		vector<int> ID;
		vector<int> amout;
		if (ne->itm->isA() == eweapon) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID() + 15) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID() + 15);
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		else if (ne->itm->isA() == efood) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID()) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID());
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		else if (ne->itm->isA() == eequiment) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID() + 33) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID() + 33);
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		ofstream fout_h("save_bag2.txt", ios::app);
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	else if (data_save == 3) {
		int cnt = 0;
		vector<int> ID;
		vector<int> amout;
		if (ne->itm->isA() == eweapon) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID() + 15) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID() + 15);
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		else if (ne->itm->isA() == efood) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID()) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID());
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		else if (ne->itm->isA() == eequiment) {
			int search = -1;
			for (int x = 0; x < cnt; x++) {
				if (ID[x] == ne->itm->getID() + 33) {
					search = x;
					break;
				}
			}
			if (search == -1) {
				ID.push_back(ne->itm->getID() + 33);
				amout.push_back(ne->getNum());
				cnt += 1;
			}
			else {
				amout[search] += ne->getNum();
			}
		}
		ofstream fout_h("save_bag3.txt", ios::app);
		for (int y = 0; y < cnt; y++) {
			fout_h << ID[y] << endl << amout[y] << endl;
		}
	}
	return true;
}

bool CFighter::useBagItems(int no) {
	CBagEntry* ne = bag->item_lookup(no);
	static int take_armor = 0;
	if (!ne) {
		return false;
	}
	if (ne->itm->isA() == efood) {
		if (ne->itm->getID() >= 10) {
			this->addSP(200);
			food_effect += 3;
			food_bonus = true;
			cout << "<特殊食品，加乘而外傷害200(3回合)↑>" << endl;
		}

	}
	else if (ne->itm->isA() == eweapon) {
		CWeapon* cur_weapon = this->getWeapon();
		if (cur_weapon != NULL) {
			CItem* weapon_item = (CItem*)cur_weapon;
			CBagEntry* entry = bag->item_lookup(weapon_item->isA(), weapon_item->getID());
			if (!entry)
				bag->item_insert(weapon_item);
			else
				entry->addNum(1);
			cout << this->getname() << " 將手上武器 " << weapon_item->getName() << " 放回背包中" << endl;
			weapon_item->UnUsed(this);
		}
		else {
			take_armor += 1;
		}
		this->setWeapon((CWeapon*)ne->itm);
		set_wear_weapon_ID(ne->itm->getID());
	}
	else if (ne->itm->isA() == eequiment) {
		CEquiment* cur_equiment = this->getEquiment();
		if (cur_equiment != NULL) {
			CItem* equiment_item = (CItem*)cur_equiment;
			CBagEntry* entry = bag->item_lookup(equiment_item->isA(), equiment_item->getID());
			if (!entry)
				bag->item_insert(equiment_item);
			else
				entry->addNum(1);
			cout << this->getname() << " 將手上裝備 " << equiment_item->getName() << " 放回背包中" << endl;
			equiment_item->UnUsed(this);
		}
		else {
			take_armor += 1;
		}
		this->setEquiment((CEquiment*)ne->itm);
		set_wear_equiment_ID(ne->itm->getID());
	}
	if (take_armor == 2) {
		this->addSP(50);
		cout << "<裝備和武器加乘傷害50↑>" << endl;
		//if()
	}

	ne->itm->beUsed(this);
	ne->deleteNum();
	if (ne->getNum() == 0) {
		bag->item_delete(ne);
	}
	this->showAllBagItems();
	return true;
}

int CFighter::isA() {
	return efighter;
}

int CFighter::goto_next_city(int next_dir) {
	int next_city = CGlobalInfo::map_data->next_city(cur_city, next_dir);
	if (next_city) {
		cur_city = next_city;
		return cur_city;
	}
	return 0;
}

int CFighter::get_current_city() {
	return cur_city;
}
