/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "variables.h"

MavenVariables dissectArguments(MavenCompiler* c, string line) {
	// chomp () off
	line = trim(line.substr(1, line.length() - 2));
	MavenVariables vars;
	if(line == "") return vars;
	
	// process
	StringList args = splitCommas(line);
	for(int i = 0; i < args.length(); ++i)
		vars.push(dissectVariable(c, args[i]));
	
	return vars;
}
