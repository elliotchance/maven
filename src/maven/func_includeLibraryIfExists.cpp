/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "keywords.h"

bool includeLibraryIfExists(MavenCompiler* c, string import) {
	string look = combinePaths(c->currentDirectory, c->iniFile.getKey("directories.lib")) + import + ".o";
	if(fileExists(look))
		c->extraLibraries.push(look);
	return true;
}
