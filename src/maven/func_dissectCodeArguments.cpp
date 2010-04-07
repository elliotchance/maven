/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_dissect.h"

void dissectCodeArguments(MavenCompiler* c, string& rawargs, string& blocktype) {
	if(rawargs != "") {
		// we split the arguments and dissect them indervidualy
		StringList arg = splitCommas(rawargs);
		string signature = "";
		rawargs = "";
		for(int a = 0; a < arg.length(); ++a) {
			if(signature != "") {
				signature += ",";
				rawargs += ",";
			}
			StringList argtype;
			MavenMutability m;
			rawargs += dissectCode(c, arg[a], argtype, m);
			signature += argtype.join(",");
		}
		blocktype = signature;
	}
}
