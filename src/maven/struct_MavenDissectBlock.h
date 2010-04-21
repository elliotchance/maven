/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_DISSECTBLOCK_H
#define _MAVEN_STRUCT_DISSECTBLOCK_H 1

#include "maven.h"
#include "struct_StringList.h"
#include "enum_MavenMutability.h"

class MavenDissectBlock {
public:
	string forceCast;
	string unary, postunary;
	string original, processed;
	StringList types;
	MavenMutability mutability;
	
public:
	MavenDissectBlock();
	void reset();
	void trim();
};

#endif
