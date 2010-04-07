/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isUnaryOperator(string type) {
	if(type == "") return false;
	
	// auto increment and decrement
	if(type == "++" || type == "--")
		return true;
	
	// positive and negative
	if(type == "+" || type == "-")
		return true;
	
	// bytewise and bitwise inverse
	if(type == "!" || type == "~")
		return true;
	
	// not a valid unary operator
	return false;
}
