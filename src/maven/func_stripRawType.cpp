/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

string stripRawType(string type) {
	string rawtype = "";
	for(int i = 0; i < type.length(); ++i) {
		if(type[i] == '[') break;
		rawtype += type[i];
	}
	return rawtype;
}
