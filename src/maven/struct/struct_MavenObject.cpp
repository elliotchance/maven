/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenObject.h"

using namespace std;

MavenObject::MavenObject() {
	variables = new MavenVariables();
	functions = new MavenFunctions();
	reset();
}

MavenObject::~MavenObject() {
	//if(variables)
	//	free(variables);
	//if(functions)
	//	free(functions);
}

void MavenObject::reset() {
	name = "";
	isAbstract = false;
	isFinal = false;
	line = 0;
	extends = "";
}
