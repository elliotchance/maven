/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

bool isComparisonOperator(string type) {
	if(type == "") return false;
	
	// comparison operators
	if(type == "<" || type == "<=" || type == ">" || type == ">=" || type == "==" || type == "!=")
		return true;
	
	// more comparison operators
	if(type == "&&" || type == "||")
		return true;
	
	// not comparing
	return false;
}
