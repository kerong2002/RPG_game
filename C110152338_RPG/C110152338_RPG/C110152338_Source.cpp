#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
//#include "C110152338_Profession.h"
#include "C110152338_Fighter.h"
#include "C110152338_Monster.h"
#include "C110152338_food.h"
#include "C110152338_ItemData.h"
#include "C110152338_MapData.h"
#include "C110152338_GlobalInfo.h"
#include "C110152338_CmdParser.h"
#include "C110152338_User.h"
#include "C110152338_MonsterData.h"
#include <limits>
#pragma comment(lib, "Winmm.lib")

#define cursor_x_offset 6		//光標X座標的偏移
#define cursor_y_offset 3		//光標X座標的偏移
using namespace std;

#define Profession_size 5		//職業數量
#define MAXBARLEN 40
#define map_y_size 15			//地圖y大小
#define map_x_size 20			//地圖x大小
int pos_x = map_x_size / 2;		//玩家座標x
int pos_y = map_y_size / 2;		//玩家座標y
char all_map[15][20];
string my_profession = "你";
//==================<職業>=====================
static struct profession {
	string name;			//名稱
	int HP;					//血量
	int Damage;				//傷害
	int Lucky;				//幸運值
	string mark;			//標示
}
profession[Profession_size + 1] = {
	{},
	{"射手"	 , 100, 200,  10, "射"},
	{"法師"	 , 200, 100,   3, "法"},
	{"召喚師", 100, 130,   5, "召"},
	{"戰士"  , 500,  40,  25, "戰"},
	{"輔助"  ,  20,   1, 100, "輔"}
};

//=================<重製位置>==========================
void reset_pos() {
	pos_x = map_x_size / 2;		//玩家座標x
	pos_y = map_y_size / 2;		//玩家座標y
}

//==================<建立顏色>==========================
void SetColor(int color = 7) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

//==================<光標移動>=========================
void cursor_movement(int x, int y) {
	COORD coord;
	coord.X = (x + cursor_x_offset) * 2;
	coord.Y = (y + cursor_y_offset);
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
//==================<光標移動>=========================
void cursor_movement_animation(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
//================<清屏>=============================
void clear_screen() {
	for (int y = 0; y < 50; y++) {
		cursor_movement(-cursor_x_offset, map_y_size / 2 + 10 + y);
		for (int x = 0; x < 100; x++) {
			cout << " ";
		}
	}
	cursor_movement(-cursor_x_offset, -cursor_y_offset);
}
//==================<讀地圖圖形>=======================
void ReadFile_line(const string file_name) {
	fstream fs(file_name, ios::in);
	if (!fs.is_open())
		throw runtime_error("Reading error.");

	for (string str; getline(fs, str);) {
		cout << str << endl;
	} fs.seekg(0, fs.beg);
	fs.close();
}

// 按照空格或跳行讀取
void ReadFile_space(const string file_name) {
	fstream fs(file_name, ios::in);
	if (!fs.is_open())
		throw runtime_error("Reading error.");
	for (string str; fs >> str;) {
		cout << str << endl;
	} fs.seekg(0, ios::beg);
	fs.close();
}

// 一次性讀取整個文件
void ReadFile_all(const string file_name) {
	fstream fs(file_name, ios::in);
	if (!fs.is_open())
		throw runtime_error("Reading error.");
	string str(
		(istreambuf_iterator<char>(fs)),
		istreambuf_iterator<char>()
	);
	//    cout<<str.length()<<endl;
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x <= 20; x++) {
			if (x == 20) {
				continue;
			}
			else {
				all_map[y][x] = str[y * 21 + x];
			}
		}
	}
	//    cout << str << endl;
	fs.close();
}

// 按照所需長度讀取到C字串char*
void ReadFile_buffer(const string file_name) {
	fstream fs(file_name, ios::in);
	if (!fs.is_open())
		throw runtime_error("Reading error.");
	char buffer[256]{};
	size_t readSize = sizeof(buffer);
	fs.getline(buffer, readSize);
	cout << buffer << endl;
	fs.close();
}

