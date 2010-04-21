/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_OBJECT_H
#define _MAVEN_STRUCT_OBJECT_H 1

#include "maven.h"
#include "struct_MavenFunctions.h"
#include "struct_MavenVariables.h"
#include "struct_MavenDocTag.h"

struct MavenObject {
	string name;
	bool isAbstract;
	bool isFinal;
	int line;
	MavenDocTag doc;
	MavenVariables* variables;
	MavenFunctions* functions;
	string extends;
	
	MavenObject();
	~MavenObject();
	void reset();
};

#endif
