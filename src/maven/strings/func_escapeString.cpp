/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

#include <sstream>

int hexToInt(string hexString) {
	unsigned int x;   
	stringstream ss(stringstream::in | stringstream::out);
	ss << std::hex << hexString;
	ss >> x;
	return x;
}

string escapeString(string c) {
	string c2 = "";
	for(int i = 0; i < c.length(); ++i) {
		if(c[i] == '\\') {
			if(c[i + 1] == 'a') c2 += '\a';
			else if(c[i + 1] == 'b') c2 += '\b';
			else if(c[i + 1] == 'f') c2 += '\f';
			else if(c[i + 1] == 'n') c2 += '\n';
			else if(c[i + 1] == 'r') c2 += '\r';
			else if(c[i + 1] == 't') c2 += '\t';
			else if(c[i + 1] == '\\') c2 += '\\';
			else if(c[i + 1] == '\'') c2 += '\'';
			else if(c[i + 1] == '"') c2 += '"';
			else if(c[i + 1] == 'x') {
				c2 += (char) hexToInt(c.substr(i + 2, 2));
				i += 2;
			}
			++i;
		} else c2 += c[i];
	}
	return c2;
}
