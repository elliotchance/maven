/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

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
				// FIXME: needs to be fixed.
				c2 += '\x00';
			}
			++i;
		} else c2 += c[i];
	}
	return c2;
}
