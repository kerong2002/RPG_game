#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class CCmdParser {		
public:	
	CCmdParser ();	
	void cursor_movement_cmd(int x, int y);
	void splitstring(const string& s, vector<string>& v, const string& c);
	int query (string thing);
private:		
	map<string,  void (*)> mappingfunc;
};

#endif