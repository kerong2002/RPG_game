#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
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

#define cursor_x_offset 6		//光標X座標的偏移
#define cursor_y_offset 3		//光標X座標的偏移
using namespace std;

#define Profession_size 8		//職業數量
#define MAXBARLEN 40
#define map_y_size 15			//地圖y大小
#define map_x_size 20			//地圖x大小
int pos_x = map_x_size / 2;		//玩家座標x
int pos_y = map_y_size / 2;		//玩家座標y
char all_map[15][20];
//==================<職業>=====================
static struct profession {
	string name;			//名稱
	int HP;					//血量
	int Damage;				//傷害
	int Lucky;				//幸運值
	string mark;			//標示
}
profession[Profession_size+1] = {
	{},
	{"射手"	 , 150, 200,   5, "射"},
	{"法師"	 , 200, 100,  20, "法"},
	{"召喚師", 100, 130,  15, "召"},
	{"戰士"  , 300,  60,  25, "戰"},
	{"劍士"  ,  50, 300,   1, "劍"},
	{"坦克"  , 800,   5,  30, "坦"},
	{"忍者"  , 100, 100,  10, "忍"},
	{"輔助"  ,  20,  20, 100, "輔"}
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
					cursor_movement(x, y);							//放置游標位置
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
	system("CLS");													//清除
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

void Initialize() {
	srand((unsigned int)time(NULL));
	CGlobalInfo::itm_data->Initialize();
	CGlobalInfo::map_data->generate_monsters();
}
//==================<選擇職業>===========================
int choose_profession(string & token) {
	system("CLS");
	system("color 0F");
	cursor_movement(0, 0);
	printf("請選擇您的職業：");
	cursor_movement(2, 1);
	printf("職業   血量    傷害    幸運    圖標");
	for (int i = 1; i <= Profession_size; i++){
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
	printf(">>");
	int key = 0;
	while (key != 13){
		key = _getch();
		if (key == 'w' || key == 'W'){
			cursor_movement(0, 1 + choose_pos);
			printf("  ");
			choose_pos--;
		}
		if (key == 's' || key == 'S'){
			cursor_movement(0, 1 + choose_pos);
			printf("  ");
			choose_pos++;
		}
		if (choose_pos > Profession_size) {
			choose_pos = 1;
		}
		if (choose_pos < 1) {
			choose_pos = Profession_size;
		}
		cursor_movement(0, 1 + choose_pos);
		printf(">>");
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
void opening_password() {
	cursor_movement(0, 0);
	cout << "user : ";
	cursor_movement(0, 1);
	cout << "password : ";
	char key = 0;
	while (true) {
		string user;
		string password;
		cursor_movement(4, 0);
		cin >> user;
		cursor_movement(6, 1);
		while (key != 13) {
			key = _getch();
			if (key == 13) {
				break;
			}
			password += key;
			cout << "#";
		}
		if (user.compare("kerong")==0 && password.compare("abc1234")==0) {
			break;
		}
		else {
			system("CLS");
			cursor_movement(0, 0);
			cout << "user : ";
			cursor_movement(0, 1);
			cout << "password : ";
			key = 0;
		}
	}
}
//===================<主要程式>==========================
int main() {
	//modeset(150, 50);					//視窗大小設定
	string my_profession = "你";
	//opening_password();				//登入系統
	//opening_animation();				//開始RPG動畫

	int get_job_num = choose_profession(my_profession);	//選擇職業
	string filename = "graph_map/map_center.txt";
	ReadFile_all(filename);
	
	string active;
	cursor_movement(-cursor_x_offset, map_y_size / 2 + 10);
	//建置玩家
	CFighter* fighter = new CFighter(get_job_num, profession[get_job_num].HP, profession[get_job_num].Damage, profession[get_job_num].Lucky, profession[get_job_num].name, 1);
	Initialize();												//初始化設定
	//system("CLS");
	printmap();
	CGlobalInfo::user->set_user((CLifeEntity*)fighter);
	int cur_city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(cur_city);
	/*while (CGlobalInfo::parser->query() >= 0) {
		CGlobalInfo::map_data->show_description(cur_city);
		//	cin >> cur_city;
	}*/
	char key;
	while (true) {
		key = _getch();
		fighter->show_fighter_detail(fighter);
		system("color 0F");
		if (key == ' ') {
			clear_screen();
			cursor_movement(map_x_size + 5, map_y_size / 2);
			cout << "請輸入指令";
			cursor_movement(map_x_size + 5, map_y_size / 2 + 1);
			cin >> active;
			cursor_movement(-cursor_x_offset, map_y_size / 2 + 10);
			CGlobalInfo::parser->query(active);
			cursor_movement(map_x_size + 5, map_y_size / 2);
			cout << "                      ";
			cursor_movement(map_x_size + 5, map_y_size / 2 + 1);
			for (int y = 0; y <active.length(); y++) {
				cout << "        ";
			}
			fighter->show_fighter_detail(fighter);
			printmap();
			//CGlobalInfo::map_data->show_description(cur_city);
		}
		if ((key == 'W' || key == 'w')) {
			if (pos_x == map_x_size / 2 && pos_y == 1) {
				CGlobalInfo::parser->query("north");
				//SetColor(15);
				cursor_movement(pos_x, pos_y);
				cout << "  ";
				reset_pos();
				printmap();
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
				CGlobalInfo::parser->query("south");
				//SetColor(15);
				cursor_movement(pos_x, pos_y);
				cout << "  ";
				reset_pos();
				printmap();
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
				CGlobalInfo::parser->query("west");
				//SetColor(15);
				cursor_movement(pos_x, pos_y);
				cout << "  ";
				reset_pos();
				printmap();
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
				CGlobalInfo::parser->query("east");
				//SetColor(15);
				cursor_movement(pos_x, pos_y);
				cout << "  ";
				reset_pos();
				printmap();
				fighter->show_fighter_detail(fighter);
				//CGlobalInfo::map_data->show_description(cur_city);
				//break;
			}
			else if(pos_x < map_x_size - 2) {
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
	cout << "out";
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

