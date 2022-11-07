
#ifndef BAG_H
#define BAG_H

#include <iostream>
#include "C110152338_bsd-list.h"
class CItem;

class CBagEntry {
	friend class CBag;
	friend class CFighter;
public:
	CBagEntry (CItem *in_item = NULL, int in_num = 1);
	void addNum (int adds = 1){number += adds;};
	void deleteNum (int dels = 1){number -= dels;};
	int getNum (){return number;};
private:
	LIST_ENTRY(CBagEntry) next_link;
	CItem *itm;
	int number;
};

LIST_HEAD(bag_itemlist, CBagEntry);

class CBag {
public:
	CBag ();
	~CBag ();
	void item_insert (CItem *);
	CBagEntry* item_lookup (int type, int id);
	CBagEntry* item_lookup (int no);
	void item_delete (CBagEntry*);
	int showAllItems ();	
private:
	bag_itemlist listhead;
};

#endif