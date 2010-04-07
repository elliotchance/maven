/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void newLocalScope(MavenCompiler* c) {
	c->localScope.push_back(MavenVariables());
}
