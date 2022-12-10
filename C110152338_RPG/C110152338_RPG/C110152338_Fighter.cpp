#include <iostream>
#include <iomanip>
#include <fstream>
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

CFighter::CFighter (int job,int initHP, int initSP, int initLucky, string name, int in_city) {
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
	setInitSPHP (initHP,initSP);
	set_Initjob(job);
	Lucky = initLucky;
	setInitLucky(Lucky);
	cur_city = in_city;
	bag = new CBag ();
	cursor_movement_fighter(60, 4);
	cout << "���a��q�G" << initHP;
	cursor_movement_fighter(60, 5);
	cout << "���a�ˮ`�G" << initSP;
	cursor_movement_fighter(60, 6);
	cout << "���a�����G$" << showMoney();
	cursor_movement_fighter(60, 7);
	cout << "���a���B�G��" << show_Lucky();
	cursor_movement_fighter(60, 8);
	cout << "���a���šG<" << getDegree()<<">";
	cursor_movement_fighter(60, 9);
	cout << "���a�g��G" << setw(2)<<setfill('0')<<getEXP()<<" / 50";
	cursor_movement_fighter(60, 10);
	cout << "�ޯ��I�ơG" << showSkill_point();
	cursor_movement_fighter(60, 11);
	cout << "�]�O�I�ơG" << setw(3) << setfill('0') << showMagic_power() << " / 300";
	cursor_movement_fighter(0, 20);			//�վ��Ц�m
	//cout << "One Fighter is created with (maxHP, maxSP, maxLucky) = (" << initHP << ", " << initSP << ", " << initLucky << ")" <<endl; 
}

CFighter::~CFighter (){
	if (bag)
		delete bag;
}
void CFighter::show_fighter_detail(CLifeEntity* fighter) {
	cursor_movement_fighter(60, 4);
	show_HP_detail(fighter);
	cursor_movement_fighter(60, 5);
	show_SP_detail(fighter);
	cursor_movement_fighter(60, 6);
	show_Money_detail(fighter); 
	cursor_movement_fighter(60, 7);
	cout << "���a���B�G��" << show_Lucky();
	cursor_movement_fighter(60, 8);
	show_Degree_detail(fighter);
	cursor_movement_fighter(60, 9);
	show_EXP_detail(fighter);
	cursor_movement_fighter(60, 10);
	cout << "�ޯ��I�ơG" << showSkill_point();
	cursor_movement_fighter(60, 11);
	cout << "�]�O�I�ơG" << setw(3) << setfill('0') << showMagic_power() << " / 300";
}
int CFighter::get_move_city(int move_city) {
	cur_city = move_city;
	return cur_city;
}

int CFighter::getLucky (){
	return Lucky;
}

int CFighter::physicaldamage (){
	return (rand () % getSP ());
}


