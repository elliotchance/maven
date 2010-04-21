/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

int findNamespaceID(MavenCompiler* c, string namespaceName) {
	for(int i = 0; i < c->namespaces->length(); ++i)
		if(c->namespaces->at(i).name == namespaceName)
			return i;
	return -1;
}
