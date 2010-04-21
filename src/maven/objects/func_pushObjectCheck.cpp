/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void pushObjectCheck(MavenCompiler* c, string test, string action) {
	// see if it's already there
	for(int i = 0; i < c->objectCheck.size(); ++i)
		if(c->objectCheck[i].key == test) return;
	
	c->objectCheck.push_back(MavenPair(test, action));
}
