/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isOperatorPart(string type) {
	if(type == "") return false;
	
	// rather than list all of the operators in every combination
	// we will asume anythign thats not part of an entity name is an operator
	// this will also help when custom operator overloading comes along.
	if(isalnum(type[0]) || type[0] == '_' || type[0] == ' ')
		return false;
	
	// the object operator is not seen as an offical operator becuase it cant be overloaded
	// and its part of bare numbers and some entities
	if(type[0] == '.')
		return false;
	if(type[0] == ',')
		return false;
	
	// brackets are not consider to be operators and have to be tested for separatly
	// depending on the situation
	if(type[0] == '(' || type[0] == ')')
		return false;
	
	// must be an operator...
	return true;
}
