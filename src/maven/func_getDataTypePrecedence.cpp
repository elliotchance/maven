/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

int getDataTypePrecedence(string name) {
	if(name == "quad") return 8;
	if(name == "double") return 7;
	if(name == "float") return 6;
	if(name == "long") return 5;
	if(name == "int") return 4;
	if(name == "short") return 3;
	if(name == "char") return 2;
	if(name == "byte") return 1;
	return 0;
}
