#include <iostream>
#pragma warning( disable : 4996 )
#include <string>
#include <fstream>
#include <cassert>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <thread>
#include "C110152338_Place.h"
#include "C110152338_CmdParser.h"
#include "C110152338_GlobalInfo.h"
#include "C110152338_User.h"
#include "C110152338_MapData.h"
#include "C110152338_Fighter.h"
#include "C110152338_Monster.h"
#include "C110152338_def.h"
#include "C110152338_ItemData.h"


//==================<光標移動>=========================
void cursor_movement_cmd(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y + 3;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}

//==================<建立顏色>==========================
void SetColor_cmd(int color = 7) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void sound_christmas() {
	PlaySound(TEXT("christmas.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
	CFighter* f = (CFighter*)usr;
	assert(usr);
	monster->set_skip(f->get_skip());
	if (usr->kill(monster)) {
		cityptr->remove_moster_by_engname(monster_engname);
		cout << "怪物已死，從怪物身上掉下寶物" << endl;
		int take_EXP = (rand() % 30 + 20);
		cout << "獲取：(" << take_EXP << ")經驗值" << endl;
		usr->AddEXP(take_EXP);
		usr->AddMoney((rand() % 30 + 30));
		usr->set_kill_counter();
		usr->AddSkill_point(rand()%10+10);
		usr->addMagic_power(rand() % 20 +10);
		if (usr->show_kill_counter() >= 6) {
			//cout << "monser generated";
			CGlobalInfo::map_data->generate_monsters();
		}
		CItemData* id = CGlobalInfo::itm_data;
		if (usr->isA() == efighter) {
			((CFighter*)usr)->captureItem(id->getRand());
			//((CFighter*)usr)->captureItem(id->getCheck_num(12));
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
		usr->addMagic_power(rand() % 20 + 10);
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

//=================<取走一樣物品>================
int function_get_bag(vector<string>& tokens) {
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;
	ifstream fin_f("house.txt");
	int no = -1;
	fin_f >> no;
	if (no != -1) {
		((CFighter*)usr)->house_captureItem(id->getCheck_num(no));
	}
	string file_name = "house.txt";
	ofstream file_writer(file_name, ios_base::out);
	return 0;
}
//=================<放置一樣物品>================
int function_put_bag(vector<string>& tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);
	if (usr->isA() == efighter) {
		CFighter* f = (CFighter*)usr;
		cout << f->getname() << " 將倉庫打開" << endl;
		int num = f->showAllBagItems();
		if (num == 0) {
			cout << "倉庫空空如也" << endl;
			cout << f->getname() << "  離開倉庫" << endl;
			return 0;
		}

		int selection = 0;
		cout << "需要什麼物品 (0代表不需要)" << endl;
		cin >> selection;
		while (selection > 0) {
			if (!f->put_storeItems(selection)) {
				cout << "無此選項存在" << endl;
			}
			selection = 0;
			cout << "需要什麼物品 (0代表不需要)" << endl;
			cin >> selection;
		}
		cout << f->getname() << "  關上背包" << endl;
	}
	cin.clear();
	cin.ignore(1024, '\n');
	return 0;
}

//===============<放置倉庫>========================
int function_put_house(vector<string>& tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);
	if (usr->isA() == efighter) {
		CFighter* f = (CFighter*)usr;
		cout << f->getname() << " 將倉庫打開" << endl;
		int num = f->showAllBagItems();
		if (num == 0) {
			cout << "倉庫空空如也" << endl;
			cout << f->getname() << "  離開倉庫" << endl;
			return 0;
		}

		int selection = 0;
		cout << "需要什麼物品 (0代表不需要)" << endl;
		cin >> selection;
		while (selection > 0) {
			if (!f->put_houseItems(selection)) {
				cout << "無此選項存在" << endl;
			}
			selection = 0;
			cout << "需要什麼物品 (0代表不需要)" << endl;
			cin >> selection;
		}
		cout << f->getname() << "  關上背包" << endl;
	}
	cin.clear();
	cin.ignore(1024, '\n');
	return 0;
}

//===============<開啟倉庫>========================
int function_check_house(vector<string>& tokens) {
	int cnt = 0;
	ifstream fin_h("house.txt");
	vector<int> ID;
	vector<int> amout;
	int take_ID;
	int take_amout;
	while (fin_h >> take_ID) {
		fin_h >> take_amout;
		cnt += 1;
		ID.push_back(take_ID);
		amout.push_back(take_amout);
	}
	if (cnt == 0) {
		cout << "倉庫空空如也" << endl;
		return 0;
	}
	CItemData* id = CGlobalInfo::itm_data;
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);
	if (usr->isA() == efighter) {
		CFighter* f = (CFighter*)usr;
		cout << f->getname() << " 將倉庫打開" << endl;
		for (int x = 0; x < cnt; x++) {
			cout << "(" << x+1<< ")" << id->getCheck_num(ID[x])->getName() << " 數量：" << amout[x] << endl;
		}
		int selection = 0;
		cout << "需要什麼物品 (0代表不需要)" << endl;
		while (cin >> selection) {
			if (selection == 0) {
				break;
			}
			cout << "需要什麼物品 (0代表不需要)" << endl;
			
			if (selection <= cnt && amout[selection-1]>=1) {
				((CFighter*)usr)->house_captureItem(id->getCheck_num(ID[selection-1]));
				if (amout[selection - 1] == 1) {
					ofstream fout_h("house.txt");
					amout[selection - 1] -= 1;
					for (int y = 0; y < cnt; y++) {
						if (amout[y] > 0) {
							fout_h <<ID[y] <<endl<< amout[y] << endl;
						}
					}
				}
				else {
					ofstream fout_h("house.txt");
					amout[selection - 1] -= 1;
					for (int y = 0; y < cnt; y++) {
						if (amout[y] > 0) {
							fout_h << ID[y] << endl << amout[y] << endl;
						}
					}
				}
			}
			else {
				cout << "超出倉庫存取範圍" << endl;
			}
			for (int x = 0; x < cnt; x++) {
				if (amout[x] > 0) {
					cout << "(" << x + 1 << ")" << id->getCheck_num(ID[x])->getName() << " 數量：" << amout[x] << endl;
				}
			}
		}
		cout << f->getname() << "  關上倉庫" << endl;
	}
	ID.clear();
	amout.clear();
	cin.clear();
	cin.ignore(1024, '\n');
	return cnt;

}	
//===============<開啟背包>========================
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
//=====================<技能解鎖>=======================
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
	for (int i = 0; i <= 4; i++) {
		cursor_movement_cmd(8, 3 + i);
		cout << id->skill_array[i]->getName();
		cursor_movement_cmd(22, 3 + i);
		if (id->skill_array[i]->get_skill_level() == 0) {
			cout << id->skill_array[i]->getattackbonus();
		}
		else {
			cout << id->skill_array[i]->getattackbonus() * id->skill_array[i]->get_skill_level();
		}
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
				for (int i = 0; i <= 4; i++) {
					cursor_movement_cmd(8, 3 + i);
					cout << id->skill_array[i]->getName();
					cursor_movement_cmd(22, 3 + i);
					if (id->skill_array[i]->get_skill_level() == 0) {
						cout << id->skill_array[i]->getattackbonus();
					}
					else {
						cout << id->skill_array[i]->getattackbonus() * id->skill_array[i]->get_skill_level();
					}
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
		if (choose_pos > 7) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 7;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << ">>";
	}

	system("CLS");
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}
//=====================<頭盔>=======================
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
//=====================<職業限定傳奇盔甲>=======================
void function_lshop() {
	system("cls");
	system("color 0F");
	cursor_movement_cmd(15, 0);
	cout << "   <職業限定鎧甲> ";
	cursor_movement_cmd(8, 2);  
	cout << " 名稱      血量增量    買價      等級";
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;

	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	for (int i = 0; i <= 4; i++) {
		cursor_movement_cmd(8, 3 + i);
		cout << id->Legend_Armor_array[i]->getName();
		cursor_movement_cmd(22, 3 + i);
		if (id->Legend_Armor_array[i]->get_armor_level() == 0) {
			cout << id->Legend_Armor_array[i]->getattackbonus();
		}
		else {
			cout << id->Legend_Armor_array[i]->getattackbonus() * id->Legend_Armor_array[i]->get_armor_level();
		}
		cursor_movement_cmd(32, 3 + i);
		if (id->Legend_Armor_array[i]->get_armor_level() >= 1) {
			cout << id->Legend_Armor_array[i]->get_armor_cost() * (id->Legend_Armor_array[i]->get_armor_level() + 1);
		}
		else {
			cout << id->Legend_Armor_array[i]->get_armor_cost();
		}
		cursor_movement_cmd(42, 3 + i);
		cout << id->Legend_Armor_array[i]->get_armor_level();
	}
	int choose_pos = 3;
	cursor_movement_cmd(5, 3);
	cout << ">>";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 13) {
			int compare_money_cost = usr->getMoney();
			
			if (compare_money_cost < id->Legend_Armor_array[choose_pos - 3]->get_armor_cost()) {
				cursor_movement_cmd(2, 14);
				cout << "                                                        ";
				cursor_movement_cmd(2, 14);
				cout << "您沒有足夠的金錢，解鎖職業限定鎧甲";
			}
			else if (usr->get_Initjob() != (choose_pos -2)) {
				cursor_movement_cmd(2, 15);
				cout << "                                                       ";
				cursor_movement_cmd(2, 15);
				cout << "您不是該職業的角色";
			}
			else {
				usr->subMoney(id->Legend_Armor_array[choose_pos - 3]->get_armor_cost());
				cursor_movement_cmd(2, 3);
				cout << "                                                       ";
				cursor_movement_cmd(2, 13);
				cout << "您的血量增量："<< id->Legend_Armor_array[choose_pos - 3]->getattackbonus();
				usr->addMAXHP(id->Legend_Armor_array[choose_pos - 3]->getattackbonus());
				//id->Legend_Armor_array[choose_pos-3]->getattackbonus();
				cursor_movement_cmd(2, 14);
				cout << "                                       ";
				cursor_movement_cmd(2, 14);
				cout << "您剩下的金錢為 :$ " << usr->showMoney();
				cursor_movement_cmd(2, 15);
				cout << "                                                       ";
				id->Legend_Armor_array[choose_pos - 3]->add_armor_level();
				for (int i = 0; i <= 4; i++) {
					cursor_movement_cmd(8, 3 + i);
					cout << id->Legend_Armor_array[i]->getName();
					cursor_movement_cmd(22, 3 + i);
					if (id->Legend_Armor_array[i]->get_armor_level() == 0) {
						cout << id->Legend_Armor_array[i]->getattackbonus();
					}
					else {
						cout << id->Legend_Armor_array[i]->getattackbonus() * id->Legend_Armor_array[i]->get_armor_level();
					}
					cursor_movement_cmd(32, 3 + i);
					if (id->Legend_Armor_array[i]->get_armor_level() >= 1) {
						cout << id->Legend_Armor_array[i]->get_armor_cost() * (id->Legend_Armor_array[i]->get_armor_level() + 1);
					}
					else {
						cout << id->Legend_Armor_array[i]->get_armor_cost();
					}
					cursor_movement_cmd(42, 3 + i);
					cout << id->Legend_Armor_array[i]->get_armor_level();
				}
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
		if (choose_pos > 7) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 7;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << ">>";
	}

	system("CLS");
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}
//=====================<武器商店>=======================
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
				((CFighter*)usr)->shop_captureItem(id->getCheck_num(weapon_list[choose_pos - 2] + id->food_array.size()+1));//撿到商品
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

//=====================<食物商店>=======================
void function_fshop() {
	system("cls");
	system("color 0F");
	cursor_movement_cmd(15, 0);
	cout << "   <食品商店>";
	cursor_movement_cmd(8, 2);
	cout << " 名稱      增血量      買價";
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;

	//((CFighter*)usr)->captureItem(id->getCheck_num(17));//撿到商品
	for (int i = 0; i < 15; i++) {
		cursor_movement_cmd(8, 3 + i);
		cout << id->food_array[i]->getName();
		cursor_movement_cmd(20, 3 + i);
		cout << id->food_array[i]->gethpbonus();
		cursor_movement_cmd(32, 3 + i);
		cout << id->food_array[i]->gethpbonus() * 2;
	}
	int choose_pos = 3;
	cursor_movement_cmd(5, 3);
	cout << ">>";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 13) {
			int compare_money = usr->getMoney();
			if (compare_money < id->food_array[choose_pos-3]->gethpbonus()) {
				cursor_movement_cmd(2, 19);
				cout << "                                       ";
				cursor_movement_cmd(2, 19);
				cout << "你沒有足夠的錢";
			}
			else {
				usr->subMoney(id->food_array[choose_pos - 3]->gethpbonus());
				cursor_movement_cmd(2, 20);
				cout << "                                       ";
				cursor_movement_cmd(2, 20);
				cout << "您剩下的金錢為 $" << usr->getMoney();
				cursor_movement_cmd(2, 21);
				cout << "                                       ";
				cursor_movement_cmd(2, 21);
				((CFighter*)usr)->shop_captureItem(id->getCheck_num(choose_pos-2));//撿到商品
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
		if (choose_pos > 17) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 17;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << ">>";
	}
	system("CLS");
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}
//=======================<釣魚>=============================
void function_fish() {
	ifstream fin_A1("fish.txt");
	string take_animation;
	int cnt = 1;
	while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_A1 >> take_animation;
		for (int y = 0; y < take_animation.length(); y++) {
			if (take_animation[y] == '@') {
				cursor_movement_cmd(60 + y, 8 + cnt);
				cout << " ";
			}
			else {
				cursor_movement_cmd(60 + y, 8 + cnt);
				cout << take_animation[y];
			}
		}
		cout << endl;
		if (cnt % 41 == 0) {
			cursor_movement_cmd(60, 9);
			cnt -= 41;
			//Sleep(40);
			//system("cls");
			//for(int yy=0;yy<)
		}
		cnt += 1;
	}
	for (int y = 0; y < 40; y++) {
		cursor_movement_cmd(60, 8 + y);
		cout << "                                                                                                                        ";
	}
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;
	cursor_movement_cmd(0, 18);
	((CFighter*)usr)->fish_captureItem(id->getCheck_num(rand() % 4+1));
	cursor_movement_cmd(0, -3);
}

//=====================<商城總攬>=======================
void function_all_shop() {
	system("cls");
	system("color 0F");
	cursor_movement_cmd(8, 2);
	cout << "  [商城總攬]";
	cursor_movement_cmd(8, 3);
	cout << "  <武器商店>";
	cursor_movement_cmd(8, 4);
	cout <<"  <裝備商店>";
	cursor_movement_cmd(8, 5);
	cout << "  <技能解鎖>";
	cursor_movement_cmd(8, 6);
	cout << "  <傳奇盔甲>";
	cursor_movement_cmd(8, 7);
	cout << "  <食品商店>";
	int choose_pos = 3;
	cursor_movement_cmd(5, 3);
	cout << "->";
	int key = 0;
	while (key != 27) {
		key = _getch();
		if (key == 13) {
			if (choose_pos == 3) {
				system("CLS");
				function_wshop();
				return;
			}
			else if (choose_pos == 4) {
				system("CLS");
				function_eshop();
				return;
			}
			else if (choose_pos == 5) {
				system("CLS");
				function_sshop();
				return;
			}
			else if (choose_pos == 6) {
				system("CLS");
				function_lshop();
				return;
			}
			else if (choose_pos == 7) {
				system("CLS");
				function_fshop();
				return;
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
		if (choose_pos > 7) {
			choose_pos = 3;
		}
		if (choose_pos < 3) {
			choose_pos = 7;
		}
		cursor_movement_cmd(5, choose_pos);
		cout << "->";
	}
	system("CLS");
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CFighter* set = (CFighter*)usr;
	CGlobalInfo::map_data->show_description(set->get_current_city());
}

void function_hack() {
	static bool hack_check = false;
	if (hack_check == false) {
		hack_check = true;
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		usr->out_hack_data();
		usr->set_all_thing("kerong", 9999, 999999, 9999, 9999, 9999, 9999, 9999, 9999, 9999, 9999);
	}
	else {
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		usr->read_hack_data();
		hack_check = false;
	}
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
void function_log_out() {
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;
	int get_save = usr->show_output_data_num();
	if (get_save == 1) {
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		assert(usr);
		string file_name = "save_bag1.txt";
		ofstream file_writer(file_name, ios_base::out);
		if (usr->isA() == efighter) {
			CFighter* f = (CFighter*)usr;
			int num = f->showAllBagItems();
			if (num > 0) {
				for (int y = num; y >=0; y--) {
					f->save_bag_Items(y,get_save);
				}
			}
			f->save_wear(get_save);
			/*
			int get_w_ID = f->show_wear_weapon_ID();
			int get_e_ID = f->show_wear_eauiment_ID();
			int cnt = 0;
			if (get_w_ID > 15 && get_w_ID <= 33) {
				cnt += 1;
				f->delSP(id->weapon_array[get_w_ID - 16]->getattackbonus());
				//cout << id->weapon_array[get_w_ID - 16]->getattackbonus()<<"@@@";
			}
			if (get_e_ID > 33) {
				cnt += 1;
				f->delMAXHP(id->equiment_array[get_e_ID - 33]->getattackbonus());
				cout << id->equiment_array[get_e_ID - 33]->getattackbonus();
			}
			if (cnt == 2) {
				f->delSP(50);
			}*/
		}
		ofstream fout_s1("skill_1.txt");
		ofstream fout_L1("legend_armor_1.txt");
		for (int y = 1; y <= 5; y++) {
			fout_s1 << y << "\t" << id->skill_array[y - 1]->getName() << "\t" << id->skill_array[y - 1]->getattackbonus() << "\t" << id->skill_array[y - 1]->get_skill_cost() << "\t" << id->skill_array[y - 1]->get_skill_level()<<endl;
			fout_L1 << y << "\t" << id->Legend_Armor_array[y - 1]->getName() << "\t" << id->Legend_Armor_array[y - 1]->getattackbonus() << "\t" << id->Legend_Armor_array[y - 1]->get_armor_cost() << "\t" << id->Legend_Armor_array[y - 1]->get_armor_level() << endl;
		}
	}
	else if (get_save == 2) {
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		assert(usr);
		string file_name = "save_bag2.txt";
		ofstream file_writer(file_name, ios_base::out);
		if (usr->isA() == efighter) {
			CFighter* f = (CFighter*)usr;
			int num = f->showAllBagItems();
			if (num > 0) {
				for (int y = num; y >= 0; y--) {
					f->save_bag_Items(y, get_save);
				}
			}
			f->save_wear(get_save);
		}
		ofstream fout_s2("skill_2.txt");
		ofstream fout_L2("legend_armor_2.txt");
		for (int y = 1; y <= 5; y++) {
			fout_s2 << y << "\t" << id->skill_array[y - 1]->getName() << "\t" << id->skill_array[y - 1]->getattackbonus() << "\t" << id->skill_array[y - 1]->get_skill_cost() << "\t" << id->skill_array[y - 1]->get_skill_level() << endl;
			fout_L2 << y << "\t" << id->Legend_Armor_array[y - 1]->getName() << "\t" << id->Legend_Armor_array[y - 1]->getattackbonus() << "\t" << id->Legend_Armor_array[y - 1]->get_armor_cost() << "\t" << id->Legend_Armor_array[y - 1]->get_armor_level() << endl;
		}
	}
	else if (get_save == 3) {
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		assert(usr);
		string file_name = "save_bag3.txt";
		ofstream file_writer(file_name, ios_base::out);
		
		if (usr->isA() == efighter) {
			CFighter* f = (CFighter*)usr;
			int num = f->showAllBagItems();
			if (num > 0) {
				for (int y = num; y >= 0; y--) {
					f->save_bag_Items(y, get_save);
				}
			}
			f->save_wear(get_save);
		}
		ofstream fout_s3("skill_3.txt");
		ofstream fout_L3("legend_armor_3.txt");
		for (int y = 1; y <= 5; y++) {
			fout_s3 << y << "\t" << id->skill_array[y - 1]->getName() << "\t" << id->skill_array[y - 1]->getattackbonus() << "\t" << id->skill_array[y - 1]->get_skill_cost() << "\t" << id->skill_array[y - 1]->get_skill_level() << endl;
			fout_L3 << y << "\t" << id->Legend_Armor_array[y - 1]->getName() << "\t" << id->Legend_Armor_array[y - 1]->getattackbonus() << "\t" << id->Legend_Armor_array[y - 1]->get_armor_cost() << "\t" << id->Legend_Armor_array[y - 1]->get_armor_level() << endl;
		}
	}
	usr->out_all_thing();
	cout << "您的存檔已完成";
}
//====================<登出>=========================
int function_exit(vector<string>& tokens) {
	function_log_out();
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;
	CFighter* f = (CFighter*)usr;
	int get_w_ID = f->show_wear_weapon_ID();
	int get_e_ID = f->show_wear_eauiment_ID();
	int cnt = 0;
	if (get_w_ID > 15 && get_w_ID <= 33) {
		cnt += 1;
		f->delSP(id->weapon_array[get_w_ID - 16]->getattackbonus());
	}
	if (get_e_ID > 33) {
		cnt += 1;
		f->delMAXHP(id->equiment_array[get_e_ID - 34]->getattackbonus());
		cout << id->equiment_array[get_e_ID - 34]->getattackbonus();
	}
	if (cnt == 2) {
		f->delSP(50);
	}
	usr->out_all_thing();
	return -1;
}
void function_skip_animation() {
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CItemData* id = CGlobalInfo::itm_data;
	CFighter* f = (CFighter*)usr;
	f->set_skip();
	bool take = f->get_skip();
	if (take) {
		cout << "<<跳過動畫>>" << endl;
	}
	else {
		cout << "<<開啟動畫>>" << endl;
	}
}

void function_christmas() {
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	CFighter* f = (CFighter*)usr;
	int get_now_degree = f->getDegree();
	time_t curtime;
	time(&curtime);
	tm* nowtime = localtime(&curtime);
	if(1 + nowtime->tm_mon==12 && nowtime->tm_mday>=20 && nowtime->tm_mday<= 30){
		usr->addHP(usr->getMAXHP());
		cout << "\t\t\\聖誕節快樂!/" << "獲取禮物->恢復滿您的血量" << endl;
		thread th_tree(sound_christmas);
		//PlaySound(TEXT("christmas.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		for (int x = 0; x < 55; x++) {
			ifstream fin_A1("tree.txt");
			string take_animation;
			int cnt = 1;
			while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
				fin_A1 >> take_animation;
				int get_rand_1 = rand() % 255 + 1;
				int get_rand_2 = rand() % 255 + 1;
				for (int y = 0; y < take_animation.length(); y++) {
					if (take_animation[y] == '@') {
						SetColor_cmd();
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << " ";
					}
					else if (take_animation[y] == 'J') {
						SetColor_cmd(get_rand_1);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == 'o') {
						SetColor_cmd(get_rand_2);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '9') {
						SetColor_cmd(205);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '9') {
						SetColor_cmd(205);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '\\' || take_animation[y] == '/') {
						SetColor_cmd(163);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '~') {
						SetColor_cmd(236);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '7') {
						SetColor_cmd(64);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '#') {
						SetColor_cmd(170);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else if (take_animation[y] == '-' || take_animation[y] == '|' || take_animation[y] == '&' || take_animation[y] == '^' || take_animation[y] == '(' || take_animation[y] == ')') {
						SetColor_cmd(252);
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
					else {
						SetColor_cmd();
						cursor_movement_cmd(60 + y, 8 + cnt);
						cout << take_animation[y];
					}
				}
				cout << endl;
				if (cnt % 34 == 0) {
					cursor_movement_cmd(60, 9);
					cnt -= 34;
					//Sleep(40);
					//system("cls");
					//for(int yy=0;yy<)
				}
				cnt += 1;
			}
			Sleep(100);
		}
		th_tree.join();
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		for (int y = 0; y < 40; y++) {
			cursor_movement_cmd(60, 8 + y);
			cout << "                                                                                                                        ";
		}
		cursor_movement_cmd(0, -3);
	}
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
	mappingfunc [string("christmas")] = function_christmas;             //彩蛋
	mappingfunc [string("skip")] = function_skip_animation;             //跳過動畫
	mappingfunc [string("puthouse")] = function_put_house;				//放置倉庫
	mappingfunc [string("checkhouse")] = function_check_house;			//檢測倉庫
	mappingfunc [string("move")] = function_move;						//舜移
	mappingfunc [string("wshop")] = function_wshop;						//武器
	mappingfunc [string("eshop")] = function_eshop;						//裝備
	mappingfunc [string("sshop")] = function_sshop;						//技能
	mappingfunc [string("lshop")] = function_lshop;						//職業限定裝備
	mappingfunc [string("fshop")] = function_fshop;						//食品商店
	mappingfunc [string("fish")] = function_fish;						//釣魚
	mappingfunc [string("shop")] = function_all_shop;				 	//商城總攬
	mappingfunc [string("log_out")] = function_log_out;					//登出
	mappingfunc [string("kerong")] = function_hack;					    //商城總攬
	//mappingfunc [string("putbag")] = function_put_bag;					//放置一樣物品
	//mappingfunc [string("getbag")] = function_get_bag;					//取走一樣物品
	mappingfunc [string("meet_monster")] = function_meet_monster;		//遇到自走怪
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

