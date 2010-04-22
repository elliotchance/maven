/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "keywords.h"
#include "compiler.h"

bool importAll(MavenCompiler* c, string import, bool compiling) {
	StringList parts = split('.', import);
	
	// bug #32: use readDirectory()
	struct dirent *ep;
	string location = combinePaths(c->binDirectory, c->iniFile.getKey("directories.import")) + parts[0];
	DIR* dp = opendir(location.c_str());
	if(dp != NULL) {
		while(ep = readdir(dp)) {
			if(ep->d_name[0] == '.')
				continue;
			
			string filepath = location + "/" + ep->d_name;
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
	} else {
		cout << "Error import location " << location << endl;
		exit(1);
	}
	
	return false;
}
