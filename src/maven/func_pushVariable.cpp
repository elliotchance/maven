/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void pushVariable(MavenCompiler* c, int namespaceID, int objectID, MavenVariable var) {
	// safety
	if(namespaceID > c->namespaces.length()) return;
	if(objectID > c->namespaces[namespaceID].objects.length()) return;
	
	// push variable
	c->namespaces[namespaceID].objects[objectID].variables.push(var);
}
