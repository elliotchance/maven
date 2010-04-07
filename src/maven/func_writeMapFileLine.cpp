/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void writeMapFileLine(MavenCompiler* c, string line) {
	c->mapFileHandle.write(line.c_str(), line.length());
	c->mapFileHandle.write("\n", 1);
}
