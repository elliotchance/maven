/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

int countStaticVariables(MavenCompiler* c, int namespaceID, int objectID) {
	int r = 0;
	for(int k = 0; k < c->namespaces[namespaceID].objects[objectID].variables.length(); ++k)
		if(c->namespaces[namespaceID].objects[objectID].variables[k].isStatic)
			++r;
	return r;
}
