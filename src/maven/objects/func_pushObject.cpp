/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "strings.h"
#include "errors.h"
#include "objects.h"

bool pushObject(MavenCompiler* c, int namespaceID, MavenObject* obj) {
	// validate
	smartAssert(namespaceID >= 0);
	smartAssert(namespaceID < c->namespaces->length());
	smartAssert(obj != 0);
	
	// Because Object and String require each other, they were pushed manually when the compiler was
	// created, and hence when we come across these we have to assume the user is not doing something
	// naughty. This probably should be looked at some time in the future.
	if(c->currentNamespace == "maven")
		if(obj->name == "Object" || obj->name == "String") return true;
	
	int objectID = findObjectID(c, namespaceID, obj->name);
	if(objectID >= 0) {
		// bug #35: obj.line shows the new line not the original definition
		pushError(c, "Class %s already defined (previously defined at line %s)", obj->name,
				  intToString(obj->line));
		return false;
	}
	
	// push class
	c->namespaces->at(namespaceID).objects->push(obj);
	
	// push discovery, so the classes can be mapped back in the same order
	c->discovery.push_back(MavenObjectDiscovery(namespaceID,
												c->namespaces->at(namespaceID).objects->length() - 1));
										
	return true;
}
