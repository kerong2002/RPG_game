#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <windows.h>
#include <conio.h>
#include "C110152338_Place.h"
#include "C110152338_CmdParser.h"
#include "C110152338_GlobalInfo.h"
#include "C110152338_User.h"
#include "C110152338_MapData.h"
#include "C110152338_Fighter.h"
#include "C110152338_def.h"
#include "C110152338_ItemData.h"

int function_exit (vector<string> &tokens){	
	return -1;
}
//==================<光標移動>=========================
void cursor_movement_cmd(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y + 3;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
int function_next_direction (vector<string> &tokens){	
	if (tokens.size () != 1){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	int next_dir = 0;
	string dir = tokens [0];
	if (dir == string ("east")){
		next_dir = eEast;
	} else if  (dir == string ("west")){
		next_dir = eWest;
	} else if  (dir == string ("north")){
		next_dir = eNorth;	
	} else if  (dir == string ("south")){
		next_dir = eSouth;	
	} else if  (dir == string ("eastnorth")){
		next_dir = eEastNorth;	
	} else if  (dir == string ("eastsouth")){
		next_dir = eEastSouth;	
	} else if  (dir == string ("westnorth")){
		next_dir = eWestNorth;	
	} else if  (dir == string ("westsouth")){
		next_dir = eWestSouth;
	} else {
		cout << "no such command " << dir << endl;
		return 0;
	}

	int next_city = CGlobalInfo::user->goto_next_city (next_dir);
	if (next_city){
		system ("cls");
		CGlobalInfo::map_data->show_description (next_city);		
	} else {
		cursor_movement_cmd(0, 21);
		cout << "那邊沒路喔!!!請換個方向吧" << endl;	
		return 1;
	}
	return 0;
}

int function_list (vector<string> &tokens){	
	if (tokens.size () != 1){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}	
	int city = CGlobalInfo::user->get_current_city ();	
	CPlace *cityptr = CGlobalInfo::map_data->get_place_by_id (city);
	if (cityptr){
		//cout << cityptr->get_monster_num();
		//cityptr->show_random_mosters();
		//cout << "@@@";
		cityptr->show_mosters ();
	}	
	return 0;
}
int function_meet_monster(vector<string>& tokens) {
	/*if (tokens.size() != 2) {
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}*/
	system("color 0F");
	for (int y = 0; y < 34; y++) {
		cursor_movement_cmd(0, 17+y);
		cout << "                                                                                                      ";
	}
	cursor_movement_cmd(0, 17);
	int city = CGlobalInfo::user->get_current_city();
	CPlace* cityptr = CGlobalInfo::map_data->get_place_by_id(city);
	assert(cityptr);
	string monster_engname = cityptr->show_random_mosters();
	CMonster* monster = cityptr->get_monster_by_engname(monster_engname);
	if (!monster) {
		cout << "no such monsters" << endl;
		cursor_movement_cmd(0, -3);
		return 0;
	}

	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);
	if (usr->kill(monster)) {
		cityptr->remove_moster_by_engname(monster_engname);
		cout << "怪物已死，從怪物身上掉下寶物" << endl;
		int take_EXP = (rand() % 30 + 20);
		cout << "獲取：(" << take_EXP << ")經驗值" << endl;
		usr->AddEXP(take_EXP);
		usr->AddMoney((rand() % 30 + 30));
		usr->set_kill_counter();
		usr->AddSkill_point(rand()%10+10);
		usr->addMagic_power(rand() % 50 + 50);
		if (usr->show_kill_counter() >= 6) {
			//cout << "monser generated";
			CGlobalInfo::map_data->generate_monsters();
		}
		CItemData* id = CGlobalInfo::itm_data;
		if (usr->isA() == efighter) {
			((CFighter*)usr)->captureItem(id->getRand());
		}
		cursor_movement_cmd(0, -3);
	}
	else {
		cout << "你現在屬於死亡狀態" << endl;
		cursor_movement_cmd(0, -3);
	}
	cursor_movement_cmd(0, -3);
	return 0;
}
int function_kill (vector<string> &tokens){	
	/*if (tokens.size() != 2) {
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}*/	
	string monster_engname;
	cin >> monster_engname;
	int city = CGlobalInfo::user->get_current_city ();	
	CPlace *cityptr = CGlobalInfo::map_data->get_place_by_id (city);
	assert(cityptr);
	CMonster *monster = cityptr->get_monster_by_engname (monster_engname);
	if (!monster){
		cout << "no such monsters" << endl;
		cursor_movement_cmd(0, -3);
		return 0;
	}

	CLifeEntity *usr = CGlobalInfo::user->get_user ();
	assert (usr);
	if (usr->kill (monster)){	
		cityptr->remove_moster_by_engname (monster_engname);		
		cout << "怪物已死，從怪物身上掉下寶物" << endl;	
		int take_EXP = (rand()%30 + 20);
		cout << "獲取：(" << take_EXP << ")經驗值"<<endl;
		usr->AddEXP(take_EXP);
		usr->AddMoney((rand() % 30 + 30));
		usr->set_kill_counter();
		usr->AddSkill_point(rand() % 10 + 10);
		if (usr->show_kill_counter()>=6) {
			//cout << "monser generated";
			CGlobalInfo::map_data->generate_monsters();
		}
		CItemData *id = CGlobalInfo::itm_data;		
		if (usr->isA() == efighter){
			((CFighter *) usr)->captureItem (id->getRand ());				
		}
		cursor_movement_cmd(0, -3);
	} else {
		cout << "你現在屬於死亡狀態" << endl;
		cursor_movement_cmd(0, -3);
	}
	cursor_movement_cmd(0, -3);
	return 0;
}


int function_check_bag (vector<string> &tokens){	
	if (tokens.size () != 1){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}	
	CLifeEntity *usr = CGlobalInfo::user->get_user ();
	assert (usr);
	if (usr->isA() == efighter){
		CFighter *f = (CFighter *) usr;	
		cout << f->getname () << " 把背包打開" << endl;
		int num = f->showAllBagItems ();		
		if (num == 0){			
			cout << "背包空空如也" << endl;
			cout << f->getname () << "  關上背包" << endl;
			return 0;
		}
	
		int selection = 0;		
		cout << "需要什麼物品 (0代表不需要)" << endl;
		cin >> selection;
		while (selection > 0){
			if (!f->useBagItems (selection)){
				cout << "無此選項存在" << endl;
			}
			selection = 0;
			cout << "需要什麼物品 (0代表不需要)" << endl;
			cin >> selection;
		}		
		cout << f->getname () << "  關上背包" << endl;
	}	
	cin.clear();
	cin.ignore(1024, '\n');		
	return 0;
}

void function_sshop() {
	system("cls");
	system("color 0F");
	cursor_movement_cmd(15, 0);
	cout << "   <技能解鎖> ";
	cursor_movement_cmd(8, 2);
	cout << " 名稱      傷害值      買價      等級";
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;

	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	for (int i = 0; i <= 7; i++) {
		cursor_movement_cmd(8, 3 + i);
		cout << id->skill_array[i]->getName();
		cursor_movement_cmd(22, 3 + i);
		cout << id->skill_array[i]->getattackbonus();
		cursor_movement_cmd(32, 3 + i);
		if (id->skill_array[i]->get_skill_level() >= 1) {
			cout << id->skill_array[i]->get_skill_cost() * (id->skill_array[i]->get_skill_level() + 1);
		}
		else {
			cout << id->skill_array[i]->get_skill_cost();
		}
		cursor_movement_cmd(42, 3 + i);
		cout << id->skill_array[i]->get_skill_level();
	}
	int choose_pos = 3;
	cursor_movement_cmd(5, 3);
	cout << ">>";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 13) {
			int compare_skill_point = usr->showSkill_point();
			if (compare_skill_point < id->skill_array[choose_pos - 3]->get_skill_cost()) {
				cursor_movement_cmd(2, 14);
				cout << "                                       ";
				cursor_movement_cmd(2, 14);
				cout << "你沒有足夠的技能點數";
			}
			else {
				usr->SubSkill_point(id->skill_array[choose_pos - 3]->get_skill_cost());
				cursor_movement_cmd(2, 14);
				cout << "                                       ";
				cursor_movement_cmd(2, 14);
				cout << "您剩下的技能點數為 : " << usr->showSkill_point();
				id->skill_array[choose_pos - 3]->add_skill_level();
				for (int i = 0; i <= 7; i++) {
					cursor_movement_cmd(8, 3 + i);
					cout << id->skill_array[i]->getName();
					cursor_movement_cmd(22, 3 + i);
					cout << id->skill_array[i]->getattackbonus();
					cursor_movement_cmd(32, 3 + i);
					if (id->skill_array[i]->get_skill_level() >= 1) {
						cout << id->skill_array[i]->get_skill_cost() * (id->skill_array[i]->get_skill_level()+1);
					}
					else {
						cout << id->skill_array[i]->get_skill_cost();
					}
					cursor_movement_cmd(42, 3 + i);
					cout << id->skill_array[i]->get_skill_level();
				}
				/*
				cursor_movement_cmd(2, 15);
				cout << "                                       ";
				cursor_movement_cmd(2, 15);*/
				//((CFighter*)usr)->shop_captureItem(id->get_equiment_num(equiment_list[choose_pos - 2]));//撿到商品
			}
		}
		if (key == 'w' || key == 'W') {
			cursor_movement_cmd(5, choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement_cmd(5, choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 10) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 10;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << ">>";
	}

	system("CLS");
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}

void function_eshop() {
	system("cls");
	system("color 0F");
	cursor_movement_cmd(15, 0);
	cout << "   <裝備商店>";
	cursor_movement_cmd(8, 2);
	cout << " 名稱      傷害值      買價";
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;

	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	CEquiment take;
	int equiment_list[7] = { 0 };
	for (int i = 1; i <= 6; i++) {
		int take = rand() % id->equiment_array_size();
		equiment_list[i] = take;
		cursor_movement_cmd(8, 2 + i);
		cout << id->equiment_array[take]->getName();
		cursor_movement_cmd(22, 2 + i);
		cout << id->equiment_array[take]->getattackbonus();
		cursor_movement_cmd(32, 2 + i);
		cout << id->equiment_array[take]->getattackbonus() * 2;
	}
	int choose_pos = 3;
	cursor_movement_cmd(5, 3);
	cout << ">>";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 13) {
			int compare_money = usr->getMoney();
			//cout << weapon_list[choose_pos - 2];
			if (compare_money < id->equiment_array[equiment_list[choose_pos - 2]]->getattackbonus() * 2) {
				cursor_movement_cmd(2, 10);
				cout << "                                       ";
				cursor_movement_cmd(2, 10);
				cout << "你沒有足夠的錢";
			}
			else {
				usr->subMoney(id->equiment_array[equiment_list[choose_pos - 2]]->getattackbonus() * 2);
				cursor_movement_cmd(2, 10);
				cout << "                                       ";
				cursor_movement_cmd(2, 10);
				cout << "您剩下的金錢為 $" << usr->getMoney();
				cursor_movement_cmd(2, 11);
				cout << "                                       ";
				cursor_movement_cmd(2, 11);
				((CFighter*)usr)->shop_captureItem(id->get_equiment_num(equiment_list[choose_pos - 2]));//撿到商品
			}
			//
		}
		if (key == 'w' || key == 'W') {
			cursor_movement_cmd(5, choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement_cmd(5, choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 8) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 8;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << ">>";
	}
	
	system("CLS");
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}
void function_wshop() {
	system("cls");
	system("color 0F");
	cursor_movement_cmd(15, 0);
	cout <<"   <武器商店>";
	cursor_movement_cmd(8, 2);
	cout<<" 名稱      傷害值      買價";
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;

	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	CWeapon take;
	int weapon_list[7] = { 0 };
	for (int i = 1; i <= 6; i++) {
		int take = rand() % id->weapon_array_size();
		weapon_list[i] = take;
		cursor_movement_cmd(8, 2 + i); 
		cout << id->weapon_array[take]->getName();
		cursor_movement_cmd(20, 2 + i);
		cout << id->weapon_array[take]->getattackbonus();
		cursor_movement_cmd(32, 2 + i);
		cout << id->weapon_array[take]->getattackbonus() * 2;
	}
	int choose_pos = 3;
	cursor_movement_cmd(5, 3);
	cout << ">>";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 13) {
			int compare_money = usr->getMoney();
			//cout << weapon_list[choose_pos - 2];
			if (compare_money < id->weapon_array[weapon_list[choose_pos - 2]]->getattackbonus() * 2) {
				cursor_movement_cmd(2, 10);
				cout << "                                       ";
				cursor_movement_cmd(2, 10);
				cout << "你沒有足夠的錢";
			}
			else { 
				usr->subMoney(id->weapon_array[weapon_list[choose_pos - 2]]->getattackbonus() * 2);
				cursor_movement_cmd(2, 10);
				cout << "                                       ";
				cursor_movement_cmd(2, 10);
				cout << "您剩下的金錢為 $"<< usr->getMoney();
				cursor_movement_cmd(2, 11);
				cout << "                                       ";
				cursor_movement_cmd(2, 11);
				((CFighter*)usr)->shop_captureItem(id->getCheck_num(weapon_list[choose_pos - 2] + id->food_array.size()));//撿到商品
			}
			//
		}
		if (key == 'w' || key == 'W') {
			cursor_movement_cmd(5, choose_pos);
			cout<<"  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement_cmd(5, choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 8) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 8;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << ">>";
	}
	system("CLS");
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}
int function_move(vector<string>& tokens){
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CFighter* set = (CFighter*)usr;
	int go_next;
	cursor_movement_cmd(62, 11);
	cout << "請輸入傳送位置:";
	cin >> go_next;
	cursor_movement_cmd(62, 12);
	if (go_next > 9 || go_next < 0) {
		cout << "Out of map!";
		cursor_movement_cmd(62, 11);
		cout << "                              ";
		cursor_movement_cmd(62, 12);
		cout << "                              ";
		return -1;
	}
	cursor_movement_cmd(62, 11);
	cout << "                              ";
	cursor_movement_cmd(62, 12);
	cout << "                              ";
	int next_city = set->get_move_city(go_next);
	if (next_city) {
		CGlobalInfo::map_data->show_description(next_city);
	}
	else {
		cout << "那邊沒路喔!!!請換個方向吧" << endl;
	}
	return 0;
}

