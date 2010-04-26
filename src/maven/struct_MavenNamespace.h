/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_NAMESPACE_H
#define _MAVEN_STRUCT_NAMESPACE_H 1

#include "maven.h"
#include "struct_MavenDocTag.h"
#include "struct_MavenObjects.h"
#include "struct_MavenEnum.h"

struct MavenNamespace {
	string name;
	MavenDocTag doc;
	MavenObjects* objects;
	vector<MavenEnum> enums;
	
	MavenNamespace();
	~MavenNamespace();
	void sortObjects();
	void sortEnums();
	void swapEnum(int ID1, int ID2);
};

#endif
