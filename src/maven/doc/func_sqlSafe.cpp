/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string sqlSafe(string str) {
	string r = "";
	for(int i = 0; i < str.length(); ++i) {
		if(str[i] == '\\') r += "\\\\";
		else if(str[i] == '\'') r += "''";
		else if(str[i] == '\n') r += "\\n";
		else if(str[i] == '\t') r += "\\t";
		else r += str[i];
	}
	return string("'") + r + "'";
}

string sqlSafe(bool b) {
	if(b) return "1";
	return "0";
}
