/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

bool pushSelector(MavenCompiler* c, string name) {
	// make sure it doesn't already exist
	for(int i = 0; i < c->selectors.size(); ++i)
		if(c->selectors[i] == name) return false;
	
	c->selectors.push_back(name);
	return true;
}
