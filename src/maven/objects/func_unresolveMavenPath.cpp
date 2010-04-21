/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"

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
