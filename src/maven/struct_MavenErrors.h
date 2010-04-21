/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_ERRORS_H
#define _MAVEN_STRUCT_ERRORS_H 1

#include "maven.h"
#include "struct_MavenError.h"

class MavenErrors {
private:
	vector<MavenError> errors;
	
public:
	MavenErrors();
	int length();
	MavenError& operator[](int element);
	void push(MavenError error);
	void clear();
};

#endif
