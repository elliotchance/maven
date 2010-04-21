/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void clean(MavenCompiler* c) {
	unlink((c->option_n + ".o").c_str());
	unlink((c->option_n + ".cpp").c_str());
	unlink((c->option_n + ".mmap").c_str());
}
