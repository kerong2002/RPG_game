#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <vector>

class CFood;
class CWeapon;
class CItem;

class CItemData {
public:
	CItemData (){};
	~CItemData ();
	void Initialize ();
	int totalsize ();
	CItem *getRand ();
	vector <CFood *> food_array;	
	vector <CWeapon *> weapon_array;	
private:
	void LoadFoodData ();
	void LoadWeaponData ();
};

#endif