/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_ERROR_H
#define _MAVEN_STRUCT_ERROR_H 1

#include "maven.h"

struct MavenError {
	string file;
	int line;
	int level;
	string message;
	string arg1, arg2;
	
	MavenError();
};

#endif
