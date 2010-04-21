/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

bool isAssignOperator(string type) {
	if(type == "") return false;
	
	// all operators that change the value of the left hand side
	if(type == "=" || type == "+=" || type == "-=" || type == "*=" || type == "/=" || type == "%=")
		return true;
	
	// not assigning
	return false;
}
