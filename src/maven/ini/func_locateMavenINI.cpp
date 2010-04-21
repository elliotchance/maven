/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "files.h"

string locateMavenINI(MavenCompiler* c) {
	StringList locations;
	locations.push(c->currentDirectory);   // look in the current directory
	locations.push(getenv("HOME"));        // look in the home directory
#if MAVEN_OS == 1
	locations.push("/etc");      // only on *nix do we look in the absolute /etc folder
#endif
	locations.push("etc");
	locations.push("../etc");
	
	for(int i = 0; i < locations.length(); ++i) {
		if(fileExists(locations[i] + "/maven.ini"))
			return locations[i] + "/maven.ini";
	}
	
	return "";
}
