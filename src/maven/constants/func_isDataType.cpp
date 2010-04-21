/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

bool isDataType(string type) {
	if(type == "boolean") return true;
	if(type == "byte") return true;
	if(type == "char") return true;
	if(type == "int") return true;
	if(type == "long") return true;
	if(type == "float") return true;
	if(type == "double") return true;
	if(type == "quad") return true;
	if(type == "short") return true;
	if(type == "void") return true;
	
	return false;
}
