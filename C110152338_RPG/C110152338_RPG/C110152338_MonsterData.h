
#ifndef MONSTERDATA_H
#define MONSTERDATA_H

#include <string>
#include <vector>

using namespace std;

class CMonsterType {
	friend class CMonsterData;
	friend class CMonster;
public:	
	CMonsterType (int, string, string, int, int, int);	
private:
	int id;
	string name;
	string prefix_eng_name;
	int max_hp;
	int max_sp;
	int max_rough;
};

class CMonsterData {
	
public:	
	CMonsterData ();
	~CMonsterData ();	
	int rand_get_monster_id ();
	CMonsterType *get_monstertype_by_id (int);
	
private:
	vector<CMonsterType *> monsterdata;	
};

#endif