CCmdParser::CCmdParser (){
	mappingfunc [string("exit")] = function_exit;
	mappingfunc [string("east")] = function_next_direction;
	mappingfunc [string("eastnorth")] = function_next_direction;
	mappingfunc [string("eastsouth")] = function_next_direction;
	mappingfunc [string("west")] = function_next_direction;
	mappingfunc [string("westsouth")] = function_next_direction;
	mappingfunc [string("westnorth")] = function_next_direction;
	mappingfunc [string("north")] = function_next_direction;
	mappingfunc [string("south")] = function_next_direction;
	mappingfunc [string("ls")] = function_list;
	mappingfunc [string("kill")] = function_kill;
	mappingfunc [string("checkbag")] = function_check_bag;
	mappingfunc [string("move")] = function_move;
	mappingfunc [string("wshop")] = function_wshop;			//武器
	mappingfunc [string("eshop")] = function_eshop;			//裝備
	mappingfunc [string("sshop")] = function_sshop;			//技能
	mappingfunc [string("meet_monster")] = function_meet_monster;
#if 0
	for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
		cout << (*it) << endl;			
	}		
#endif

}

int CCmdParser::query (string thing) {
	string sentense;
	sentense = thing;
	//getline (cin, sentense);	
	vector<string> tokens;		
	splitstring (sentense, tokens, string(" "));	
	if (tokens.size () == 0){
		return 0;
	}

	map<string,  void (*)>::iterator it;
	it = mappingfunc.find (tokens [0]);
	if (it == mappingfunc.end ()){
		cout << "no such commands" << endl;
		return 0;
	}	
	return (reinterpret_cast<int(*)(const vector<string> &)>(it->second)(tokens));		
}

void CCmdParser::splitstring(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find_first_of(c);
	pos1 = 0;
	while (string::npos != pos2){
		if(pos2-pos1)
			v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

