/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

bool isBitwiseOperator(string type) {
	if(type == "") return false;
	
	// bitwise operators
	if(type == "&" || type == "|" || type == "^" || type == "&=" || type == "|=" || type == "^=")
		return true;
	
	// bitwise shifting operators
	if(type == "<<" || type == ">>" || type == "<<=" || type == ">>=")
		return true;
	
	// not comparing
	return false;
}
