/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isString(string test) {
	if(test.length() > 1 && test[0] == '"' && test[test.length() - 1] == '"')
		return true;
	return false;
}
