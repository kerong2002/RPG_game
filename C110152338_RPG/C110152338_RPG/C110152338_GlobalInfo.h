
#ifndef GLOBALINFO_H
#define GLOBALINFO_H


class CItemData;
class CMapData;
class CCmdParser;
class CUser;
class CMonsterData;

class CGlobalInfo {
public:
	static CItemData *itm_data;	
	static CMapData *map_data;	
	static CCmdParser *parser;
	static CUser *user;
	static CMonsterData *monster_data;
};

#endif