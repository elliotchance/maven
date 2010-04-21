/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "strings.h"

string padIntToString(int value, int size) {
	string r = intToString(value);
	int pad = size - r.length();
	for(int i = 0; i < pad; ++i)
		r = "0" + r;
	return r;
}
