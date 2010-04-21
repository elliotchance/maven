/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

bool pushSelector(MavenCompiler* c, string name) {
	// make sure it doesn't already exist
	for(int i = 0; i < c->selectors.size(); ++i)
		if(c->selectors[i] == name) return false;
	
	c->selectors.push_back(name);
	return true;
}
