/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isNumber(string test) {
	// without this a single character like 'e' would be approved as a number
	if(test.length() == 1 && isalpha(test[0])) return false;
	
	// hexadecimal
	// !C002
	if(test.length() > 2 && test.substr(0, 2) == "0x" &&
	   strspn(test.c_str(), "+-0123456789xabcdefABCDEF") == test.length())
		return true;
	
	return (strspn(test.c_str(), "+-0123456789.eEfFdDlLbBsScCiI") == test.length() &&
			((test[0] >= '0' && test[0] <= '9') || test[0] == '-' || test[0] == '+'));
}
