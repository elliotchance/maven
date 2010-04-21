/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_ENUMITEM_H
#define _MAVEN_STRUCT_ENUMITEM_H 1

#include "maven.h"

struct MavenEnumItem {
	string name;
	int value;
	bool isDefault;
	
	MavenEnumItem();
};

#endif
