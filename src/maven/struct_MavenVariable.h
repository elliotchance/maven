/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_VARIABLE_H
#define _MAVEN_STRUCT_VARIABLE_H 1

#include "maven.h"
#include "enum_MavenMutability.h"
#include "struct_MavenDocTag.h"

class MavenCompiler;

class MavenVariable {
public:
	string name;
	string type;
	string defaultValue;
	int atLine;
	bool isStatic;
	MavenMutability mutability;
	bool isPublic;
	MavenDocTag doc;
	bool isInherited;
	bool isExternal;
	
public:
	MavenVariable();
	MavenVariable(string _name, string _type);
	string getCPP(MavenCompiler* mc);
	void reset();
	string getAnchorID();
};

#endif
