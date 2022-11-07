#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class CCmdParser {		
public:	
	CCmdParser ();	
	void splitstring(const string& s, vector<string>& v, const string& c);
	int query ();
private:		
	map<string,  void (*)> mappingfunc;
};

#endif