/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void deleteLocalScope(MavenCompiler* c) {
	if(c->localScope.size() > 0)
		c->localScope.pop_back();
}
