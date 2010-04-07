/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool startsWith(string a, string b) {
	if(a.length() < b.length()) return false;
	return (a.substr(0, b.length()) == b);
}
