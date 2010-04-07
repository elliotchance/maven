/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_find.h"

string compilerFunctionCast(MavenCompiler* c, string signature, string args, string& type) {
	StringList parts = split(',', args);
	type = trim(parts[0]);
	
	// replace string
	string::size_type pos = 0;
    while((pos = type.find("::", pos)) != string::npos) {
        type.replace(pos, string("::").size(), ".");
        pos++;
    }
	if(type[type.length() - 1] == '.')
		type = type.substr(0, type.length() - 1);
	
	return string("((") + findObjectPath(c, type) + ")" + parts[1] + ")";
}
