#include <iostream>
#include "C110152338_Fighter.h"
#include "C110152338_food.h"
#include "C110152338_Bag.h"
#include "C110152338_def.h"
#include "C110152338_GlobalInfo.h"
#include "C110152338_MapData.h"

using namespace std;

CFighter::CFighter (int initHP, int initSP, int initLucky, int in_city) {
	if (initHP == 0 && initSP == 0 && initLucky == 0){
		initHP = 1 + rand() % (FIGHTER_MAXHP);
		initSP = 1 + rand() % (FIGHTER_MAXSP);
		initLucky = 1 + rand() % (FIGHTER_MAXLUCKY);
		setname ("勇者無敵");
	}

	setInitSPHP (initHP,initSP);
	Lucky = initLucky;
	cur_city = in_city;
	bag = new CBag ();
	cout << "One Fighter is created with (maxHP, maxSP, maxLucky) = (" << initHP << ", " << initSP << ", " << initLucky << ")" <<endl; 
}

CFighter::~CFighter (){
	if (bag)
		delete bag;
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
		cout << this->getname () << " 猛力一揮，造成 " << l->getname () << " " << damage << " 血損失" <<endl;			
	} else {
		cout << this->getname () << " 猛力一揮，但是 " << l->getname () << " 強力一擋，因此沒有造成任何損失" <<endl;
	}
	return (damage > 0 ? damage : 0);
}

int CFighter::defense (CLifeEntity *l){
	return 	getLucky();
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
			cout << this->getname () << " 將手上武器 " << weapon_item->getName () << " 放回背包中" << endl;
			weapon_item->UnUsed (this);			
		}
		this->setWeapon ((CWeapon *) ne->itm);				
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