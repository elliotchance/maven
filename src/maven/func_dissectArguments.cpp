/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_dissect.h"

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
