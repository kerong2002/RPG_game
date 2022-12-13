#include <fstream>
#include <iostream>
#include "C110152338_Item.h"
#include "C110152338_food.h"
#include "C110152338_weapon.h"
#include "C110152338_Equiment.h"
#include "C110152338_Skill.h"
#include "C110152338_legend_armor.h"
#include "C110152338_ItemData.h"
#include "C110152338_GlobalInfo.h"
using namespace std;

void CItemData::Initialize(int save) {
	LoadFoodData();
	LoadWeaponData();
	LoadEquimentData();
	LoadSkillData(save);
	LoadLegend_Armor(save);
}

int CItemData::totalsize() {
	return food_array.size() + weapon_array.size();
}

int CItemData::weapon_array_size() {
	return weapon_array.size();
}

int CItemData::equiment_array_size() {
	return equiment_array.size();
}

CItem* CItemData::get_f_num(int pick) {
	if (pick < food_array.size()) {
		return food_array[pick];
	}
	return NULL;
}

CItem* CItemData::get_w_num(int pick) {
	if (pick < weapon_array.size()) {
		return weapon_array[pick];
	}
	return NULL;
}
CItem* CItemData::get_equiment_num(int pick) {
	if (pick < equiment_array.size()) {
		return equiment_array[pick];
	}
	return NULL;
}

CItem* CItemData::getCheck_num(int pick) {
	if (pick >= 1 && pick <= food_array.size()) {
		return food_array[pick-1];
	}
	pick -= food_array.size();
	if (pick <= weapon_array.size()) {
		return weapon_array[pick-1];
	}
	pick -= weapon_array.size();
	if (pick <= equiment_array.size()) {
		return equiment_array[pick-1];
	}
	/*
	if (pick < food_array.size()) {
		return food_array[pick];
	}
	else {
		if (pick > weapon_array.size() + 15) {
			return equiment_array[pick - 33];
		}
		else {
			return weapon_array[pick - 15];
		}
	}*/
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
void CItemData::LoadEquimentData() {
	ifstream fin("equiment.txt");
	if (!fin) {
		cout << "ÅªÀÉ¥¢±Ñ: equiment.txt" << endl;
		return;
	}
	string name;
	int attack_bonus;
	int inID;
	CEquiment* equiment;
	while (!fin.eof()) {
		fin >> inID >> name >> attack_bonus;
		equiment = new CEquiment(name, 0, 0, inID, attack_bonus);
		CGlobalInfo::itm_data->equiment_array.push_back(equiment);
	}
	fin.close();

}

void CItemData::LoadSkillData(int save) {
	if (save <=0) {
		ifstream fin("skill_0.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: skill.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int skill_cost;
		int skill_level;
		CSkill* skill;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> skill_cost >> skill_level;
			skill = new CSkill(name, 0, 0, inID, attack_bonus, skill_cost, skill_level);
			CGlobalInfo::itm_data->skill_array.push_back(skill);
		}
		fin.close();
	}
	else if (save == 1) {
		ifstream fin("skill_1.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: skill.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int skill_cost;
		int skill_level;
		CSkill* skill;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> skill_cost >> skill_level;
			skill = new CSkill(name, 0, 0, inID, attack_bonus, skill_cost, skill_level);
			CGlobalInfo::itm_data->skill_array.push_back(skill);
		}
		fin.close();
	}
	else if (save == 2) {
		ifstream fin("skill_2.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: skill.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int skill_cost;
		int skill_level;
		CSkill* skill;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> skill_cost >> skill_level;
			skill = new CSkill(name, 0, 0, inID, attack_bonus, skill_cost, skill_level);
			CGlobalInfo::itm_data->skill_array.push_back(skill);
		}
		fin.close();
	}
	else if (save == 3) {
		ifstream fin("skill_3.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: skill.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int skill_cost;
		int skill_level;
		CSkill* skill;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> skill_cost >> skill_level;
			skill = new CSkill(name, 0, 0, inID, attack_bonus, skill_cost, skill_level);
			CGlobalInfo::itm_data->skill_array.push_back(skill);
		}
		fin.close();
	}
}

void CItemData::LoadLegend_Armor(int save) {
	if (save <= 0) {
		ifstream fin("legend_armor_0.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: legend_armor.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int Armor_cost;
		int Armor_level;
		CLegend_Armor* Armor;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> Armor_cost >> Armor_level;
			Armor = new CLegend_Armor(name, 0, 0, inID, attack_bonus, Armor_cost, Armor_level);
			CGlobalInfo::itm_data->Legend_Armor_array.push_back(Armor);
		}
		fin.close();
	}
	else if (save == 1) {
		ifstream fin("legend_armor_1.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: legend_armor.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int Armor_cost;
		int Armor_level;
		CLegend_Armor* Armor;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> Armor_cost >> Armor_level;
			Armor = new CLegend_Armor(name, 0, 0, inID, attack_bonus, Armor_cost, Armor_level);
			CGlobalInfo::itm_data->Legend_Armor_array.push_back(Armor);
		}
		fin.close();
	}
	else if (save == 2) {
		ifstream fin("legend_armor_2.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: legend_armor.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int Armor_cost;
		int Armor_level;
		CLegend_Armor* Armor;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> Armor_cost >> Armor_level;
			Armor = new CLegend_Armor(name, 0, 0, inID, attack_bonus, Armor_cost, Armor_level);
			CGlobalInfo::itm_data->Legend_Armor_array.push_back(Armor);
		}
		fin.close();
	}
	else if (save == 3) {
		ifstream fin("legend_armor_3.txt");
		if (!fin) {
			cout << "ÅªÀÉ¥¢±Ñ: legend_armor.txt" << endl;
			return;
		}
		string name;
		int attack_bonus;
		int inID;
		int Armor_cost;
		int Armor_level;
		CLegend_Armor* Armor;
		while (!fin.eof()) {
			fin >> inID >> name >> attack_bonus >> Armor_cost >> Armor_level;
			Armor = new CLegend_Armor(name, 0, 0, inID, attack_bonus, Armor_cost, Armor_level);
			CGlobalInfo::itm_data->Legend_Armor_array.push_back(Armor);
		}
		fin.close();
	}
}