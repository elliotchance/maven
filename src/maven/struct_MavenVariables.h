/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_VARIABLES_H
#define _MAVEN_STRUCT_VARIABLES_H 1

#include "maven.h"
#include "struct_MavenVariable.h"

class MavenCompiler;

struct MavenVariables {
	vector<MavenVariable> vars;
	
	MavenVariables();
	
	void push(MavenVariable var);
	int length();
	MavenVariable& operator[](int element);
	MavenVariable& at(int element);
	string getCPP(MavenCompiler* mc);
};

#endif
