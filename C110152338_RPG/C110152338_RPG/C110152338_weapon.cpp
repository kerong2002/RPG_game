#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_weapon.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_def.h"

using namespace std;

CWeapon::CWeapon (string inname, int initSize, int initWeight, int initID, int init_attack) : CItem (inname, initSize, initWeight, initID){	
	bonus_attack = init_attack;
}

int CWeapon::getattackbonus (){	
	return bonus_attack;
}

void CWeapon::beUsed (CLifeEntity *le){
	cout << "�Ԥh�ϥΪZ��" << getName () << ", ";
	cout << "�����O�q�쥻 " << le->getSP ();
	le->addSP (this->getattackbonus ());
	cout << "�W�ɨ� " << le->getSP () << endl;
}

void CWeapon::UnUsed (CLifeEntity *le){
	cout << "�Ԥh " << getName () << " ";
	cout << "�����O�q�쥻 " << le->getSP ();
	le->delSP (this->getattackbonus ());
	cout << "�U���� " << le->getSP () << endl;
}


int CWeapon::isA (){
	return eweapon;
}