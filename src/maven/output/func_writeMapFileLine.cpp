/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void writeMapFileLine(MavenCompiler* c, string line) {
	c->mapFileHandle.write(line.c_str(), line.length());
	c->mapFileHandle.write("\n", 1);
}
