/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_compilefile.h"
#include "compiler_strings.h"

void init(MavenCompiler* c) {
	// open the required file handles
	c->mapFileHandle.open((c->option_n + ".mmap").c_str());
	c->cppFileHandle.open((c->option_n + ".cpp").c_str());
	// bug #42: test for bad file handles

	string mavencoreh = combinePaths(c->binDirectory, c->iniFile.getKey("directories.src")) +
									 "mavencore/mavencore.h";
	writeCPPLine(c, string("#include \"") + mavencoreh + "\"");
	writeCPPLine(c, string("#include \"") +
				 combinePaths(c->currentDirectory, c->option_n, false) + ".mmap\"");
	writeCPPLine(c, string("namespace ") + MAVEN_BARE_NAMESPACE + " {\n");
}
