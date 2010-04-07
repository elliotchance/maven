/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

int findObjectID(MavenCompiler* c, int namespaceID, string objectName) {
	if(namespaceID < 0) return -1;
	for(int i = 0; i < c->namespaces[namespaceID].objects.length(); ++i)
		if(c->namespaces[namespaceID].objects[i].name == objectName)
			return i;
	return -1;
}
