/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

bool isErrors(MavenCompiler* c) {
	// count errors
	int errorcount = 0;
	for(int i = 0; i < c->errors.length(); ++i)
		if(c->errors[i].level == MAVEN_ERROR) ++errorcount;
	return errorcount > 0;
}
