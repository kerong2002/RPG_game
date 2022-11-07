#include <iostream>
#include <fstream>
#include <cassert>
#include "C110152338_Place.h"
#include "C110152338_MapData.h"
#include "C110152338_MonsterData.h"
#include "C110152338_GlobalInfo.h"

using namespace std;

CPlace::CPlace (string filename){	
	ifstream fin(filename);	
	if (!fin){
		cout << "讀檔失敗: " << filename << endl;
		return;
	}
	fin >> name >> description;	
	fin.close ();
	for (int i = 0; i < MAX_DIRECTIONS; i++){
		exits [i] = 0;
	}	
}

string CPlace::get_exits (){
	string output;
	int next_city;
	bool comma = false;
	for (int i = 0; i < MAX_DIRECTIONS; i++){
		next_city = exits[i];
		if (next_city > 0){
			if (comma)
				output += string("，");				
			switch (i){
			case eNorth:
				output += string("往北方(north)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eEastNorth:
				output += string("往東北方(eastnorth)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eEast:
				output += string("往東方(east)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eEastSouth:
				output += string("往東南方(eastsouth)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eSouth:
				output += string("往南方(south)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eWestSouth:
				output += string("往西南方(westsouth)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eWest:
				output += string("往西方(west)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			case eWestNorth:
				output += string("往西北方(westnorth)是 ") + CGlobalInfo::map_data->mapdata [next_city]->getname ();
				break;
			default:
				cerr << "Error in calling CPlace::show_exits" << endl;		
				exit (0);
			}			
			comma = true;
		}
	}
	if (comma)
		output += string("。");	
	return output;
}

void CPlace::gen_monster_by_id (int id){
	CMonsterType *type = CGlobalInfo::monster_data->get_monstertype_by_id (id);
	assert (type);
	CMonster *tmp = new CMonster (type);
	monsters.push_back (tmp);
}

CMonster *CPlace::get_monster_by_engname (string engname){
	for (vector <CMonster *>::iterator it = monsters.begin (); it != monsters.end (); it++){
		if ((*it)->get_engname () == engname)
			return (*it);
	}
	return NULL;
}

bool CPlace::remove_moster_by_engname (string engname){	
	for (vector <CMonster *>::iterator it = monsters.begin (); it != monsters.end (); it++){
		if ((*it)->get_engname () == engname){			
			delete (*it);
			monsters.erase (it);			
			return true;
		}
	}	
	return false;
}


void CPlace::show_mosters (){
	vector <CMonster *>::iterator it = monsters.begin ();
	if (it == monsters.end ()){
		cout << "無任何怪物資料" << endl;
		return;
	}
	for (; it != monsters.end (); it++){
		cout << (*it)->get_basic_data () << endl;
	}
}