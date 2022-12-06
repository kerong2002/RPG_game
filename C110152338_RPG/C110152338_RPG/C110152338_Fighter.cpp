#include <iostream>
#include <iomanip>
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
	initHP = initHP;
	initSP = initSP;
	initLucky = initLucky;
	get_job_num = job;
	setname(name);
	setInitSPHP (initHP,initSP);
	
	Lucky = initLucky;
	cur_city = in_city;
	bag = new CBag ();
	cursor_movement_fighter(60, 5);
	cout << "���a��q�G" << initHP;
	cursor_movement_fighter(60, 6);
	cout << "���a�ˮ`�G" << initSP;
	cursor_movement_fighter(60, 7);
	cout << "���a�����G$" << showMoney();
	cursor_movement_fighter(60, 8);
	cout << "���a���šG<" << getDegree()<<">";
	cursor_movement_fighter(60, 9);
	cout << "���a�g��G" << setw(2)<<setfill('0')<<getEXP()<<" / 50";
	cursor_movement_fighter(0, 20);			//�վ��Ц�m
	//cout << "One Fighter is created with (maxHP, maxSP, maxLucky) = (" << initHP << ", " << initSP << ", " << initLucky << ")" <<endl; 
}

CFighter::~CFighter (){
	if (bag)
		delete bag;
}
void CFighter::show_fighter_detail(CLifeEntity* fighter) {
	cursor_movement_fighter(60, 5);
	show_HP_detail(fighter);
	cursor_movement_fighter(60, 6);
	show_SP_detail(fighter);
	cursor_movement_fighter(60, 7);
	show_Money_detail(fighter);
	cursor_movement_fighter(60, 8);
	show_Degree_detail(fighter);
	cursor_movement_fighter(60, 9);
	show_EXP_detail(fighter);
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

int CFighter::attack (CLifeEntity *l){
	int damage = physicaldamage () - l->defense (l); 
	if (damage > l->getHP ())
		damage = l->getHP ();
	l->gethurt (damage);
	
	if (damage > 0){
		cout << this->getname () << " �r�O�@���A�y�� " << l->getname () << " " << damage << " ��l��" <<endl;			
	} else {
		cout << this->getname () << " �r�O�@���A���O " << l->getname () << " �j�O�@�סA�]���S���y������l��" <<endl;
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
	if (ne->itm->isA () == eweapon){
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
