
#ifndef MAPDATA_H
#define MAPDATA_H

#include <map>
#include "C110152338_Place.h"

#define MAX_MONSTER_PER_PLACE 5

class CMapData {
	friend class CPlace;
public:	
	CMapData ();
	~CMapData ();	
	void show_description (int in_ID);
	string get_exits (int in_ID);
	int next_city (int cur_city, int next_dir);
	void generate_monsters ();
	CPlace *get_place_by_id (int id);
private:
	map<int, CPlace *> mapdata;
	int num_cities;
};

#endif