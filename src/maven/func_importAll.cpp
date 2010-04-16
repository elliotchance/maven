/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_compilefile.h"
#include "keywords.h"

bool importAll(MavenCompiler* c, string import, bool compiling) {
	StringList parts = split('.', import);
	
	// bug #32: use readDirectory()
	struct dirent *ep;
	DIR* dp = opendir((combinePaths(c->binDirectory,
									c->iniFile.getKey("directories.import")) +
									parts[0]).c_str());
	if(dp != NULL) {
		while(ep = readdir(dp)) {
			if(ep->d_name[0] == '.') continue;
			string filepath = combinePaths(c->binDirectory,
										   c->iniFile.getKey("directories.import")) +
										   parts[0] + "/" + ep->d_name;
			if(alreadyImported(c, filepath))
				continue;
			
			// we have to take 1 off the line number to negate the ++lineNumber in compileFile
			// becuase there is a import for all files, not just one.
			--c->lineNumber;
			if(compiling)
				compileFile(c, filepath, MAVEN_ONLY_COMPILE);
			else compileFile(c, filepath, MAVEN_ONLY_MAP);
		}
		closedir(dp);
		return true;
	}
	return false;
}
