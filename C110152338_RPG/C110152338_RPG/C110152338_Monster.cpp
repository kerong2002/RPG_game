#include <iostream>
#include <string>
#include "C110152338_Monster.h"
#include "C110152338_MonsterData.h"
#include "C110152338_def.h"

using namespace std;
CMonster::CMonster (int initHP, int initSP, int initrough, string init_name, string init_eng_name) : CLifeEntity (initHP,initSP,init_name), RoughDegree(initrough), eng_name(init_eng_name) {	
	counter_for_monster_id++;
	cout << "one monster called " << init_name << " (" << init_eng_name << ") is created with <HP, SP, rough> = <" << initHP << ", " << initSP << ", " << initrough << ">" << endl;
}


	
CMonster::CMonster(const CMonsterType* type) : CLifeEntity(1 + rand() % type->max_hp, 1 + rand() % type->max_sp, type->name), RoughDegree(type->max_rough) {
	counter_for_monster_id++;
	eng_name = type->prefix_eng_name + to_string ((long double)counter_for_monster_id);	
	cout << "Monster called " << type->name << " (" << eng_name << ") is created with <HP, SP, rough> = <" << this->getHP () << ", " << this->getSP () << ", " << this->getRough () << ">" << endl;
}


int CMonster::getRough (){
	return RoughDegree;
}

int CMonster::physicaldamage (){
	return (rand () % getSP () + getRough ());
}

int CMonster::attack (CLifeEntity *l){
	int damage = physicaldamage () - l->defense (l); 
	if (damage > l->getHP ())
		damage = l->getHP ();

	l->gethurt (damage);
	
	if (damage > 0){
		cout << this->getname () << " ��ŧ�ӨӡA�y�� " << l->getname () << " " << damage << " ��l��" <<endl;			
	} else {
		cout << this->getname () << " ��ŧ�ӨӡA���O " << l->getname () << " ���`���B�A�]�����פF����" <<endl;
	}
	return (damage);
}

int CMonster::defense (CLifeEntity *l){
	return 0;		
}

int CMonster::isA (){
	return emonster;
}

string CMonster::get_basic_data (){
	string output = this->getname () + string ("(") + this->eng_name + string (") <HP, SP, rough> = <") + to_string((long double)this->getHP ()) + string (", ")  + to_string((long double)this->getSP ()) + string (", ") + to_string((long double)this->getRough ()) + string(">");
	return output;	
}