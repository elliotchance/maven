/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_find.h"

using namespace std;

MavenVariable::MavenVariable() {
	reset();
}

MavenVariable::MavenVariable(string _name, string _type) {
	MavenVariable();
	name = _name;
	type = _type;
}

string MavenVariable::getCPP(MavenCompiler* c) {
	string r = "";
	if(isStatic)
		r += "static ";
	r += findObjectPath(c, type) +  " " + name;
	return r;
}

void MavenVariable::reset() {
	name = "";
	type = "";
	defaultValue = "";
	atLine = 0;
	isStatic = false;
	mutability = MU_OK;
	isPublic = false;
	isInherited = false;
	isExternal = false;
}

string MavenVariable::getAnchorID() {
	return name;
}
