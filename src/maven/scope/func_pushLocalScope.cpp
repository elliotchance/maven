/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void pushLocalScope(MavenCompiler* c, MavenVariable var) {
	// safety (this should never occur)
	if(c->localScope.size() == 0) return;
	
	c->localScope[c->localScope.size() - 1].push(var);
}
