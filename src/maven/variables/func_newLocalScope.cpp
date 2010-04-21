/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void newLocalScope(MavenCompiler* c) {
	c->localScope.push_back(MavenVariables());
}
