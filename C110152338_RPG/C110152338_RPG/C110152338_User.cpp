#include <iostream>
#include "C110152338_LifeEntity.h"
#include "C110152338_User.h"
#include "C110152338_def.h"
#include "C110152338_Fighter.h"

CUser::CUser (){
	user = NULL;
};	

void CUser::set_user (CLifeEntity *in_usr){
	user = in_usr;
}

int CUser::goto_next_city (int next){
	if (user->isA () == efighter){
		return ((CFighter *) user)->goto_next_city (next);
	}
	cout << "不是一般戰士" << endl;
	return -1;
}

int CUser::get_current_city (){
	if (user->isA () == efighter){
		return ((CFighter *) user)->get_current_city ();
	}
}