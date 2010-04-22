/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "objects.h"
#include "output.h"

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
	
	return string("((") + cType(findObjectPath(c, type)) + ")" + parts[1] + ")";
}
