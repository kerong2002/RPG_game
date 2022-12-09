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
	cout << "玩家血量：" << initHP;
	cursor_movement_fighter(60, 5);
	cout << "玩家傷害：" << initSP;
	cursor_movement_fighter(60, 6);
	cout << "玩家金錢：$" << showMoney();
	cursor_movement_fighter(60, 7);
	cout << "玩家幸運：☆" << show_Lucky();
	cursor_movement_fighter(60, 8);
	cout << "玩家等級：<" << getDegree()<<">";
	cursor_movement_fighter(60, 9);
	cout << "玩家經驗：" << setw(2)<<setfill('0')<<getEXP()<<" / 50";
	cursor_movement_fighter(60, 10);
	cout << "技能點數：" << showSkill_point();
	cursor_movement_fighter(60, 11);
	cout << "魔力點數：" << setw(3) << setfill('0') << showMagic_power() << " / 300";
	cursor_movement_fighter(0, 20);			//調整游標位置
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
	cout << "玩家幸運：☆" << show_Lucky();
	cursor_movement_fighter(60, 8);
	show_Degree_detail(fighter);
	cursor_movement_fighter(60, 9);
	show_EXP_detail(fighter);
	cursor_movement_fighter(60, 10);
	cout << "技能點數：" << showSkill_point();
	cursor_movement_fighter(60, 11);
	cout << "魔力點數：" << setw(3) << setfill('0') << showMagic_power() << " / 300";
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
void skill_attack_function() {
	ifstream fin_A1("among_skill.txt");
	string take_animation;
	int cnt = 1;
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
void attack_function() {
	ifstream fin_A1("among.txt");
	string take_animation;
	int cnt = 1;
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
		cout << this->getname () << " 猛力一揮，造成 " << l->getname () << " " << damage << " 血損失" <<endl;			
	} else {
		cout << this->getname () << " 猛力一揮，但是 " << l->getname () << " 強力一擋，因此沒有造成任何損失" <<endl;
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


int CFighter::magic_skill_attack(CLifeEntity* l,int pos) {
	int damage = get_skill_damage(pos) - l->defense(l);
	if (damage > l->getHP())
		damage = l->getHP();
	l->gethurt(damage);
	skill_attack_function();
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

int CFighter::defense (CLifeEntity *l){
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

void CFighter::captureItem (CItem *in_item){
	
	CBagEntry *entry = bag->item_lookup (in_item->isA(), in_item->getID ());
	if (!entry)
		bag->item_insert (in_item);
	else
		entry->addNum (1);	
	cout << this->getname () << " 從地上撿起 " << in_item->getName () << endl;
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
			cout << "<特殊食品，加乘而外傷害200(3回合)↑>" << endl;
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
			cout << this->getname () << " 將手上武器 " << weapon_item->getName () << " 放回背包中" << endl;
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
			cout << this->getname() << " 將手上裝備 " << equiment_item->getName() << " 放回背包中" << endl;
			equiment_item->UnUsed(this);
		}
		else {
			take_armor += 1;
		}
		this->setEquiment((CEquiment*)ne->itm);
	}
	if (take_armor == 2) {
		this->addSP(50);
		cout << "<裝備和武器加乘傷害50↑>" <<endl;
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
