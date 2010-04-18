/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_strings.h"
#include "keywords.h"

string getImportName(MavenCompiler* c, string import) {
	string file = "";
	for(int i = 0; i < import.length(); ++i) {
		if(import[i] == '.') file += "/";
		else file += import[i];
	}
	return file + ".mav";
}

string locateImport(MavenCompiler* c, string import) {
	string file = getImportName(c, import);
	StringList locations;
	locations.push(combinePaths(c->binDirectory + "/", c->iniFile.getKey("directories.import")));
	locations.push(c->currentDirectory + "/");
	
	for(int i = 0; i < locations.length(); ++i) {
		if(fileExists(locations[i] + file))
			return locations[i] + file;
	}
	
	pushError(c, "Can't find import %s, looking in %s", import, locations.join(";"));
}
