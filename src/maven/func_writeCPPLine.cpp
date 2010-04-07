/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void writeCPPLine(MavenCompiler* c, string line) {
	c->cppFileHandle.write(line.c_str(), line.length());
	c->cppFileHandle.write("\n", 1);
}
