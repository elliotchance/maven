/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_variables.h"

void pushEntryLine(MavenCompiler* c, string line) {
	c->entryPoint.push(objectCheckCPP(c));
	c->entryPoint.push(line);
}
