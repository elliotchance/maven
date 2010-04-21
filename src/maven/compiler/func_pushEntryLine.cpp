/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "objects.h"

void pushEntryLine(MavenCompiler* c, string line) {
	c->entryPoint.push(objectCheckCPP(c));
	c->entryPoint.push(line);
}
