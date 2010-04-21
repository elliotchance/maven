/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"

int countStaticVariables(MavenCompiler* c, int namespaceID, int objectID) {
	int r = 0;
	for(int k = 0; k < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++k)
		if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).isStatic)
			++r;
	return r;
}
