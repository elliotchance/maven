/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_ENUM_H
#define _MAVEN_STRUCT_ENUM_H 1

#include "maven.h"
#include "struct_MavenEnumItem.h"

struct MavenEnum {
	string name;
	vector<MavenEnumItem> items;
	
	int getDefaultValue();
};

#endif
