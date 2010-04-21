/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"

int findObjectID(MavenCompiler* c, int namespaceID, string objectName) {
	smartAssertMessage(namespaceID >= 0,
					   "namespaceID = %d", namespaceID);
	
	smartAssertMessage(namespaceID < c->namespaces->length(),
					   "namespaceID = %d, c->namespaces.length() = %d",
					   namespaceID, c->namespaces->length());
	
	for(int i = 0; i < c->namespaces->at(namespaceID).objects->length(); ++i)
		if(c->namespaces->at(namespaceID).objects->at(i)->name == objectName)
			return i;
	
	return -1;
}
