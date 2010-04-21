/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_NAMESPACES_H
#define _MAVEN_STRUCT_NAMESPACES_H 1

#include "maven.h"
#include "struct_MavenNamespace.h"

struct MavenNamespaces {
	vector<MavenNamespace> namespaces;
	
	MavenNamespaces();
	
	int length();
	MavenNamespace& operator [](int element);
	MavenNamespace& at(int element);
	void push(MavenNamespace* ns);
};

#endif
