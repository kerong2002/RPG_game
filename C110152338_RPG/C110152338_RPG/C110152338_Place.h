#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include "C110152338_Monster.h"
using namespace std;

#define MAX_DIRECTIONS 8
enum {
	eNorth = 0,
	eEastNorth,
	eEast,
	eEastSouth,
	eSouth,
	eWestSouth,
	eWest,
	eWestNorth
};
// type of exits
// 0: north
// 1: eastnorth
// 2: east
// 3: eastsouth
// 4: south 
// 5: westsouth
// 6: west
// 7: westnorth

class CMonster;

class CPlace {	
	friend class CMapData;
public:	
	CPlace (string filename);	
	void cursor_movement_place(int x, int y);
	string getname (){return name;};	
	string getdescription (){return description;};
	string get_exits ();
	void gen_monster_by_id (int);
	void show_mosters ();	
	CMonster *get_monster_by_engname (string);
	bool remove_moster_by_engname (string);
	int get_monster_num();
private:		
	string name;
	string description;
	int exits [8]; // store next direction place ID
	vector <CMonster *> monsters;
	
};

#endif