// 獲取檔案長度
size_t FileSize(fstream& fs) {
	size_t curr = fs.tellg();
	fs.seekg(0, ios::end);
	size_t len = fs.tellg();
	fs.seekg(curr);
	return len;
};
//=======================================================

//==================<開場動畫>==========================
void opening_animation() {
	int gametitle[7][22] =
	{
		{-1,1, 8,10,12,-1,-1,-1,19,26,28,30,-1,-1,-1,-1,39,40,43,-1,-1,-1},
		{-1,2,-1,-1,-1,15,-1,-1,20,-1,-1,-1,32,-1,-1,37,-1,-1,-1,46,-1,-1},
		{-1,3,-1,-1,-1,16,-1,-1,21,-1,-1,-1,33,-1,34,-1,-1,-1,-1,-1,-1,-1},
		{-1,4, 9,11,13,-1,-1,-1,22,27,29,31,-1,-1,35,-1,-1,-1,44,47,49,-1},
		{-1,5,-1,-1,14,-1,-1,-1,23,-1,-1,-1,-1,-1,36,-1,-1,-1,-1,-1,50,-1},
		{-1,6,-1,-1,-1,17,-1,-1,24,-1,-1,-1,-1,-1,-1,38,-1,-1,-1,48,51,-1},
		{-1,7,-1,-1,-1,-1,18,-1,25,-1,-1,-1,-1,-1,-1,-1,40,42,45,-1,52,-1}
	};
	for (int k = 1; k <= 52; k++) {
		for (int y = 0; y < 7; y++) {
			for (int x = 0; x < 22; x++) {
				if (gametitle[y][x] == k) {
					cursor_movement(x + 10, y - cursor_y_offset + 1);							//放置游標位置
					SetColor(70);									//設定放置位置顏色
					cout << "■";										//放置方塊
					Sleep(10);										//延遲
				}
			}
		}
	}
	SetColor(15);													//把顏色設為初始值
	Sleep(1000);													//延遲
	cout << endl;
	//system("PAUSE");												//停止
}
//==================<繪製地圖>==========================
void printmap() {
	system("color 0F");
	cursor_movement(0, 15);				//移動位置
	SetColor(15);						//設定顏色
	for (int y = 0; y < map_y_size; y++) {
		for (int x = 0; x < map_x_size; x++) {
			cursor_movement(x, y);
			if (all_map[y][x] == '=') {
				cout << "■";
			}
			/*else if (x == map_x_size / 2 && y == map_y_size / 2) {
				cout << "商";
			}*/
			else {
				cout << "  ";
			}
		}
	}
	cout << endl;
}
//=====================================================
void askforbaglist(CFighter* f) {
	int num = f->showAllBagItems();
	if (num == 0)
		return;
	cout << f->getname() << " 需要使用背包物品嗎?\n0 --> No, Others --> Yes, 使用之物品編號: ";
	int selection;
	cin >> selection;
	if (selection) {
		if (!f->useBagItems(selection))
			cout << "無此選項存在" << endl;
	}
}

CMonster* MonsterSelection(CFighter* f) {
	int selection;
	askforbaglist(f);
	cout << "請選擇怪物等級: 1. 訊咖 2. 強咖 3. 猛咖 4. 找死咖 " << endl;
	cin >> selection;
	int m_MaxHP, m_MaxSP, m_MaxRough;
	switch (selection) {
	case 1:
		m_MaxHP = f->getMAXHP() / 2;
		m_MaxSP = f->getMAXSP() / 2;
		m_MaxRough = (int)(f->getMAXHP() * 0.1);
		break;
	case 2:
		m_MaxHP = f->getMAXHP();
		m_MaxSP = f->getMAXSP();
		m_MaxRough = (int)(f->getMAXHP() * 0.2);
		break;
	case 3:
		m_MaxHP = (int)(f->getMAXHP() * 1.5);
		m_MaxSP = (int)(f->getMAXSP() * 1.2);
		m_MaxRough = (int)(f->getMAXHP() * 0.2);
		break;
	default:
		m_MaxHP = f->getMAXHP() * 2;
		m_MaxSP = f->getMAXSP() * 2;
		m_MaxRough = (int)(f->getMAXHP() * 0.5);
	}
	CMonster* m = new CMonster(m_MaxHP, m_MaxSP, m_MaxRough);
	system("CLS");
	return m;
}

