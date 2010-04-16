/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

using namespace std;

MavenObject::MavenObject() {
	cout << "alocating\n";
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
