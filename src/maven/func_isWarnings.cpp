/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool isWarnings(MavenCompiler* c) {
	// count warnings
	int warningcount = 0;
	for(int i = 0; i < c->errors.length(); ++i)
		if(c->errors[i].level == MAVEN_WARNING) ++warningcount;
	return warningcount;
}
