/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

int findVariableID(MavenCompiler* c, int namespaceID, int objectID, string variable) {
	if(namespaceID < 0 || objectID < 0) return -1;
	
	for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].variables.length(); ++i)
		if(c->namespaces[namespaceID].objects[objectID].variables[i].name == variable)
			return i;
	
	// can't find it
	return -1;
}
