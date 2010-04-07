/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void pushObjectCheck(MavenCompiler* c, string test, string action) {
	// see if it's already there
	for(int i = 0; i < c->objectCheck.size(); ++i)
		if(c->objectCheck[i].key == test) return;
	
	c->objectCheck.push_back(MavenPair(test, action));
}
