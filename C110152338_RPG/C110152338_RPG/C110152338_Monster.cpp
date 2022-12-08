#include <iostream>
#include <string>
#include <Windows.h>
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
	int rand_take = (rand() % 3 + 1);				//亂數產生等級
	eng_name = type->prefix_eng_name + "<" + to_string(rand_take) + ">";
	if(rand_take >1){
		this->addMAXHP(this->getHP() * (rand_take-1));
	}
	cout << "Monster called " << type->name << " (" << eng_name << ") is created with <HP, SP, rough> = <" << this->getHP () << ", " << this->getSP() << ", " << this->getRough() << ">" << endl;
}

//==================<光標移動>=========================
void cursor_movement_Monster(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
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
		cout << this->getname () << " 突襲而來，造成 " << l->getname () << " " << damage << " 血損失" <<endl;			
	} else {
		cout << this->getname () << " 突襲而來，但是 " << l->getname () << " 異常幸運，因此躲避了攻擊" <<endl;
	}
	return (damage);
}

int CMonster::magic_attack(CLifeEntity* l) {
	int damage = physicaldamage() - l->defense(l);
	if (damage > l->getHP())
		damage = l->getHP();
	l->gethurt(damage);

	if (damage > 0) {
		cout << this->getname() << " 突襲而來，造成 " << l->getname() << " " << damage << " 血損失" << endl;
	}
	else {
		cout << this->getname() << " 突襲而來，但是 " << l->getname() << " 異常幸運，因此躲避了攻擊" << endl;
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

string CMonster::get_monster_name() {
	string output = this->eng_name ;
	return output;
}