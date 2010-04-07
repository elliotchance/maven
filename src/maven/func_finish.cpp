/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void finish(MavenCompiler* c) {
	// close file handles
	c->mapFileHandle.close();
	c->cppFileHandle.close();
}
