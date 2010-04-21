/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "operators.h"

bool isOperator(string type) {
	if(type == "") return false;
	
	// no need to double up
	if(isUnaryOperator(type)) return true;
	if(isAssignOperator(type)) return true;
	if(isComparisonOperator(type)) return true;
	if(isBitwiseOperator(type)) return true;
	
	// valid maven operators
	// bug #56: add all the operators here and the other place
	if(type == "+" || type == "-" || type == "*" || type == "/" || type == "%")
		return true;
	
	// not a valid unary operator
	return false;
}
