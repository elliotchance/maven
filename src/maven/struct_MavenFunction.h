/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_FUNCTION_H
#define _MAVEN_STRUCT_FUNCTION_H 1

#include "maven.h"
#include "struct_MavenVariables.h"

class MavenCompiler;

struct MavenFunction {
	string returnType;
	string name;
	MavenVariables args;
	string descArgs;
	int atLine;
	MavenDocTag doc;
	bool isPublic;
	bool isConstant;
	bool isStatic;
	bool isExternal;
	string alias;
	bool alias_system;
	bool isExported;
	bool isInherited;
	bool isOverride;
	
	MavenFunction();
	string getCPPLine(MavenCompiler* mc, string className, bool isVirtual = false);
	string getSignature();
	string getAnchorID();
	void print();
};

#endif
