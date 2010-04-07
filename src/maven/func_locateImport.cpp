/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_strings.h"
#include "keywords.h"

string locateImport(MavenCompiler* c, string import) {
	string file = combinePaths(c->currentDirectory, c->iniFile.getKey("directories.import"));
	for(int i = 0; i < import.length(); ++i) {
		if(import[i] == '.') file += "/";
		else file += import[i];
	}
	file += ".mav";
	
	// make sure the file exists
	if(!fileExists(file)) {
		pushError(c, "Can't find import %s", import);
		return "";
	}
	
	return file;
}
