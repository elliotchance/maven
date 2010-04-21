/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_STRINGLIST_H
#define _MAVEN_STRUCT_STRINGLIST_H 1

#include "maven.h"

class StringList {
private:
	vector<string> list;
	
public:
	StringList();
	void push(string item);
	int length();
	string& operator [](int element);
	StringList operator =(string str);
	string join(string glue);
	string join(string glue, int length);
	string join(string glue, int start, int end);
	string pop();
	void clear();
	StringList setTypes(string str);
};

#endif