void skill_1_attack_function() {
	ifstream fin_A1("Hanzo.txt");
	string take_animation;
	int cnt = 1;
	while (!fin_A1.eof()) { //�u�n�٨SŪ�짹�A���󦨥ߴN�~��@��Ū
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@'|| take_animation[y] == '.') {
				cursor_movement_fighter(60 + y, 11 + cnt);
				cout << " ";
			}
			else {
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
	cursor_movement_fighter(0, 0);
}

void skill_2_attack_function() {
	ifstream fin_A1("among_skill.txt");
	string take_animation;
	int cnt = 1;
	while (!fin_A1.eof()) { //�u�n�٨SŪ�짹�A���󦨥ߴN�~��@��Ū
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
	cursor_movement_fighter(0, 0);
}

void skill_3_attack_function() {
	ifstream fin_A1("Pharah.txt");
	string take_animation;
	int cnt = 1;
	while (!fin_A1.eof()) { //�u�n�٨SŪ�짹�A���󦨥ߴN�~��@��Ū
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
	cursor_movement_fighter(0, 0);
}

void skill_4_attack_function() {
	ifstream fin_A1("Genji.txt");
	string take_animation;
	int cnt = 1;
	while (!fin_A1.eof()) { //�u�n�٨SŪ�짹�A���󦨥ߴN�~��@��Ū
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
		cursor_movement_fighter(60, 12 + y);
		cout << "                                                                                                                        ";
	}
	cursor_movement_fighter(0, 0);
}
void skill_5_attack_function() {
	for (int x = 0; x < 4; x++) {
		ifstream fin_A1("Beam.txt");
		string take_animation;
		int cnt = 1;
		while (!fin_A1.eof()) { //�u�n�٨SŪ�짹�A���󦨥ߴN�~��@��Ū
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
	cursor_movement_fighter(0, 0);
}
void attack_function() {
	ifstream fin_A1("among.txt");
	string take_animation;
	int cnt = 1;
	while (!fin_A1.eof()) { //�u�n�٨SŪ�짹�A���󦨥ߴN�~��@��Ū
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
	cursor_movement_fighter(0, 0);
}
int CFighter::attack (CLifeEntity *l){
	int damage = physicaldamage () - l->defense (l); 
	if (damage > l->getHP ())
		damage = l->getHP ();
	l->gethurt (damage);
	attack_function();
	cursor_movement_fighter(0, 20);
	if (damage > 0){
		cout << this->getname () << " �r�O�@���A�y�� " << l->getname () << " " << damage << " ��l��" <<endl;			
	} else {
		cout << this->getname () << " �r�O�@���A���O " << l->getname () << " �j�O�@�סA�]���S���y������l��" <<endl;
	}
	if (food_effect) {
		//cout << "<�S���~�A�[���ӥ~�ˮ`200��> �Ѿl�G(" << food_effect << ")�^�X" << endl;
		food_effect -= 1;
	}
	if (food_bonus == true && food_effect == 0) {
		delSP(200);
		cursor_movement_fighter(0, 30);
		cout << "�S���~�A�[���ĪG�����A����200�ӥ~�ˮ`" << endl;
		cursor_movement_fighter(0, 20);
	}
	if (food_effect == 0) {
		food_bonus = false;
	}
	return (damage > 0 ? damage : 0);
}


int CFighter::magic_skill_attack(CLifeEntity* l,int pos) {
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
		cout << "�ϥΧޯ� ";
		show_skill_name(pos);
		cout << "�A�y�� " << l->getname() << " " << damage << " ��l��" << endl;
	}
	else {
		cout << "�ϥΧޯ� ";
		show_skill_name(pos);
		cout << " �A���O " << l->getname() << " �j�O�@�סA�]���S���y������l��" << endl;
	}
	return (damage > 0 ? damage : 0);
}

int CFighter::defense (CLifeEntity *l){
	return 	getLucky();
}
void CFighter::shop_captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " �q�ө���� " << in_item->getName() << endl;
}

void CFighter::fish_captureItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " �q������� " << in_item->getName() << endl;
}

void CFighter::captureItem (CItem *in_item){
	
	CBagEntry *entry = bag->item_lookup (in_item->isA(), in_item->getID ());
	if (!entry)
		bag->item_insert (in_item);
	else
		entry->addNum (1);	
	cout << this->getname () << " �q�a�W�߰_ " << in_item->getName () << endl;
}

int CFighter::showAllBagItems (){	
	return bag->showAllItems ();	
}

bool CFighter::useBagItems (int no){
	CBagEntry* ne = bag->item_lookup (no);
	static int take_armor = 0;
	if (!ne){		
		return false;
	} 
	if (ne->itm->isA() == efood) {
		if (ne->itm->getID() >= 10) {
			this->addSP(200);
			food_effect += 3;
			food_bonus = true;
			cout << "<�S���~�A�[���ӥ~�ˮ`200(3�^�X)��>" << endl;
		}
		
	}
	else if (ne->itm->isA () == eweapon){
		CWeapon *cur_weapon = this->getWeapon ();
		if (cur_weapon != NULL){			
			CItem *weapon_item = (CItem *) cur_weapon;
			CBagEntry *entry = bag->item_lookup (weapon_item->isA(), weapon_item->getID ());
			if (!entry)
				bag->item_insert (weapon_item);
			else
				entry->addNum (1);	
			cout << this->getname () << " �N��W�Z�� " << weapon_item->getName () << " ��^�I�]��" << endl;
			weapon_item->UnUsed (this);			
		}
		else {
			take_armor += 1;
		}
		this->setWeapon ((CWeapon *) ne->itm);				
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
			cout << this->getname() << " �N��W�˳� " << equiment_item->getName() << " ��^�I�]��" << endl;
			equiment_item->UnUsed(this);
		}
		else {
			take_armor += 1;
		}
		this->setEquiment((CEquiment*)ne->itm);
	}
	if (take_armor == 2) {
		this->addSP(50);
		cout << "<�˳ƩM�Z���[���ˮ`50��>" <<endl;
		//if()
	}

	ne->itm->beUsed (this);
	ne->deleteNum ();
	if (ne->getNum () == 0){
		bag->item_delete (ne);
	}
	this->showAllBagItems ();
	return true;
}

int CFighter::isA (){
	return efighter;
}

int CFighter::goto_next_city (int next_dir){
	int next_city = CGlobalInfo::map_data->next_city (cur_city, next_dir);	
	if (next_city){
		cur_city = next_city;
		return cur_city;
	}
	return 0;
}

int CFighter::get_current_city (){
	return cur_city;	
}
