#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
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

#define MAXBARLEN 40
int map_y_size = 25;			//地圖y大小
int map_x_size = 30;			//地圖x大小
int pos_x = 10;					//玩家座標x
int pos_y = 8;					//玩家座標y

//==================<建立顏色>==========================
void SetColor(int color = 7) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
//=====================================================
//==================<光標移動>=========================
void cursor_movement(int x, int y) {
	COORD coord;
	coord.X = (x + cursor_x_offset) * 2;
	coord.Y = (y + cursor_y_offset);
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}
//=====================================================
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
//======================================================
//==================<繪製地圖>==========================
void printmap() {
	system("color 0F");
	cursor_movement(0, 15);				//移動位置
	SetColor(15);						//設定顏色
	for (int y = 0; y < map_y_size; y++) {
		for (int x = 0; x < map_x_size; x++) {
			cursor_movement(x, y);
			if (y == 0 || y == map_y_size - 1 || x == 0 || x == map_x_size - 1) {
				cout << "■";
			}
			else if (x == map_x_size / 2 && y == map_y_size / 2) {
				cout << "商";
			}
			else {
				cout << "  ";
			}
		}
	}
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
//===================<主要程式>==========================
int main() {
	opening_animation();			//開始RPG動畫
	printmap();
	
	char key;
	string move_map;
	while (true) {
		
		key = _getch();
		if (key == ' ') {
			cursor_movement(map_x_size + 5, 14);
			system("color 0F");
			cout << "請輸入移動位置";
			cursor_movement(map_x_size + 5, 15);
			cin >> move_map;
			if (move_map == "A_city") {
				cout << "";
			}
			cursor_movement(map_x_size + 5, 14);
			cout << "                      ";
			cursor_movement(map_x_size + 5, 15);
			for (int y = 0; y < move_map.length(); y++) {
				cout << " ";
			}
			//printmap();
		}
		if ((key == 'W' || key == 'w')) {
			if (pos_y > 1) {
				cursor_movement(pos_x, pos_y);
				SetColor(15); printf("  ");
				pos_y--;
			}
		}
		if ((key == 'S' || key == 's')) {
			if (pos_y < map_y_size - 2) {
				cursor_movement(pos_x, pos_y);
				SetColor(15); printf("  ");
				pos_y++;
			}
		}
		if ((key == 'A' || key == 'a')) {
			if (pos_x > 1) {
				cursor_movement(pos_x, pos_y);
				SetColor(15); printf("  ");
				pos_x--;
			}
		}
		if ((key == 'D' || key == 'd')) {
			if (pos_x == map_x_size - 2  && pos_y == map_y_size - 5) {
				break;
			}
			if (pos_x < map_x_size - 2) {
				cursor_movement(pos_x, pos_y);
				SetColor(15); printf("  ");
				pos_x++;
			}
		}
		SetColor(15);
		cursor_movement(map_x_size - 1, map_y_size - 5);
		printf("門");
		cursor_movement(pos_x, pos_y);
		SetColor(240);
		printf("我");
		Sleep(100);
	}

	system("CLS");
	system("color 0F");											//黑底白字
	//SetColor(15);
	Initialize();												//初始化設定
	CFighter* fighter = new CFighter();
	CGlobalInfo::user->set_user((CLifeEntity*)fighter);
	int cur_city = CGlobalInfo::user->get_current_city();

	CGlobalInfo::map_data->show_description(cur_city);
	while (CGlobalInfo::parser->query() >= 0) {
		//CGlobalInfo::map_data->show_description (cur_city);
	//	cin >> cur_city;
	}
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

