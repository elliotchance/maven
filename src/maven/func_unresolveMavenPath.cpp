/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

string unresolveMavenPath(MavenCompiler* c, string path) {
	// remove "$static", "->a", spaces and brackets
	while(path.find("$static") != string::npos)
		path = path.erase(path.find("$static"), strlen("$static"));
	while(path.find("->a") != string::npos)
		path = path.erase(path.find("->a"), strlen("->a"));
	while(path.find(" ") != string::npos)
		path = path.erase(path.find(" "), strlen(" "));
	while(path.find("(") != string::npos)
		path = path.erase(path.find("("), strlen("("));
	while(path.find(")") != string::npos)
		path = path.erase(path.find(")"), strlen(")"));
	
	// finalise
	StringList parts = split("::", path);
	return parts.join(".");
}
