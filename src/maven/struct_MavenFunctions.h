/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_FUNCTIONS_H
#define _MAVEN_STRUCT_FUNCTIONS_H 1

#include "maven.h"
#include "struct_MavenFunction.h"

struct MavenFunctions {
	vector<MavenFunction> funcs;
	
	MavenFunctions();
	
	void push(MavenFunction func);
	int length();
	MavenFunction& operator[](int element);
	MavenFunction& at(int element);
};

#endif
