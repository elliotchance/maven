/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

using namespace std;

MavenObject::MavenObject() {
	reset();
}

void MavenObject::reset() {
	name = "";
	isAbstract = false;
	isFinal = false;
	line = 0;
	doc = "";
	//MavenVariables variables;
	//MavenFunctions functions;
	extends = "";
}
