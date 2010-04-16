/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

int findObjectID(MavenCompiler* c, int namespaceID, string objectName) {
	// HERE!1
	return -1;
	smartAssertMessage(namespaceID >= 0,
					   "namespaceID = %d", namespaceID);
	
	smartAssertMessage(namespaceID < c->namespaces.length(),
					   "namespaceID = %d, c->namespaces.length() = %d",
					   namespaceID, c->namespaces.length());
	
	for(int i = 0; i < c->namespaces[namespaceID].objects.length(); ++i)
		if(c->namespaces[namespaceID].objects[i].name == objectName)
			return i;
	return -1;
}
