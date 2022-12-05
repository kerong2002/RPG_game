#include <fstream>
#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_food.h"
#include "C110152338_weapon.h"
#include "C110152338_ItemData.h"
#include "C110152338_GlobalInfo.h"
using namespace std;

void CItemData::Initialize() {
	LoadFoodData();
	LoadWeaponData();
}

int CItemData::totalsize() {
	return food_array.size() + weapon_array.size();
}
int CItemData::weapon_array_size() {
	return weapon_array.size();
}
CItem* CItemData::getCheck_num(int pick) {
	if (pick < food_array.size()) {
		return food_array[pick];
	}
	pick -= food_array.size();
	if (pick < weapon_array.size()) {
		return weapon_array[pick];
	}
	return NULL;
}
CItem* CItemData::getRand() {
	unsigned int randnum = rand() % totalsize();
	if (randnum < food_array.size()) {
		return food_array[randnum];
	}
	randnum -= food_array.size();
	if (randnum < weapon_array.size()) {
		return weapon_array[randnum];
	}
	return NULL;
}

void CItemData::LoadFoodData() {
	ifstream fin("food.txt");
	if (!fin) {
		cout << "ÅªÀÉ¥¢±Ñ: food.txt" << endl;
		return;
	}
	string name;
	int hp_bonus;
	int inID;
	CFood* food;
	while (!fin.eof()) {
		fin >> inID >> name >> hp_bonus;
		food = new CFood(name, 0, 0, inID, hp_bonus);
		CGlobalInfo::itm_data->food_array.push_back(food);
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close();
}
void CItemData::showWeaponData() {
	for (int x = 0; x < weapon_array.size(); x++) {
		cout << weapon_array[x]->getName() << endl;
	}
}
void CItemData::LoadWeaponData() {
	ifstream fin("weapon.txt");
	if (!fin) {
		cout << "ÅªÀÉ¥¢±Ñ: weapon.txt" << endl;
		return;
	}
	string name;
	int attack_bonus;
	int inID;
	CWeapon* weapon;
	while (!fin.eof()) {
		fin >> inID >> name >> attack_bonus;
		weapon = new CWeapon(name, 0, 0, inID, attack_bonus);
		//cout << weapon;
		CGlobalInfo::itm_data->weapon_array.push_back(weapon);
		/*for (int x = 0; x < weapon_array.size(); x++) {
			cout << weapon_array[x];
		}*/
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close();

}
