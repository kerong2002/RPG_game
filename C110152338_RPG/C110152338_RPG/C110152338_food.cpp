#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_food.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_def.h"

using namespace std;

CFood::CFood (string inname, int initSize, int initWeight, int initID, int init_hp) : CItem (inname, initSize, initWeight, initID){	
	bonus_hp = init_hp;
}

int CFood::gethpbonus (){	
	return bonus_hp;
}

void CFood::beUsed (CLifeEntity *le){
	cout << "�Ԥh�ϥέ���" << getName () << ", ";
	le->addHP (this->gethpbonus ());
	cout << "��O�^�ɨ� " << le->getHP () << endl;
}

void CFood::UnUsed (CLifeEntity *le){	
}


int CFood::isA (){
	return efood;
}