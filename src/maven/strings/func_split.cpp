/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"

StringList split(char on, string line) {
	StringList r;
	string token = "";
	for(int i = 0; i < line.length(); ++i) {
		if(line[i] == on) {
			r.push(token);
			token = "";
		} else token += line[i];
	}
	r.push(token);
	return r;
}

StringList split(string delimiters, string str) {
	StringList r;
	
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);
	
    while(string::npos != pos || string::npos != lastPos) {
        r.push(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
	
	return r;
}
