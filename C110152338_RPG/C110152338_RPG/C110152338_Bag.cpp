#include <iostream>
#include "C110152338_Bag.h"
#include "C110152338_Item.h"

using namespace std;

CBagEntry::CBagEntry(CItem *in_item, int in_num){
	itm = in_item; 
	number = in_num;
}

CBag::CBag (){
	LIST_INIT(&listhead);	
}

CBag::~CBag (){
	CBagEntry* ne = listhead.lh_first;
	CBagEntry* tmp = NULL;
	while (ne){
		tmp = ne->next_link.le_next;
		LIST_REMOVE (ne, next_link);
		ne = tmp;
	}
}

void CBag::item_insert (CItem *in_item){
	CBagEntry* new_entry = new CBagEntry (in_item);
	LIST_INSERT_HEAD(&listhead, new_entry, next_link);
}

CBagEntry* CBag::item_lookup (int type, int id){
	CBagEntry* ne = listhead.lh_first;
	for (; ne; ne = ne->next_link.le_next){
		if (ne->itm->isA() == type && ne->itm->getID () == id)
			break;
	}
	return ne;
}

CBagEntry* CBag::item_lookup (int no){
	CBagEntry* ne = listhead.lh_first;
	int countnum = 1;
	for (; ne; ne = ne->next_link.le_next){
		if (no == countnum){						
			break;
		}
		countnum++;
	}
	return ne;
}

void CBag::item_delete (CBagEntry* be){
	LIST_REMOVE (be, next_link);
}

int CBag::showAllItems (){
	CBagEntry* ne = listhead.lh_first;
	CItem *tmp;
	int countnum = 0;
	if (ne)
		cout << "背包內容如下所示：" << endl;
	for (; ne; ne = ne->next_link.le_next){
		tmp = ne->itm;
		cout << ++countnum << ". " << tmp->getName () << ", 數量-> " << ne->number << endl;
	}	
	return countnum;
}

