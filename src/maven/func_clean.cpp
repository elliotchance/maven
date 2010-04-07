/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void clean(MavenCompiler* c) {
	unlink((c->option_n + ".o").c_str());
	unlink((c->option_n + ".cpp").c_str());
	unlink((c->option_n + ".mmap").c_str());
}
