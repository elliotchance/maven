/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string padIntToString(int value, int size) {
	string r = intToString(value);
	int pad = size - r.length();
	for(int i = 0; i < pad; ++i)
		r = "0" + r;
	return r;
}
