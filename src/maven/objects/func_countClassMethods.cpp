/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"

int countClassMethods(MavenCompiler* c, int namespaceID, int objectID) {
	int r = 0;
	for(int k = 0; k < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++k)
		if(!c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).isExported)
			++r;
	return r;
}
