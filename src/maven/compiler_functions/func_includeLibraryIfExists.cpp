/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "files.h"

bool includeLibraryIfExists(MavenCompiler* c, string import) {
	string look = combinePaths(c->binDirectory, c->iniFile.getKey("directories.lib")) + import + ".o";
	if(fileExists(look))
		c->extraLibraries.push(look);
	return true;
}
