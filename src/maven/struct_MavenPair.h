/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_PAIR_H
#define _MAVEN_STRUCT_PAIR_H 1

#include "maven.h"

struct MavenPair {
	string key;
	string value;
	
	MavenPair(string k, string v);
};

#endif
