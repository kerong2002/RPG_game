#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_food.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_def.h"

using namespace std;

CFood::CFood (string inname, int initSize, int initWeight, int initID, int init_hp) : CItem (inname, initSize, initWeight, initID){	
	bonus_hp = init_hp;
	food_ID = initID;
}

int CFood::gethpbonus (){	
	return bonus_hp;
}

int CFood::get_food_ID() {
	return food_ID;
}

void CFood::beUsed (CLifeEntity *le){
	cout << "戰士使用食物" << getName () << ", ";
	le->addHP (this->gethpbonus ());
	cout << "體力回升到 " << le->getHP () << endl;
}

void CFood::UnUsed (CLifeEntity *le){	
}


int CFood::isA (){
	return efood;
}