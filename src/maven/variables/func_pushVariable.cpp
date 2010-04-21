/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"

void pushVariable(MavenCompiler* c, int namespaceID, int objectID, MavenVariable var) {
	// safety
	smartAssertMessage(namespaceID < c->namespaces->length(),
					   "namespaceID = %d, c->namespaces.length() = %d",
					   namespaceID, c->namespaces->length());
	smartAssertMessage(objectID < c->namespaces->at(namespaceID).objects->length(),
					   "objectID = %d, c->namespaces[namespaceID].objects.length() = %d",
					   objectID, c->namespaces->at(namespaceID).objects->length());
	
	// push variable
	c->namespaces->at(namespaceID).objects->at(objectID)->variables->push(var);
}
