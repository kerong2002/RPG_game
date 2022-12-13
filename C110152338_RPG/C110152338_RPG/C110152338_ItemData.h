#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <vector>

class CFood;
class CWeapon;
class CItem;
class CEquiment;
class CSkill;
class CLegend_Armor;

class CItemData {
public:
	CItemData (){};
	~CItemData ();
	void Initialize (int);
	int totalsize ();
	int weapon_array_size();
	int equiment_array_size();
	CItem *getRand ();
	CItem* getCheck_num(int);
	CItem* get_equiment_num(int);
	CItem* get_f_num(int);
	CItem* get_w_num(int);
	void showWeaponData();
	vector <CFood *> food_array;	
	vector <CWeapon *> weapon_array;	
	vector <CEquiment *> equiment_array;
	vector <CSkill *> skill_array;
	vector <CLegend_Armor *> Legend_Armor_array;
private:
	void LoadFoodData ();
	void LoadWeaponData ();
	void LoadEquimentData();
	void LoadSkillData(int);
	void LoadLegend_Armor(int);
};

#endif