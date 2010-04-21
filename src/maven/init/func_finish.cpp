/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void finish(MavenCompiler* c) {
	// close file handles
	c->mapFileHandle.close();
	c->cppFileHandle.close();
}
