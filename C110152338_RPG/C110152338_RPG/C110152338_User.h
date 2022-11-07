#ifndef USER_H
#define USER_H

#include <string>
#include "C110152338_LifeEntity.h"
using namespace std;

class CUser {		
public:	
	CUser ();	
	void set_user (CLifeEntity *in_usr);
	int goto_next_city (int next);
	int get_current_city ();
	CLifeEntity* get_user (){return user;};
private:		
	CLifeEntity *user;
};

#endif