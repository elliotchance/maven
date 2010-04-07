/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

int countClassMethods(MavenCompiler* c, int namespaceID, int objectID) {
	int r = 0;
	for(int k = 0; k < c->namespaces[namespaceID].objects[objectID].functions.length(); ++k)
		if(!c->namespaces[namespaceID].objects[objectID].functions[k].isExported)
			++r;
	return r;
}
