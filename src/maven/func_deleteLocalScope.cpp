/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void deleteLocalScope(MavenCompiler* c) {
	if(c->localScope.size() > 0)
		c->localScope.pop_back();
}
