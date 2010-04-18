/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_find.h"
#include "compiler_strings.h"

using namespace std;

MavenFunction::MavenFunction() {
	returnType = "";
	name = "";
	descArgs = "";
	atLine = 0;
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

string MavenFunction::getAnchorID() {
	string s = name + "(";
	for(int l = 0; l < args.length(); ++l) {
		if(l) s += ",";
		s += args[l].type;
	}
	return s + ")";
}

void MavenFunction::print() {
	cout << "returnType: " << returnType << endl;
	cout << "name: " << name << endl;
	cout << "descArgs: " << descArgs << endl;
	cout << "atLine: " << atLine << endl;
	cout << "isPublic: " << boolOnOff(isPublic) << endl;
	cout << "isStatic: " << boolOnOff(isStatic) << endl;
	cout << "isExternal: " << boolOnOff(isExternal) << endl;
	cout << "alias: " << alias << endl;
	cout << "alias_system: " << boolOnOff(alias_system) << endl;
	cout << "isExported: " << boolOnOff(isExported) << endl;
	cout << "isInherited: " << boolOnOff(isInherited) << endl;
	cout << "isOverride: " << boolOnOff(isOverride) << endl;
}