void bloodbarshow(int maxhp, int hp) {
	cout << "HP     |";
	float hpslotlen = (float)maxhp / MAXBARLEN;
	int numhp = (int)ceil(hp / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << "#";
	}
	numhp = (int)floor((maxhp - hp) / hpslotlen);
	for (int i = 0; i < numhp; i++) {
		cout << " ";
	}
	cout << "|" << endl;
}

void fightstatus(CMonster* m, CFighter* f) {
	cout << endl << f->getname() << endl;
	bloodbarshow(f->getMAXHP(), f->getHP());
	cout << m->getname() << endl;
	bloodbarshow(m->getMAXHP(), m->getHP());
	cout << endl;
}

void fightshow(CMonster* m, CFighter* f) {
	fightstatus(m, f);
	cout << "您剩下 " << f->getHP() << "滴血" << endl;
	Sleep(1000);
}

void startfight(CMonster* m, CFighter* f) {
	int f_damage = 0, s_damage = 0;
	CLifeEntity* first, * second;
	int whofirst;
	while (!m->isdead() && !f->isdead()) {

		whofirst = rand() % 2;
		if (whofirst == 0) {
			cout << "怪物搶得先機，先出手傷人" << endl;
			first = (CLifeEntity*)m;
			second = (CLifeEntity*)f;
		}
		else {
			cout << "你搶得先機，先出手傷人" << endl;
			first = (CLifeEntity*)f;
			second = (CLifeEntity*)m;
		}

		s_damage = first->attack(second);
		if (second->isdead()) {
			whofirst == 0 ? fightshow((CMonster*)first, (CFighter*)second) : fightshow((CMonster*)second, (CFighter*)first);
			break;
		}

		f_damage = second->attack(first);
		whofirst == 0 ? fightshow((CMonster*)first, (CFighter*)second) : fightshow((CMonster*)second, (CFighter*)first);
	}
	if (m->isdead() && !f->isdead()) {
		cout << "怪物已死，從怪物身上掉下寶物" << endl;
		CItemData* id = CGlobalInfo::itm_data;
		f->captureItem(id->getRand());
		//f->showAllBagItems ();
	}
}


CItemData* CGlobalInfo::itm_data = new CItemData;
CMapData* CGlobalInfo::map_data = new CMapData;
CCmdParser* CGlobalInfo::parser = new CCmdParser;
CUser* CGlobalInfo::user = new CUser;
CMonsterData* CGlobalInfo::monster_data = new CMonsterData;

int CMonster::counter_for_monster_id = 0;

