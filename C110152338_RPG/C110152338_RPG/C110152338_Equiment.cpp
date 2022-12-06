#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_Equiment.h"
#include "C110152338_LifeEntity.h"
#include "C110152338_def.h"

using namespace std;

CEquiment::CEquiment(string inname, int initSize, int initWeight, int initID, int init_attack) : CItem(inname, initSize, initWeight, initID) {
	bonus_attack = init_attack;
}

int CEquiment::getattackbonus() {
	return bonus_attack;
}

void CEquiment::beUsed(CLifeEntity* le) {
	cout << "���a�ϥθ˳�" << getName() << ", ";
	cout << "�ͩR�O�q�쥻 " << le->getMAXHP();
	le->addMAXHP(this->getattackbonus());
	cout << "�W�ɨ� " << le->getMAXHP() << endl;
}

void CEquiment::UnUsed(CLifeEntity* le) {
	cout << "���a " << getName() << " ";
	cout << "�ͩR�O�q�쥻 " << le->getMAXHP();
	le->delMAXHP(this->getattackbonus());
	cout << "�U���� " << le->getMAXHP() << endl;
}


int CEquiment::isA() {
	return eequiment;
}