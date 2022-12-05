#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cassert>
#include <windows.h>
#include "C110152338_MapData.h"
#include "C110152338_MonsterData.h"
#include "C110152338_GlobalInfo.h"

using namespace std;

CMapData::CMapData (){
	ifstream fin("mapdata.txt");	
	if (!fin){
		cout << "ÅªÀÉ¥¢±Ñ: mapdata.txt" << endl;
		return;
	}
	fin >> num_cities;
	int id, num_exits, dirs, place_id;
	map<int, CPlace *>::iterator it;
	string map_name;	
	CPlace *tmp_place;
	for (int i = 0; i < num_cities; i++){
		fin >> id >> map_name;
		tmp_place = new CPlace (map_name);
		it = mapdata.find (id);
		if (it == mapdata.end ()){
			mapdata.insert (pair<int, CPlace *> (id, tmp_place));
			fin >> num_exits;
			for (int j = 0; j < num_exits; j++){
				fin >> dirs >> place_id;
				tmp_place->exits [dirs] = place_id;
			}
		} else {
			cout << map_name << " with " << id << " has been added before" << endl;
			exit (0);
		}
	}	
	fin.close ();
#if 0
	for(it = mapdata.begin(); it != mapdata.end(); it++){
		cout << (*it).first << " " << (*it).second->getname () << endl;
	}
#endif    
}

CMapData::~CMapData (){
	for(map<int, CPlace *>::iterator it = mapdata.begin(); it != mapdata.end(); it++){
		delete it->second;
	}
}

void CMapData::cursor_movement(int x, int y){
	COORD coord;
	coord.X = (x + 4) * 2;
	coord.Y = (y + 1);
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}

string CMapData::get_exits (int in_ID){
	map<int, CPlace *>::iterator it = mapdata.find (in_ID);
	if (it == mapdata.end ()){
		cerr << "CMapData::get_exits Error";
		exit (0);
	}
	return (*it).second->get_exits ();
}

void CMapData::show_description (int in_ID){
	map<int, CPlace *>::iterator it = mapdata.find (in_ID);
	if (it == mapdata.end ()){
		cerr << "CMapData::show_description Error";
		exit (0);
	}
	CPlace *place = (*it).second;
	assert (place);
	cursor_movement(10, 0);
	cout << "                            ";
	cursor_movement(10, 0);
	cout << "<" << place->getname() << ">";
	//cout << place->getdescription() << endl;
	cursor_movement(1, 1);
	cout << "                                                                                                                         ";
	cursor_movement(1, 1);
	cout << place->get_exits () << endl;
}

int CMapData::next_city (int cur_city, int next_dir){
	map<int, CPlace *>::iterator it = mapdata.find (cur_city);
	if (it == mapdata.end ()){
		cerr << "user is in a wrong city";
		exit (0);
	}
	assert (next_dir >= 0 && next_dir <= 7);	
	return (it->second->exits [next_dir]);
}

void CMapData::generate_monsters (){	
	map<int, CPlace *>::iterator it;
	int num, monster_id;
	for(it = mapdata.begin(); it != mapdata.end(); it++){
		num = rand () % MAX_MONSTER_PER_PLACE;
		//cursor_movement(6, 0);
		cout << it->second->name << "²£¥Í " << num << " °¦©ÇÃ~"<< endl;
		//cursor_movement(0, 16);
		for (int i = 0; i < num; i++){
			monster_id = CGlobalInfo::monster_data->rand_get_monster_id ();
			it->second->gen_monster_by_id (monster_id);
		}
	}

}

CPlace *CMapData::get_place_by_id (int id){
	map<int, CPlace *>::iterator it = mapdata.find (id);
	if (it == mapdata.end ()){
		cerr << id << " id is wrong";
		exit (0);
	}	
	return (it->second);
}