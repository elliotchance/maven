/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_find.h"

using namespace std;

MavenFunction::MavenFunction() {
	returnType = "";
	name = "";
	descArgs = "";
	atLine = 0;
	doc = "";
	isPublic = false;
	isStatic = false;
	isExternal = false;
	alias = "";
	alias_system = false;
	isExported = false;
	isInherited = false;
	isOverride = false;
}

string MavenFunction::getCPPLine(MavenCompiler* c, string className, bool isVirtual) {
	string r = " ";
	if(isVirtual) r += "virtual ";
	if(returnType != "<constructor>")
		r += findObjectPath(c, returnType, true) + " ";
	r += className + "::" + name + "(";
	
	// function arguments can't be static
	for(int i = 0; i < args.length(); ++i)
		args[i].isStatic = false;
		
	r += args.getCPP(c);
	r += ")";
	return r;
}

string MavenFunction::getSignature() {
	string s = "";
	for(int l = 0; l < args.length(); ++l) {
		if(l) s += ",";
		s += args[l].type;
	}
	return s;
}