void Initialize(int pos) {
	srand((unsigned int)time(NULL));
	CGlobalInfo::itm_data->Initialize(pos);
	CGlobalInfo::map_data->generate_monsters();
}
//==================<選擇職業>===========================
int choose_profession(string& token) {
	system("CLS");
	system("color 0F");
	cursor_movement(0, 0);
	cout << "請選擇您的職業：";
	cursor_movement(2, 1);
	cout << "職業   血量    傷害    幸運    圖標";
	for (int i = 1; i <= Profession_size; i++) {
		cursor_movement(2, 1 + i);
		cout << profession[i].name;
		cursor_movement(6, 1 + i);
		cout << profession[i].HP;
		cursor_movement(10, 1 + i);
		cout << profession[i].Damage;
		cursor_movement(14, 1 + i);
		cout << profession[i].Lucky;
		cursor_movement(18, 1 + i);
		cout << profession[i].mark;
	}
	int choose_pos = 1;
	cursor_movement(0, 2);
	cout << ">>";
	int key = 0;
	while (key != 13) {
		key = _getch();
		if (key == 'w' || key == 'W') {
			cursor_movement(0, 1 + choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement(0, 1 + choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > Profession_size) {
			choose_pos = 1;
		}
		if (choose_pos < 1) {
			choose_pos = Profession_size;
		}
		cursor_movement(0, 1 + choose_pos);
		cout << ">>";
	}
	token.assign(profession[choose_pos].mark);
	return choose_pos;
}
//================<視窗大小設定>========================
void modeset(int w, int h) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	SMALL_RECT rc = { 1,1, w, h };
	SetConsoleWindowInfo(hOut, true, &rc);
	system("cls");
	return;
}
//===================<登入系統>===========================
string user_set = "";				//帳號
string password_set = "";			//密碼
string forgot_hint = "";
int logint_cnt = 0;
void opening_password() {
	string data[3];
	system("CLS");
	system("color 0F");
	int choose_pos = 1;
	cursor_movement(2, 2);
	cout << "  user   : ";
	cursor_movement(2, 3);
	cout << "password : ";
	cursor_movement(2, 4);
	cout << "<忘記密碼> ";
	cursor_movement(2, 5);
	cout << "<確定登入> ";
	cursor_movement(0, 2);
	cout << ">>";
	int key = 0;
	while (true) {
		key = _getch();
		cursor_movement(2, 2);
		cout << "  user   : ";
		cursor_movement(2, 3);
		cout << "password : ";
		cursor_movement(2, 4);
		cout << "<忘記密碼> ";
		cursor_movement(2, 5);
		cout << "<確定登入> ";
		if (key == 13) {
			cursor_movement(8, 1 + choose_pos);
			if (choose_pos == 2) {
				key = 0;
				while (key != 13) {
					key = _getch();
					if (key == 13) {
						break;
					}
					data[choose_pos - 1] += key;
					cout << "#";
				}
			}
			else if (choose_pos == 3) {
				cout << "請輸入密語->";
				cin >> data[2];
				if (data[2].compare(forgot_hint) == 0) {
					cursor_movement(4, 10);
					cout << "請輸入您想修改的密碼:";
					ofstream out_f("password.txt");
					string get_F_password, get_S_password;
					while (true) {
						cursor_movement(4, 11);
						cout << "                                                   ";
						cursor_movement(4, 12);
						cout << "                                                   ";
						cursor_movement(4, 11);
						cin >> get_F_password;
						cursor_movement(4, 12);
						cin >> get_S_password;
						if (get_F_password == get_S_password) {
							break;
						}
						else {
							cursor_movement(4, 13);
							cout << "兩次輸入的密碼不相符，請重新再試一次";
						}
					}
					out_f << get_F_password;
					cursor_movement(4, 10);
					cout << "                                         ";
				}
				else {
					cursor_movement(8, 2 + 2);
					cout << "                                        ";
				}
				cursor_movement(8, 2 + 2);
				cout << "                                        ";
				for (int y = 0; y < 5; y++) {
					cursor_movement(4, 10 + y);
					cout << "                                         ";
				}
			}
			else if (choose_pos == 4) {
				if (data[0].compare(user_set) == 0 && data[1].compare(password_set) == 0) {
					logint_cnt = 0;
					break;
				}
				else {
					logint_cnt += 1;
					data[1] = "";
					for (int y = 0; y < 3; y++) {
						cursor_movement(8, 2 + y);
						cout << "                                        ";
					}
					cursor_movement(4, 8);
					cout << "您輸入錯誤" << logint_cnt << "次";
					if (logint_cnt >= 3) {
						cursor_movement(4, 9);
						cout << "請問是否要嘗試忘記密碼?";
					}
				}
			}
			else {
				cin >> data[choose_pos - 1];
			}
		}
		if (key == 'w' || key == 'W') {
			cursor_movement(0, 1 + choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement(0, 1 + choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 4) {
			choose_pos = 1;
		}
		if (choose_pos < 1) {
			choose_pos = 4;
		}
		cursor_movement(0, 1 + choose_pos);
		cout << ">>";
	}
	system("CLS");
}
//===================<超出地圖邊界>=======================
int monster_x = rand() % (map_x_size - 2) + 1;
int monster_y = rand() % (map_y_size - 2) + 1;
void out_of_map() {
	cursor_movement(pos_x, pos_y);
	cout << "  ";
	//reset_pos();
	printmap();
	monster_x = rand() % (map_x_size - 2) + 1;
	monster_y = rand() % (map_y_size - 2) + 1;
	while (monster_x == pos_x && monster_y == pos_y) {
		monster_x = rand() % (map_x_size - 2) + 1;
		monster_y = rand() % (map_y_size - 2) + 1;
	}
	cursor_movement(monster_x, monster_y);
	cout << "敵";
}
//===================<怪物移動>========================
void monster_move(int pos_x, int pos_y) {
	if (pos_x == monster_x && pos_y == monster_y) {
		CGlobalInfo::parser->query("meet_monster");
		monster_x = rand() % (map_x_size - 2) + 1;
		monster_y = rand() % (map_y_size - 2) + 1;
		while (monster_x == pos_x && monster_y == pos_y) {
			monster_x = rand() % (map_x_size - 2) + 1;
			monster_y = rand() % (map_y_size - 2) + 1;
		}
		cursor_movement(monster_x, monster_y);
		cout << "敵";
		return;
	}
	SetColor(15);
	int m_list[8][2] =
	{
		{ 0, 1},
		{ 1, 0},
		{-1, 0},
		{ 0,-1},
		{ 0, 0},
		{ 0, 0},
		{ 0, 0}
	};
	int new_pos = rand() % 8;
	while (true) {
		if ((monster_x + m_list[new_pos][0]) > 0 && (monster_x + m_list[new_pos][0]) < map_x_size - 2 && (monster_y + m_list[new_pos][1]) > 0 && (monster_y + m_list[new_pos][1]) < map_y_size - 2) {
			break;
		}
		new_pos = rand() % 7 + 1;
	}
	cursor_movement(monster_x, monster_y);
	cout << "  ";
	monster_x += m_list[new_pos][0];
	monster_y += m_list[new_pos][1];
	cursor_movement(monster_x, monster_y);
	cout << "敵";

}
void read_login() {
	ifstream fin_u("user.txt");
	ifstream fin_p("password.txt");
	ifstream fin_f("forgot_hint.txt");
	while (!fin_u.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_u >> user_set;
	}
	while (!fin_p.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_p >> password_set;
	}
	while (!fin_f.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
		fin_f >> forgot_hint;
	}
	//cout << forgot_hint;
}
/*
void ow2_animation() {
	cursor_movement_animation(5, 5);
	for (int x = 0; x < 1; x++) {
		ifstream fin_A1("ow2.txt");
		string take_animation;
		int cnt = 1;
		while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
			fin_A1 >> take_animation;
			for (int y = 0; y < take_animation.length(); y++) {
				if (take_animation[y] == '@') {
					SetColor(1);
					cursor_movement_animation(y + 5, 7 + cnt);
					cout << " ";
				}
				else {
					SetColor(177);
					cursor_movement_animation(y + 5, 7 + cnt);
					cout << take_animation[y];
				}
			}
			cout << endl;
			cursor_movement_animation(0, 0);
			if (cnt % 45 == 0) {
				cnt -= 45;
				cursor_movement_animation(5, 7);
				//Sleep(40);
				//system("cls");
				//for(int yy=0;yy<)
			}
			cnt += 1;
		}
	}
	system("pause");
	system("color 0F");
	system("cls");
}*/
void attack_among() {
	cursor_movement_animation(5, 5);
	PlaySound(TEXT("among_start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	for (int x = 0; x < 4; x++) {
		ifstream fin_A1("among_go.txt");
		string take_animation;
		int cnt = 1;
		while (!fin_A1.eof()) { //只要還沒讀到完，條件成立就繼續一直讀
			if (_kbhit()) {
				break;
			}
			fin_A1 >> take_animation;
			for (int y = 0; y < take_animation.length(); y++) {
				if (take_animation[y] == '@' || take_animation[y] == '=') {
					SetColor(1);
					cursor_movement_animation(y + 5, 7 + cnt);
					cout << " ";
				}
				else {
					SetColor(177);
					cursor_movement_animation(y + 5, 7 + cnt);
					cout << take_animation[y];
				}
			}
			cout << endl;
			cursor_movement_animation(0, 0);
			if (cnt % 43 == 0) {
				cnt -= 43;
				cursor_movement_animation(5, 7);
				//Sleep(40);
				//system("cls");
				//for(int yy=0;yy<)
			}
			cnt += 1;
		}
	}
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("pause");
	system("color 0F");
	system("cls");
}
int choose_save_data() {
	system("CLS");
	system("color 0F");
	string job1 = "";
	string job2 = "";
	string job3 = "";
	ifstream input_f1("play1.txt");
	input_f1 >> job1;
	ifstream input_f2("play2.txt");
	input_f2 >> job2;
	ifstream input_f3("play3.txt");
	input_f3 >> job3;
	int choose_pos = 1;
	cursor_movement(2, 2);
	cout << "存檔編號    <職業> ";
	cursor_movement(2, 3);
	cout << "   1        " << job1;
	cursor_movement(2, 4);
	cout << "   2        " << job2;
	cursor_movement(2, 5);
	cout << "   3        " << job3;
	cursor_movement(2, 6);
	cout << " <清空存檔> ";
	cursor_movement(0, 3);
	cout << ">>";
	int key = 0;
	while (true) {
		key = _getch();
		if (key == 13) {
			if (choose_pos == 1) {
				if (job1 == "") {
					return -1;
				}
				else {
					if (job1 == "射手") {
						my_profession = "射";
					}
					else if (job1 == "法師") {
						my_profession = "法";
					}
					else if (job1 == "召喚師") {
						my_profession = "召";
					}
					else if (job1 == "戰士") {
						my_profession = "戰";
					}
					else if (job1 == "輔助") {
						my_profession = "輔";
					}
					return 1;
				}
			}
			else if (choose_pos == 2) {
				if (job2 == "") {
					return -2;
				}
				else {
					if (job2 == "射手") {
						my_profession = "射";
					}
					else if (job2 == "法師") {
						my_profession = "法";
					}
					else if (job2 == "召喚師") {
						my_profession = "召";
					}
					else if (job2 == "戰士") {
						my_profession = "戰";
					}
					else if (job2 == "輔助") {
						my_profession = "輔";
					}
					return 2;
				}
			}
			else if (choose_pos == 3) {
				if (job3 == "") {
					return -3;
				}
				else {
					if (job3 == "射手") {
						my_profession = "射";
					}
					else if (job3 == "法師") {
						my_profession = "法";
					}
					else if (job3 == "召喚師") {
						my_profession = "召";
					}
					else if (job3 == "戰士") {
						my_profession = "戰";
					}
					else if (job3 == "輔助") {
						my_profession = "輔";
					}
					return 3;
				}
			}
			else if (choose_pos == 4) {
				cursor_movement(4, 9);
				cout << "請輸入想清除的存檔編號：";
				int choose_clear;
				cin >> choose_clear;
				if (choose_clear == 1) {
					string file_name = "play1.txt";
					ofstream file_writer(file_name, ios_base::out);
					string file_save = "save_bag1.txt";
					ofstream file_writer1(file_save, ios_base::out);
					job1 = "";
					cursor_movement(7, 2 + choose_clear);
					cout << "                                      ";
				}
				else if (choose_clear == 2) {
					string file_name = "play2.txt";
					ofstream file_writer(file_name, ios_base::out);
					string file_save = "save_bag2.txt";
					ofstream file_writer1(file_save, ios_base::out);
					job2 = "";
					cursor_movement(7, 2 + choose_clear);
					cout << "                                      ";
				}
				else if (choose_clear == 3) {
					string file_name = "play3.txt";
					ofstream file_writer(file_name, ios_base::out);
					string file_save = "save_bag3.txt";
					ofstream file_writer1(file_save, ios_base::out);
					job3 = "";
					cursor_movement(7, 2 + choose_clear);
					cout << "                                      ";
				}
				cursor_movement(4, 9);
				cout << "                                      ";
			}
		}
		if (key == 'w' || key == 'W') {
			cursor_movement(0, 2 + choose_pos);
			cout << "  ";
			choose_pos--;
		}
		if (key == 's' || key == 'S') {
			cursor_movement(0, 2 + choose_pos);
			cout << "  ";
			choose_pos++;
		}
		if (choose_pos > 4) {
			choose_pos = 1;
		}
		if (choose_pos < 1) {
			choose_pos = 4;
		}
		cursor_movement(0, 2 + choose_pos);
		cout << ">>";
	}
	system("CLS");
	return -9;
}
void max_window() {
	HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);   
	COORD NewSize = GetLargestConsoleWindowSize(HOUT);

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(HOUT, TRUE, &DisplayArea);   
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);   
}
//===================<主要程式>==========================
int main() {
	max_window();
	read_login();
	//modeset(150, 50);					//視窗大小設定
	opening_password();					//登入系統
	opening_animation();				//開始RPG動畫
	attack_among();
	//ow2_animation();
	//attack_among();
	int data_num = choose_save_data();
	//system("pause");
	int get_job_num = 0;
	if (data_num < 0) {
		get_job_num = choose_profession(my_profession);	//選擇職業
	}
	else {
		get_job_num = data_num;
	}
	string filename = "graph_map/map_center.txt";
	ReadFile_all(filename);

	string active;
	cursor_movement(-cursor_x_offset, map_y_size / 2 + 10);
	Initialize(data_num);												//初始化設定
	//建置玩家
	CFighter* fighter = new CFighter(get_job_num, profession[get_job_num].HP, profession[get_job_num].Damage, profession[get_job_num].Lucky, profession[get_job_num].name, 1);

	//system("CLS");
	printmap();
	CGlobalInfo::user->set_user((CLifeEntity*)fighter);
	int cur_city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(cur_city);
	if (data_num > 0) {
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		usr->set_output_data_num(data_num);
		usr->file_read_data();
		CItemData* id = CGlobalInfo::itm_data;
		if (data_num == 1) {
			int cnt = 0;
			ifstream fin_h("save_bag1.txt");
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
			for (int y = 0; y < cnt; y++) {
				for (int x = 0; x < amout[y]; x++) {
					((CFighter*)usr)->save_captureItem(id->getCheck_num(ID[y]));
				}
			}
			//system("pasue");
			ID.clear();
			amout.clear();
		}
		else if (data_num == 2) {
			int cnt = 0;
			ifstream fin_h("save_bag2.txt");
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
			for (int y = 0; y < cnt; y++) {
				for (int x = 0; x < amout[y]; x++) {
					((CFighter*)usr)->save_captureItem(id->getCheck_num(ID[y]));
				}
			}
			ID.clear();
			amout.clear();
		}
		else if (data_num == 3) {
			int cnt = 0;
			ifstream fin_h("save_bag3.txt");
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
			for (int y = 0; y < cnt; y++) {
				for (int x = 0; x < amout[y]; x++) {
					((CFighter*)usr)->save_captureItem(id->getCheck_num(ID[y]));
				}
			}
			ID.clear();
			amout.clear();
		}
	}
	else {
		CLifeEntity* usr = CGlobalInfo::user->get_user();
		usr->set_output_data_num(-data_num);
	}
	/*while (CGlobalInfo::parser->query() >= 0) {
		CGlobalInfo::map_data->show_description(cur_city);
		//	cin >> cur_city;
	}*/
	cursor_movement(pos_x, pos_y);
	SetColor(240);
	cout << my_profession;
	int key = 0;
	while (true) {
		key = _getch();
		monster_move(pos_x, pos_y);
		fighter->show_fighter_detail(fighter);
		system("color 0F");
		if (key == ' ') {
			clear_screen();
			cursor_movement(map_x_size + 5, map_y_size / 2 + 2);
			cout << "請輸入指令";
			cursor_movement(map_x_size + 5, map_y_size / 2 + 3);
			cin >> active;
			cursor_movement(-cursor_x_offset, map_y_size / 2 + 10);
			CGlobalInfo::parser->query(active);
			if (active == "exit") {
				break;
			}
			cursor_movement(map_x_size + 5, map_y_size / 2 + 2);
			cout << "                      ";
			cursor_movement(map_x_size + 5, map_y_size / 2 + 3);
			for (int y = 0; y < active.length(); y++) {
				cout << "        ";
			}
			fighter->show_fighter_detail(fighter);
			printmap();
			//CGlobalInfo::map_data->show_description(cur_city);
		}
		if ((key == 'W' || key == 'w')) {
			if (pos_x == map_x_size / 2 && pos_y == 1) {
				int cur_city = CGlobalInfo::user->get_current_city();
				CGlobalInfo::parser->query("north");

				//SetColor(15);
				if (cur_city > 3) {
					pos_y = map_y_size - 2;
				}
				out_of_map();
				fighter->show_fighter_detail(fighter);
				//CGlobalInfo::map_data->show_description(cur_city);
			}
			else if (pos_y > 1) {
				cursor_movement(pos_x, pos_y);
				SetColor(15);
				cout << "  ";
				pos_y--;
			}
		}
		if ((key == 'S' || key == 's')) {
			if (pos_x == map_x_size / 2 && pos_y == map_y_size - 2) {
				int cur_city = CGlobalInfo::user->get_current_city();
				CGlobalInfo::parser->query("south");

				//SetColor(15);
				if (cur_city < 7) {
					pos_y = 1;
				}
				out_of_map();
				fighter->show_fighter_detail(fighter);
			}
			else if (pos_y < map_y_size - 2) {
				cursor_movement(pos_x, pos_y);
				SetColor(15);
				cout << "  ";
				pos_y++;
			}
		}
		if ((key == 'A' || key == 'a')) {
			if (pos_x == 1 && pos_y == map_y_size / 2) {

				int cur_city = CGlobalInfo::user->get_current_city();
				//SetColor(15);
				if (cur_city != 1 && cur_city != 4 && cur_city != 7) {
					pos_x = map_x_size - 2;
				}
				CGlobalInfo::parser->query("west");
				out_of_map();
				fighter->show_fighter_detail(fighter);
				//CGlobalInfo::map_data->show_description(cur_city);
			}
			else if (pos_x > 1) {
				cursor_movement(pos_x, pos_y);
				SetColor(15);
				cout << "  ";
				pos_x--;
			}
		}
		if ((key == 'D' || key == 'd')) {
			if (pos_x == map_x_size - 2 && pos_y == map_y_size / 2) {
				int cur_city = CGlobalInfo::user->get_current_city();
				CGlobalInfo::parser->query("east");

				//SetColor(15);
				if (cur_city % 3 != 0) {
					pos_x = 1;
				}
				out_of_map();
				fighter->show_fighter_detail(fighter);
				//CGlobalInfo::map_data->show_description(cur_city);
				//break;
			}
			else if (pos_x < map_x_size - 2) {
				cursor_movement(pos_x, pos_y);
				SetColor(15);
				cout << "  ";
				pos_x++;
			}
		}
		SetColor(15);
		cursor_movement(map_x_size - 1, map_y_size / 2);		//東
		cout << "門";
		cursor_movement(0, map_y_size / 2);						//西
		cout << "門";
		cursor_movement(map_x_size / 2, map_y_size - 1);		//南
		cout << "門";
		cursor_movement(map_x_size / 2, 0);						//北
		cout << "門";
		cursor_movement(pos_x, pos_y);
		SetColor(240);
		cout << my_profession;
		Sleep(100);
	}


	system("CLS");
	system("color 0F");											//黑底白字
	//SetColor(15);
	cout << "遊戲結束" << endl;
	/*while (CGlobalInfo::parser->query() >= 0) {
		CGlobalInfo::map_data->show_description(cur_city);
		//	cin >> cur_city;
	}*/
#if 0
	CFighter fighter;
	while (!fighter.isdead()) {
		CMonster* m = MonsterSelection(&fighter);
		if (m) {
			fightstatus(m, &fighter);
			cout << endl << endl << "戰鬥開始" << endl << endl;
			startfight(m, &fighter);
			delete m;
}
		else
			cout << "No monster generated" << endl;
	}
	cout << "Game Over!!!" << endl;
#endif
	system("pause");
	return 0;
}

