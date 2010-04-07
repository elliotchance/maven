/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

int charToInt(string c) {
	// first convert all the escape characters to singles
	string c2 = escapeString(c);
	
	// now convert base 256 to base 10
	int r = 0;
	for(int i = 0; i < c2.length(); ++i)
		r += (int) pow(256, i) * c2[c2.length() - 1 - i];
	return r;
}
